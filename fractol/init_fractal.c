/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:13:28 by yel-moha          #+#    #+#             */
/*   Updated: 2025/03/23 16:16:59 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_fractal_1(t_fractal *fractal, char *type)
{
	fractal->type = type;
	fractal->julia_re = -0.7;
	fractal->julia_im = 0.27015;
	fractal->color_mode = 0;
	fractal->flag = 0;
	fractal->mlx = NULL;
	fractal->win = NULL;
	fractal->img = NULL;
	fractal->bpp = 0;
	fractal->size_line = 0;
	fractal->endian = 0;
}

void	init_fractal(t_fractal *fractal, char *type)
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
	else
	{
		display_usage();
		return ;
	}
	init_fractal_1(fractal, type);
}

void	free_fractal(t_fractal *fractal)
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
	free(fractal);
}
