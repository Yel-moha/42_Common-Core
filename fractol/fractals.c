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