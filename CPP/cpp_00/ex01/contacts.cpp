/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contacts.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:00:31 by yel-moha          #+#    #+#             */
/*   Updated: 2026/03/23 17:05:08 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "contacts.hpp"

Contacts::Contacts()
{
}

Contacts::Contacts(std::string first_name, std::string last_name, \
        std::string nickname, std::string phone_number, std::string \
        darkest_secret)
{
    this->first_name = first_name;
    this->last_name = last_name;
    this->nickname = nickname;
    this->phone_number = phone_number;
    this->darkest_secret = darkest_secret;      
}

Contacts::~Contacts()
{
}

std::string Contacts::get_first_name() const
{
    if (this->first_name.length() > 10)
        return this->first_name.substr(0, 9) + ".";
    return this->first_name;
}

std::string Contacts::get_last_name() const
{
    if(this->last_name.length() > 10)
        return this->first_name.substr(0, 9) + ".";
    return (this->last_name);
}

std::string Contacts::get_nickname() const
{
    if(this->nickname.length() > 10)
        return this->nickname.substr(0, 9) + ".";
    return (this->nickname);
}

