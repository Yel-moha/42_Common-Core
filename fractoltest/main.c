#include "fractol.h"
#include <stdio.h>
#include <string.h> // strcmp function sostituire con ft_strcmp in libft
#include <stdbool.h>

void display_usage(void)
{
    printf("Usage: ./fractol <fractal_type> [c_real c_imag]\n");
    printf("Available fractal types:\n");
    printf("  - mandelbrot\n");
    printf("  - julia\n");
    printf("  - burningship\n");
    exit(0);
}


int main(int argc, char **argv)
{
    t_fractal fractal;
    char fractal_type;
    double julia_re;
    double julia_im;
 
    init_fractal(&fractal);
    if(argc == 1)
    {
        display_usage();
        return (0);
    }
    else if(argc == 3)
    {
        if (strcmp(argv[1], "mandelbrot") == 0)
        {
            draw_fractal(&fractal);
            //fractal.type = MANDELBROT;
        }
        else if (strcmp(argv[1], "julia") == 0)
        {
            julia_re = atof(argv[2]);
            julia_im = atof(argv[3]);
            draw_fractal(&fractal);
            //fractal.type = JULIA;
                if(argv[2])
                {
                    julia_re = atof(argv[2]);
                    julia_im = atof(argv[3]);
                }
                else
                {
                    julia_re = -0.7;
                    julia_im = 0.27015;
                }
        }
        else
        {
            printf("Usage: ./fractol [mandelbrot/julia]\n");
            return (0);
        }
    }
    //draw_fractal(&fractal);
    //mlx_key_hook(win, key_hook, params);
    //mlx_mouse_hook(win, mouse_hook, params);

    

    //mlx_loop(mlx);
    return (0);
}