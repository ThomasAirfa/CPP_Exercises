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

    std::cout << "Début de la partie" << std::endl;

    Player p1 { "Gerald" };
    Player p2 { "Julien" };
    Player::deal_all_cards(p1, p2);

    // for (auto i = 0; i < 16; ++i) {
    //     p1[i].print();
    //     std::cout << std::endl;
    //     p2[i].print();
    //     std::cout << std::endl;
    // }

    bool game_finished = false;
    while (!game_finished) {
        game_finished = Player::play(p1, p2);
    }
    std::cout << "Fin de la partie" << std::endl;
    std::cout << "Score de Gerald : " << p1.get_score() << std::endl;
    std::cout << "Score de Julien : " << p2.get_score() << std::endl;
    
    if (p1.get_score() > p2.get_score()) {
        std::cout << "Gerald gagne la partie !" << std::endl;
    } else if (p2.get_score() > p1.get_score()) {
        std::cout << "Julien gagne la partie !" << std::endl;
    } else {
        std::cout << "Match nul !" << std::endl;
    }
}