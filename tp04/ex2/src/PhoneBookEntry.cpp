#include "PhoneBookEntry.hpp"
#include "PhoneNumber.hpp"

const std::string& PhoneBookEntry::get_name() const {
    return _name;
}

const PhoneNumber& PhoneBookEntry::get_number() const {
    return _number;
}