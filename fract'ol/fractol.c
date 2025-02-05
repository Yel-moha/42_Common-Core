
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void   *draw_mandelbrot(void *arg)
{
    t_vars	*vars;
    t_data	*img;
    int		x;
    int		y;
    int		color;
    double	z_re;
    double	z_im;
    double	c_re;
    double	c_im;
    double	tmp;
    int		i;

    vars = (t_vars *)arg;
    img = &vars->img;
    y = 0;
    while (y < 800)
    {
        x = 0;
        while (x < 800)
        {
            z_re = 0;
            z_im = 0;
            c_re = (x - 400) / 200.0;
            c_im = (y - 400) / 200.0;
            i = 0;
            while (z_re * z_re + z_im * z_im <= 4 && i < 100)
            {
                tmp = z_re;
                z_re = z_re * z_re - z_im * z_im + c_re;
                z_im = 2 * tmp * z_im + c_im;
                i++;
            }
            color = i * 255 / 100;
            my_mlx_pixel_put(img, x, y, color);
            x++;
        }
        y++;
    }
    return (NULL);
}