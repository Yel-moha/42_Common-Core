/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 14:08:47 by yel-moha          #+#    #+#             */
/*   Updated: 2026/03/28 15:14:33 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"

int main(void)
{
    int const amounts[8] = {42, 54, 957, 432, 1234, 0, 754, 16576};
    int const deposits[8] = {5, 765, 564, 2, 87, 23, 9, 20};
    int const withdrawals[8] = {321, 34, 657, 4, 76, 275, 657, 7654};

    Account accounts[8] = {
        Account(amounts[0]), Account(amounts[1]), Account(amounts[2]), Account(amounts[3]),
        Account(amounts[4]), Account(amounts[5]), Account(amounts[6]), Account(amounts[7])};

    Account::displayAccountsInfos();
    for (int i = 0; i < 8; ++i)
        accounts[i].displayStatus();

    for (int i = 0; i < 8; ++i)
        accounts[i].makeDeposit(deposits[i]);

    Account::displayAccountsInfos();
    for (int i = 0; i < 8; ++i)
        accounts[i].displayStatus();

    for (int i = 0; i < 8; ++i)
        accounts[i].makeWithdrawal(withdrawals[i]);

    Account::displayAccountsInfos();
    for (int i = 0; i < 8; ++i)
        accounts[i].displayStatus();

    return 0;
}