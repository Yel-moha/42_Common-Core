#include "fractol.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/libft/libft.h"
#include <math.h>

void init_fractal(t_fractal *fractal, char *type)
{
    if (ft_strncmp(type, "mandelbrot", 10) == 0)
    {
        fractal->min_re = -2.0;
        fractal->max_re = 1.0;
        fractal->min_im = -1.2;
        fractal->max_im = 1.2;
    }
    else if (ft_strncmp(type, "julia", 5) == 0)
    {
        fractal->min_re = -1.5;
        fractal->max_re = 1.5;
        fractal->min_im = -1.5;
        fractal->max_im = 1.5;
    }
 /*    else if (ft_strncmp(type, "cantor", 6) == 0)
    {
        fractal->min_re = 0.0;
        fractal->max_re = 1.0;
        fractal->min_im = 0.0;
        fractal->max_im = 0.0;
    } */
    else
    {
        display_usage();
        return;
    }

    fractal->type = type;
    fractal->julia_re = -0.7;
    fractal->julia_im = 0.27015;
    fractal->color_mode = 0;
    fractal->mlx = NULL;
    fractal->win = NULL;
    fractal->img = NULL;
    fractal->bpp = 0;
    fractal->size_line = 0;
    fractal->endian = 0;
   //free(type);////////////////////
}

void free_split(char **arr)
{
    int i;
    
    i = 0;
    if (!arr)
        return;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

double parse_julia_value(char *str)
{
    char **split;
    double result;

    split = ft_split(str, '.');
    if (!split || !split[0] || !split[1])
    {
        free_split(split);
        display_usage();
        return (0);
    }

    result = ft_atoi(split[0]) + ft_atoi(split[1]) * \
            pow(0.1, ft_strlen(split[1]));
    if (str[0] == '-')
        result = -result;

    free_split(split);
    return (result);
}

void c_julia(t_fractal *fractal, char **type)
{
    if (!type[2] || !type[3])
        return (display_usage());

    fractal->julia_re = parse_julia_value(type[2]);
    fractal->julia_im = parse_julia_value(type[3]);
}

void display_usage(void)
{
    ft_printf("Usage: ./fractol [mandelbrot | julia | sierpinski]\n");
    ft_printf("if the fractal is julia, you can add two more arguments\n");
    ft_printf("the first is the real part and the second is the imaginary part\n");
    ft_printf("example: ./fractol julia 0.285 0.013\n");
    ft_printf("intresting values for c can be:\
    c=0,285+0,013i;0,45-0,1428i;-0,70176-0,3842i;-0,835-0,2321i.\n");
    exit(1);
}

void zoom(void *param, int x, int y, double zoom_factor)
{
    t_fractal *fractal = (t_fractal *)param;
    double mouse_re = fractal->min_re + ((double)x / WIDTH) * (fractal->max_re - fractal->min_re);
    double mouse_im = fractal->min_im + ((double)y / HEIGHT) * (fractal->max_im - fractal->min_im);

    ft_printf("Mouse coordinates: (%d, %d)\n", x, y);
    ft_printf("Mapped to complex plane: (%f, %f)\n", mouse_re, mouse_im);

    fractal->min_re = mouse_re - (mouse_re - fractal->min_re) * zoom_factor;
    fractal->max_re = mouse_re + (fractal->max_re - mouse_re) * zoom_factor;
    fractal->min_im = mouse_im - (mouse_im - fractal->min_im) * zoom_factor;
    fractal->max_im = mouse_im + (fractal->max_im - mouse_im) * zoom_factor;

    ft_printf("Zoom at (%d, %d) with factor %f\n", x, y, zoom_factor);
}

/* int key_hook(int keycode, t_fractal *fractal, int iterations)
{
    int color;
    int flag;
    //int color;

    if (keycode == 65307)
    {
        free_fractal(fractal);
        exit(0);
    }
    if (keycode == 65505)
    {
        ft_printf(" keycode = %d\n", keycode);
        flag = choose_fractal(fractal, fractal->type);
        fractal->color_mode++;
        if(fractal->color_mode == 7)
            fractal->color_mode = 0;
        //ft_printf("color: %d\n", fractal->color_mode);
        color = iterations;
        color = get_color(iterations, fractal->color_mode) % 128;
        //fractal->color_mode = get_color(iterations, fractal->color_mode);
        ft_printf("fractal_color_mode: %d\n", fractal->color_mode);
        mlx_clear_window(fractal->mlx, fractal->win);
        draw_fractal(fractal, flag);
        //mlx_clear_window(fractal->mlx, fractal->win);
        //mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
        ft_printf(" shift key pressed\n");
        
    }
    return (0);
} */

int key_hook(int keycode, t_fractal *fractal)
{
    int flag;

    if (keycode == 65307)  // Tasto ESC
    {
        free_fractal(fractal);
        exit(0);
    }
    if (keycode == 65505)  // Tasto Shift sinistro
    {
        ft_printf("Shift key pressed\n");

        // Cambia la modalità colore
        fractal->color_mode++;
        if (fractal->color_mode == 7)
            fractal->color_mode = 0;

        ft_printf("Color mode: %d\n", fractal->color_mode);

        // Ridisegna il frattale
        mlx_clear_window(fractal->mlx, fractal->win);
        flag = choose_fractal(fractal, fractal->type);
        draw_fractal(fractal, flag);
    }
    return (0);
}

int choose_fractal(t_fractal *fractal, char *type)
{
    int fractal_flag;

    fractal_flag = 0;
    fractal->type = type;
    if (ft_strncmp(fractal->type, "mandelbrot", 10) == 0)
        fractal_flag = 1;
  /*   else if (ft_strncmp(fractal->type, "cantor", 6) == 0)
        fractal_flag = 3; */
    else if (ft_strncmp(fractal->type, "julia", 5) == 0)
        fractal_flag = 2;
    else
        display_usage();
    return (fractal_flag);
}

void init_image(t_fractal *fractal, char *type)
{
    int fractal_flag;

    fractal_flag = choose_fractal(fractal, type);
    //if (fractal_flag == 1 || fractal_flag == 2 || fractal_flag == 3)
    if (fractal_flag == 1 || fractal_flag == 2)
    {
        if (!fractal->mlx)
        {
            //fractal->mlx = malloc(sizeof(void *));
            fractal->mlx = mlx_init();
            fractal->win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT, "Fractal");
        }
        if (!fractal->img)
        {
            fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
            fractal->data = (int *)mlx_get_data_addr(fractal->img, \
                &fractal->bpp, &fractal->size_line, &fractal->endian);
        }
    }
    else
        display_usage();
}

/* int get_color(int iterations, int shift_color)
{
    //static int color_shift;
    //int color;
    //double t;
    
    //color_shift = 0;
    //t = (double)iterations / 100.0;  // Normalizza le iterazioni

    if (iterations == 0)
        return (0x000000);  // Nero se non ci sono iterazioni
    if(shift_color == 0)
        return (iterations << 16) | (iterations << 8) | iterations;  // Scala di grigi
    else if(shift_color == 1)
        return (iterations << 16);  // Scala di rossi
    else if(shift_color == 2)
        return (iterations << 8);  // Scala di verdi
    else if(shift_color == 3)
        return (iterations);  // Scala di blu
    else if(shift_color == 4)
        return (iterations << 16) | (iterations << 8);  // Rosso + Verde
    else if(shift_color == 5)
        return (iterations << 8) | (iterations);  // Verde + Blu
    else if(shift_color == 6)
        return (iterations << 16) | (iterations);  // Rosso + Blu
    else
        return (0xFFFFFF);  // Bianco (default)

    // Aggiorna il color_shift
    color_shift = (color_shift + shift_color) % 6;

    // Calcola il colore in base al color_shift con effetti psichedelici
    
}
 */

 #include <math.h>

int get_color(int iterations, int shift_color)
{
    double t;
    int r;
    int g;
    int b;

    t = (double)iterations / 10.0;  // Normalizza le iterazioni
    if (iterations == MAX_ITER)
        return (0x000000);
    else
    {
        r = (int)((sin(t + 10 * shift_color) * 127 + 128));
        g = (int)((sin(t + 10 * shift_color + 2) * 127 + 128));
        b = (int)((sin(t + 10 * shift_color + 4) * 127 + 128));
        return(effect_psychedelic(r, g, b));
    }
}

int effect_psychedelic(int r, int g, int b)
{
   // int r_psychedelic;
    //int g_psychedelic;
    //int b_psychedelic;
    return((r * 65536) + (g * 256) + b);

}

int mouse_hook(int button, int x, int y, void *param, int flag)
{
    t_fractal *fractal;

    fractal = (t_fractal *)param;
    if (button == 5)
    {
        mlx_clear_window(fractal->mlx, fractal->win);
        zoom(param, x, y, 2.0);
    }
    else if (button == 4)
    {
        mlx_clear_window(fractal->mlx, fractal->win);
        zoom(param, x, y, 0.5);
    }
    flag = choose_fractal(fractal, fractal->type);
    draw_fractal(fractal, flag);
    return (0);
}

static int compute_fractal(t_fractal *fractal, int x, int y, int flag)
{
    double real;
    double imag;

    real = fractal->min_re + (double)x / WIDTH * (fractal->max_re - fractal->min_re);
    imag = fractal->min_im + (double)y / HEIGHT * (fractal->max_im - fractal->min_im);    
    if (flag == 1)
        return (mandelbrot(real, imag));
    if (flag == 2)
        return (julia(real, imag, fractal->julia_re, fractal->julia_im));
    /* if (flag == 3)
    {
       // real = fractal->min_re + (double)x / WIDTH * (fractal->max_re - fractal->min_re);
       // imag = fractal->max_re + (double)x / WIDTH * (fractal->max_re - fractal->min_re);
        //return (is_in_cantor(x, y));
        ;
    } */
    return (0);
}
/* void draw_fractal(t_fractal *fractal, int flag)
{
    int x, y, k;

    init_image(fractal, fractal->type);
    x = -1;
    while (++x < WIDTH)
    {
        y = -1;
        while (++y < HEIGHT)
        {
            k = compute_fractal(fractal, x, y, flag);
            fractal->data[y * WIDTH + x] = get_color(k, fractal->color_mode);
        }
    }
    execute_fractal(fractal);
} */
void draw_fractal(t_fractal *fractal, int flag)
{
    int x, y, k;

    init_image(fractal, fractal->type);
    x = -1;
 /*    if(flag == 3)
        is_in_cantor(fractal);
    else
    { */
        while (++x < WIDTH)
        {
            y = -1;
            while (++y < HEIGHT)
            {
                k = compute_fractal(fractal, x, y, flag);
                fractal->data[y * WIDTH + x] = get_color(k, fractal->color_mode);
                
            }
        }
    // }

    execute_fractal(fractal);
}
void execute_fractal(t_fractal *fractal)
{
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
    mlx_key_hook(fractal->win, key_hook, (void *)fractal);
    mlx_mouse_hook(fractal->win, mouse_hook, (void *)fractal);
    mlx_hook(fractal->win, 17, 0, close_window, (void *)fractal);
    mlx_loop(fractal->mlx);
}

int close_window(t_fractal *fractal)
{
    free_fractal(fractal);
    exit(0);
    return (0);
}



void free_fractal(t_fractal *fractal)
{
    if (fractal->img)
        mlx_destroy_image(fractal->mlx, fractal->img);
    if (fractal->win)
        mlx_destroy_window(fractal->mlx, fractal->win);
    if (fractal->mlx)
    {
        mlx_destroy_display(fractal->mlx);
        free(fractal->mlx);
    }
}
