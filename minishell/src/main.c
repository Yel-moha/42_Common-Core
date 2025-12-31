#include "minishell.h"

int	g_signal;

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;  // Struttura LOCALE (non globale!)
	
	(void)ac;
	(void)av;
	
	// 1. Inizializza la struttura shell
	shell.envp_copy = copy_envp(envp);  // Copia envp originale
	shell.exit_code = 0;  // Inizializza exit_code
	
	// 2. Inizializza segnali
	init_signals();
	
	// 3. Avvia il loop principale passando la struttura
	prompt_loop(&shell);
	
	// 4. Pulizia prima di uscire
	free_envp(shell.envp_copy);
	
	// 5. Ritorna l'ultimo exit_code (come bash)
	return (shell.exit_code);
}