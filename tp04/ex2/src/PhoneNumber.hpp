#pragma once

#include <vector>
#include <iostream>

class PhoneNumber {
    public : 
    PhoneNumber(int x1, int x2, int x3, int x4, int x5);
    bool is_valid() const;
    friend std::ostream& operator<<(std::ostream& ostream, const PhoneNumber _phone_number);
    int operator[](int index) const;
    
    private : 
    std::vector<int> _phone_number;
};