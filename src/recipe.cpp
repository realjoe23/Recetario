#include "recipe.hpp"
using namespace std;

string Recipe::formatData(string data) {
  data.substr(0, 30);
  while (data.length() < 30) {
    data += " ";
  }
  return data;
}

Recipe::Recipe() : name(""), type(""), prepTime(0), chef() {}

Recipe::Recipe(const Recipe& p) {
  *this = p;
}

Recipe::Recipe(string name, string type, int prepTime, Name chef)
    : name(formatData(name)),
      type(formatData(type)),
      prepTime(prepTime),
      chef(chef) {}

string Recipe::getName() const {
  return this->name;
}

string Recipe::getType() const {
  return this->type;
}

int Recipe::getPrepTime() const {
  return this->prepTime;
}

Name Recipe::getChef() const {
  return this->chef;
}

List<Ingredient> Recipe::getIngredients() const {
  return this->ingredients;
}

List<string> Recipe::getDirections() const {
  return this->directions;
}

string Recipe::toString() const {
  stringstream writtenRecipy;
  writtenRecipy << " Nombre: " << name << " | Categoria: " << type
                << " | Tiempo de preparacion: " << prepTime << " min \t"
                << " | Autor: " << chef.toString();
  return writtenRecipy.str();
}

string Recipe::showAll() const {
  stringstream all;

  all << " Nombre: " << name << "\n  Categoria: " << type
      << "\n  Tiempo de preparacion: " << prepTime
      << " min \n  Autor: " << chef.toString() << "\n\n"
      << "  Ingredientes: \n";

  for (int i = 0; i <= ingredients.getLastPos(); i++) {
    all << ingredients.retrieve(i).toString();
  }

  all << "\n\n  Procedimiento: \n";

  for (int i = 0; i <= directions.getLastPos(); i++) {
    all << "  " << i + 1 << ".- " << directions.retrieve(i) << "\n";
  }

  return all.str();
}

void Recipe::setName(const std::string& n) {
  this->name = n;
}

void Recipe::setType(const std::string& t) {
  this->type = t;
}

void Recipe::setPrepTime(const int& p) {
  this->prepTime = p;
}

void Recipe::setChef(const Name& c) {
  this->chef = c;
}

void Recipe::setIngredients(const List<Ingredient>& i) {
  ingredients.quickSort(Ingredient::compareByName);
  this->ingredients = ingredients;
}

void Recipe::setDirections(const List<std::string>& d) {
  this->directions = d;
}

int Recipe::compareByName(const Recipe& a, const Recipe& p) {
  if (a.name > p.name) {
    return 1;
  } else if (a.name == p.name) {
    return 0;
  } else if (a.name < p.name) {
    return -1;
  }
}

int Recipe::compareByType(const Recipe& a, const Recipe& p) {
  if (a.type > p.type) {
    return 1;
  } else if (a.type == p.type) {
    return 0;
  } else if (a.type < p.type) {
    return -1;
  }
}

int Recipe::compareByPrepTime(const Recipe& a, const Recipe& p) {
  if (a.prepTime > p.prepTime) {
    return 1;
  } else if (a.prepTime == p.prepTime) {
    return 0;
  } else if (a.prepTime < p.prepTime) {
    return -1;
  }
}

Recipe& Recipe::operator=(const Recipe& p) {
  ingredients = p.ingredients;
  directions = p.directions;
  name = p.name;
  type = p.type;
  prepTime = p.prepTime;
  chef = p.chef;

  return *this;
}

istream& operator>>(istream& is, Recipe& r) {
  string myStr;

  getline(is, r.name);
  getline(is, r.type);
  getline(is, myStr);
  r.prepTime = atoi(myStr.c_str());
  is >> r.chef;

  getline(is, myStr);
  int numIngredients = atoi(myStr.c_str());

  List<Ingredient> tempingredients;
  Ingredient tempIngredient;

  for (int i = 0; i <= numIngredients; i++) {
    is >> tempIngredient;
    tempingredients.insertData(i, tempIngredient);
  }
  r.ingredients = tempingredients;

  getline(is, myStr);
  int numSteps = atoi(myStr.c_str());

  List<string> tempdirections;
  string tempStep;

  for (int i = 0; i <= numSteps; i++) {
    getline(is, tempStep);
    tempdirections.insertData(i, tempStep);
  }
  r.directions = tempdirections;

  return is;
}

ostream& operator<<(ostream& os, Recipe& r) {
  os << r.name << endl;
  os << r.type << endl;
  os << r.prepTime << endl;
  os << r.chef << endl;

  int i(0);
  os << r.ingredients.getLastPos() << endl;
  while (i <= r.ingredients.getLastPos()) {
    os << r.ingredients.retrieve(i) << endl;
    i++;
  }

  i = 0;
  os << r.directions.getLastPos() << endl;
  while (i <= r.directions.getLastPos()) {
    if (i == r.directions.getLastPos()) {
      os << r.directions.retrieve(i);
    } else {
      os << r.directions.retrieve(i) << endl;
    }
    i++;
  }
  return os;
}
