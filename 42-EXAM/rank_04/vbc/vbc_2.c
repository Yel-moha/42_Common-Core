/*
** VBC_2.C - Implementazione alternativa del calcolatore
** Versione compatta con funzioni abbreviate (n, factor, term)
** Contiene anche operatori speciali: + unario e * speciale
** 
** Differenze da vbc.c:
** - Supporta unario + e * speciale che ritorna 0
** - Nomi di funzione più brevi (n, factor, term vs parse_addition, etc.)
** - Usa designatori di inizializzazione (.type, .val, etc.)
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
** Struttura dati identica a vbc.c
*/
typedef struct node {
    enum { ADD, MULTI, VAL } type;  /* Tipo di nodo */
    int val;                         /* Valore numerico */
    struct node *l;                  /* Figlio sinistro */
    struct node *r;                  /* Figlio destro */
}   node;

/* Dichiarazione forward della funzione principale di parsing */
node *n(char **s);

/*
** new_node()
** Alloca e inizializza un nuovo nodo
*/
node    *new_node(node n)
{
    node *ret = calloc(1, sizeof(n));
    if (!ret)
        return (NULL);
    *ret = n;
    return (ret);
}

/*
** destroy_tree()
** Libera ricorsivamente l'albero dalla memoria
*/
void    destroy_tree(node *n)
{
    if (!n)
        return ;
    if (n->type != VAL)
    {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

/*
** unexpected()
** Stampa messaggio di errore per token inaspettato
*/
void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of file\n");
}

/*
** accept()
** Accetta il carattere c e avanza il puntatore
*/
int accept(char **s, char c)
{
    if (**s == c)
    {
        (*s)++;
        return (1);
    }
    return (0);
}

/*
** expect()
** Richiede obbligatoriamente il carattere c
** Versione potenziata: controlla specificamente la parentesi di chiusura mancante
*/
int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    /* Se aspettiamo ) ma arriviamo a fine stringa, è come se mancasse la ( di apertura */
    if (!**s && c == ')')
        unexpected('(');
    else
        unexpected(**s);
    return (0);
}

/*
** factor()
** Parsa il livello BASSO della gerarchia
**
** Differenze da parse_num_parenthesis():
** - Supporta operatore unario +: +expr → recursione su factor()
** - Supporta operatore * speciale che ritorna 0: *expr → 0
**
** Casi:
** 1. "+": operatore unario, ricorre su factor()
** 2. "*": operatore speciale, salta il resto e ritorna 0
** 3. DIGIT: numero singolo
** 4. "(": espressione tra parentesi
** 5. Altrimenti: errore
*/
node    *factor(char **s)
{
    node *ret;

    if (**s == '+')  /* Operatore unario + */
    {
        (*s)++;
        return (factor(s));  /* Ricorre semplicemente su factor() */
    }
    if (**s == '*')  /* Operatore * speciale */
    {
        (*s)++;
        factor(s);  /* Consuma il fattore ma lo ignora */
        return (new_node((node){.type = VAL, .val = 0}));  /* Ritorna 0 */
    }
    if (isdigit(**s))  /* Numero singolo */
    {
        ret = new_node((node){.type = VAL, .val = **s - '0'});
        (*s)++;
        return (ret);
    }
    if (accept(s, '('))  /* Espressione tra parentesi */
    {
        ret = n(s);  /* Chiama la funzione principale di parsing */
        if (!ret || !expect(s, ')'))  /* Verifica parentesi bilanciate */
        {
            destroy_tree(ret);
            return (NULL);
        }
        return (ret);
    }
    unexpected(**s);
    return (NULL);
}

/*
** term()
** Parsa il livello INTERMEDIO della gerarchia: moltiplicazioni
**
** Algoritmo (left-associative):
** 1. Parsa il primo fattore con factor()
** 2. Finché c'è un "*":
**    - Parsa il prossimo fattore
**    - Crea un nodo MULTI
**    - Aggiorna left
**
/*
** term()
** Parsa il livello INTERMEDIO della gerarchia: moltiplicazioni
**
** Algoritmo (left-associative):
** 1. Parsa il primo fattore con factor()
** 2. Finché c'è un "*":
**    - Parsa il prossimo fattore
**    - Crea un nodo MULTI
**    - Aggiorna left
**
** Ritorna: l'albero di moltiplicazione
*/
node    *term(char **s)
{
    node *left = factor(s);
    if (!left)
        return (NULL);
    while (accept(s, '*'))
    {
        node *right = factor(s);
        if (!right)
        {
            destroy_tree(left);
            return (NULL);
        }
        left = new_node((node){.type = MULTI, .l = left, .r = right});
    }
    return (left);
}

/*
** n()
** Funzione principale di parsing - parsa il livello TOP della gerarchia: addizioni
**
** Nome abbreviato (n) probabilmente sta per "number" o semplicemente è breve per risparmiare spazio
**
** Algoritmo (left-associative):
** 1. Parsa il primo termine con term()
** 2. Finché c'è un "+":
**    - Parsa il prossimo termine
**    - Crea un nodo ADD
**    - Aggiorna left
**
** IMPORTANTE: term() è chiamata, non factor(), per garantire priorità della moltiplicazione
**
** Ritorna: l'albero di addizione
*/
node    *n(char **s)
{
    node *left = term(s);
    if (!left)
        return (NULL);
    while (accept(s, '+'))
    {
        node *right = term(s);
        if (!right)
        {
            destroy_tree(left);
            return (NULL);
        }
        left = new_node((node){.type = ADD, .l = left, .r = right});
    }
    return (left);
}

/*
** parse_expr()
** Funzione wrapper per il parsing
**
** Caso speciale: se la stringa è vuota o NULL, ritorna un nodo VAL con valore 0
**
** Flusso:
** 1. Se stringa vuota: ritorna 0
** 2. Chiama n() per fare il parsing principale
** 3. Verifica che sia stata consumata TUTTA la stringa
** 4. Se rimangono caratteri: errore (tranne il caso speciale di ) seguito da altri caratteri)
**
** Ritorna: l'albero di parsing, o NULL in caso di errore
*/
node    *parse_expr(char *s)
{
    if (!s || !*s)  /* Caso speciale: stringa vuota */
        return (new_node((node){.type = VAL, .val = 0}));
    node *ret = n(&s);  /* Parsing principale */
    if (!ret)
        return (NULL);
    if (*s)  /* Se ci sono caratteri rimanenti */
    {
        /* Eccezione: ) seguito da altri caratteri è consentito */
        if (*s == ')' && *(s + 1))
            return (ret);
        unexpected(*s);  /* Altrimenti è un errore */
        destroy_tree(ret);
        return (NULL);
    }
    return (ret);
}

/*
** eval_tree()
** Valuta ricorsivamente l'albero sintattico
**
** Ritorna il risultato numerico dell'espressione
*/
int eval_tree(node *tree)
{
    switch (tree->type)
    {
        case ADD:
            return (eval_tree(tree->l) + eval_tree(tree->r));
        case MULTI:
            return (eval_tree(tree->l) * eval_tree(tree->r));
        case VAL:
            return (tree->val);
    }
    return (0);
}

/*
** main()
** Punto di ingresso del programma
**
** Flusso:
** 1. Verifica argomenti (deve essere esattamente 1: l'espressione)
** 2. Parsa l'espressione
** 3. Valuta l'albero
** 4. Stampa il risultato
** 5. Libera la memoria
**
** Esempio: ./vbc_2 "2+3*4"  →  14
** Esempio: ./vbc_2 "+5"     →  5 (unario +)
** Esempio: ./vbc_2 "*5"     →  0 (operatore * speciale)
*/
int main(int argc, char **argv)
{
    if (argc != 2)  /* Controlla numero di argomenti */
        return (1);
    node *tree = parse_expr(argv[1]);  /* Parsa l'espressione */
    if (!tree)  /* Errore di parsing */
        return (1);
    printf("%d\n", eval_tree(tree));  /* Valuta e stampa il risultato */
    destroy_tree(tree);  /* Libera la memoria */
    return (0);
}
