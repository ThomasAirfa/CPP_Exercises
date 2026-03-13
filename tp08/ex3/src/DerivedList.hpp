#pragma once

#include "Base.hpp"
#include <memory>
#include <sstream>
#include <string>
#include <vector>


class DerivedList : public Base {
    public:
    DerivedList() : Base(DerivedList::_type) {}

    DerivedList(const DerivedList& other) : DerivedList() {
        for (auto& e : other._data)
        add(*e);
    }

    DerivedList(DerivedList&& other) : Base(DerivedList::_type), _data(std::move(other._data)) {}

    bool is_null() const override {
        return _data.empty();
    }

    std::string to_string() const override {
        std::stringstream result;
        result << "[";
        bool first = true;
        for (auto& element : _data) {
        if (first)
            first = false;
        else
            result << ",";
        result << element->to_string();
        }
        result << "]";
        return result.str();
    }

    void add(const Base& element) { 
        _data.push_back(element.new_copy()); 
    }

    std::unique_ptr<Base> new_copy() const override { 
        return std::make_unique<DerivedList>(*this); 
    }

    void add(Base&& element) {
        _data.push_back(element.new_move());
    }

    std::unique_ptr<Base> new_move() override {
        return std::make_unique<DerivedList>(std::move(*this));
    }

    protected:
    bool is_equal_assuming_same_type(const Base& b) const override {
        const DerivedList& other = dynamic_cast<const DerivedList&>(b);
        if (other._data.size() != _data.size())
        return false;
        for (unsigned i = 0; i < _data.size(); ++i)
        if (!(*(other._data[i]) == *(_data[i])))
            return false;
        return true;
    }

    private :
      std::vector<std::unique_ptr<Base>> _data;
      static inline const std::string _type = "List";

};