#pragma once
#include <iostream>
#include <vector>

enum class Color {
    COEUR,
    CARREAU,
    PIQUE,
    TREFLE
};

enum class Value {
    SEPT,
    HUIT,
    NEUF,
    DIX,
    VALET,
    DAME,
    ROI,
    AS,
};

extern std::vector<Color> all_colors;
extern std::vector<Value> all_values;

std::ostream& operator<<(std::ostream& ostream, Color color);
std::ostream& operator<<(std::ostream& ostream, Value value); 

class Card {
    public :
        Card(Color color, Value value);
        void print() const;
        bool operator==(const Card& other) const;
        bool operator<(const Card& other) const;
    private : 
    Value _value;
    Color _color;
};
