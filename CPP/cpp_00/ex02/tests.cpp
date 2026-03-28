// ************************************************************************** //
//                                                                            //
//                tests.cpp for GlobalBanksters United                        //
//                Created on  : Thu Nov 20 23:45:02 1989                      //
//                Last update : Wed Jan 04 09:23:52 1992                      //
//                Made by : Brad "Buddy" McLane <bm@gbu.com>                  //
//                                                                            //
// ************************************************************************** //

// Include della libreria standard per usare std::vector (contenitore dinamico).
#include <vector>
// Include della libreria standard per algoritmi generici (qui usiamo std::for_each).
#include <algorithm>
// Include di utility funzionali (qui usiamo std::mem_fun_ref).
#include <functional>
// Include dell'header della classe Account da testare.
#include "Account.hpp"


// Punto di ingresso del programma:
// - int: tipo di ritorno (codice di uscita verso il sistema operativo)
// - main: funzione speciale avviata all'esecuzione
// - ( void ): in stile C/42 indica "nessun parametro"
int		main( void ) {

	// typedef crea un "alias" di tipo per evitare tipi troppo lunghi nel codice.
	// std::vector<Account::t> e' un vettore dinamico di oggetti Account.
	// Account::t e' a sua volta un alias di Account definito dentro la classe.
	typedef std::vector<Account::t>							  accounts_t;
	// Alias per un vettore di int.
	typedef std::vector<int>								  ints_t;
	// Alias per una coppia (std::pair) di iteratori:
	// - first  -> iteratore su accounts_t
	// - second -> iteratore su ints_t
	// Utile per avanzare in parallelo due sequenze.
	typedef std::pair<accounts_t::iterator, ints_t::iterator> acc_int_t;

	// Array C di int con i depositi iniziali.
	// "const" rende i valori non modificabili.
	int	const				amounts[]	= { 42, 54, 957, 432, 1234, 0, 754, 16576 };
	// Calcolo della dimensione dell'array:
	// sizeof(amounts) -> byte totali dell'array
	// sizeof(int)     -> byte di un elemento
	// divisione       -> numero elementi
	size_t const			amounts_size( sizeof(amounts) / sizeof(int) );
	// Costruzione del vector da range [first, last):
	// - first = amounts
	// - last  = amounts + amounts_size
	// In C++ il limite superiore e' escluso.
	accounts_t				accounts( amounts, amounts + amounts_size );
	// Iteratore al primo elemento del vector.
	accounts_t::iterator	acc_begin	= accounts.begin();
	// Iteratore "one past the end" (non dereferenziabile).
	accounts_t::iterator	acc_end		= accounts.end();

	// Array C con gli importi dei depositi da applicare.
	int	const			d[]			= { 5, 765, 564, 2, 87, 23, 9, 20 };
	// Numero elementi del vettore depositi.
	size_t const		d_size( sizeof(d) / sizeof(int) );
	// Vector costruito dal range dell'array d.
	ints_t				deposits( d, d + d_size );
	// Iteratori begin/end per scorrere deposits.
	ints_t::iterator	dep_begin	= deposits.begin();
	ints_t::iterator	dep_end		= deposits.end();

	// Array C con gli importi dei prelievi da tentare.
	int	const			w[]			= { 321, 34, 657, 4, 76, 275, 657, 7654 };
	// Numero elementi del vettore prelievi.
	size_t const		w_size( sizeof(w) / sizeof(int) );
	// Vector costruito dal range dell'array w.
	ints_t				withdrawals( w, w + w_size );
	// Iteratori begin/end per scorrere withdrawals.
	ints_t::iterator	wit_begin	= withdrawals.begin();
	ints_t::iterator	wit_end		= withdrawals.end();

	// Stampa statistiche aggregate iniziali di tutti gli account.
	Account::displayAccountsInfos();
	// std::for_each applica una funzione a ogni elemento del range [acc_begin, acc_end).
	// std::mem_fun_ref(&Account::displayStatus) trasforma il metodo membro
	// in un "callable" che puo' essere invocato su oggetti (per riferimento).
	std::for_each( acc_begin, acc_end, std::mem_fun_ref( &Account::displayStatus ) );

	// Ciclo for con inizializzazione "di tipo oggetto coppia".
	// acc_int_t it(acc_begin, dep_begin): it.first punta account corrente,
	// it.second punta deposito corrente.
	for ( acc_int_t it( acc_begin, dep_begin );
		  // Condizione: continua finche' nessuno dei due iteratori raggiunge end.
		  it.first != acc_end && it.second != dep_end;
		  // Incremento: avanza entrambi gli iteratori a ogni iterazione.
		  ++(it.first), ++(it.second) ) {

		// Dereferenziazione iteratore con * per ottenere l'oggetto puntato.
		// (*(it.first)).makeDeposit(...) equivale a it.first->makeDeposit(...).
		// *(it.second) e' l'importo di deposito corrente.
		(*(it.first)).makeDeposit( *(it.second) );
	}

	// Stampa stato aggregato dopo i depositi.
	Account::displayAccountsInfos();
	// Stampa stato dei singoli account dopo i depositi.
	std::for_each( acc_begin, acc_end, std::mem_fun_ref( &Account::displayStatus ) );

	// Stesso schema del ciclo precedente, ma sui prelievi.
	for ( acc_int_t it( acc_begin, wit_begin );
		  it.first != acc_end && it.second != wit_end;
		  ++(it.first), ++(it.second) ) {

		// Tenta il prelievo dell'importo corrente sul conto corrente.
		(*(it.first)).makeWithdrawal( *(it.second) );
	}

	// Stampa stato aggregato finale dopo i prelievi.
	Account::displayAccountsInfos();
	// Stampa stato finale di ogni account.
	std::for_each( acc_begin, acc_end, std::mem_fun_ref( &Account::displayStatus ) );

	// 0 indica terminazione avvenuta con successo.
	return 0;
}


// ************************************************************************** //
// vim: set ts=4 sw=4 tw=80 noexpandtab:                                      //
// -*- indent-tabs-mode:t;                                                   -*-
// -*- mode: c++-mode;                                                       -*-
// -*- fill-column: 75; comment-column: 75;                                  -*-
// ************************************************************************** //
