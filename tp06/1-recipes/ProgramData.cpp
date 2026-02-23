#include "ProgramData.hpp"
#include <iostream>
#include <memory>
#include <utility>


void ProgramData::register_material(std::string name)
{
  _registered_materials.push_back(std::make_unique<Material>(std::move(name)));
  // _registered_materials.emplace_back(std::make_unique<Material>(std::move(name)));
  // _registered_materials.emplace_back(Material(std::move(name)));
}

void ProgramData::get_registered_materials(std::vector<const Material*>& materials) const
{
  for (auto& material : _registered_materials) {
    materials.push_back(material.get());
  }
}

void ProgramData::add_material_to_inventory(const Material& mat, int quantity)
{
  for (auto& slot : _inventory) {
    if (*slot.first == mat) {
      slot.second += quantity;
      return;
    }
  }
  _inventory.emplace_back(&mat, (size_t) quantity);
}

void ProgramData::get_inventory(MaterialBag& materials) const
{
  for (auto& slot : _inventory) {
    materials.emplace_back(slot);
  }
}

const Material* ProgramData::get_material_by_name(const std::string& name) const
{
  for (auto& material : _registered_materials) {
    if (*material == name) {
      return material.get();
    }
  }
  return nullptr;
}


// ============================================================================
// = Partie Recette ===========================================================
// ============================================================================

void ProgramData::register_recipe(std::vector<const Material*> materials,
                                  const Material& product)
{
  std::cout << "Feature is not yet implemented (register_recipe)" << std::endl;
}

void ProgramData::get_all_recipes(std::vector<const Recipe*>& recipes) const
{
  std::cout << "Feature is not yet implemented (get_all_recipes)" << std::endl;
}

const Recipe* ProgramData::get_recipe_by_id(size_t id) const
{
  std::cout << "Feature is not yet implemented (get_recipe_by_id)" << std::endl;
  return nullptr;
}

void ProgramData::unregister_recipe(const Recipe&)
{
  std::cout << "Feature is not yet implemented (unregister_recipe)" << std::endl;
}


// ============================================================================
// = Partie Production ========================================================
// ============================================================================


void ProgramData::get_doable_recipes(std::vector<const Recipe*>& recipes) const
{
  std::cout << "Feature is not yet implemented (get_doable_recipes)" << std::endl;
}

Outcome ProgramData::produce(const Recipe& recipe, MaterialBag& materials)
{
  std::cout << "Feature is not yet implemented (produce)" << std::endl;
  return Outcome::FAILURE;
}
