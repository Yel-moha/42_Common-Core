#include "fractol.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/libft/libft.h"
#include <stdlib.h>  // Per malloc


int main(int argc, char **argv) 
{
    t_fractal *fractal;
	int choice;

    if (argc != 2 && argc != 4) 
	{

        display_usage();
        return 1;
    }
    fractal = (t_fractal *)malloc(sizeof(t_fractal));
    if (!fractal)
        return 1;
	init_fractal(fractal, argv[1]);
	if(argc == 4)	
		c_julia(fractal, argv);
    choice = choose_fractal(fractal, argv[1]);
	if (!choice) 
	{
		display_usage();
		free_fractal(fractal);
		return 1;
	}
	draw_fractal(fractal, choice);
    free_fractal(fractal);
    return (0);
}
