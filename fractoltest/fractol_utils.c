#include "minilibx-linux/mlx.h"

#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
/*
int mandelbrot(double real, double imag, int max_iter)
{
    double complex z = 0 + 0 * I;
    double complex c = real + imag * I;
    int i;

    for (i = 0; i < max_iter; i++)
    {
        z = z * z + c;
        if (creal(z) * creal(z) + cimag(z) * cimag(z) > 4)
            break;
    }
    return i;
}
*/

/* 
int main(void)
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 1000, 600, "Fract'ol");
    mlx_loop(mlx);
    return (0);
}
 */

/* int main(void)
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 800, 600, "Fract'ol");

    // Disegna un pixel rosso alla posizione (400, 300)
    int i = 100;
    while (--i)
        mlx_pixel_put(mlx, win, 100 + i*i, 300 - i*i, 0xFF0000);
    mlx_key_hook(win, key_hook, NULL);
    mlx_loop(mlx);
    return (0);
}
 */


int key_hook(int keycode, void *param)
{
    if (keycode == 65307) // 53 è il codice per il tasto ESC su macOS
    {
        // Chiudi la finestra e esci dal programma
        void *mlx = ((void **)param)[0];
        void *win = ((void **)param)[1];
        mlx_destroy_window(mlx, win);
        exit(0);
    }
    return (0);
}

int main(void)
{
    void *mlx;
    void *win;
    void *params[2];

    mlx = mlx_init();
    win = mlx_new_window(mlx, 800, 600, "Fract'ol");

    // Passa mlx e win come parametri
    params[0] = mlx;
    params[1] = win;

    // Disegna un pixel rosso alla posizione (400, 300)
    int i = 100;
    while (--i)
        mlx_pixel_put(mlx, win, 100 + i*i, 300 - i*i, 0xFF0000);

    // Collega la funzione key_hook all'evento della tastiera
    mlx_key_hook(win, key_hook, params);

    // Entra nel loop principale
    mlx_loop(mlx);
    return (0);
}


/* int main(void)
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 800, 600, "Fract'ol");

    mlx_key_hook(win, key_hook, NULL);
    mlx_loop(mlx);
    return (0);
}

 */