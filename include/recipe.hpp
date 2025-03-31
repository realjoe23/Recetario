#ifndef __RECIPE_H__
#define __RECIPE_H__

#include "ingredient.hpp"
#include "list.hpp"
#include "name.hpp"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Recipe {
 private:
  std::string name;
  List<Ingredient> ingredients;
  List<std::string> directions;
  std::string type;
  int prepTime;
  Name chef;

  std::string formatData(std::string data);

 public:
  Recipe();
  Recipe(const Recipe&);
  Recipe(std::string, std::string, int, Name);

  std::string getName() const;
  std::string getType() const;
  int getPrepTime() const;
  Name getChef() const;
  List<Ingredient> getIngredients() const;
  List<std::string> getDirections() const;

  std::string toString() const;
  std::string showAll() const;

  void setName(const std::string&);
  void setType(const std::string&);
  void setPrepTime(const int&);
  void setChef(const Name&);
  void setIngredients(const List<Ingredient>&);
  void setDirections(const List<std::string>&);

  static int compareByName(const Recipe&, const Recipe&);
  static int compareByType(const Recipe&, const Recipe&);
  static int compareByPrepTime(const Recipe&, const Recipe&);

  Recipe& operator=(const Recipe&);
  bool operator==(const Ingredient&);
  bool operator!=(const Ingredient&);
  bool operator<(const Ingredient&);
  bool operator<=(const Ingredient&);
  bool operator>(const Ingredient&);
  bool operator>=(const Ingredient&);

  friend std::ostream& operator<<(std::ostream&, Recipe&);
  friend std::istream& operator>>(std::istream&, Recipe&);
};

#endif  // __RECIPE_H__