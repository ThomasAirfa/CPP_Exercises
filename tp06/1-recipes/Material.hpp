#pragma once

#include <iostream>

class Material
{
  public :
    Material(std::string name) : _name { std::move(name) } {
      std::cout << _name << " was created" << std::endl;
    }

    ~Material() {
      std::cout << _name << " was destroyed" << std::endl;
    }

    // Affiche le nom d'un matériau
    friend std::ostream& operator<<(std::ostream& stream, const Material& material)
    {
      return stream << material._name;
    }

    friend bool operator==(const Material& mat, const Material& other) {
      return mat._name == other._name;
    }
    
    friend bool operator==(const Material& mat, const std::string& name) {
      return mat._name == name;
    }

    private :
      std::string _name;
};
