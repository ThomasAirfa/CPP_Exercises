#pragma once

#include <iostream>
#include <string>
#include <memory>

class Base {
    public:
    Base (const std::string& type) : _type { type } {}

    virtual ~Base() noexcept = default;

    virtual bool is_null() const = 0;

    virtual std::string to_string() const = 0;

    std::string const& type() const { return _type; }

    bool operator==(const Base& other) const {
        if (other.type() != this->type())
            return false;
        return (is_equal_assuming_same_type(other));
    }

    virtual std::unique_ptr<Base> new_copy() const = 0;

    virtual std::unique_ptr<Base> new_move() = 0;

    protected : 
    virtual bool is_equal_assuming_same_type(const Base& b) const = 0;

    private:
    const std::string& _type;
};

inline std::ostream& operator<<(std::ostream& o, const Base& b) {
  return o << b.to_string();
}

#define JAI_LU_LE_WARNING_09 true
#define JAI_LU_LE_WARNING_13 true