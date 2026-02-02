#pragma once

#include "PhoneBookEntry.hpp"
#include "PhoneNumber.hpp"
#include <vector>

class PhoneBook {
    public :
    void add_entry(const PhoneBookEntry& entry);
    const PhoneNumber* get_entry(const std::string& name);

    private :
    std::vector<PhoneBookEntry> _entry;
};