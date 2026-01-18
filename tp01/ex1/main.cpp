#include <iomanip>
#include <iostream>

int main()
{
    std::cout << "Entre ton nom: "; // print sur stdout

    //char name[20] = "";
    std::string name;
    std::cin >> std::setw(20) >> name; // attend les 20 premiers caractères
    std::cout << "Bonjour Palluche La Falluche ! "  << name << std::endl; // print sur stdout 

    return 0;
}
