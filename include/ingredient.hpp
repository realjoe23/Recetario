#ifndef __INGREDIENT_H__
#define __INGREDIENT_H__

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Ingredient {
 private:
  std::string name;
  std::string unit;
  float amount;

 public:
  Ingredient();
  Ingredient(const Ingredient&);
  Ingredient(std::string, std::string, float);

  std::string getName() const;
  std::string getUnit() const;
  float getAmount() const;

  std::string toString() const;

  void setName(const std::string&);
  void setUnit(const std::string&);
  void setAmount(const float&);

  Ingredient& operator=(const Ingredient&);

  bool operator==(const Ingredient&);
  bool operator!=(const Ingredient&);
  bool operator<(const Ingredient&);
  bool operator<=(const Ingredient&);
  bool operator>(const Ingredient&);
  bool operator>=(const Ingredient&);

  static int compareByName(const Ingredient&, const Ingredient&);

  friend std::ostream& operator<<(std::ostream&, const Ingredient&);
  friend std::istream& operator>>(std::istream&, Ingredient&);
};

#endif  // __INGREDIENT_H__