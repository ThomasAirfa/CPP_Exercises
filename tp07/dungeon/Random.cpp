#include "Random.hpp"

#include <random>

int random_value(int min, int max)
{
    auto generator = std::default_random_engine { std::random_device {}() };
    return std::uniform_int_distribution<int> { min, max }(generator);
}

void random_move(int& x, int& y)
{
    auto generator    = std::default_random_engine { std::random_device {}() };
    auto distribution = std::uniform_int_distribution<int> { 0, 4 };

    switch (distribution(generator))
    {
    case 0:
        // No move
        break;

    case 1:
        // Move left
        if (x == 0) {
        break;   
        }
        --x;
        break;

    case 2:
        // Move right
        if (x == 49) {
            break;
        }
        ++x;
        break;

    case 3:
        // Move down
        if (y == 9) {
            break;
        }
        ++y;
        break;

    case 4:
        // Move up
        if (y == 0) {
            break;
        }
        --y;
        break;

    default:
        break;
    }
}
