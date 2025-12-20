/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:13:15 by yel-moha          #+#    #+#             */
/*   Updated: 2025/03/23 16:15:15 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_image(t_fractal *fractal, char *type)
{
	int	fractal_flag;

	fractal_flag = choose_fractal(fractal, type);
	if (fractal_flag == 1 || fractal_flag == 2 || fractal_flag == 3)
	{
		if (!fractal->mlx)
		{
			fractal->mlx = mlx_init();
			fractal->win = mlx_new_window(fractal->mlx,
					WIDTH, HEIGHT, "Fractal");
		}
		if (!fractal->img)
		{
			fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
			fractal->data = (int *)mlx_get_data_addr(fractal->img,
					&fractal->bpp, &fractal->size_line, &fractal->endian);
		}
	}
	else
		display_usage();
}

void	draw_fractal(t_fractal *fractal)
{
	int	x;
	int	y;
	int	k;

	init_image(fractal, fractal->type);
	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			k = compute_fractal(fractal, x, y);
			if (fractal->flag == 3 && k == 0)
				fractal->data[y * WIDTH + x] = 0x000000;
			fractal->data[y * WIDTH + x] = get_color(k, fractal->color_mode);
		}
	}
	execute_fractal(fractal);
}

int	mouse_hook(int button, int x, int y, void *param)
{
	t_fractal	*fractal;

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
	fractal->flag = choose_fractal(fractal, fractal->type);
	draw_fractal(fractal);
	return (0);
}

int	key_hook(int keycode, t_fractal *fractal)
{
	if (keycode == 65307)
	{
		free_fractal(fractal);
		exit(0);
	}
	if (keycode == 65505)
	{
		fractal->color_mode++;
		if (fractal->color_mode == 7)
			fractal->color_mode = 0;
		mlx_clear_window(fractal->mlx, fractal->win);
		fractal->flag = choose_fractal(fractal, fractal->type);
		draw_fractal(fractal);
	}
	return (0);
}

int	close_window(t_fractal *fractal)
{
	free_fractal(fractal);
	exit(0);
	return (0);
}
