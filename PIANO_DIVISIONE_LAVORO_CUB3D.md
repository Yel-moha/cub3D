# Piano divisione lavoro (2 persone) - cub3D

## Obiettivo
Dividere il progetto in due stream paralleli per ridurre blocchi e integrare in modo progressivo.

## Persona A - Parsing e validazione
Responsabilita principali:
- Lettura e parsing del file `.cub`
- Parsing texture `NO`, `SO`, `WE`, `EA`
- Parsing colori `F` e `C`
- Parsing e normalizzazione della mappa
- Validazioni:
  - caratteri ammessi
  - mappa chiusa
  - un solo player
  - bordi validi
- Costruzione delle struct dati finali per il motore
- Gestione errori con messaggi chiari

Deliverable:
- Parser completo che restituisce dati validi o errore
- Set di mappe di test minime (`valid` / `invalid`)

## Persona B - Motore grafico e gameplay
Responsabilita principali:
- Inizializzazione MLX, finestra, immagini e main loop
- Raycasting (DDA) e proiezione dei muri
- Rendering pareti + floor/ceiling
- Applicazione texture
- Input tastiera, rotazione, movimento
- Collisioni su mappa
- Hook eventi e uscita pulita

Deliverable:
- Engine funzionante con movimento e rendering stabile
- Frame loop pulito e senza leak evidenti

## Contratto tra A e B (fondamentale)
Definire subito una interfaccia comune:
- Struct condivise: config, mappa, player, texture, colori
- Persona A garantisce: dati sempre validi oppure errore esplicito
- Persona B assume: dati validi e non rifà tutte le validazioni

## Timeline consigliata
### Giorno 1
- Allineamento su struct, header, naming e convenzioni

### Giorni 2-3
- Persona A: parser base completo
- Persona B: scheletro MLX + rendering verticale semplice

### Giorni 4-5
- Integrazione parser -> engine

### Giorni 6-7
- Texture complete, collisioni, edge cases, memory checks

### Ultimi giorni
- Pulizia codice, refactor leggero, test finali

## Regole team anti-blocco
- Branch separati: `parsing` e `engine`
- Merge piccoli e frequenti
- Ogni merge deve compilare
- Nessun merge con leak noti
- Review veloce reciproca prima del merge su branch principale

## Checklist integrazione
- [ ] Struct condivise definite
- [ ] Parser produce output conforme
- [ ] Engine legge output parser senza patch manuali
- [ ] Movimento + collisioni funzionanti
- [ ] Texture su tutte le direzioni (`NO/SO/WE/EA`)
- [ ] Nessun crash su mappe invalide
- [ ] Test finale su piu mappe
