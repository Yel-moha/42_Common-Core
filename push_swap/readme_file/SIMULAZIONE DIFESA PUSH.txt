🎓 SIMULAZIONE DIFESA PUSH_SWAP

(focus: flusso, costi, normalizzazione, scelte algoritmiche)

🔹 PARTE 1 — Visione generale
❓ Spiegami in poche parole cosa fa il tuo push_swap

✅ Risposta ideale:

“Il programma ordina uno stack usando solo operazioni consentite.
Dopo una fase di normalizzazione, sposto quasi tutti gli elementi nello stack B,
ordino A con tre elementi, e poi reinserisco ogni elemento di B nella posizione
ottimale minimizzando il costo totale di rotazioni.”

❓ Qual è il flusso principale delle funzioni?

✅ Risposta:

“main → parsing input → normalizzazione → cycle_sort.
Dentro cycle_sort spingo in B, ordino tre elementi, poi reinserisco
ogni elemento di B usando il calcolo dei costi.”

🔹 PARTE 2 — Normalizzazione (domande molto frequenti)
❓ Perché normalizzi i valori?

✅ Risposta:

“La normalizzazione sostituisce ogni valore con il suo rango.
Questo preserva l’ordine relativo ma rende i confronti indipendenti
dai valori originali.”

❓ L’ordine è davvero preservato? Dimostralo.

✅ Risposta:

“Se a < b allora il numero di elementi minori di a
è minore del numero di elementi minori di b.
Quindi rank(a) < rank(b) e l’ordine relativo è preservato.”

❓ Che complessità ha la tua normalizzazione?

✅ Risposta:

“È O(N²), perché confronto ogni elemento con tutti gli altri.
Tuttavia N è limitato e il codice è semplice e affidabile.”

❓ Esiste una versione più veloce?

✅ Risposta:

“Sì, usando un array ordinato di riferimento si può ottenere O(N log N),
ma per i vincoli del progetto ho preferito la versione più semplice.”

🔹 PARTE 3 — Strategia di ordinamento
❓ Perché lasci solo 3 elementi in A?

✅ Risposta:

“Tre elementi possono essere ordinati in modo deterministico
con un numero minimo di mosse, senza calcolo dei costi.”

❓ Perché non 4 o 5?

✅ Risposta:

“Perché il numero di combinazioni cresce rapidamente,
mentre 3 è un caso completamente gestibile.”

🔹 PARTE 4 — Costi (parte più importante)
❓ Cos’è il costo?

✅ Risposta:

“È il numero minimo di rotazioni necessarie per portare
un elemento in cima allo stack e posizionarlo correttamente.”

❓ Come lo calcoli matematicamente?

✅ Risposta:

“Uso la distanza circolare:
cost = pos se l’elemento è nella prima metà,
altrimenti size - pos.”

❓ Perché è corretto usare size / 2?

✅ Risposta:

“Perché rappresenta il punto in cui la rotazione inversa
diventa più conveniente della rotazione normale.”

❓ Il costo totale cos’è?

✅ Risposta:

“È la somma del costo in A e del costo in B
per lo stesso elemento.”

❓ Perché scegli sempre il costo minimo?

✅ Risposta:

“Perché riduce il numero totale di operazioni,
applicando una strategia greedy localmente ottimale.”

🔹 PARTE 5 — Funzioni chiave
❓ A cosa serve target_position?

✅ Risposta:

“Trova la posizione corretta in A dove inserire un valore di B
mantenendo l’ordine crescente.”

❓ E se non esiste un valore più grande in A?

✅ Risposta:

“Inserisco l’elemento prima del minimo,
chiudendo il ciclo circolare dello stack.”

❓ bring_to_top cosa fa esattamente?

✅ Risposta:

“Esegue il numero minimo di rotazioni
per portare un elemento in cima allo stack.”

🔹 PARTE 6 — Edge cases
❓ Cosa succede se l’input è già ordinato?

✅ Risposta:

“Lo rilevo subito con is_sorted e termino senza operazioni.”

❓ Input con un solo numero?

✅ Risposta:

“Il programma termina immediatamente.”

🔹 PARTE 7 — Chiusura (domanda da valutatore bravo)
❓ Se rifacessi il progetto, cosa miglioreresti?

✅ Risposta ECCELLENTE:

“Implementerei una normalizzazione O(N log N)
e valuterei l’uso di rotazioni combinate rr e rrr
per ridurre ulteriormente il numero di mosse.”
