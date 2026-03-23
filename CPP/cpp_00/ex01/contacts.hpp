/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contacts.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 17:35:18 by yel-moha          #+#    #+#             */
/*   Updated: 2026/03/23 16:15:16 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACTS_HPP
# define CONTACTS_HPP

#include <iostream>
#include <string>

class   Contacts
{
    public:
        Contacts();
        Contacts(std::string first_name, std::string last_name, \
        std::string nickname, std::string phone_number, std::string darkest_secret);
        ~Contacts();
        std::string get_first_name() const;
        std::string get_last_name() const;
        std::string get_nickname() const;
    private:
        std::string first_name;
        std::string last_name;
        std::string nickname;
        std::string phone_number;
        std::string darkest_secret;
};

#endif