
/*
** VBC - Virtual Basic Calculator
** Un semplice calcolatore che parsa e valuta espressioni matematiche
** Utilizza un parser ricorsivo discendente per rispettare la precedenza degli operatori
*/

#ifndef VBC_H
# define VBC_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
** STRUTTURA DATI PRINCIPALE: node
** Rappresenta un nodo dell'albero binario di parsing (AST - Abstract Syntax Tree)
**
** type:
**   - ADD:   nodo di addizione (somma i due figli)
**   - MULTI: nodo di moltiplicazione (moltiplica i due figli)
**   - VAL:   nodo foglia che contiene un valore numerico
**
** val:  il valore numerico (usato solo quando type == VAL)
** l:    puntatore al figlio sinistro (operando sinistro dell'operazione)
** r:    puntatore al figlio destro (operando destro dell'operazione)
**
** Esempio per l'espressione "2+3*4":
**        +
**       / \
**      2   *
**         / \
**        3   4
*/
typedef struct node {
    enum {
        ADD,        /* Addizione: somma */
        MULTI,      /* Moltiplicazione: prodotto */
        VAL         /* Valore: numero singolo */
    }   type;
    int val;        /* Valore numerico (solo per VAL) */
    struct node *l; /* Puntatore figlio sinistro */
    struct node *r; /* Puntatore figlio destro */
}   node;

/*
** FUNZIONI DI PARSING RICORSIVO DISCENDENTE
** Seguono la gerarchia di precedenza:
** 1. parse_addition() - livello top (precedenza bassa per +)
** 2. parse_multiplication() - livello intermedio (precedenza alta per *)
** 3. parse_num_parenthesis() - livello basso (numeri e parentesi)
*/

/* Parsa espressioni con addizione (es: "2+3+4") - precedenza BASSA */
node *parse_addition(char **s);

/* Parsa espressioni con moltiplicazione (es: "2*3*4") - precedenza ALTA */
node *parse_multiplication(char **s);

/* Parsa numeri singoli (0-9) o espressioni tra parentesi */
node *parse_num_parenthesis(char **s);

/*
** FUNZIONI AUSILIARIE DI PARSING
*/

/* Accetta il carattere c se presente, avanza il puntatore e ritorna 1, altrimenti ritorna 0 */
int accept(char **s, char c);

/* Richiede obbligatoriamente il carattere c, ritorna 1 se trovato, altrimenti errore */
int expect(char **s, char c);

/* Stampa un messaggio di errore per un token inaspettato */
void    unexpected(char c);

/*
** FUNZIONI DI GESTIONE DELL'ALBERO
*/

/* Alloca memoria e crea un nuovo nodo */
node    *new_node(node n);

/* Libera ricorsivamente tutta la memoria dell'albero */
void    destroy_tree(node *n);

/* Valuta ricorsivamente l'albero e ritorna il risultato numerico */
int eval_tree(node *tree);

#endif