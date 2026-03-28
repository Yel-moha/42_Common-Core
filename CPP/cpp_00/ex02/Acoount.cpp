/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Acoount.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 14:01:32 by yel-moha          #+#    #+#             */
/*   Updated: 2026/03/28 15:15:31 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>


Account::Account( int initial_deposit)
{
    _amount = initial_deposit;
}
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