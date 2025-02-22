#include "fractol.h"

int main(void)
{
    void *mlx;
    void *win;
    void *params[2];

    //while(i <= 480000)
    
        mlx = mlx_init();
        win = mlx_new_window(mlx, 800, 600, "Fract'ol");

        // Passa mlx e win come parametri
        params[0] = mlx;
        params[1] = win;

        // Disegna un pixel rosso alla posizione (400, 300)
        int i = 1;
        //int j = 1;
        while (++i < 600)
        {
                mlx_pixel_put(mlx, win, i, i, 0x00FF00);
                i++;

          //  mlx_loop(mlx);
                printf("i = %d\n", i);
          //  ft_printf("j = %d\n", j);
        }

        // Collega la funzione key_hook all'evento della tastiera
        mlx_key_hook(win, key_hook, params);

        // Entra nel loop principale
        mlx_loop(mlx);
        i++;
    return (0);
}
