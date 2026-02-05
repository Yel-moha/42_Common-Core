# Limite thread e memoria per thread (Linux)

## 1) Limite massimo di thread/processi per utente
Comando usato:

```
ulimit -u
```

Questo valore indica il massimo numero di processi/thread che un singolo utente può creare (limitazione del sistema, non della tua applicazione).

---

## 2) Stack di default per thread e memoria disponibile
Comandi usati:

```
ulimit -s
free -m
```

- `ulimit -s` mostra la dimensione dello stack di default per thread (in KB).
- `free -m` mostra memoria RAM disponibile (in MB).

---

## 3) Stima del numero massimo di thread basata sulla memoria
Calcolo approssimato:

1. Converti lo stack in MB:
   - Stack (MB) = `ulimit -s` / 1024
2. Usa la memoria disponibile (colonna “available” di `free -m`).
3. Stima:

```
max_thread ≈ memoria_available_MB / stack_MB
```

Esempio (valori del tuo sistema):
- Stack = 8192 KB = 8 MB
- Memoria available ≈ 12286 MB

```
max_thread ≈ 12286 / 8 ≈ 1535
```

Questa è una stima teorica. Nella pratica il numero reale è più basso per overhead del sistema, librerie, heap e scheduling.

---

## 4) Come decidere la memoria per singolo thread
La memoria “per thread” è soprattutto lo stack. La scelta dipende da:
- profondità delle chiamate (call stack)
- uso di grandi array/locali nello stack
- ricorsione
- librerie usate dal thread

Se il thread fa poco lavoro e non usa grandi variabili locali, puoi ridurre lo stack.

---

## 5) Impostare stack per thread via pthread
Si può ridurre o aumentare lo stack per thread con `pthread_attr_setstacksize()` prima della `pthread_create()`.
