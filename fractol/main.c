/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:13:36 by yel-moha          #+#    #+#             */
/*   Updated: 2025/03/23 16:13:36 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractal	*fractal;
	int			choice;

	if (argc != 2 && argc != 4)
	{
		display_usage();
		return (1);
	}
	fractal = (t_fractal *)malloc(sizeof(t_fractal));
	if (!fractal)
		return (1);
	init_fractal(fractal, argv[1]);
	if (argc == 4)
		c_julia(fractal, argv);
	choice = choose_fractal(fractal, argv[1]);
	if (!choice)
	{
		display_usage();
		free_fractal(fractal);
		return (1);
	}
	init_image(fractal, fractal->type);
	draw_fractal(fractal);
	ft_printf("il flag è: %s, = %d\n", fractal->type, choice);
	return (free_fractal(fractal), 0);
}
