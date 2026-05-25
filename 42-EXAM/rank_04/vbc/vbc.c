#include "vbc.h"

/*
** new_node()
** Crea un nuovo nodo allocando memoria dinamica
** Ritorna un puntatore al nuovo nodo, o NULL se l'allocazione fallisce
*/
node    *new_node(node n)
{
	/* Alloca memoria per un nuovo nodo (calloc inizializza tutto a 0) */
	node *ret = calloc(1, sizeof(n));
	if (!ret)
		return (NULL);
	/* Copia il contenuto della struttura nel nuovo nodo */
	*ret = n;
	return (ret);
}

/*
** destroy_tree()
** Libera ricorsivamente tutta la memoria allocata dall'albero
** IMPORTANTE: se il nodo è una foglia (VAL), non ha figli quindi non ricorre
*/
void    destroy_tree(node *n)
{
	if (!n)  /* Base case: nodo NULL */
		return ;
	/* Se non è una foglia, libera ricorsivamente i figli */
	if (n->type != VAL)
	{
		destroy_tree(n->l);  /* Libera il sottoalbero sinistro */
		destroy_tree(n->r);  /* Libera il sottoalbero destro */
	}
	free(n);  /* Libera il nodo stesso */
}

/*
** unexpected()
** Stampa un messaggio di errore per un token non previsto
** Se c == '\0' significa fine input prematura
*/
void    unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n");
}

/*
** accept()
** Tenta di consumare il carattere c dalla stringa
** Se il carattere corrente è c:
**   - Avanza il puntatore (**s)++
**   - Ritorna 1 (successo)
** Altrimenti ritorna 0 (il carattere non corrisponde)
**
** Uso: usato nelle alternative opzionali (es: accetta + se presente)
*/
int accept(char **s, char c)
{
	if (**s == c)
	{
		(*s)++;  /* Avanza il puntatore al prossimo carattere */
		return (1);
	}
	return (0);
}

/*
** expect()
** Richiede obbligatoriamente il carattere c
** Se presente: accetta e ritorna 1
** Se assente: stampa errore e ritorna 0
**
** Uso: usato per caratteri obbligatori (es: ) dopo un'espressione in parentesi)
*/
int expect(char **s, char c)
{
	if (accept(s, c))
		return (1);
	unexpected(**s);
	return (0);
}

/*
** parse_num_parenthesis()
** Parsa il livello BASSO della gerarchia di precedenza: numeri singoli e parentesi
**
** Grammatica BNF:
**   num_or_paren = "(" addition ")" | DIGIT
**
** Casi:
** 1. Se il carattere è '(': ricorre su parse_addition(), poi richiede ')'
** 2. Se è una cifra: crea un nodo VAL con il valore numerico
** 3. Altrimenti: errore (token inaspettato)
**
** Ritorna: il nodo creato, o NULL in caso di errore
*/
node *parse_num_parenthesis(char **s)
{
	/* Caso 1: espressione tra parentesi */
	if(accept(s, '('))
	{
		/* Ricorre per parsare l'espressione dentro le parentesi */
		node *n = parse_addition(s);
		if(!expect(s, ')'))  /* Verifica che le parentesi siano bilanciate */
		{
			destroy_tree(n);  /* Libera l'albero in caso di errore */
			return (NULL);
		}
		return (n);
	}
	/* Caso 2: numero singolo (cifra) */
	if(isdigit(**s))
	{
		/* Crea un nodo foglia con il valore numerico (converte char a int) */
		node n = {VAL, **s - '0', NULL, NULL};
		(*s)++;  /* Avanza al prossimo carattere */
		return(new_node(n));
	}
	/* Caso 3: carattere non valido */
	unexpected(**s);
	return (NULL);
}

/*
** parse_multiplication()
** Parsa il livello INTERMEDIO della gerarchia di precedenza: moltiplicazioni
**
** Grammatica BNF:
**   multiplication = num_or_paren ("*" num_or_paren)*
**
** Algoritmo (left-associative):
** 1. Parsa il primo operando a sinistra
** 2. Finché c'è un "*":
**    - Parsa l'operando destro
**    - Crea un nodo MULTI con (left * right)
**    - Aggiorna left al nuovo nodo creato
**
** Questo crea un albero left-associative: ((2*3)*4) non (2*(3*4))
**
** Ritorna: l'albero di moltiplicazione, o NULL in caso di errore
*/
node *parse_multiplication(char **s)
{
	node *left = parse_num_parenthesis(s);  /* Parsa il primo fattore */
	while(accept(s, '*'))  /* Finché ci sono moltiplicazioni */
	{
		node *right = parse_num_parenthesis(s);  /* Parsa il prossimo fattore */
		if(!right)  /* Errore se il fattore destro manca */
		{
			destroy_tree(left);
			return (NULL);
		}
		/* Crea il nodo di moltiplicazione con i due fattori */
		node n = {MULTI, 0, left, right};
		left = new_node(n);  /* Aggiorna left per la prossima iterazione */
	}
	return (left);
}

/*
** parse_addition()
** Parsa il livello TOP della gerarchia di precedenza: addizioni
**
** Grammatica BNF:
**   addition = multiplication ("+" multiplication)*
**
** Algoritmo (left-associative):
** 1. Parsa il primo operando a sinistra con parse_multiplication()
** 2. Finché c'è un "+":
**    - Parsa l'operando destro con parse_multiplication()
**    - Crea un nodo ADD con (left + right)
**    - Aggiorna left al nuovo nodo creato
**
** Questo crea un albero left-associative: ((2+3)+4) non (2+(3+4))
**
** IMPORTANTE: parse_multiplication() è chiamato, non parse_num_parenthesis(),
** perché garantisce che la moltiplicazione abbia priorità più alta dell'addizione.
** Esempio: "2+3*4" parsa come "2+(3*4)" = 14, non "(2+3)*4" = 20
**
** Ritorna: l'albero di addizione, o NULL in caso di errore
*/
node *parse_addition(char **s)
{
	node *left = parse_multiplication(s);  /* Parsa il primo addendo (che potrebbe contenere moltiplicazioni) */
	while(accept(s, '+'))  /* Finché ci sono addizioni */
	{
		node *right = parse_multiplication(s);  /* Parsa il prossimo addendo */
		if(!right)  /* Errore se l'addendo destro manca */
		{
			destroy_tree(left);
			return(NULL);
		}
		/* Crea il nodo di addizione con i due addendi */
		node n = {ADD, 0, left, right};
		left = new_node(n);  /* Aggiorna left per la prossima iterazione */
	}
	return (left);
}

/*
** eval_tree()
** Valuta ricorsivamente l'albero di parsing e ritorna il risultato numerico
**
** Casi:
** - ADD:   ritorna left + right (somma i risultati dei figli)
** - MULTI: ritorna left * right (moltiplica i risultati dei figli)
** - VAL:   ritorna il valore numerico del nodo
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
** Uso: ./vbc "espressione_matematica"
**
** Flusso:
** 1. Verifica che sia stata passata esattamente 1 riga di comando (l'espressione)
** 2. Parsa l'espressione creando un albero sintattico
** 3. Valuta l'albero per ottenere il risultato
** 4. Stampa il risultato
** 5. Libera la memoria
**
** Esempio: ./vbc "2+3*4"  →  14
** Esempio: ./vbc "(1+2)*3"  →  9
*/
int main(int argc, char **argv)
{
	if (argc != 2)  /* Controlla che ci sia esattamente 1 argomento */
		return (1);
	char *input = argv[1];  /* Puntatore alla stringa di input */
	node *tree = parse_addition(&input);  /* Parsa e crea l'albero */
	if (!tree)  /* Se il parsing fallisce, ritorna errore */
		return (1);
	else if(*input)  /* Se non abbiamo consumato tutta la stringa, errore */
	{
		unexpected(*input);  /* Stampa errore con il carattere non consumato */
		destroy_tree(tree);  /* Libera l'albero creato */
		return (1);
	}
	printf("%d\n", eval_tree(tree));  /* Valuta l'albero e stampa il risultato */
	destroy_tree(tree);  /* Libera la memoria allocata */
	return (0);
}
