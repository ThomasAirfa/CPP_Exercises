#pragma once
#include <string>

#include "Card.hpp"

class Player {
    static inline unsigned int turn_number = 0;

    public :
        Player(std::string name);
        static void deal_all_cards(Player& p1, Player& p2);
        const Card& operator[](int index) const;
        static bool play(Player& p1, Player& p2);
        unsigned int get_score() const;
        

    private :
        std::string _name;
        std::vector<Card> _cards;
        unsigned int _score = 0;
};