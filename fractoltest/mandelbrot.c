
#include "fractol.h"


int mandelbrot(double real, double imag, int max_iter, double julia_re, double julia_im)
{
    double complex c;
    double complex z = 0 + 0 * I;
    int i;

    i = 0;
    if(julia_re == 0 && julia_im == 0)
            c = real + imag * I;
    else if (julia_re != 0 && julia_im != 0)
            c = julia_re + julia_im * I;
    while (i < max_iter)
    {
        z = z * z + c;
        if (creal(z) * creal(z) + cimag(z) * cimag(z) > 4)
            break;
        i++;
    }
    return i;
}

int julia(double real, double imag, int max_iter, double julia_re, double julia_im)
{
    double complex z = real + imag * I;
    double complex c = julia_re + julia_im * I;
    int i;

    for (i = 0; i < max_iter; i++)
    {
        z = z * z + c;
        if (creal(z) * creal(z) + cimag(z) * cimag(z) > 4)
            break;
    }
    return i;
}
/* 
To print a complex number in C programming language, 
you can use the printf() function with the "%f + %fi" format specifier, 
where %f is for the real part and %i is for the imaginary part.1 mar 2023
*/