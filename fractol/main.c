/* #include "fractol.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/libft/libft.h"

void show_display(t_fractal *fractal)
{
	choose_fractal(fractal);
	mlx_key_hook(fractal->win, key_hook, fractal);
	mlx_mouse_hook(fractal->win, mouse_hook, fractal);
	mlx_hook(fractal->win, 17, 0, close_window, fractal);
	mlx_loop(fractal->mlx);
}
int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2) // Aggiungi questo controllo per evitare il segfault
        return (-1);
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int main(int argc, char **argv)
{
    t_fractal *fractal;

	fractal = malloc(sizeof(t_fractal));
	if (!fractal)
		return (1);
	/////////////////////////////////
	ft_printf(" mandelbrto: %d\n", ft_strncmp(argv[1], "mandelbrot", 10));
	ft_printf(" julia: %d\n", strncmp(argv[1], "julia", 5));
	ft_printf(" sierpinski: %d\n", ft_strncmp(argv[1], "sierpinski", 10));
	ft_printf("argc: %d\n", argc);
    for (int i = 0; i < argc; i++)
        ft_printf("argv[%d]: %s\n", i, argv[i]);
    
	//////////////////////////////
    if (argc < 2)
        display_usage();
	else if (argc == 2)
	{
		if (ft_strncmp(argv[1], "mandelbrot", 10) == 0)
		{
			ft_printf("sono a mandelbrto ---->mandelbrot\n");
			draw_mandelbrot(fractal);
			show_display(fractal);
		}
		else if (ft_strncmp(argv[1], "sierpinski", 10) == 0)
		{
			draw_sierpinski(fractal);
			show_display(fractal);
		}
		else
			display_usage();
	}
	else if (argc >= 2 && ft_strncmp(argv[1], "julia", 5) == 0)
	{
		fractal->julia_re = atof(argv[2]);
		fractal->julia_im = atof(argv[3]);
		draw_julia(fractal);
		show_display(fractal);
	}
	else
		display_usage();
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
    mlx_key_hook(fractal->win, key_hook, (void *)fractal);
    mlx_mouse_hook(fractal->win, mouse_hook, (void *)fractal);
    mlx_loop(fractal->mlx);
	free(fractal);
	return (0);
}

int close_window(void *param)
{
	t_fractal *fractal;

	fractal = (t_fractal *)param;
	mlx_destroy_image(fractal->mlx, fractal->img);
	mlx_destroy_window(fractal->mlx, fractal->win);
	mlx_destroy_display(fractal->mlx);
	free(fractal->mlx);
	exit(0);
} */

#include "fractol.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/libft/libft.h"
#include <stdlib.h>  // Per malloc


int main(int argc, char **argv) {
    t_fractal *fractal;

    if (argc != 2) {
        display_usage();
        return 1;  // Terminare l'esecuzione se il numero di argomenti è errato
    }

    // Allocazione memoria per fractal
    fractal = (t_fractal *)malloc(sizeof(t_fractal));
    if (!fractal) {  // Controllo per errori di allocazione
        perror("Memory allocation failed");
        return 1;
    }

    // Inizializza fractal
    init_fractal(fractal);
	fractal->type = (char *)malloc(ft_strlen(argv[1]) + 1);
    // Controlla il tipo di fractale passato come argomento
    if (ft_strncmp(argv[1], "mandelbrot", ft_strlen(argv[1])) == 0) {
        ft_strlcpy(fractal->type, "mandelbrot", 1 + ft_strlen(argv[1]));
    } else if (ft_strncmp(argv[1], "julia", ft_strlen(argv[1])) == 0) {
        ft_strlcpy(fractal->type, "julia", 1 + ft_strlen(argv[1]));
    } else if (ft_strncmp(argv[1], "sierpinski", ft_strlen(argv[1])) == 0) {
        ft_strlcpy(fractal->type, "sierpinski", 1 + ft_strlen(argv[1]));
    } else {
        display_usage();
        free(fractal);  // Libera la memoria allocata in caso di errore
        return 1;  // Uscita dal programma
    }

    // Inizializza e visualizza il fractale

    int choice;
    choice = choose_fractal(fractal);
	init_image(fractal);
	draw_fractal(fractal, choice);
	//execute_fractal(fractal);
	ft_printf(" il flag è: %s, = %d\n", fractal->type, choose_fractal(fractal));

    // Libera la memoria allocata
    free(fractal);

    return 0;
}
