#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

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

unsigned int Player::get_score() const {
    return _score;
}

bool Player::play(Player& p1, Player& p2) {
    unsigned int index = turn_number;
    unsigned int battle_cards = 2;

    std::cout << "\nTour " << turn_number + 1 << std::endl;

    while (true) {
        // Vérification fin de paquet
        if (index >= p1._cards.size() || index >= p2._cards.size()) {
            std::cout << "Bataille interrompue : plus de cartes.\n";
            turn_number = index + 1;
            return turn_number >= 16;
        }

        std::cout << p1._name << " joue : ";
        p1._cards[index].print();

        std::cout << p2._name << " joue : ";
        p2._cards[index].print();

        if (p2._cards[index] < p1._cards[index]) {
            unsigned int points = battle_cards / 2;
            p1._score += points;
            std::cout << p1._name << " remporte la bataille (" 
                      << points << " points)\n";
            break;

        } else if (p1._cards[index] < p2._cards[index]) {
            unsigned int points = battle_cards / 2;
            p2._score += points;
            std::cout << p2._name << " remporte la bataille (" 
                      << points << " points)\n";
            break;

        } else {
            std::cout << "Égalité ! Bataille !\n";
            battle_cards += 2;
            index++;
        }
    }

    turn_number = index + 1;

    std::this_thread::sleep_for(std::chrono::seconds(1));
    return turn_number >= 16;
}