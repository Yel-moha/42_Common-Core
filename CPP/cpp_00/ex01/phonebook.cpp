/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:33:53 by yel-moha          #+#    #+#             */
/*   Updated: 2026/03/24 16:05:22 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

PhoneBook::PhoneBook()
{
    this->next_index = 0;
    this->contact_count = 0;
}

void PhoneBook::add_contact()
{
    std::string first_name;
    std::string last_name;
    std::string nickname;
    std::string phone_number;
    std::string darkest_secret;

    std::cout << "Write the first name" << std::endl;
    std::cin >> first_name;
    std::cout << "Write the last name" << std::endl;
    std::cin >> last_name;
    std::cout << "Write the nickname" << std::endl;
    std::cin >> nickname;
    std::cout << "Write the phone number" << std::endl;
    std::cin >> phone_number;
    std::cout << "Write the darkest secret" << std::endl;
    std::cin >> darkest_secret;
    this->store_contact(Contacts(first_name, last_name, nickname, phone_number, darkest_secret));
}

void PhoneBook::store_contact(Contacts contact)
{
    this->contacts[this->next_index] = contact;
    this->next_index = (this->next_index + 1) % 8;
    if (this->contact_count < 8)
        this->contact_count++;
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
    if (index < 0 || index > 7)
    {
        std::cout << "Index non valido: deve essere tra 0 e 7" << std::endl;
        return ;
    }
    if (this->contacts[index].get_first_name().empty())
    {
        std::cout << "Contatto non presente." << std::endl;
        return ;
    }
    this->contacts[index].print_contact();
}
void PhoneBook::list_contacts()
{
    int i;

    std::cout << std::setw(10) << "index" << "|"
              << std::setw(10) << "first name" << "|"
              << std::setw(10) << "last name" << "|"
              << std::setw(10) << "nickname" << std::endl;
    i = 0;
    while (i < 8)
    {
        if (!this->contacts[i].get_first_name().empty())
        {
            std::cout << std::setw(10) << i << "|"
                      << std::setw(10) << this->contacts[i].get_first_name() << "|"
                      << std::setw(10) << this->contacts[i].get_last_name() << "|"
                      << std::setw(10) << this->contacts[i].get_nickname() << std::endl;
        }
        i++;
    }
}

PhoneBook::~PhoneBook()
{
}