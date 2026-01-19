#include "Card.hpp"
#include <vector>

std::vector<Color> all_colors = {Color::CARREAU, Color::COEUR, Color::PIQUE, Color::TREFLE};
std::vector<Value> all_values = {Value::AS, Value::ROI, Value::DAME, Value::VALET, Value::DIX, Value::NEUF, Value::HUIT, Value::SEPT};

Card::Card(Color color, Value value) {
    _color = color;
    _value = value;
}

std::ostream& operator<<(std::ostream& ostream, Color color) {
    switch (color) {
        case Color::COEUR : ostream << "Coeur"; break;
        case Color::CARREAU : ostream << "Carreau"; break;
        case Color::PIQUE : ostream << "Pic"; break;
        case Color::TREFLE : ostream << "Trèfle"; break;
    }
    return ostream;
}

std::ostream& operator<<(std::ostream& ostream, Value value) {
    switch (value) {
        case Value::AS : ostream << "As"; break;
        case Value::ROI : ostream << "Roi"; break;
        case Value::DAME : ostream << "Dame"; break;
        case Value::VALET : ostream << "Valet"; break;
        case Value::DIX : ostream << "10"; break;
        case Value::NEUF : ostream << "9"; break;
        case Value::HUIT : ostream << "8"; break;
        case Value::SEPT : ostream << "7"; break;
    }
    return ostream;
}    


void Card::print() const {
    std::cout << _value << " de " << _color << std::endl;
}

bool Card::operator==(const Card& other) const {
    //return this->_value == other._value && this->_color == other._color;
    return this->_value == other._value;
}

bool Card::operator<(const Card& other) const {
    return this->_value < other._value;
}