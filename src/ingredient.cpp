#include "ingredient.hpp"
using namespace std;

Ingredient::Ingredient() : name(""), unit(""), amount(0.0) {}

Ingredient::Ingredient(const Ingredient& i) {
  *this = i;
}

Ingredient::Ingredient(string name, string unit, float amount)
    : name(name), unit(unit), amount(amount) {}

string Ingredient::getName() const {
  return this->name;
}

string Ingredient::getUnit() const {
  return this->unit;
}

float Ingredient::getAmount() const {
  return this->amount;
}

string Ingredient::toString() const {
  stringstream writtenIngredient;
  writtenIngredient << "  " << name << " - " << amount << " " << unit << "\n";
  return writtenIngredient.str();
}

void Ingredient::setName(const string& n) {
  this->name = n;
}

void Ingredient::setUnit(const string& u) {
  this->unit = u;
}

void Ingredient::setAmount(const float& a) {
  this->amount = a;
}

Ingredient& Ingredient::operator=(const Ingredient& o) {
  if (this != &o) {
    name = o.name;
    unit = o.unit;
    amount = o.amount;
  }
  return *this;
}

bool Ingredient::operator==(const Ingredient& o) {
  return name == o.name;
}

bool Ingredient::operator!=(const Ingredient& o) {
  return name != o.name;
}

bool Ingredient::operator<(const Ingredient& o) {
  return name < o.name;
}

bool Ingredient::operator<=(const Ingredient& o) {
  return name <= o.name;
}

bool Ingredient::operator>(const Ingredient& o) {
  return name > o.name;
}

bool Ingredient::operator>=(const Ingredient& o) {
  return name >= o.name;
}

int Ingredient::compareByName(const Ingredient& a, const Ingredient& p) {
  if (a.name > p.name) {
    return 1;
  } else if (a.name == p.name) {
    return 0;
  } else if (a.name < p.name) {
    return -1;
  }
}

istream& operator>>(istream& is, Ingredient& i) {
  string myStr;
  getline(is, i.name);
  getline(is, myStr);
  i.amount = atof(myStr.c_str());
  getline(is, i.unit);

  return is;
}

ostream& operator<<(ostream& os, const Ingredient& i) {
  os << i.name << endl;
  os << i.amount << endl;
  os << i.unit;
  return os;
}
