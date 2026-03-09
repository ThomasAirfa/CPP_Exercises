#pragma once

#include "./Base.hpp"
#include <string>

class DerivedString : public Base {
    public:
        DerivedString(std::string string) : _string { std::move(string) } {}
        
        std::string& data() {
            return _string;
        }

        bool is_null() const override {
            return _string.empty();
        }
    private:
        std::string _string;
};