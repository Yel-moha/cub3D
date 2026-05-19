# Guida alla correzione — Q&A

Guida concisa per le domande/risposte alla difesa. Divisa in due parti: **Parsing** e **Engine**. Alla fine è riportato lo stato dei bonus (implementati / non implementati) e i comandi rapidi per i controlli.

**Parsing**
- **Qual è il formato atteso del file `.cub`?**: Segui il subject; le chiavi sono `R`, `NO`, `SO`, `WE`, `EA`, `S`, `F`, `C` e poi la mappa in fondo. Vedi il soggetto ufficiale per i dettagli.
- **Dove è il codice di parsing?**: Funzioni principali in [src/parsing](src/parsing) — `parse_line`, `parse_textures`, `parse_colors`, `fill_grid`.
- **Come vengono gestiti i path delle texture e gli errori?**: Le verifiche sono in `textures_exist` e `textures_error_path`. In caso di errore il programma esce con `Error\n` e un messaggio esplicito.
- **La mappa deve essere chiusa?**: Sì — la validazione è implementata in `validate_borders` / `validate_line` / `middle_row_is_closed` (vedi [src/parsing/grid_validation.c](src/parsing/grid_validation.c)).
- **Come si controllano i caratteri della mappa e lo spawn?**: Il parsing conta i simboli e imposta `scene->pos`; se ci sono spawn multipli o nessuno viene sollevato `error_spawn_player` (vedi [src/parsing/map_grid.c](src/parsing/map_grid.c)).
- **Gestione spazi e linee vuote**: `is_blank_line`, `is_map_line` e `fill_grid_pass` permettono di accettare spazi nelle righe di mappa come previsto dal subject.

**Engine**
- **Dove inizializzate la grafica e il loop di rendering?**: `init_graphics`, `engine_init`, `render_frame` in [src/engine](src/engine).
- **Come sono gestiti input e chiusura?**: `key_press`, `key_release`, `close_window`, `handle_keys` sono le entry per la gestione eventi; ESC e il clic sulla croce devono chiudere l'applicazione pulitamente.
- **Movimenti e collisioni:** Implementati in [src/engine/player_movment.c](src/engine/player_movment.c). La funzione `move_player` e `strafe_player` controllano le collisioni usando `is_wall` — quindi la feature "Wall collisions" è presente.
- **Rotazione e controllo camera:** `rotate_player` ruota `dir` e `plane` correttamente usando seno/coseno.
- **Texture walls e rendering colonne:** `load_texture`, `load_textures`, `init_ray`, `perform_dda`, `compute_distance`, `draw_column` gestiscono il raycasting e il disegno delle colonne (vedi [src/engine/raycasting.c](src/engine/raycasting.c) e `render_colums.c`).
- **Minimap:** Implementata — `init_dimensions`, `draw_grill`, `draw_rays_on_minimap` permettono di calcolare e disegnare la minimappa e i raggi (vedi [src/engine/minimap.c](src/engine/minimap.c)).
- **Sprite:** Lo subject prevede la texture `S` per sprite, ma non si trovano implementazioni complete per gestione/ordinamento/disegno degli sprite: consideralo non implementato.

**Bonus — stato**
- **Implementati:**
  - **Wall collisions**: controllo in `player_movment.c`.
  - **Minimap**: `src/engine/minimap.c`, `init_dimensions`.
- **Non implementati / parziali:**
  - **Doors (porte)**: nessuna gestione trovata nel codice (`door` non presente).
  - **Animated sprites**: manca pipeline di rendering sprite/animazione.
  - **Rotate POV with mouse**: la miniLibX include API mouse ma nel progetto non è presente il `mlx_mouse_hook` per ruotare la camera.

**Domande pratiche da fare al candidato durante la correzione**
- Mostrami dove parsate i colori (`F`/`C`) e come verifichi i range [0,255].
- Come gestiresti un file `.cub` con chiavi duplicate o path non validi? (risposta attesa: exit con `Error\n` e messaggio; funzioni `double_color_path` e check dei path).
- Come verifichi che la mappa sia chiusa su border non rettangolari? (risposta attesa: spiegazione di `validate_borders` / controllo righe e colonne).
- Mostrami il flusso di rendering per una singola colonna (ray init → DDA → distanza perpendicolare → draw column).
- Come gestite leak di memoria e pulizie su exit? (risposta attesa: `free_scene`, `destroy_textures`, `cleanup_and_exit`).

**Checklist rapida per il correttore**
- Compilazione: `make` deve creare l'eseguibile `cub3D` senza rilink non necessari.
- Eseguire i test di display: aprire il programma senza `--save` (window), e con `--save` verificare il BMP di output.
- Test input: premere ESC / clic sulla croce; movimento con WASD e rotazione sx/dx; tutte le azioni devono produrre output visibile e mantenere la finestra stabile.
- Test textures: cambiare un percorso texture nel file `.cub` e ricompilare; se il percorso è inesistente il programma deve fallire con `Error\n`.
- Controllo memoria: eseguire `valgrind --leak-check=full ./cub3D <scene>.cub` e verificare l'assenza di leak significativi.

Se vuoi, posso:
- Aggiungere note riga-per-riga con esempi di domande specifiche per ogni funzione.
- Preparare un test script che esegue automaticamente la checklist minima.

File creato: [GUIDA_CORREZIONE.md](GUIDA_CORREZIONE.md)
