//#include "libft.h"
//#include <mlx.h> // Includiamo la libreria MLX
#include <math.h> 
#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


/* Structure to handle image data */
typedef struct s_data
{
	void	*img;			/* Pointer to the image */
	char	*addr;			/* Address of the image data */
	int		bits_per_pixel;	/* Number of bits per pixel */
	int		line_length;	/* Length of a line in bytes */
	int		endian;			/* Endianness of the image */
}    t_data;

/* Structure to handle MLX window and image variables */
typedef struct s_vars
{
	void	*mlx;			/* MLX connection pointer */
	void	*win;			/* Window pointer */
	t_data	img;			/* Image structure */
}   t_vars;



void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void   *draw_mandelbrot(void *arg);
void   *draw_julia(void *arg);
