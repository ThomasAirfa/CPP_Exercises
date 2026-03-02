#pragma once

#include "Item.hpp"
#include "Logger.hpp"

class Trap : public Item {
    public: 
    Trap(int width, int height) : 
    Item(width, height) {
        logger << "Trap set at ( " << get_x() << ", " << get_y() << ")" << std::endl;
    }

    char get_representation() const override { return '#'; };

    private : 
};