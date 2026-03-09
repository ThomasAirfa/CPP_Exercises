#pragma once

#include "./Base.hpp"

class DerivedInt : public Base {
    public:
        DerivedInt(int value) : _value { value } {}
        
        int data() {
            return _value;
        }

        bool is_null() const override {
            return _value == 0;
        }
    private:
        int _value; 
};