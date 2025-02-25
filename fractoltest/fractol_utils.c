#include "fractol.h"

void init_fractal(t_fractal *fractal)
{
    fractal->min_re = -2.0;
    fractal->max_re = 1.0;
    fractal->min_im = -1.2;
    //fractal->min_im = -1.3075;
    fractal->max_im = 1.0;
    fractal->mlx = NULL;
    fractal->win = NULL;
}

int key_hook(int keycode, void *param)
{
    if (keycode == 65307) // 65307 è il codice per il tasto ESC su macOS
    {
        // Chiudi la finestra e esci dal programma
        void *mlx = ((void **)param)[0];
        void *win = ((void **)param)[1];
        mlx_destroy_window(mlx, win);
        exit(0);
    }
    return (0);
}

int mouse_hook(int button, int x, int y, void *param)
{
   // t_fractal *fractal = (t_fractal *)param;
    if (button == 1) // 1 è il codice per il click sinistro del mouse
    {
        // Gestisci l'evento di click sinistro del mouse
        // Ad esempio, puoi stampare le coordinate del click
        printf("Mouse click at (%d, %d)\n", x, y);
    }
    else if (button == 4) // 4 è il codice per la rotellina del mouse su
    {
        //mlx_clear_window(fractal->mlx, fractal->win);
        // Chiama la funzione zoom per ingrandire
       zoom(param, x, y, 1.1); // 1.1 è il fattore di zoom per ingrandire
      // draw_fractal(fractal);
    }
    else if (button == 5) // 5 è il codice per la rotellina del mouse giù
    {
        //mlx_clear_window(fractal->mlx, fractal->win);
        
        // Chiama la funzione zoom per ridurre
      zoom(param, x, y, 0.9); // 0.9 è il fattore di zoom per ridurre
      //draw_fractal(fractal);
    }
    return (0);
}




void zoom(void *param, int x, int y, double zoom_factor)
{
    t_fractal *fractal = (t_fractal *)param;
     // Mappa le coordinate del mouse al piano complesso
    double mouse_re = fractal->min_re + (double)x / WIDTH * (fractal->max_re - fractal->min_re);
    double mouse_im = fractal->max_im - (double)y / HEIGHT * (fractal->max_im - fractal->min_im);
     
    printf("Mouse coordinates: (%d, %d)\n", x, y);
    printf("Mapped to complex plane: (%f, %f)\n", mouse_re, mouse_im);

    double re_range = (fractal->max_re - fractal->min_re) * zoom_factor;
    double im_range = (fractal->max_im - fractal->min_im) * zoom_factor;

    fractal->min_re = mouse_re - re_range / 2;
    fractal->max_re = mouse_re + re_range / 2;
    fractal->min_im = mouse_im - im_range / 2;
    fractal->max_im = mouse_im + im_range / 2;

    printf("Zoom at (%d, %d) with factor %f\n", x, y, zoom_factor);

    draw_fractal(fractal);
}

void draw_fractal(t_fractal *fractal)
{
    
    if (!fractal->mlx)
    {
        fractal->mlx = mlx_init();
        fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, "Fract'ol");
    }
  /*   else
    {
        mlx_clear_window(fractal->mlx, fractal->win);
    } */

    int x = 0;
    int y;
    int max_iter = 100;
    int k;
    double real;
    double imag;

    while (x < WIDTH)
    {
        y = 0;
        while (y < HEIGHT)
        {
            real = fractal->min_re + (double)x / WIDTH * (fractal->max_re - fractal->min_re);
            imag = fractal->min_im + (double)y / HEIGHT * (fractal->max_im - fractal->min_im);
            k = mandelbrot(real, imag, max_iter);
            //mlx_pixel_put(fractal->mlx, fractal->win, x, y, k * 0x010101);
            if (k == max_iter)
                mlx_pixel_put(fractal->mlx, fractal->win, x, y, 0x000000);
            else
                mlx_pixel_put(fractal->mlx, fractal->win, x, y, k * 0x010101);
               // mlx_pixel_put(fractal->mlx, fractal->win, x, y, 0xFFFFFF);
            //0xFFFFFF
            y++;
        }
        x++;
    }
    mlx_key_hook(fractal->win, key_hook, (void *)fractal);
    mlx_mouse_hook(fractal->win, mouse_hook, (void *)fractal);
    mlx_loop(fractal->mlx);

}
