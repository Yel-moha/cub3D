Mappe di test critiche (cartella map/tests)

- edge_border_zero.cub
  - '0' sulla prima riga di bordo; verifica la validazione permissiva.
- edge_nonrect.cub
  - righe non rettangolari: una riga più corta per testare padding/normalizzazione.
- edge_long_corridor.cub
  - mappa più grande a corridoio; include caratteri '.' per testare gestione caratteri non validi e dimensione.
- edge_concatenated_rooms.cub
  - stanze concatenate orizzontalmente con corridoi e una riga separatrice tutta zero.
- edge_player_border.cub
  - spawn del giocatore vicino al bordo per testare collisioni e movimento.

Esempi di esecuzione:

```bash
./cub3d map/tests/edge_border_zero.cub
./cub3d map/tests/edge_nonrect.cub
./cub3d map/tests/edge_player_border.cub
```

Note:
- Alcune mappe contengono caratteri non standard (es. '.') di proposito per testare i controlli di carattere.
- Se preferisci, posso generare mappe più grandi (100x100) automaticamente o convertire i '.' in spazi ' ' per testare padding invece di caratteri invalidi.
