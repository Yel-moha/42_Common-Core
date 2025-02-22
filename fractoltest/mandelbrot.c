
#include "fractol.h"


int mandelbrot(double real, double imag, int max_iter)
{
    double complex z = 0 + 0 * I;
    double complex c = real + imag * I;
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