# Guida completa: dal C al C++ (con focus su tests.cpp)

Questa guida e' pensata per chi conosce il C e sta iniziando C++.
L'obiettivo e' spiegare in modo approfondito tutto quello che in `tests.cpp` puo' sembrare nuovo.

## 1) Mappa mentale: C vs C++

In C ragioni soprattutto in termini di:
- funzioni
- struct
- puntatori
- array
- gestione manuale della memoria

In C++ aggiungi un livello in piu':
- tipi che hanno comportamento (classi)
- oggetti che si costruiscono e distruggono automaticamente
- libreria standard molto piu' ricca (`vector`, algoritmi, iteratori)
- genericita' (template)

Idea chiave:
- C = "dati + funzioni separate"
- C++ = "dati + funzioni insieme nel tipo" (incapsulamento)

## 2) Che cos'e' una classe rispetto a struct C

In C puoi fare:

```c
typedef struct s_account {
    int amount;
    int deposits;
} t_account;

void deposit(t_account *a, int x) {
    a->amount += x;
    a->deposits++;
}
```

In C++ il modello tipico diventa:

```cpp
class Account {
public:
    void makeDeposit(int x);
private:
    int _amount;
    int _nbDeposits;
};
```

Differenza profonda:
1. Nel C passi sempre la struct alla funzione.
2. Nel C++ il metodo "sa" su quale oggetto lavora tramite `this` (implicito nelle funzioni non static).

## 3) static vs non-static (fondamentale)

### 3.1 Campi non-static
Esempio: `_amount`, `_nbDeposits`.

Significa:
- ogni oggetto Account ha la sua copia
- se hai 8 account, hai 8 `_amount` diversi

Paragone C:
- e' come avere 8 struct separate in memoria

### 3.2 Campi static
Esempio: `_nbAccounts`, `_totalAmount`.

Significa:
- esiste una sola copia condivisa da tutti gli oggetti
- rappresenta stato globale della classe

Paragone C:
- simile a una variabile globale di modulo, ma "namespaced" dentro la classe

### 3.3 Metodi non-static
Esempio: `makeDeposit`, `displayStatus`.

Significa:
- agiscono su un singolo account
- possono usare `this`

### 3.4 Metodi static
Esempio: `displayAccountsInfos`, `getNbAccounts`.

Significa:
- appartengono alla classe, non al singolo oggetto
- non hanno `this`
- si chiamano come `Account::displayAccountsInfos()`

## 4) typedef dentro la classe: `typedef Account t;`

Questa riga crea un alias interno:
- `Account::t` e' solo un altro nome di `Account`

Perche' si usa:
1. Stile del progetto/test.
2. Uniformita' in codice generico.
3. Evitare ripetizione di nomi lunghi in certi contesti.

In C++ moderno si userebbe spesso:

```cpp
using t = Account;
```

## 5) include standard che vedi in tests.cpp

- `<vector>`: contenitore dinamico (array che cresce automaticamente)
- `<algorithm>`: algoritmi generici come `std::for_each`
- `<functional>`: utility per adattare funzioni/metodi (qui `std::mem_fun_ref`, stile vecchio ma valido nel contesto)

## 6) Spiegazione ultra-lenta della riga che ti creava dubbio

Riga:

```cpp
accounts_t accounts( amounts, amounts + amounts_size );
```

### 6.1 Primo pezzo: `accounts_t`
E' un alias di tipo, definito cosi':

```cpp
typedef std::vector<Account::t> accounts_t;
```

Quindi `accounts_t` = `std::vector<Account>`.

### 6.2 Secondo pezzo: `accounts`
E' il nome della variabile.

### 6.3 Terzo pezzo: `(amounts, amounts + amounts_size)`
Questi sono due iteratori/puntatori che definiscono un intervallo.

Regola standard C++: intervalli come `[first, last)`
- `first` incluso
- `last` escluso

Qui:
- `first = amounts` (puntatore al primo int)
- `last = amounts + amounts_size` (puntatore subito dopo l'ultimo int)

### 6.4 Cosa fa davvero la riga
Costruisce un `vector<Account>` prendendo tutti gli int dell'array.

Ogni int viene convertito in `Account` usando il costruttore:

```cpp
Account(int initial_deposit)
```

Quindi e' come dire:
- prendi 42 -> crea Account(42)
- prendi 54 -> crea Account(54)
- ...

## 7) Equivalente mentale in stile C/C++ "manuale"

La riga sopra equivale concettualmente a:

```cpp
accounts_t accounts;
for (size_t i = 0; i < amounts_size; ++i) {
    accounts.push_back(Account(amounts[i]));
}
```

Vantaggio della forma compatta:
- meno codice
- meno errori
- piu' idiomatica C++

## 8) Cosa sono gli iteratori (traduzione da puntatori C)

In C sei abituato a puntatori su array.

In C++ un iteratore e' un oggetto che "si comporta" come puntatore:
- `*it` -> elemento puntato
- `++it` -> elemento successivo
- `it1 != it2` -> confronto posizione

Per `vector`, l'iteratore e' molto simile a un puntatore reale.

`begin()` = primo elemento.

`end()` = posizione oltre l'ultimo elemento (non dereferenziare).

## 9) `std::for_each` e `std::mem_fun_ref`

Codice:

```cpp
std::for_each(acc_begin, acc_end, std::mem_fun_ref(&Account::displayStatus));
```

### 9.1 `std::for_each`
Applica una funzione a ogni elemento del range `[acc_begin, acc_end)`.

### 9.2 Perche' serve `mem_fun_ref`
`displayStatus` e' un metodo membro, non una funzione libera.

Un metodo membro ha bisogno di un oggetto su cui essere chiamato.
`mem_fun_ref` adatta il metodo a una forma invocabile da algoritmo.

Nota storica:
- Questo stile e' pre-C++11.
- Oggi spesso useresti lambda.

## 10) For con coppia di iteratori (depositi/prelievi)

Nel codice c'e':

```cpp
typedef std::pair<accounts_t::iterator, ints_t::iterator> acc_int_t;
```

Poi:

```cpp
for (acc_int_t it(acc_begin, dep_begin);
     it.first != acc_end && it.second != dep_end;
     ++(it.first), ++(it.second))
{
    (*(it.first)).makeDeposit(*(it.second));
}
```

Traduzione lenta:
1. `it.first` cammina sugli account.
2. `it.second` cammina sui numeri dei depositi.
3. A ogni giro avanzi entrambi.
4. Applichi deposito dell'importo corrente all'account corrente.

Paragone C:
- e' come tenere due indici/puntatori in parallelo su due array.

## 11) `(*it).metodo()` vs `it->metodo()`

Queste due forme sono equivalenti:

```cpp
(*(it.first)).makeDeposit(*(it.second));
```

```cpp
it.first->makeDeposit(*(it.second));
```

La seconda e' solo piu' leggibile.

## 12) RAII e distruttori: differenza pratica rispetto al C

In C devi spesso fare `malloc/free` manuale.

In C++ oggetti locali e container gestiscono vita/memoria automaticamente:
- quando `main` finisce, il `vector` distrugge i suoi elementi
- ogni `Account` chiama il distruttore

Questo riduce memory leak e cleanup dimenticati.

## 13) `const` in C++ (oltre il C)

In C++ `const` appare su:
1. dati (`int const x`)
2. metodi (`int checkAmount() const`)

Metodo `const` significa:
- promessa: non modifico lo stato osservabile dell'oggetto
- il compilatore controlla questa promessa

E' utilissimo per design robusto e leggibile.

## 14) Checklist pratica per leggere codice C++ se vieni dal C

Quando vedi una riga, chiediti in ordine:
1. E' una dichiarazione di tipo o variabile?
2. Ci sono alias (`typedef`/`using`) da espandere mentalmente?
3. E' oggetto singolo o contenitore?
4. Se vedo parentesi dopo un nome, e' costruttore?
5. Se vedo `::`, sto accedendo a qualcosa di classe/namespace?
6. Se vedo `begin/end`, sto lavorando su un range `[first, last)`?
7. Se vedo metodo con `const`, puo' modificare stato?
8. Se vedo `static`, manca `this`?

## 15) Mini glossario essenziale

- Oggetto: istanza concreta di una classe.
- Classe: blueprint che definisce dati+metodi.
- Costruttore: funzione speciale che inizializza l'oggetto.
- Distruttore: funzione speciale chiamata a fine vita oggetto.
- Metodo static: funzione di classe, senza `this`.
- Membro static: dato condiviso tra tutte le istanze.
- Iteratore: astrazione di posizione in contenitore.
- Range `[first, last)`: intervallo con limite finale escluso.
- Alias di tipo: nome alternativo di un tipo (`typedef`/`using`).

## 16) Esercizio consigliato (per fissare davvero)

Prova a riscrivere solo il blocco di costruzione account in tre versioni:
1. Versione attuale con costruttore range.
2. Versione con loop e `push_back`.
3. Versione con indice classico stile C.

Se tutte e tre ti sono chiare, hai capito il salto C -> C++ su questo file.

---

Se vuoi, nel prossimo step posso prepararti una seconda guida gemella dedicata solo a `Account.hpp` e `Account.cpp`, sempre con confronto C -> C++ riga per riga.
