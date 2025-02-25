

/**/
#include "fractol.h"

int main(void)
{

    /* void *mlx;
    void *win;
    t_fractal fractal;

    mlx = mlx_init();
    win = mlx_new_window(mlx, WIDTH, HEIGHT, "Fract'ol");

    fractal.mlx = mlx;
    fractal.win = win;
    fractal.min_re = -2.0;
    fractal.max_re = 1.0;
    fractal.min_im = -1.3075;
    fractal.max_im = 1.3075; */
    


    /////////////////////////Numeri Compllessi///////////////////////////
    double complex z = 3.0 + 4.0 * I;  // Numero complesso 3 + 4i
    printf("Parte reale: %f\n", creal(z));  // Estrae la parte reale
    printf("Parte immaginaria: %f\n", cimag(z));  // Estrae la parte immaginaria
    printf("Modulo: %f\n", cabs(z));  // Calcola il modulo |z|
    ///////////////////////////////////////////////////////////////////////////


   

    
    void *params[2];

    //while(i <= 480000)
    
       /*  fractal.mlx = mlx_init();
        fractal.win = mlx_new_window(mlx, WIDTH, HEIGHT, "Fract'ol"); */

        // Passa mlx e win come parametri
        /* params[0] = fractal.mlx;
        params[1] = fractal.win;
 */
        /* int i = 1;
        while (++i < 800)
        {
                mlx_pixel_put(mlx, win, i, 300, 0x00FF00);
                if (i <= 600)
                    mlx_pixel_put(mlx, win, (1600 / 3), i, 0x00FF00);
                i++;
        } */
        //////////////////////////////////////////////////////////////////////////////

         /////////////////Parte Corrisponednza pixel con coordinate/////////////////////
    int x = 0;
    int y = 0;
    int max_iter = 100;
    int k;
    double real;
    double imag;
    while (x <= 800)
    {
        real = 0;
        imag = 0;
        while(y <= 600)
        {
            real = (x - 2*WIDTH / 3) * 3.0 / WIDTH;
            imag = (y - HEIGHT / 2) * 3.0 / WIDTH;
            k = mandelbrot(real, imag, max_iter);
            if (k == max_iter)
                mlx_pixel_put (mlx, win, x, y, 0x000000);
            else
                mlx_pixel_put (mlx, win, x, y, 0x0000FF);
                /*xc.red = (color>>8)&0xFF00;
                xc.green = color&0xFF00;
                xc.blue = (color<<8)&0xFF00;*/
            y++;
            //mlx_loop(mlx);
        }
        x++;
        y = 0;
    }
    /* printf("Coordinate: (%d, %d)\n", x, y);
    printf("Coordinate complesse: (%f, %f)\n", real, imag); */
    //////////////////////////////////////////////////////////////////////////////
        // Collega la funzione key_hook all'evento della tastiera
        mlx_key_hook(win, key_hook, params);
        mlx_mouse_hook(win, mouse_hook, params);

        // Entra nel loop principale
        mlx_loop(mlx);
    /*
    Rosso: 0xFF0000

    Verde: 0x00FF00

    Blu: 0x0000FF

    Bianco: 0xFFFFFF

    Nero: 0x000000

    Giallo: 0xFFFF00

    Ciano: 0x00FFFF

    Magenta: 0xFF00FF
    */

        


    return (0);
}

