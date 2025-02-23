#include "fractol.h"

int main(void)
{

    /////////////////////////Numeri Compllessi///////////////////////////
    double complex z = 3.0 + 4.0 * I;  // Numero complesso 3 + 4i
    printf("Parte reale: %f\n", creal(z));  // Estrae la parte reale
    printf("Parte immaginaria: %f\n", cimag(z));  // Estrae la parte immaginaria
    printf("Modulo: %f\n", cabs(z));  // Calcola il modulo |z|
    ///////////////////////////////////////////////////////////////////////////


    /////////////////Parte Corrisponednza pixel con coordinate/////////////////////
    int x = 300;
    int y = 380;
    int width = 800;
    int height = 600;
    double real = (x - width / 3) * 4.0 / width;
    double imag = (y - height / 2) * 4.0 / width;
    printf("Coordinate: (%d, %d)\n", x, y);
    printf("Coordinate complesse: (%f, %f)\n", real, imag);
    //////////////////////////////////////////////////////////////////////////////

    
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
        while (++i < 800)
        {
                mlx_pixel_put(mlx, win, i, 300, 0x00FF00);
                if (i <= 600)
                    mlx_pixel_put(mlx, win, (1600 / 3), i, 0x00FF00);
                i++;
        }
        //////////////////////////////////////////////////////////////////////////////
    int max_iter = 100;
    int j = mandelbrot(real, imag, max_iter);
    printf("Iterazioni: %d\n", j);
    if (j == max_iter)
    {
        mlx_pixel_put(mlx, win, x, y, 0x00FF00);
        printf("Il punto appartiene all'insieme di Mandelbrot\n");
    }
    else
        printf("Il punto non appartiene all'insieme di Mandelbrot\n");
    ////////////////////////////////////////////////////
        // Collega la funzione key_hook all'evento della tastiera
        mlx_key_hook(win, key_hook, params);

        // Entra nel loop principale
        mlx_loop(mlx);


        


    return (0);
}
