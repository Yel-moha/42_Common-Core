/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 14:01:32 by yel-moha          #+#    #+#             */
/*   Updated: 2026/03/28 17:18:21 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;
    
    /*
    _accountIndex = 0;
	_amount = 0 ;
	_nbDeposits = 0;
	_nbWithdrawals = 0;
    */
    
Account::Account( int initial_deposit)
{
    _accountIndex = _nbAccounts;
    ++_nbAccounts;
    
    _amount = initial_deposit;
    _nbDeposits = 0;
    _nbWithdrawals = 0;

    _totalAmount += initial_deposit;
}

Account::Account( void )
{
    _accountIndex = _nbAccounts;
    ++_nbAccounts;
    _amount = 0;
    _nbDeposits = 0;
    _nbWithdrawals = 0;
}

int		Account::checkAmount( void ) const
{
    return _amount;
}
int Account::getNbAccounts(void)
{
    return _nbAccounts;
}

int	Account::getTotalAmount( void )
{
    return _totalAmount;
}

int Account::getNbDeposits( void )
{
    return _totalNbDeposits;
}

int	Account::getNbWithdrawals( void )
{
    return _totalNbWithdrawals;
}

void	Account::displayAccountsInfos( void )
{
    _displayTimestamp();
    std::cout << " accounts:" << _nbAccounts
              << ";total:" << _totalAmount
              << ";deposits:" << _totalNbDeposits
              << ";withdrawals:" << _totalNbWithdrawals
              << std::endl;
}

////////////////////////////////////////////////////////////////////

void	Account::makeDeposit( int deposit )
{
    _amount += deposit;
    ++_nbDeposits;

    _totalAmount += deposit;
    ++_totalNbDeposits;
}
bool Account::makeWithdrawal( int withdrawal )
{
    if(withdrawal > _amount)
        return false;
    _amount -= withdrawal;
    ++_nbWithdrawals;

    _totalAmount -= withdrawal;
    ++_totalNbWithdrawals;
    return true;
}
////////////////////////////////////////////////////////////////////
void	Account::displayStatus( void ) const
{  
    _displayTimestamp();
    std::cout << " index:" << _accountIndex
              << ";amount:" << _amount
              << ";deposits:" << _nbDeposits
              << ";withdrawals:" << _nbWithdrawals
              << std::endl;
}

void Account::_displayTimestamp( void )
{
    std::time_t now = std::time(NULL);
    std::tm *lt = std::localtime(&now);

    std::cout
        << "["
        << (lt->tm_year + 1900)
        << std::setw(2) << std::setfill('0') << (lt->tm_mon + 1)
        << std::setw(2) << std::setfill('0') << lt->tm_mday
        << "_"
        << std::setw(2) << std::setfill('0') << lt->tm_hour
        << std::setw(2) << std::setfill('0') << lt->tm_min
        << std::setw(2) << std::setfill('0') << lt->tm_sec
        << "]";
}
Account::~Account(void) {
    _nbAccounts--;
}