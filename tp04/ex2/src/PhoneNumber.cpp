#include "PhoneNumber.hpp"

PhoneNumber::PhoneNumber(int x1, int x2, int x3, int x4, int x5) {
    _phone_number = std::vector<int> {x1, x2, x3, x4, x5};
}

bool PhoneNumber::is_valid() const {
    for (auto number : _phone_number) {
        if (number < 0 || number > 99) {
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& ostream, const PhoneNumber phoneNumber) {
    for (auto number : phoneNumber._phone_number) {
        if (number <= 9) {
            ostream << 0 << number;
        }
        else {
        ostream << number;
        }
    }
    return ostream;
}

int PhoneNumber::operator[](int index) const {
    if (index < 0 || index > _phone_number.size() - 1) {
        return -1;
    }
    return _phone_number[index];
}