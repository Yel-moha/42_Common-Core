#include "fractol.h"
#include <stdio.h>
#include <string.h> // strcmp function sostituire con ft_strcmp in libft
#include <stdbool.h>

int main(int argc, char **argv)
{
    //bool state = true;
    t_fractal fractal;
   /*  if(state)
    {
        init_fractal(&fractal);
        state = false;
    } */
    init_fractal(&fractal);

    if(argc == 1)
    {
        printf("Usage: ./fractol [mandelbrot/julia]\n");
        return (0);
    }
    else
    {
        if (strcmp(argv[1], "mandelbrot") == 0)
        {
            draw_fractal(&fractal);
            //fractal.type = MANDELBROT;
        }
        else if (strcmp(argv[1], "julia") == 0)
        {
            draw_fractal(&fractal);
            //fractal.type = JULIA;
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