#pragma once
#include <string>
#include <memory>
#include "../lib/Tracker.hpp"

class StringInstancePair {
public:
    StringInstancePair(std::string string)
        : _string { std::move(string) }, _tracker { new Tracker {} } {}

    StringInstancePair(const StringInstancePair& other)
        : _string { other._string },
          _tracker { new Tracker { *other._tracker } }  
    {}

    StringInstancePair(StringInstancePair&& other) 
        : _string { std::move(other._string) },
          _tracker { std::move(other._tracker) }
    {}

    const std::string& get_str() const {
        return _string;
    }

    const Tracker& get_tracker() const {
        return *_tracker;
    }

private:
    std::string _string;
    std::unique_ptr<Tracker> _tracker;
};