#pragma once

#include "PhoneNumber.hpp"
#include <string>

class PhoneBookEntry {
    public :
    PhoneBookEntry(std::string name, const PhoneNumber& phoneNumber)
    : _name {name}, _number {phoneNumber} {}
    const std::string& get_name() const;
    const PhoneNumber& get_number() const;

    private :
    std::string _name;
    PhoneNumber _number;
};