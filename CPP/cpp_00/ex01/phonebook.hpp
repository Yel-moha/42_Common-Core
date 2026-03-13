/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:33:44 by yel-moha          #+#    #+#             */
/*   Updated: 2026/03/13 16:27:57 by yel-moha         ###   ########.fr       */
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
        PhoneBook(Contacts Contact, int index);
        ~PhoneBook();
        //int get_index(const Contacts &contact);
        
    private:
        Contacts contacts[8];
};

#endif