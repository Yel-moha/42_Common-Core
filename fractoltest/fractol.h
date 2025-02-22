#ifndef FRACTOL_H
#define FRACTOL_H

#include "minilibx-linux/mlx.h"
#include <complex.h>

#include <stdio.h>

#include <stdlib.h>

int key_hook(int keycode, void *param);
int mandelbrot(double real, double imag, int max_iter);

#endif