# Engine - Documentazione tecnica

Questa documentazione descrive in dettaglio l'engine del progetto cub3D: il ciclo di rendering, il raycasting (con tecnica DDA), la matematica sottostante, il mapping delle texture, la gestione del movimento e le funzioni di MinilibX usate. Il testo è orientato a fornire chiarezza sulle formule e sui passaggi implementativi.

## Indice
- Panoramica
- Architettura e loop principale
- Matematica di base e proiezione della camera
- Raycasting passo-passo
- Algoritmo DDA (Digital Differential Analyzer)
- Calcolo della distanza perpendicolare e correzione fisheye
- Texture mapping e coordinate di texture
- Gestione del buffer e MiniLibX
- Movimento del giocatore e collisioni
- Sprites (concetti e z-buffer)
- Funzioni MiniLibX utilizzate
- Riferimenti ai file del progetto

## Panoramica
L'engine implementa una versione classica del raycasting per creare una vista 3D da una mappa 2D a griglia. Per ogni colonna di pixel dello schermo viene tracciato un raggio che interseca il mondo della mappa, si calcola la distanza fino alla parete, si determina la porzione di texture da disegnare e si scrivono i pixel nel buffer immagine, poi si manda il buffer in finestra.

## Architettura e loop principale
- Inizializzazione: crea la finestra e l'immagine / buffer, carica le texture, imposta lo stato del giocatore (posizione `posX,posY`, direzione `dirX,dirY`, piano camera `planeX,planeY`).
- Main loop: per ogni frame
  - processa input (tasti, movimenti)
  - esegue il raycasting per ogni colonna orizzontale dello schermo
  - disegna le colonne nel buffer immagine
  - renderizza l'immagine con MinilibX

## Matematica di base e proiezione della camera
Rappresentazione del giocatore/camera:
- Posizione: $(posX, posY)$ nella griglia di map.
- Direzione (vettore unitario): $(dirX, dirY)$ — verso dove punta il giocatore.
- Piano camera (camera plane): $(planeX, planeY)$ — vettore ortogonale a `dir` che determina il FOV.

Per calcolare la direzione del raggio per una colonna dello schermo si usa il parametro `cameraX`:
$$cameraX = 2\cdot x / screenWidth - 1$$
dove $x$ è l'indice della colonna (0..screenWidth-1). La direzione del raggio è:
$$rayDirX = dirX + planeX \cdot cameraX$$
$$rayDirY = dirY + planeY \cdot cameraX$$

Questo significa che per `cameraX = -1` otteniamo il raggio più a sinistra del fov, per `cameraX = 1` il raggio più a destra.

## Raycasting passo-passo
Per ogni colonna `x`:
1. Calcolare `cameraX` e `rayDir` come sopra.
2. Determinare la cella della mappa in cui si trova il player: `mapX = floor(posX)`, `mapY = floor(posY)`.
3. Calcolare `deltaDistX` e `deltaDistY`, cioè la distanza che il raggio percorre per passare da una linea di griglia verticale all'altra (o orizzontale) in termini di distanza del raggio:
   $$deltaDistX = \left|\frac{1}{rayDirX}\right|, \quad deltaDistY = \left|\frac{1}{rayDirY}\right|$$
4. Calcolare `stepX`/`stepY` e `sideDistX`/`sideDistY` (inizializzazione per DDA):
   - Se $rayDirX < 0$ allora `stepX = -1` e
     $$sideDistX = (posX - mapX) \cdot deltaDistX$$
     altrimenti `stepX = 1` e
     $$sideDistX = (mapX+1.0 - posX) \cdot deltaDistX$$
   - Similmente per Y:
     Se $rayDirY < 0$ allora `stepY = -1` e
     $$sideDistY = (posY - mapY) \cdot deltaDistY$$
     altrimenti `stepY = 1` e
     $$sideDistY = (mapY+1.0 - posY) \cdot deltaDistY$$
5. Eseguire il ciclo DDA: avanzare nella griglia scegliendo il minore tra `sideDistX` e `sideDistY`. Se `sideDistX < sideDistY`:
   - `sideDistX += deltaDistX`
   - `mapX += stepX`
   - `side = 0` (colpita parete verticale)
   altrimenti:
   - `sideDistY += deltaDistY`
   - `mapY += stepY`
   - `side = 1` (colpita parete orizzontale)
   Continuare finché nella cella `map[mapX][mapY]` non è presente un muro.

## Algoritmo DDA (dettagli)
L'idea è muoversi cella per cella nella griglia determinando quale bordo di cella viene raggiunto per primo dal raggio. `deltaDistX`/`deltaDistY` sono pre-calcolati per evitare divisioni durante il ciclo.

Complessità: tipicamente $O(screenWidth \cdot stepsPerRay)$, ma `stepsPerRay` è limitato dalla dimensione della mappa e dalla densità delle pareti.

## Calcolo della distanza perpendicolare e correzione fisheye
Alla fine del DDA, si calcola la distanza dal player alla parete. Per evitare l'effetto 'fisheye' (distanze misurate lungo il raggio e non perpendicolarmente alla camera) si calcola la distanza perpendicolare alla camera:
Se `side == 0` (parete verticale):
$$perpWallDist = (mapX - posX + (1 - stepX)/2) / rayDirX$$
altrimenti:
$$perpWallDist = (mapY - posY + (1 - stepY)/2) / rayDirY$$

Questa `perpWallDist` è quella usata per calcolare l'altezza della linea da disegnare:
$$lineHeight = \left\lfloor \frac{screenHeight}{perpWallDist} \right\rfloor$$
Con questo si determina `drawStart` e `drawEnd` (i pixel verticali della colonna occupati dalla parete).

## Texture mapping e coordinate di texture
Per disegnare la texture corretta sulla parete occorre calcolare la coordinata orizzontale della texture `texX`:
- Calcolare la posizione esatta dell'intersezione con la parete (`wallX`) — la coordinata lungo la parete (fra 0 e 1):
  - Se `side == 0`:
    $$wallX = posY + perpWallDist \cdot rayDirY$$
  - Altrimenti:
    $$wallX = posX + perpWallDist \cdot rayDirX$$
  - Poi: $$wallX = wallX - \lfloor wallX \rfloor$$
- `texX = \lfloor wallX \cdot textureWidth \rfloor` (con eventuale correzione se side e direzione richiedono flip della texture)

Per ogni pixel verticale della colonna calcoliamo `texY` attraverso un passo `step`:
$$step = \frac{1.0 \cdot textureHeight}{lineHeight}$$
$$texPos = (drawStart - screenHeight/2 + lineHeight/2) \cdot step$$
e poi per ogni y:
$$texY = \lfloor texPos \rfloor; \quad texPos += step$$

Usare `texX` e `texY` per leggere il colore dalla texture e scriverlo nel buffer immagine.

## Gestione del buffer e MiniLibX
È buona pratica disegnare in un buffer in memoria (es. immagine con `mlx_new_image`) e poi trasferire il buffer su schermo con `mlx_put_image_to_window` per evitare flicker.

Funzioni chiave MinilibX (usate e da citare):
- `mlx_init()` — inizializza il contesto grafico.
- `mlx_new_window(mlx, width, height, title)` — crea la finestra.
- `mlx_new_image(mlx, width, height)` — crea un'immagine/buffer su cui scrivere.
- `mlx_get_data_addr(img, bits_per_pixel, size_line, endian)` — ottiene puntatore al buffer pixel, stride e info.
- `mlx_put_image_to_window(mlx, win, img, 0, 0)` — copia l'immagine su finestra.
- `mlx_hook(win, event, mask, func, param)` — registra callback (es. chiusura, pressione tasti).
- `mlx_key_hook(win, func, param)` — callback per tasti (usata in molte implementazioni semplici).
- `mlx_loop(mlx)` — entra nel loop principale di MinilibX.
- Altre utili: `mlx_destroy_image`, `mlx_destroy_window`, `mlx_clear_window`, `mlx_pixel_put` (meno efficiente per pixel singolo).

Nel codice, si ottiene il puntatore ai pixel con `mlx_get_data_addr` e si scrive nel buffer con il calcolo dell'offset: `offset = y * size_line + x * (bits_per_pixel/8)`. Prestare attenzione all'`endian` se si copia direttamente il colore.

## Movimento del giocatore e collisioni
Movimento avanti/indietro:
$$newX = posX + dirX \cdot moveSpeed$$
$$newY = posY + dirY \cdot moveSpeed$$
Prima di assegnare `posX,posY` verificare che `map[floor(newX)][floor(posY)]` e `map[floor(posX)][floor(newY)]` non contengano muri (semplice AABB su griglia), per evitare di 'passare' attraverso i muri.

Rotazione della vista (sinistra/destra):
Ruotare i vettori `dir` e `plane` con angolo `rotSpeed`:
$$oldDirX = dirX$$
$$dirX = dirX \cdot \cos(rot) - dirY \cdot \sin(rot)$$
$$dirY = oldDirX \cdot \sin(rot) + dirY \cdot \cos(rot)$$
E lo stesso per il `plane`:
$$oldPlaneX = planeX$$
$$planeX = planeX \cdot \cos(rot) - planeY \cdot \sin(rot)$$
$$planeY = oldPlaneX \cdot \sin(rot) + planeY \cdot \cos(rot)$$

## Sprites (concetti e z-buffer)
Per gestire oggetti 2D nel mondo (sprites) occorre:
1. Calcolare la posizione relativa al player e trasformarla nello spazio camera (moltiplicazione per la matrice inversa composta da `dir` e `plane`).
2. Calcolare la dimensione a schermo usando la distanza perpendicolare.
3. Ordinare gli sprite per distanza decrescente per disegnarli correttamente (painter's algorithm), oppure usare uno z-buffer che memorizza la `perpWallDist` per ogni colonna e non sovrascrivere pixel più vicini.

Trasformazione (schema):
Se `spriteX = spritePosX - posX`, `spriteY = spritePosY - posY`, usare la matrice:
$$invDet = 1.0 / (planeX \cdot dirY - dirX \cdot planeY)$$
$$transformX = invDet \cdot (dirY \cdot spriteX - dirX \cdot spriteY)$$
$$transformY = invDet \cdot (-planeY \cdot spriteX + planeX \cdot spriteY)$$
`transformY` è la distanza alla camera usata per la scala a schermo.

## Funzioni MiniLibX utilizzate (riepilogo e note pratiche)
- `mlx_init` — memorizzare il return in `mlx`.
- `mlx_new_window` — creare `win`.
- `mlx_new_image` / `mlx_get_data_addr` — creare buffer e ottenere pointer per scrittura rapida.
- `mlx_put_image_to_window` — swap buffer alla fine del frame.
- `mlx_hook`/`mlx_key_hook` — processare input e chiusura.
- `mlx_loop` — avviare il loop. Se usate `mlx_loop_hook` potete chiamare la funzione di rendering ad ogni iterazione.

Nota: Preferire scrittura diretta nel buffer (`get_data_addr`) anziché `mlx_pixel_put` per performance.

## Riferimenti ai file del progetto
- Implementazione engine principale: [src/engine/engine.c](src/engine/engine.c)
- Inizializzazione grafica e immagini: [src/engine/init_graphics.c](src/engine/init_graphics.c)
- Movimento giocatore: [src/engine/player_movment.c](src/engine/player_movment.c)
- Accesso texture: [src/engine/textures_access.c](src/engine/textures_access.c)

Consultare quei file per mappare le formule e i passaggi matematici alle funzioni reali.

## Suggerimenti per debug e verifiche
- Disegnare linee debug per `rayDir` e `map` in una rappresentazione top-down può aiutare a visualizzare DDA.
- Stampare `deltaDist`, `sideDist`, `step` per un singolo raggio aiuta a capire dove il raggio avanza.
- Verificare `bits_per_pixel`, `size_line`, `endian` e l'offset nel buffer prima di copiare valori di colore.

---
Se vuoi, posso estendere questa documentazione con esempi di codice presi direttamente da `src/engine/*`, aggiungere diagrammi (mermaid) o un file di riferimento rapido delle formule. Vuoi che importi porzioni di codice per commentarle passo-passo?
