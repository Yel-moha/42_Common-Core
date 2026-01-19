# ft_printf

Una re-implementazione minimale di `printf(3)` conforme ai requisiti del progetto 42. Fornisce funzioni di formattazione basilari con comportamento definito per un sottoinsieme dei conversion specifiers standard.

## Specificatori supportati
- `%c`: carattere singolo
- `%s`: stringa C terminata da `\0`
- `%p`: puntatore (prefisso `0x` + esadecimale)
- `%d`, `%i`: interi con segno in base 10
- `%u`: interi senza segno in base 10
- `%x`, `%X`: interi senza segno in esadecimale (minuscolo/MAIUSCOLO)
- `%%`: stampa il carattere `%`

## API
```c
#include "ft_printf.h"

int ft_printf(const char *format, ...);
```
Ritorna il numero di caratteri stampati o un valore non negativo equivalente.

## Build
Dentro la cartella `ft_printf`:
```bash
make        # produce libftprintf.a (includendo la libft)
make clean  # pulisce i .o
make fclean # rimuove anche la libreria
make re     # ricompila da zero
```
Il `Makefile` compila anche `libft` e incorpora i suoi oggetti dentro `libftprintf.a`, per cui è sufficiente linkare questa singola libreria.

## Integrazione in un progetto
- Includi l'header: `#include "ft_printf.h"`
- Aggiungi la libreria al linking:

Esempio (GCC/Clang):
```bash
cc main.c -Ift_printf -Lft_printf -lftprintf -o app
```
Oppure linkando direttamente l'archivio:
```bash
cc main.c ft_printf/libftprintf.a -Ift_printf -o app
```

## Esempio d'uso
```c
#include <stdlib.h>
#include "ft_printf.h"

int main(void) {
    int n = 42;
    void *p = &n;
    ft_printf("ciao %s! n=%d, hex=%x, ptr=%p, perc=%%\n", "mondo", n, n, p);
    return 0;
}
```
Output atteso (formattazione indicativa):
```
ciao mondo! n=42, hex=2a, ptr=0xXXXXXXXX, perc=%
```

## Note
- Gestione base di errori e conteggio caratteri conforme agli obiettivi del progetto.
- Nessun supporto alle flag avanzate (`-+ #0`), larghezza, precisione o lunghezza (h, l, ...).
- Compatibile con Linux.
