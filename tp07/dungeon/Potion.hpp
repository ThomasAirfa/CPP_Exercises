#pragma once

#include "Item.hpp"
#include "Logger.hpp"

class Potion : public Item {
    public: 
    Potion(int width, int height) : 
    Item(width, height) {
        logger << "Potion set at ( " << get_x() << ", " << get_y() << ")" << std::endl;
    }

    char get_representation() const override { return '+'; };
    
    private : 
};