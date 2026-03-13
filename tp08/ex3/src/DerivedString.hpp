#pragma once

#include "./Base.hpp"
#include <string>
#include <memory>

class DerivedString : public Base {
    public:
        DerivedString(std::string string) : Base {DerivedString::_type }, _string { std::move(string) } {}
        
        std::string& data() {
            return _string;
        }

        bool is_null() const override {
            return _string.empty();
        }

        std::string to_string() const override {
            return  _string;
        }

        std::unique_ptr<Base> new_copy() const override { 
            return std::make_unique<DerivedString>(*this); 
        }

        std::unique_ptr<Base> new_move() override {
        return std::make_unique<DerivedString>(std::move(*this));
        }

    protected : 
        bool is_equal_assuming_same_type(const Base& other) const override {
            return (dynamic_cast<const DerivedString&>(other)._string == _string);
        }

    private:
        std::string _string;
        static inline const std::string _type = "String";
};