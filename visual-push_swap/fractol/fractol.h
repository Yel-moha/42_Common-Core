#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include "ft_printf/ft_printf.h"
# include "ft_printf/libft/libft.h"
# include <complex.h>
# include <stdbool.h>
# include <math.h>
# include <stdlib.h>

# define WIDTH 800
# define HEIGHT 600
# define MAX_ITER 100

typedef struct s_fractal
{
	double	min_re;
	double	max_re;
	double	min_im;
	double	max_im;
	double	julia_re;
	double	julia_im;
	int		color_mode;
    int     flag;
	void	*mlx;
	void	*win;
	void	*img;
	int		*data;
	char	*type;
	int		bpp;
	int		size_line;
	int		endian;
}	t_fractal;

int		close_window(t_fractal *fractal);
int		choose_fractal(t_fractal *fractal, char *type);
int		compute_fractal(t_fractal *fractal, int x, int y);
int		get_color(int iterations, int shift_color);
int		julia(double real, double imag, double julia_re, double julia_im);
int		key_hook(int keycode, t_fractal *fractal);
int		mandelbrot(double real, double imag);
int		mouse_hook(int button, int x, int y, void *param);

void	c_julia(t_fractal *fractal, char **type);
void	display_usage(void);
void	draw_fractal(t_fractal *fractal);
void	execute_fractal(t_fractal *fractal);
void	free_fractal(t_fractal *fractal);
void	free_split(char **arr);
void	init_fractal(t_fractal *fractal, char *type);
void	init_image(t_fractal *fractal, char *type);
void	show_diaplay(t_fractal *fractal);
void	zoom(void *param, int x, int y, double zoom_factor);

double	parse_julia_value(char *str);

#endif
