PARTE 1 — Simulazione di peer-evaluation (come alla 42)
👨‍🏫 Valutatore:

Spiegami in poche parole cosa fa il tuo progetto.

✅ Risposta corretta:

Il progetto Minitalk implementa una comunicazione client/server usando solo segnali UNIX.
Il client invia una stringa al server bit per bit usando SIGUSR1 e SIGUSR2.
Il server riceve i segnali, ricostruisce i caratteri e li stampa immediatamente.

👨‍🏫 Valutatore:

Perché il server stampa il PID all’avvio?

✅ Risposta:

Perché il client ha bisogno del PID del server per potergli inviare i segnali tramite kill().

👨‍🏫 Valutatore:

Perché usi solo SIGUSR1 e SIGUSR2?

✅ Risposta:

Perché il subject lo impone.
Sono segnali definiti dall’utente, non riservati al sistema, e quindi sicuri da usare per la comunicazione.

👨‍🏫 Valutatore:

Come rappresenti i bit con i segnali?

✅ Risposta:

Ho deciso che:

SIGUSR1 rappresenta il bit 0

SIGUSR2 rappresenta il bit 1

Il client manda 8 segnali per ogni carattere, dal bit più significativo al meno significativo.

👨‍🏫 Valutatore:

Come fai a ricostruire un carattere nel server?

✅ Risposta:

Uso un accumulatore globale:

shift a sinistra

OR con il bit ricevuto

Quando ricevo 8 bit, ho un carattere completo che posso stampare.

👨‍🏫 Valutatore:

Perché usi una variabile globale?

✅ Risposta:

Perché il signal handler non può ricevere parametri personalizzati e deve mantenere uno stato tra una chiamata e l’altra.
Il subject consente una variabile globale per programma.

👨‍🏫 Valutatore:

Cosa succede se due segnali arrivano troppo velocemente?

✅ Risposta:

Linux non accoda i segnali uguali, quindi potrei perderli.
Per questo nel client uso usleep() tra un segnale e l’altro.

👨‍🏫 Valutatore:

Come gestisci la fine della stringa?

✅ Risposta:

Il client invia un carattere '\0' alla fine.
Quando il server lo riceve, stampa un newline \n per separare i messaggi.

👨‍🏫 Valutatore:

Il tuo server può ricevere più messaggi senza riavviarsi?

✅ Risposta:

Sì. Dopo aver stampato un messaggio, il server resetta lo stato interno e continua ad ascoltare segnali.

📡 PARTE 2 — SIGUSR1 e SIGUSR2 spiegati BENE
🔹 Cosa sono?

Sono segnali UNIX definiti per l’utente, non usati dal kernel.

SIGUSR1
SIGUSR2


👉 Servono proprio per comunicazioni personalizzate tra processi.

🔹 Come li usi nel progetto?
Segnale	Significato
SIGUSR1	bit = 0
SIGUSR2	bit = 1

Il client li invia con:

kill(pid, SIGUSR1);
kill(pid, SIGUSR2);


Il server li intercetta con:

sigaction(SIGUSR1, &sa, NULL);
sigaction(SIGUSR2, &sa, NULL);

🔹 Perché non altri segnali?

Perché:

il subject lo vieta

altri segnali (SIGINT, SIGTERM…) hanno significati di sistema

usare SIGUSR1/2 è sicuro e previsto

🧠 PARTE 3 — Riassunto COMPLETO di tutto ciò che hai usato
📂 File del progetto

client.c

server.c

minitalk.h

Makefile

libft/

🧩 Funzioni scritte da te
server.c

write_pid

signal_handler

main

client.c

send_char

main

libft

ft_atoi

🔧 Funzioni di sistema usate (tutte permesse)
Categoria	Funzioni
Output	write
Segnali	sigaction, sigemptyset, kill
PID	getpid
Attesa	pause, usleep
Uscita	exit
🧱 Strutture usate
struct sigaction

Serve per configurare il comportamento dei segnali.

Campi usati:

sa_handler

sa_mask

sa_flags

🌍 Variabili globali

volatile sig_atomic_t g_state[2]

Motivo:

mantenere stato tra segnali

consentito dal subject

⚙️ Concetti chiave usati

comunicazione inter-processo

segnali UNIX

bitwise operations (<<, |, >>)

sincronizzazione

gestione asincrona

rispetto della Norm 42

🎓 SE SAI SPIEGARE TUTTO QUESTO:

✔ passi la peer-evaluation
✔ passi Deepthought
✔ puoi rispondere a modifiche live
✔ dimostri reale comprensione