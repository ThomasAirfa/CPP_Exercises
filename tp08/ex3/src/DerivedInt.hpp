#pragma once

#include "./Base.hpp"
#include <memory>
#include <sstream>

class DerivedInt : public Base {
    public:
        DerivedInt(int value) : Base { DerivedInt::_type }, _value { value } {}
        
        int data() {
            return _value;
        }

        bool is_null() const override {
            return _value == 0;
        }

        std::string to_string() const override {
            std::stringstream ss;
            ss << _value;
            return ss.str();
        }
        
        std::unique_ptr<Base> new_copy() const override { 
            return std::make_unique<DerivedInt>(*this); 
        }

        std::unique_ptr<Base> new_move() override {
          return std::make_unique<DerivedInt>(std::move(*this));
        }

    protected : 
        bool is_equal_assuming_same_type(const Base& other) const override {
            return (dynamic_cast<const DerivedInt&>(other)._value == _value);
        }

    private:
        int _value;
        static inline const std::string _type = "Int";
};