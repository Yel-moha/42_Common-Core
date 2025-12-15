/* server.c
 *
 * Server per il progetto Minitalk.
 * Riceve messaggi dal client tramite segnali UNIX (SIGUSR1/SIGUSR2).
 * Ogni carattere viene ricostruito bit per bit dai segnali ricevuti.
 */
#include "minitalk.h"

/*
 * Variabile globale (unica consentita dal subject).
 * Deve essere volatile sig_atomic_t per sicurezza nei signal handler.
 * g_state[0] = accumulatore: contiene i bit ricevuti finora per il carattere corrente
 * g_state[1] = contatore: numero di bit ricevuti (0-8)
 */
volatile sig_atomic_t	g_state[2] = {0, 0};

/*
 * write_pid:
 * Stampa il PID del server all'avvio.
 * Converte il numero in stringa manualmente (cifra per cifra).
 * Usa write() invece di printf per conformità al subject.
 */
static void	write_pid(void)
{
	char	buf[32];      // buffer per la stringa del PID
	pid_t	pid;          // PID del processo corrente
	int		len;          // lunghezza finale della stringa
	pid_t	tmp;          // copia temporanea per la conversione
	char	reverse[32];  // buffer temporaneo (cifre in ordine inverso)
	int		i;            // indice per reverse[]

	pid = getpid();                        // ottiene il PID del processo
	len = 0;
	if (pid == 0)                          // caso speciale: PID = 0
		buf[len++] = '0';
	tmp = pid;
	i = 0;
	while (tmp > 0)                        // estrae le cifre (ordine inverso)
	{
		reverse[i++] = (tmp % 10) + '0';   // ultima cifra → carattere ASCII
		tmp /= 10;                         // rimuove l'ultima cifra
	}
	while (i > 0)                          // inverte l'ordine delle cifre
		buf[len++] = reverse[--i];
	buf[len++] = '\n';                     // aggiunge newline
	write(1, buf, len);                    // stampa su stdout
}

/*
 * signal_handler:
 * Funzione chiamata ogni volta che il server riceve SIGUSR1 o SIGUSR2.
 * Ricostruisce un carattere accumulando 8 bit.
 *
 * Protocollo:
 * - SIGUSR1 = bit 0
 * - SIGUSR2 = bit 1
 *
 * Parametri:
 * - signo: il segnale ricevuto (SIGUSR1 o SIGUSR2)
 */
static void	signal_handler(int signo)
{
	char	c;  // carattere ricostruito dopo 8 bit

	/*
	 * Operazione bit a bit:
	 * 1. (g_state[0] << 1) = shift a sinistra, fa spazio per il nuovo bit
	 * 2. (signo == SIGUSR2) = 1 se SIGUSR2, 0 se SIGUSR1
	 * 3. | = OR bit a bit, aggiunge il nuovo bit nella posizione meno significativa
	 *
	 * Esempio: se g_state[0] = 0b01100001 e arriva SIGUSR2 (bit 1):
	 *          0b01100001 << 1 = 0b11000010
	 *          0b11000010 | 1  = 0b11000011
	 */
	g_state[0] = (g_state[0] << 1) | (signo == SIGUSR2);
	g_state[1]++;  // incrementa il contatore dei bit ricevuti

	/*
	 * Quando abbiamo ricevuto 8 bit, abbiamo un carattere completo.
	 */
	if (g_state[1] == 8)
	{
		c = (char)g_state[0];  // converte l'accumulatore in char
		if (c == '\0')         // se è il terminatore di stringa
			write(1, "\n", 1); // stampa newline (fine messaggio)
		else
			write(1, &c, 1);   // stampa il carattere ricevuto
		g_state[0] = 0;        // resetta l'accumulatore per il prossimo char
		g_state[1] = 0;        // resetta il contatore dei bit
	}
}

/*
 * main:
 * Punto di ingresso del server.
 * 1. Stampa il PID
 * 2. Configura i signal handler per SIGUSR1 e SIGUSR2
 * 3. Entra in un loop infinito in attesa di segnali
 */
int	main(void)
{
	struct sigaction	sa;  // struttura per configurare il signal handler

	write_pid();                       // stampa il PID all'avvio
	sa.sa_handler = signal_handler;    // imposta la funzione handler
	sigemptyset(&sa.sa_mask);          // nessun segnale bloccato durante l'handler
	sa.sa_flags = 0;                   // nessun flag speciale
	sigaction(SIGUSR1, &sa, NULL);     // registra handler per SIGUSR1 (bit 0)
	sigaction(SIGUSR2, &sa, NULL);     // registra handler per SIGUSR2 (bit 1)
	while (1)                          // loop infinito
		pause();                       // sospende il processo fino al prossimo segnale
	return (0);                        // mai raggiunto
}
