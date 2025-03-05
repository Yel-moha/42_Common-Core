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

int sierpinski (double real, double imag, int max_iter)
{
    double z_real = 0.0;
    double z_imag = 0.0;
    double c_real = real;
    double c_imag = imag;
    int i = 0;
    while (i < max_iter)
    {
        double temp_real = z_real;
        z_real = z_real * z_real - z_imag * z_imag + c_real;
        z_imag = 2 * temp_real * z_imag + c_imag;
        if (z_real * z_real + z_imag * z_imag > 4)
            break;
        i++;
    }
    return i;
}