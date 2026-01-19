#include <algorithm>
#include <random>

#include "Player.hpp"
#include "Card.hpp"

Player::Player(std::string name) {
    _name = name;
}

void Player::deal_all_cards(Player& p1, Player& p2) {
    std::vector<Card> all_cards;
    for (auto color : all_colors) {
        for (auto value : all_values) {
           all_cards.emplace_back(color, value); 
        }
    }

    std::random_device rd;
    std::shuffle(all_cards.begin(), all_cards.end(), std::default_random_engine(rd()));

    for (unsigned int i = 0; i < all_cards.size(); i++) {
        if (i % 2 == 0) {
            p1._cards.emplace_back(all_cards[i]);
        } else {
            p2._cards.emplace_back(all_cards[i]);
        }
    }
}

const Card& Player::operator[](int index) const {
    return _cards[index];
}