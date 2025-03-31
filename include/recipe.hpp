#ifndef __RECIPE_H__
#define __RECIPE_H__

#include "name.hpp"
#include "ingredient.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <exception>
#include <iostream>
using namespace std;

class Recipe{
    private:
    std::string recipeName;
    //lista ingredientes
    int time;
    std::string directions;
    Name nameChef;

    public:
};


#endif // __RECIPE_H__