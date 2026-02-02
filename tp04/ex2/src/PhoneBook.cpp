#include "PhoneBook.hpp"
#include "PhoneBookEntry.hpp"

void PhoneBook::add_entry(const PhoneBookEntry& entry) {
    _entry.emplace_back(entry);
}

// const PhoneNumber* PhoneBook::get_entry(const std::string& name) {
//     auto ptr = nullptr;
//     for (auto entry : _entry) {
//         if (entry.get_name() == name) {
//             ptr = entry.get_number();
//         }
//     }
//     return ptr;
// }
