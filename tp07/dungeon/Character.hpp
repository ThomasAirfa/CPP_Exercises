#pragma once

#include "Entity.hpp"
#include "Logger.hpp"

class Character : public Entity {
    
    public:
    Character(int x, int y) : Entity(x, y), _name { next_name } {    
        if (next_name == 'Z') {
            next_name = 'A';
        } 
        else {
            next_name++;
        }
    logger << "Character " << _name << " was created in ( " << x << ", " << y << ")" << std::endl;
    };

    char get_representation() const override { return _name; }

    private:
        inline static char next_name = 'Z';
        char _name;
};