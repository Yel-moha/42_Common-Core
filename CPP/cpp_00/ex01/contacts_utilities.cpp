/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contacts_utilities.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 16:32:51 by yel-moha          #+#    #+#             */
/*   Updated: 2026/03/24 14:46:29 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

Contacts add_contact(std::string first_name, std::string last_name, \
                    std::string nickname, std::string phone_number, \
                    std::string darkest_secret)
{
        Contacts contact; //La classe che vorrei ritornare 
        
        std::string first_name;
        std::string last_name;
        std::string nickname;
        std::string phone_number;
        std::string darkest_secret;

        std::cout << "Write the first name" << std::endl;
        std::cin >> first_name; //usare getline perche prende spazi
        std::cout << "Write the last name" << std::endl;
        std::cin >> last_name;
        std::cout << "Write the nickname" << std::endl;
        std::cin >> nickname;
        std::cout << "Write the phone_number" << std::endl;
        std::cin >> phone_number;
        std::cout << "Write the darkest secrte" << std::endl;
        std::cin >> darkest_secret;

        Contacts Contacts(first_name, last_name, nickname, phone_number, darkest_secret);
}

