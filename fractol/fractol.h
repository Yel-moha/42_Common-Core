#ifndef FRACTOL_H
#define FRACTOL_H

#include "minilibx-linux/mlx.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/libft/libft.h"
#include <complex.h>
#include <stdbool.h>

/* #include <stdio.h>
#include <math.h> */
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_ITER 100

typedef struct s_fractal
{
    double min_re;
    double max_re;
    double min_im;
    double max_im;
	double julia_re;
	double julia_im;
    int color_mode;
    void *mlx;
    void *win;
    void *img; // Aggiungi questa variabile per l'immagine buffer
    int *data; // Aggiungi questa variabile per i dati dell'immagine
	char *type;
    int bpp;
    int size_line;
    int endian;
} t_fractal;

//int key_hook(int keycode, t_fractal *fractal, int iterations);
int key_hook(int keycode, t_fractal *fractal);
int mouse_hook(int button, int x, int y, void *param, int flag);
void zoom(void *param, int x, int y, double zoom_factor);
//void draw_fractal(t_fractal *fractal);
int mandelbrot(double real, double imag);
void init_fractal(t_fractal *fractal, char *type);
int julia(double real, double imag, double julia_re, double julia_im);
//int close_window(void *param);
void display_usage(void);
void	show_diaplay(t_fractal *fractal);
/* void draw_julia(t_fractal *fractal);
void draw_sierpinski(t_fractal *fractal);
void draw_mandelbrot(t_fractal *fractal); */
void draw_fractal(t_fractal *fractal, int flag);
int choose_fractal(t_fractal *fractal, char *type);
//int get_color (int iterations);
void execute_fractal(t_fractal *fractal);
void init_image(t_fractal *fractal, char *type);
void c_julia(t_fractal *fractal, char **type);
int get_color(int iterations, int shift_color);
int close_window(t_fractal *fractal);
void free_split(char **arr);
double parse_julia_value(char *str);
void free_fractal(t_fractal *fractal);
int effect_psychedelic(int r, int g, int b);
//void is_in_cantor(t_fractal *fractal);
//int	ft_strcmp(const char *s1, const char *s2);
/* void	ft_strlcpy(char *dst, const char *src);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
 */

#endif