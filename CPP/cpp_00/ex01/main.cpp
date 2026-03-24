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
            phonebook.add_contact();
            std::cout << "Contact added." << std::endl;
        }
        else if (choice == "SEARCH")
        {
            int index;

            phonebook.list_contacts();
            std::cout << "Index (0-7): " << std::endl;
            std::cin >> index;
            phonebook.display_cntact(index); 
        }
        else
            std::cout << "Unknown command." << std::endl;
    }
    return (0);  
}