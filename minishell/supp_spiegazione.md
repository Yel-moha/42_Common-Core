# Spiegazione minishell.supp

Questo file contiene *soppressioni* per Valgrind. Servono a ignorare leak noti e non dipendenti dal tuo codice (es. librerie esterne o comandi di sistema).

## Cosa significano le regole
- Ogni blocco `{ ... }` è una soppressione.
- `Memcheck:Leak` indica che riguarda i leak rilevati da Memcheck.
- `fun:...` e `obj:...` sono le condizioni da matchare nello stack.
- `...` è un jolly: significa “qualsiasi riga intermedia”.

## Perché sono “a monte”
Le regole “ampie” (es. `obj:/usr/bin/*`) sopprimono tutti i leak che provengono da programmi esterni lanciati dalla minishell. Questo evita di dover aggiungere una soppressione per ogni comando (`cat`, `ls`, ecc.).

## Esempi tipici
- Regole con `fun:readline` o `fun:add_history` servono a ignorare leak prodotti internamente dalla libreria readline.
- Regole con `obj:/usr/bin/*` ignorano leak di programmi esterni, che non dipendono dal tuo progetto.

## Nota importante
Se in Valgrind compaiono leak **definitely lost** con stack che punta a funzioni del tuo codice (file in `src/`), quelli **non vanno soppressi**: vanno risolti nel codice.
