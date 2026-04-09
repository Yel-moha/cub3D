# Mappe di test per cub3D

Questa cartella raccoglie mappe `.cub` pensate per testare la validazione della mappa.

## Casi inclusi

- `valid_closed_small.cub`: mappa valida minima, chiusa e con un solo player.
- `invalid_open_border.cub`: c'e' un'apertura sul bordo.
- `invalid_two_spawns.cub`: ci sono due spawn.
- `invalid_no_spawn.cub`: non c'e' nessuno spawn.
- `invalid_hole_inside.cub`: c'e' un buco interno che rompe la chiusura.
- `invalid_disconnected_space.cub`: c'e' uno spazio interno che crea una perdita verso l'esterno.
- `valid_tight_corridor.cub`: mappa valida ma stretta, utile per controllare i bordi.

## Strategia consigliata per il parsing della mappa

1. Leggi prima tutta la sezione di configurazione e conta quando hai trovato `NO`, `SO`, `WE`, `EA`, `F`, `C`.
2. Da quando inizi a leggere la mappa, conserva ogni riga in una griglia.
3. Normalizza la griglia a rettangolo: tutte le righe devono avere la stessa larghezza, riempiendo con spazi.
4. Verifica che i caratteri siano solo `0`, `1`, `N`, `S`, `E`, `W` e spazio.
5. Conta gli spawn: deve essercene esattamente uno.
6. Fai un flood fill o BFS/DFS partendo dallo spawn su una griglia padded.
7. Se il flood fill esce fuori dalla griglia o tocca uno spazio esterno, la mappa non e' chiusa quindi e' invalida.
8. Se il flood fill raggiunge tutte le caselle camminabili e non trova perdite, la mappa e' valida.

## Trucco pratico

Il trucco piu' semplice e' trattare gli spazi come vuoto esterno e fare il flood fill su una mappa gia' paddata con spazi. In questo modo qualsiasi apertura, anche di un solo carattere, viene intercettata subito.
