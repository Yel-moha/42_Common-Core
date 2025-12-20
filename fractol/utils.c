/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:14:02 by yel-moha          #+#    #+#             */
/*   Updated: 2025/03/23 16:14:06 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	display_usage(void)
{
	ft_printf("\nUsage:\n");
	ft_printf("  ./fractol <fractal_type> [<real> <imaginary>]\n\n");
	ft_printf("Available fractals:\n");
	ft_printf("  mandelbrot         (no parameters required)\n");
	ft_printf("  julia              (optional: real and imaginary parts)\n\n");
	ft_printf("Example:\n");
	ft_printf("  ./fractol mandelbrot\n");
	ft_printf("  ./fractol julia 0.285 0.013\n\n");
	ft_printf("Some interesting Julia constants:\n");
	ft_printf("  c =  0.285 + 0.013i\n");
	ft_printf("  c =  0.45  - 0.1428i\n");
	ft_printf("  c = -0.70176 - 0.3842i\n");
	ft_printf("  c = -0.835  - 0.2321i\n\n");
	ft_printf("ESC to quit | ");
	ft_printf("Mouse wheel to zoom | ");
	ft_printf("SHIFT to change color mode\n\n");
	exit(1);
}

void	zoom(void *param, int x, int y, double zoom_factor)
{
	t_fractal	*fractal;
	double		mouse_re;
	double		mouse_im;

	fractal = (t_fractal *)param;
	mouse_re = fractal->min_re + ((double)x / WIDTH)
		* (fractal->max_re - fractal->min_re);
	mouse_im = fractal->min_im + ((double)y / HEIGHT)
		* (fractal->max_im - fractal->min_im);
	fractal->min_re = mouse_re - (mouse_re - fractal->min_re) * zoom_factor;
	fractal->max_re = mouse_re + (fractal->max_re - mouse_re) * zoom_factor;
	fractal->min_im = mouse_im - (mouse_im - fractal->min_im) * zoom_factor;
	fractal->max_im = mouse_im + (fractal->max_im - mouse_im) * zoom_factor;
}

int	get_color(int iterations, int shift_color)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = (double)iterations / 10.0;
	if (iterations == MAX_ITER)
		return (0x000000);
	r = (int)((sin(t + 10 * shift_color) * 127 + 128));
	g = (int)((sin(t + 10 * shift_color + 2) * 127 + 128));
	b = (int)((sin(t + 10 * shift_color + 4) * 127 + 128));
	return ((r * 65536) + (g * 256) + b);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
