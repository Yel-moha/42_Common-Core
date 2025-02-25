#ifndef FRACTOL_H
#define FRACTOL_H

#include "minilibx-linux/mlx.h"
#include <complex.h>

#include <stdio.h>

#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct s_fractal
{
    double min_re;
    double max_re;
    double min_im;
    double max_im;
    void *mlx;
    void *win;
} t_fractal;

int key_hook(int keycode, void *param);
int mouse_hook(int button, int x, int y, void *param);
void zoom(void *param, int x, int y, double zoom_factor);
void draw_fractal(t_fractal *fractal);
int mandelbrot(double real, double imag, int max_iter);
void init_fractal(t_fractal *fractal);

#endif