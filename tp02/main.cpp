#include "Card.hpp"
#include "Player.hpp"

int main () {
    const Card c1 { Color::PIQUE , Value::HUIT };
    c1.print();

    const Card c2 { Color::COEUR, Value::HUIT };
    std::cout << (c2 == c1) << std::endl; // -> 1
    const Card c3 { Color::CARREAU, Value::AS };
    std::cout << (c2 == c3) << std::endl; // -> 0 

    std::cout << (c1 < c2) << std::endl; // -> 0
    std::cout << (c1 < c3) << std::endl; // -> 1
    std::cout << (c3 < c1) << std::endl; // -> 0

    Player p1 { "Gerald" };
    Player p2 { "Julien" };
    Player::deal_all_cards(p1, p2);

    for (auto i = 0; i < 16; ++i) {
        p1[i].print();
        std::cout << std::endl;
        p2[i].print();
        std::cout << std::endl;
    }
}