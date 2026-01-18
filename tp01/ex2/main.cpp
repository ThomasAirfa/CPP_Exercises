#include <iostream>
#include <vector>
#include <limits>

void ajoute_double(std::vector<int>& v)
{
    auto size = v.size();
    for (auto i = 0; i < size; i++) {
        v.emplace_back(v[i] * 2);
    }
    // for (auto n : v)
    // {
    //     v.emplace_back(n * 2);
    // }
    
}

void affiche(const std::vector<int>& vector) {
    std::cout << "Le tableau contient les valeurs :";
    for (auto value : vector) {
        std::cout << " " << value;
    }
    std::cout << std::endl;
}

int main()
{
    // auto entiers = std::vector<int>{1, 3, 3, 7};

    // std::cout << "Le tableau contient les valeurs :";
    // for (int i = 0; i < entiers.size(); i++)
    // {
    //     std::cout << " " << entiers[i];
    // }
    std::vector<int> entiers;
    int n;
    
    for (;;) {
        std::cin >> n;

        if (std::cin.fail()) {
            std::cerr << "Ceci n'est pas un entier!" << std::endl;
            // reprendre sur l'erreur sinon return 0;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip bad input doc iostream
            continue;
        }

        if (n == 0) {
            break;
        }

        if (n < 0 && entiers.size() > 0) {
            entiers.pop_back();
        }

        if (n > 0) {
            entiers.emplace_back(n);
        }
    }

    affiche(entiers);
    std::cout << "Premier elem : " << entiers.front() << " Dernier elem : " << entiers.back(); // Q4

    std::cout << std::endl;

    ajoute_double(entiers);

    affiche(entiers);  

    return 0;
}