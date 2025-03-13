#include "fractol.h"

int mandelbrot(double real, double imag)
{
    double complex z;
    double complex c;
    int i;

    i = 0;
    c = real + imag * I;
    z = 0 + 0 * I;
    while (i < MAX_ITER)
    {
        z = z * z + c;
        if (creal(z) * creal(z) + cimag(z) * cimag(z) > 4)
            break;
        i++;
    }
    return i;
}

int julia(double real, double imag, double julia_re, double julia_im)
{
    double complex z;
    double complex c;
    int i;

    i = 0;
    z = real + imag * I;
    c = julia_re + julia_im * I;
    while (i < MAX_ITER)
    {
        z = z * z + c;
        if (creal(z) * creal(z) + cimag(z) * cimag(z) > 4)
            break;
        i++;
    }
    return i;
}

#include <stdio.h>
#include <math.h>
/* 
void is_in_cantor(t_fractal *fractal)
{
    int segment_size;
    int level;
    int i;
    int y;

    level = 0;
    y = 0;
    while (level < 5) // Limit the recursion depth
    {
        segment_size = WIDTH / pow(3, level);
        i = 0;
        while (i < WIDTH)
        {
            if ((i / segment_size) % 3 == 1) // Middle third
            {
                int j = y + level * 50; // Space between lines
                if (j < HEIGHT)
                    fractal->data[j * WIDTH + i] = get_color(0, fractal->color_mode);
            }
            i++;
        }
        level++;
    }
    execute_fractal(fractal);
} */