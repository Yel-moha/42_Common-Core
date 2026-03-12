/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:33:44 by yel-moha          #+#    #+#             */
/*   Updated: 2026/03/12 18:11:03 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONE_BOOK_HPP
# define PHONE_BOOK_HPP

#include <iostream>
#include "contacts.hpp"

class   PhoneBook
{
    public:
        PhoneBook();
        ~PhoneBook();
        //int get_index(const Contacts &contact);
        Contacts contact[8];
    
    private:
};

#endif