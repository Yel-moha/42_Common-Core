// ************************************************************************** //
//                                                                            //
//                Account.hpp for GlobalBanksters United                //
//                Created on  : Thu Nov 20 19:43:15 1989                      //
//                Last update : Wed Jan 04 14:54:06 1992                      //
//                Made by : Brad "Buddy" McLane <bm@gbu.com>                  //
//                                                                            //
// ************************************************************************** //

// Questo file e' l'header della classe Account.
// Un header contiene la "dichiarazione" della classe: quali metodi e campi esistono.
// Le "definizioni" (implementazione vera dei metodi) stanno di solito nel file .cpp.


// pragma once evita inclusioni multiple dello stesso header nello stesso translation unit.
#pragma once
// Anche questa coppia e' una include guard classica.
// Avere sia pragma once sia include guard e' ridondante ma non sbagliato.
#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

// ************************************************************************** //
//                               Account Class                                //
// ************************************************************************** //

class Account {


public:

	// typedef interno alla classe:
	// Account::t diventa un alias di Account.
	// Perche' utile? In codice generico o vecchio stile puoi scrivere Account::t
	// invece di ripetere Account. Nel tests.cpp infatti trovi std::vector<Account::t>.
	typedef Account		t;

	// -------------------- METODI STATIC --------------------
	// static significa che il metodo appartiene alla CLASSE, non al singolo oggetto.
	// Si chiamano cosi': Account::getNbAccounts();
	// Non hanno il puntatore implicito this.
	// Quindi dentro questi metodi puoi accedere direttamente solo a campi static.
	static int	getNbAccounts( void );
	static int	getTotalAmount( void );
	static int	getNbDeposits( void );
	static int	getNbWithdrawals( void );
	static void	displayAccountsInfos( void );

	// Costruttore: chiamato quando crei un nuovo Account.
	// Riceve il deposito iniziale del conto.
	Account( int initial_deposit );
	// Distruttore: chiamato quando l'oggetto viene distrutto (esce dallo scope,
	// fine programma, erase su container, ecc.).
	~Account( void );

	// -------------------- METODI NON STATIC --------------------
	// Questi metodi operano su un singolo account (un singolo oggetto).
	// Hanno accesso a this, cioe' all'istanza corrente.
	void	makeDeposit( int deposit );
	bool	makeWithdrawal( int withdrawal );
	// const in fondo significa: questo metodo non modifica lo stato dell'oggetto.
	// Dentro un metodo const non puoi cambiare campi non-mutable.
	int		checkAmount( void ) const;
	void	displayStatus( void ) const;


private:

	// -------------------- CAMPI STATIC --------------------
	// Esiste UNA SOLA copia per tutta la classe, condivisa da tutti gli oggetti.
	// Esempio: _nbAccounts e' il numero totale di account esistenti, non di uno solo.
	// Questi campi vanno dichiarati qui e definiti una volta nel .cpp.
	static int	_nbAccounts;
	static int	_totalAmount;
	static int	_totalNbDeposits;
	static int	_totalNbWithdrawals;

	// Metodo helper static per stampare il timestamp.
	// E' static perche' non dipende da un account specifico.
	static void	_displayTimestamp( void );

	// -------------------- CAMPI NON STATIC --------------------
	// Ogni oggetto Account ha la sua copia personale di questi campi.
	// Se crei 8 account, avrai 8 _amount distinti, 8 _nbDeposits distinti, ecc.
	int				_accountIndex;
	int				_amount;
	int				_nbDeposits;
	int				_nbWithdrawals;

	// Costruttore di default dichiarato private:
	// impedisce di creare Account senza deposito iniziale dall'esterno.
	// Esempio bloccato: Account a; (se questo costruttore resta private)
	Account( void );

};



// ************************************************************************** //
// vim: set ts=4 sw=4 tw=80 noexpandtab:                                      //
// -*- indent-tabs-mode:t;                                                   -*-
// -*- mode: c++-mode;                                                       -*-
// -*- fill-column: 75; comment-column: 75;                                  -*-
// ************************************************************************** //


#endif /* __ACCOUNT_H__ */
