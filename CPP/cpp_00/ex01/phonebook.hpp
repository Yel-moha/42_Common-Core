/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:33:44 by yel-moha          #+#    #+#             */
/*   Updated: 2026/03/24 16:03:36 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONE_BOOK_HPP
# define PHONE_BOOK_HPP

#include <iostream>

#include <iomanip> // da verificare se possiamo usarla per setw()

#include "contacts.hpp"

class   PhoneBook
{
    public:
        PhoneBook();
        Contacts    find_contact(int index);
        void    add_contact();
        void    display_cntact(int index);
        void    list_contacts();
        ~PhoneBook();
        
    private:
        void    store_contact(Contacts contact);
        Contacts contacts[8];
        int      next_index;
        int      contact_count;
};

#endif