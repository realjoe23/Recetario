#ifndef __UI_H__
#define __UI_H__

#include <iostream>
#include <string>

#include "ingredient.hpp"
#include "list.hpp"
#include "name.hpp"
#include "recipe.hpp"

class UI {
 private:
  List<Recipe>* recipeBook;

 public:
  UI(List<Recipe>* _recipeBook);
  void interface();
};

#endif  // __UI_H__