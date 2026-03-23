/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:07:44 by yel-moha          #+#    #+#             */
/*   Updated: 2026/03/23 16:40:14 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

int main(void)
{
    PhoneBook phonebook;

    while(1)
    {
        std::string choice;
        std::cout << "Type ADD to add a contact, SEARCH to search an existing one, "
                  << "EXIT to quit." << std::endl;
        std::cin >> choice;

        if (choice == "EXIT")
            break;
        else if (choice == "ADD")
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

            Contacts contact(first_name, last_name, nickname, phone_number, darkest_secret);
            phonebook.add_contact(contact);
            std::cout << "Contact added." << std::endl;
        }
        else if (choice == "SEARCH")
        {
            int index;

            std::cout << "Index (0-7): " << std::endl;
            std::cin >> index;
            phonebook.find_contact(index);
            std::cout << "Search done." << std::endl;
            phonebook.display_cntact(index); 
        }
        else
            std::cout << "Unknown command." << std::endl;
    }
    return (0);  
}