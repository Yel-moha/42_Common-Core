/* client.c
 *
 * Client per il progetto Minitalk.
 * Uso: ./client <server_pid> "messaggio"
 *
 * Invia ogni carattere del messaggio bit per bit al server usando segnali:
 * - SIGUSR1 rappresenta il bit 0
 * - SIGUSR2 rappresenta il bit 1
 *
 * Dopo il contenuto del messaggio, invia un byte '\0' finale per indicare
 * la fine della trasmissione (così il server può stampare un newline).
 */
#include "minitalk.h"

/*
 * send_char:
 * Invia un singolo carattere al server, bit per bit.
 *
 * Protocollo:
 * - SIGUSR1 = bit 0
 * - SIGUSR2 = bit 1
 *
 * Parametri:
 * - pid: PID del processo server
 * - c: carattere da inviare (unsigned per evitare problemi con bit sign)
 *
 * L'invio parte dal bit più significativo (bit 7) al meno significativo (bit 0).
 * Questo è importante perché il server fa shift a sinistra quando riceve.
 */
static void	send_char(int pid, unsigned char c)
{
	int	i;  // indice del bit corrente (da 7 a 0)

	i = 7;  // partiamo dal bit più significativo (MSB)
	while (i >= 0)
	{
		/*
		 * Estrazione del bit:
		 * 1. (c >> i) = shift a destra di i posizioni
		 *    Porta il bit che ci interessa nella posizione 0
		 * 2. & 1 = AND con 1, isola solo il bit meno significativo
		 *
		 * Esempio: c = 'A' = 0b01000001, i = 6
		 *          c >> 6 = 0b00000001
		 *          0b00000001 & 1 = 1
		 */
		if ((c >> i) & 1)
		{
			// Il bit è 1 → invia SIGUSR2
			if (kill(pid, SIGUSR2) == -1)
			{
				exit(1);
			}
		}
		else
		{
			// Il bit è 0 → invia SIGUSR1
			if (kill(pid, SIGUSR1) == -1)
			{
				exit(1);
			}
		}
		/*
		 * Pausa tra un segnale e l'altro.
		 * Necessaria per dare tempo al server di processare il segnale.
		 * Senza questa pausa, i segnali potrebbero "accumularsi" e perdersi.
		 * 100 microsecondi è un buon compromesso tra velocità e affidabilità.
		 */
		usleep(100);
		i--;  // passa al bit successivo (meno significativo)
	}
}

/*
 * main:
 * Punto di ingresso del client.
 * 1. Verifica che ci siano esattamente 2 argomenti (PID e messaggio)
 * 2. Converte il PID da stringa a intero
 * 3. Invia ogni carattere del messaggio
 * 4. Invia '\0' per segnalare la fine del messaggio
 */
int	main(int argc, char **argv)
{
	int		pid;  // PID del server
	char	*msg; // puntatore al messaggio da inviare
	int		i;    // indice per scorrere il messaggio

	// Verifica numero argomenti: ./client <pid> "messaggio"
	if (argc != 3)
	{
		write(1, "Usage: ./client <pid> \"message\"\n", 33);
		return (1);
	}
	pid = ft_atoi(argv[1]);            // converte la stringa PID in intero
	// Verifica che il PID sia valido (deve essere > 0)
	if (pid <= 0)
	{
		write(1, "Invalid PID\n", 12);
		return (1);
	}
	msg = argv[2];  // puntatore al messaggio (secondo argomento)
	i = 0;
	// Invia ogni carattere del messaggio
	while (msg[i])
	{
		send_char(pid, (unsigned char)msg[i]);  // cast a unsigned per sicurezza
		i++;
	}
	/*
	 * Invia il carattere nullo '\0' alla fine.
	 * Il server lo riconosce e stampa un newline per terminare la riga.
	 */
	send_char(pid, '\0');
	return (0);
}
