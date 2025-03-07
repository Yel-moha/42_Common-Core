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

bool is_in_cantor(double min_re, double max_re, int level)
{
    if (level == MAX_ITER)
        return true;

    // Divide l'intervallo [0, 1] in tre parti
    double third = (max_re - min_re) / 3.0;

    // Se il punto è nel terzo centrale, non appartiene all'insieme di Cantor
    if (min_re >= third && min_re <= 2 * third)
        return false;

    // Altrimenti, verifica i due segmenti laterali
    if (min_re < third)
        return is_in_cantor(min_re * 3, min_re * 3 + third, level + 1);
    else
        return is_in_cantor((min_re - 2 * third) * 3, (min_re - 2 * third) * 3 + third, level + 1);
}