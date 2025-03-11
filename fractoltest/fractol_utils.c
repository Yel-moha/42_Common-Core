#include "fractol.h"

void init_fractal(t_fractal *fractal)
{
    fractal->min_re = -2.0;
    fractal->max_re = 1.0;
    fractal->min_im = -1.2;
    fractal->max_im = 1.2;
    fractal->mlx = NULL;
    fractal->win = NULL;
    fractal->img = NULL; // Inizializza l'immagine buffer a NULL
}

int key_hook(int keycode, t_fractal *fractal)
{
    if (keycode == 65307) // 65307 è il codice per il tasto ESC su macOS
    {
        mlx_destroy_image(fractal->mlx, fractal->img);
        mlx_destroy_window(fractal->mlx, fractal->win);
        mlx_destroy_display(fractal->mlx);
        free(fractal->mlx);

        exit(0);
    }
    return (0);
}

int mouse_hook(int button, int x, int y, void *param)
{
   t_fractal *fractal ;

   fractal = (t_fractal *)param;
    if (button == 5) // 4 è il codice per la rotellina del mouse su
    {
        mlx_clear_window(fractal->mlx, fractal->win);
        // Chiama la funzione zoom per ingrandire
       zoom(param, x, y, 2.0); // 1.1 è il fattore di zoom per ingrandire
      // draw_fractal(fractal);
    }
    else if (button == 4) // 5 è il codice per la rotellina del mouse giù
    {
        mlx_clear_window(fractal->mlx, fractal->win);
        
        // Chiama la funzione zoom per ridurre
      zoom(param, x, y, 0.5); // 0.9 è il fattore di zoom per ridurre
      //draw_fractal(fractal);
    }
   /*  else
        zoom(param, x, y, 1.0); */
    return (0);
}




void zoom(void *param, int x, int y, double zoom_factor)
{
    t_fractal *fractal = (t_fractal *)param;
     // Mappa le coordinate del mouse al piano complesso
    double mouse_re = fractal->min_re + ((double)x / WIDTH )* (fractal->max_re - fractal->min_re);
    double mouse_im = fractal->min_im + ((double)y / HEIGHT )* (fractal->max_im - fractal->min_im);
     
    printf("Mouse coordinates: (%d, %d)\n", x, y);
    printf("Mapped to complex plane: (%f, %f)\n", mouse_re, mouse_im);

    /* double re_range = (fractal->max_re - fractal->min_re) * zoom_factor;
    double im_range = (fractal->max_im - fractal->min_im) * zoom_factor;
  */
    
    fractal->min_re = mouse_re - (mouse_re - fractal->min_re) * zoom_factor;
    fractal->max_re = mouse_re + (fractal->max_re - mouse_re) * zoom_factor;
    fractal->min_im = mouse_im - (mouse_im - fractal->min_im) * zoom_factor;
    fractal->max_im = mouse_im + (fractal->max_im - mouse_im) * zoom_factor;

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
    if (!fractal->img)
    {
        fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
        fractal->data = (int *)mlx_get_data_addr(fractal->img, &fractal->bpp, &fractal->size_line, &fractal->endian);
    }
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
            if (k == max_iter)
                fractal->data[y * WIDTH + x] = 0x000000;
                //mlx_pixel_put(fractal->mlx, fractal->win, x, y, 0x000000);
            else
            {
                // scala grigi
                //mlx_pixel_put(fractal->mlx, fractal->win, x, y, 3*k * 0x010101);
                //psyco color
                /* int red = (int)(255 * sin(0.1 * k));
                int green = (int)(255 * sin(0.1 * k + 2));
                int blue = (int)(255 * sin(0.1 * k + 4));
                int color = (red << 16) | (green << 8) | blue; */
                
                fractal->data[y * WIDTH + x] = k * 0x010101;
                //fractal->data[y * WIDTH + x] = color;
            }
            y++;
        }
        x++;

    }
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
    mlx_key_hook(fractal->win, key_hook, (void *)fractal);
    mlx_mouse_hook(fractal->win, mouse_hook, (void *)fractal);
    mlx_loop(fractal->mlx);
}
