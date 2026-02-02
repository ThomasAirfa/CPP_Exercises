
// Ce fichier est compilé indépendamment des tests.
// Il est ici pour vous permettre de tester votre code.

// !! Ne pas inclure ce fichier dans un autre !!
// !! Ne pas inclure d'autre .cpp !!

#include "PhoneNumber.hpp"

int main() {
    auto phone_number = PhoneNumber{1, 64, 12, 66, 73};
    phone_number.print();
}