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
#include <iostream>

int main(void)
{
    int init_ammounts[8] = {42, 54, 957, 432, 1234, 0, 754, 16576};
    Account accounts[8] = {
        Account(init_ammounts[0]), Account(init_ammounts[1]), Account(init_ammounts[2]),
        Account(init_ammounts[3]), Account(init_ammounts[4]), Account(init_ammounts[5]),
        Account(init_ammounts[6]), Account(init_ammounts[7])
    };  
    for(int i = 0; i < 8; i++)
    {
        
    }
}