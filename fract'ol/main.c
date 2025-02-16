#include <mlx.h>
#include <stdio.h>

int main()
{
	t_vars vars;  // Creiamo una variabile che contiene la finestra e l'immagine
	
	// Inizializziamo la connessione con MLX
	vars.mlx = mlx_init();
	if (!vars.mlx)
	{
		printf("Errore nell'inizializzazione di MLX\n");
		return (1);
	}

	// Creiamo una finestra 800x600
	vars.win = mlx_new_window(vars.mlx, 800, 600, "Finestra MLX");

	// Creiamo un'immagine di 800x600
	vars.img.img = mlx_new_image(vars.mlx, 800, 600);

	// Otteniamo l'indirizzo della memoria dell'immagine
	vars.img.addr = mlx_get_data_addr(vars.img.img, 
                                      &vars.img.bits_per_pixel, 
                                      &vars.img.line_length, 
                                      &vars.img.endian);

	// Loop per mantenere aperta la finestra
	mlx_loop(vars.mlx);

	return (0);
}
