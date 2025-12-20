/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:12:38 by yel-moha          #+#    #+#             */
/*   Updated: 2025/03/23 16:12:38 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	parse_julia_value(char *str)
{
	char	**split;
	double	result;

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

void	c_julia(t_fractal *fractal, char **type)
{
	if (!type[2] || !type[3])
		return (display_usage());
	fractal->julia_re = parse_julia_value(type[2]);
	fractal->julia_im = parse_julia_value(type[3]);
}

int	choose_fractal(t_fractal *fractal, char *type)
{
	fractal->type = type;
	if (ft_strncmp(fractal->type, "mandelbrot", 10) == 0)
		fractal->flag = 1;
	else if (ft_strncmp(fractal->type, "cantor", 6) == 0)
		fractal->flag = 3;
	else if (ft_strncmp(fractal->type, "julia", 5) == 0)
		fractal->flag = 2;
	else
		display_usage();
	return (fractal->flag);
}

int	compute_fractal(t_fractal *fractal, int x, int y)
{
	double	real;
	double	imag;

	real = fractal->min_re + (double)x / WIDTH * \
		(fractal->max_re - fractal->min_re);
	imag = fractal->min_im + (double)y / HEIGHT * \
		(fractal->max_im - fractal->min_im);
	if (fractal->flag == 1)
		return (mandelbrot(real, imag));
	if (fractal->flag == 2)
		return (julia(real, imag, fractal->julia_re, fractal->julia_im));
	return (0);
}

void	execute_fractal(t_fractal *fractal)
{
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	mlx_key_hook(fractal->win, key_hook, (void *)fractal);
	mlx_mouse_hook(fractal->win, mouse_hook, (void *)fractal);
	mlx_hook(fractal->win, 17, 0, close_window, (void *)fractal);
	mlx_loop(fractal->mlx);
}
