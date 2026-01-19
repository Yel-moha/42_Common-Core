# Fractol

Anteprima Mandelbrot

![Anteprima Mandelbrot](Mandelbrot_fractal.gif)

## Descrizione
Fractol è un progetto grafico (MiniLibX) che visualizza e permette di esplorare insiemi frattali in tempo reale.
Sono attualmente supportati:
- mandelbrot
- julia (con parametri reali/immaginari opzionali)

## Requisiti
- Linux con X11
- `make`, `clang`
- Librerie di sviluppo X11: `libx11-dev`, `libxext-dev`

Installazione rapida (Debian/Ubuntu):

```bash
sudo apt-get update
sudo apt-get install -y build-essential clang libx11-dev libxext-dev
```

## Build
Il progetto include le dipendenze necessarie (`libft`, `ft_printf`, `minilibx-linux`). Per compilare:

```bash
make
```

Pulizia:

```bash
make clean     # rimuove .o
make fclean    # rimuove binari e librerie
make re        # ricompila da zero
```

## Utilizzo
Esegui il binario con il tipo di frattale e, opzionalmente per Julia, i parametri:

```bash
./fractol mandelbrot
./fractol julia 0.285 0.013
```

Parametri supportati:
- `mandelbrot` (nessun parametro)
- `julia <re> <im>` (parametri opzionali; alcuni valori interessanti: `0.285 0.013`, `0.45 -0.1428`, `-0.70176 -0.3842`, `-0.835 -0.2321`)

## Controlli
- ESC: chiudi
- Rotellina mouse: zoom in/out centrato sul cursore
- SHIFT: cambia palette/colore

## Note tecniche
- Risoluzione finestra: 800x600 (configurata in `fractol.h`)
- Iterazioni massime: 100 (`MAX_ITER`)
- Linker flags MLX: `-lmlx -lX11 -lXext -lm`

## Troubleshooting
- Se lanciare `./fractol` mostra errori legati a X11, assicurati di avere `libx11-dev` e `libxext-dev` installati.
- Se la finestra non appare o va in segfault, prova `make re` per ricompilare tutte le dipendenze (`minilibx-linux`, `libft`, `ft_printf`).
- Su ambienti WSL, abilita un server X (ad es. Xming/X410) e imposta `DISPLAY`.

## Licenza
Uso didattico nell'ambito del progetto 42.
