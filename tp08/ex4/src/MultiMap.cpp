// VOUS POUVEZ MODIFIER CE FICHIER
#include "MultiMap.hpp"

Tracker* MultiMap::add(std::string str, int i)
{
  auto ic = std::make_unique<Tracker>();
  auto raw = ic.get();
  _map1.emplace(std::move(str), std::move(ic));
  _map2.emplace(i, raw);
  return raw;
}