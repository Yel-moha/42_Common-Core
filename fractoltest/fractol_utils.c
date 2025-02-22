#include "fractol.h"


int key_hook(int keycode, void *param)
{
    if (keycode == 65307) // 65307 è il codice per il tasto ESC su macOS
    {
        // Chiudi la finestra e esci dal programma
        void *mlx = ((void **)param)[0];
        void *win = ((void **)param)[1];
        mlx_destroy_window(mlx, win);
        exit(0);
    }
    return (0);
}

