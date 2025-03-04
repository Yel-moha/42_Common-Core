#include "fractol.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/libft/libft.h"
#include <math.h>

void init_fractal(t_fractal *fractal, char *type)
{
    //if (fractal->type == "mandelbrot")
    if(ft_strncmp(type , "mandelbrot", 10) == 0 || ft_strncmp(type , "sierpinski", 10) == 0)
    {
        fractal->min_re = -2.0;
        fractal->max_re = 1.0;
        fractal->min_im = -1.2;
        fractal->max_im = 1.2;
    }
    else if (ft_strncmp(type , "julia", 5) == 0)
    {
        fractal->min_re = -1.5;
        fractal->max_re = 1.5;
        fractal->min_im = -1.5;
        fractal->max_im = 1.5;
    }
    else
        display_usage();
    fractal->julia_re = -0.7;
    fractal->julia_im = 0.27015;
    fractal->mlx = NULL;
    fractal->win = NULL;
    fractal->img = NULL;
}

void c_julia(t_fractal *fractal, char **type)
{
    char **julia_re;
    char **julia_im;

    julia_re = malloc(sizeof(char *) * 2);
    julia_im = malloc(sizeof(char *) * 2);
    julia_re = ft_split(type[2], '.');
    julia_im = ft_split(type[3], '.');

    if (!julia_re || !julia_im || !julia_re[0] || !julia_re[1] || !julia_im[0] || !julia_im[1])
    {
        display_usage();
        return;
    }

    if (type[2][0] == '-')
    {
        fractal->julia_re = -(ft_atoi(&type[2][1]) + ft_atoi(julia_re[1]) * pow(0.1, ft_strlen(julia_re[1])));
        //fractal->julia_re = -1 * fractal->julia_re;
    }
        else
        fractal->julia_re = ft_atoi(type[2]) + ft_atoi(julia_re[1]) * pow(0.1, ft_strlen(julia_re[1]));

    if (type[3][0] == '-')
    {
        fractal->julia_im = -(ft_atoi(&type[3][1]) + ft_atoi(julia_im[1]) * pow(0.1, ft_strlen(julia_im[1])));
        //fractal->julia_im = -1 * fractal->julia_im;
    }
    else
        fractal->julia_im = ft_atoi(type[3]) + ft_atoi(julia_im[1]) * pow(0.1, ft_strlen(julia_im[1]));

    free(julia_re[0]);
    free(julia_re[1]);
    free(julia_re);
    free(julia_im[0]);
    free(julia_im[1]);
    free(julia_im);
    
    printf("julia_re: %f\n", fractal->julia_re);
    printf("julia_im: %f\n", fractal->julia_im);
}void display_usage(void)
{
    //ft_printf("Usage: ./fractol [mandelbrot | julia | sierpinski]\n");
    ft_printf("Usage: ./fractol [mandelbrot | julia | sierpinski]\n");
   // {\displaystyle c=0,285+0,013i;0,45-0,1428i;-0,70176-0,3842i;-0,835-0,2321i.}
    exit(1);
}

void zoom(void *param, int x, int y, double zoom_factor)
{
    t_fractal *fractal = (t_fractal *)param;
    // Mappa le coordinate del mouse al piano complesso
    double mouse_re = fractal->min_re + ((double)x / WIDTH) * (fractal->max_re - fractal->min_re);
    double mouse_im = fractal->min_im + ((double)y / HEIGHT) * (fractal->max_im - fractal->min_im);

    //ft_printf("Mouse coordinates: (%d, %d)\n", x, y);
    //ft_printf("Mapped to complex plane: (%f, %f)\n", mouse_re, mouse_im);

    printf("Mouse coordinates: (%d, %d)\n", x, y);
    printf("Mapped to complex plane: (%f, %f)\n", mouse_re, mouse_im);

    fractal->min_re = mouse_re - (mouse_re - fractal->min_re) * zoom_factor;
    fractal->max_re = mouse_re + (fractal->max_re - mouse_re) * zoom_factor;
    fractal->min_im = mouse_im - (mouse_im - fractal->min_im) * zoom_factor;
    fractal->max_im = mouse_im + (fractal->max_im - mouse_im) * zoom_factor;

    //ft_printf("Zoom at (%d, %d) with factor %f\n", x, y, zoom_factor);
    printf("Zoom at (%d, %d) with factor %f\n", x, y, zoom_factor);

    //choose_fractal(fractal);
}


int key_hook(int keycode, t_fractal *fractal, int iterations)
{
    if (keycode == 65307)
    {
        mlx_destroy_image(fractal->mlx, fractal->img);
        mlx_destroy_window(fractal->mlx, fractal->win);
        mlx_destroy_display(fractal->mlx);
        free(fractal->mlx);

        exit(0);
    }
    if (keycode == 125 /*inserire numero per shift*/)
        get_color(iterations);
    return (0);
}

int choose_fractal(t_fractal *fractal, char *type)
{
    int fractal_flag;

    fractal_flag = 0;
    fractal->type = malloc(ft_strlen(type) + 1);
    fractal->type = type;
    if (ft_strncmp(fractal->type, "mandelbrot", 10) == 0)
        fractal_flag = 1;
    else if (ft_strncmp(fractal->type, "sierpinski", 10) == 0)
        fractal_flag = 3;
    else if (ft_strncmp(fractal->type, "julia", 5) == 0)
        fractal_flag = 2;
    else
        display_usage();
    return (fractal_flag);
}


int get_color(int iterations)
{
    int color;
    if (iterations == 0)
        return (0x000000);
  /*   else if (iterations == 1)
        return (0xFFFFFF);
        if (iterations == 2)
        return (0x0000FF);
    color = iterations * 0x010101;
    return(color); */
    color = (iterations * 7) % 0xFFFFFF;
    color = ((color << 8) | (color >> 16)) + iterations * 128;
    color = color * (iterations % 7 + 1);
    color = color % 0xFFFFFF;
    
    return (color | 0x101010);
}

int mouse_hook(int button, int x, int y, void *param, int flag)
{
    t_fractal *fractal;

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
        // draw_fractal(fractal);
    }
    /*  else
        zoom(param, x, y, 1.0); */
    flag = choose_fractal(fractal, fractal->type);
    draw_fractal(fractal, flag);
    return (0);
}


void draw_fractal(t_fractal *fractal, int flag)
{
    int x;
    int y;
    int k;
    double real;
    double imag;

    init_image(fractal, fractal->type);
    x = 0;
   
    while (x < WIDTH)
    {
        y = 0;
        while (y < HEIGHT)
        {
            real = fractal->min_re + (double)x / WIDTH * (fractal->max_re - fractal->min_re);
            imag = fractal->min_im + (double)y / HEIGHT * (fractal->max_im - fractal->min_im);
            if (flag == 1)
                k = mandelbrot(real, imag);
            else if (flag == 2)
                k = julia(real, imag, fractal->julia_re, fractal->julia_im);
            else if (flag == 3)
                ;
                //k = burningship(real, imag, MAX_ITER);
            if (k == MAX_ITER)
                fractal->data[y * WIDTH + x] = 0x000000;
            else
            {
                fractal->data[y * WIDTH + x] = get_color(k);
            }
            y++;
        }
        x++;
    }
    //zoom(fractal, 0, 0, 1.0);
    execute_fractal(fractal);
}



/* void draw_mandelbrot(t_fractal *fractal)
{
    int x;
    int y;
    int k;
    double real;
    double imag;

    init_image(fractal);
    x = 0;
    while (x < WIDTH)
    {
        y = 0;
        while (y < HEIGHT)
        {
            real = fractal->min_re + (double)x / WIDTH * (fractal->max_re - fractal->min_re);
            imag = fractal->min_im + (double)y / HEIGHT * (fractal->max_im - fractal->min_im);
            k = mandelbrot(real, imag);
            if (k == MAX_ITER)
                fractal->data[y * WIDTH + x] = 0x000000;
            else
            {
                fractal->data[y * WIDTH + x] = get_color(k);
            }
            y++;
        }
        x++;
    }
    //zoom(fractal, 0, 0, 1.0);
    execute_fractal(fractal);
}

void draw_julia(t_fractal *fractal)
{
    int x = 0;
    int y;
    int k;
    double real;
    double imag;

    init_image(fractal);
    while (x < WIDTH)
    {
        y = 0;
        while (y < HEIGHT)
        {
            real = fractal->min_re + (double)x / WIDTH * (fractal->max_re - fractal->min_re);
            imag = fractal->min_im + (double)y / HEIGHT * (fractal->max_im - fractal->min_im);
            k = julia(real, imag, fractal->julia_re, fractal->julia_im);
            if (k == MAX_ITER)
                fractal->data[y * WIDTH + x] = 0x000000;
            else
            {
                fractal->data[y * WIDTH + x] = k * 0x010101;
            }
            y++;
        }
        x++;
    }
    execute_fractal(fractal);
}

void draw_sierpinski(t_fractal *fractal)
{
    int x = 0;
    int y;
    int k;
    double real;
    double imag;

    init_image(fractal);
    while (x < WIDTH)
    {
        y = 0;
        while (y < HEIGHT)
        {
            real = fractal->min_re + (double)x / WIDTH * (fractal->max_re - fractal->min_re);
            imag = fractal->min_im + (double)y / HEIGHT * (fractal->max_im - fractal->min_im);
            k = mandelbrot(real, imag);
            if (k == MAX_ITER)
                fractal->data[y * WIDTH + x] = 0x000000;
            else
                fractal->data[y * WIDTH + x] = get_color(k);
            y++;
        }
        x++;
    }
    execute_fractal(fractal);
}
 */


void execute_fractal(t_fractal *fractal)
{
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
    mlx_key_hook(fractal->win, key_hook, (void *)fractal);
    mlx_mouse_hook(fractal->win, mouse_hook, (void *)fractal);
    mlx_loop(fractal->mlx);
}


void init_image(t_fractal *fractal, char *type)
{
    int fractal_flag;

    fractal_flag = choose_fractal(fractal, type);
    if (fractal_flag == 1 || fractal_flag == 2 || fractal_flag == 3)
    {
        if (!fractal->mlx)
        {
            fractal->mlx = mlx_init();
            fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, fractal->type);
        }
        if (!fractal->img)
        {
            fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
            fractal->data = (int *)mlx_get_data_addr(fractal->img, &fractal->bpp, &fractal->size_line, &fractal->endian);
        }
    }
    else
        display_usage();
}
