/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:33:53 by yel-moha          #+#    #+#             */
/*   Updated: 2026/03/23 17:22:45 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

PhoneBook::PhoneBook()
{
    this->next_index = 0;
}

void PhoneBook::add_contact(Contacts contact)
{
    this->contacts[this->next_index] = contact;
    this->next_index = (this->next_index + 1) % 8;
}

Contacts PhoneBook::find_contact(int index)
{
    if (index < 0 || index > 7)
    {
        std::cerr << "Index non valido: deve essere tra 0 e 7" << std::endl;
        return (Contacts());
    }
    return (this->contacts[index]);
}

void    PhoneBook::display_cntact(int index)
{
    Contacts contact;

    contact = this->find_contact(index);
    /*
    std::cout   << std::setw(10) << "|index  | " 
                << std::setw(10) << "first_name"
                << std::setw(10) << "|last_name" 
                << std::setw(10) << "|nickname|"
                << std::endl;
                */
    std::cout   << std::setw(10)<< index << " | " 
                << std::setw(10) << contact.get_first_name() << " | "
                << std::setw(10) << contact.get_last_name() << " | " 
                << std::setw(10) << contact.get_nickname()
                << std::endl;
}

PhoneBook::~PhoneBook()
{
}