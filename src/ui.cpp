#include "ui.hpp"
#include <iostream>
using namespace std;

UI::UI(List<Recipe>* _recipeBook) {
  recipeBook = _recipeBook;
}

void UI::interface() {
  int op1 = 0;  // Opción del menú principal
  int op2 = 0;  // Submenús
  int pos, pos2, op4, cont = 0;
  Recipe auxRecipe;
  Ingredient auxIngredient;
  string auxType;
  string iName, iUnit, steps, rName, aName, aLastName;
  int type, prepTime, iAmount;

  while (op1 != 9) {
    cout << "========== RECETARIO ==========" << endl;
    cout << " 1.- Mostrar recetario." << endl;
    cout << " 2.- Añadir receta." << endl;
    cout << " 3.- Buscar y modificar receta." << endl;
    cout << " 4.- Eliminar receta." << endl;
    cout << " 5.- Eliminar recetario." << endl;
    cout << " 6.- Ordenar recetario." << endl;
    cout << " 7.- Guardar recetario en el disco." << endl;
    cout << " 8.- Cargar recetario desde el disco." << endl;
    cout << " 9.- Salir." << endl;
    cout << " Seleccione una opción: ";
    cin >> op1;

    switch (op1) {
      case 1: {  // Mostrar recetario
        cout << "========== RECETARIO ==========" << endl;
        if (recipeBook->isEmpty()) {
          cout << "Recetario vacío" << endl;
        } else {
          cout << recipeBook->toString() << endl;
        }
        cout << "Presione Enter para regresar..." << endl;
        cin.ignore();
        cin.get();
        break;
      }

      case 2: {  // Añadir receta
        cout << "========== Añadir Receta ==========" << endl;

        chef.clear();
        ingredients.clear();
        directions.clear();

        cout << "Nombre del platillo: ";
        cin.ignore();
        getline(cin, rName);
        cout << " 1. Desayuno \n 2. Comida \n 3. Cena \n Seleccione una "
                "opción: ";
        cin >> type;
        cout << "Tiempo de preparación (min): ";
        cin >> prepTime;

        cout << "AUTOR: " << endl;
        cout << "Nombre: ";
        cin.ignore();
        getline(cin, aName);
        cout << "Apellidos: ";
        getline(cin, aLastName);

        chef.setName(aName);
        chef.setLastName(aLastName);

        auxRecipe.setName(rName);
        auxRecipe.setType(type == 1   ? "Desayuno"
                          : type == 2 ? "Comida"
                                      : "Cena");
        auxRecipe.setChef(chef);
        auxRecipe.setPrepTime(prepTime);

        // Lista de ingredientes
        cout << "\nLista de Ingredientes (ingrese '0' para salir):" << endl;
        while (true) {
          cout << "Ingrediente: ";
          getline(cin, iName);
          if (iName == "0")
            break;

          cout << "Cantidad: ";
          cin >> iAmount;
          cout << "Medida: ";
          cin.ignore();
          getline(cin, iUnit);

          auxIngredient.setName(iName);
          auxIngredient.setAmount(iAmount);
          auxIngredient.setUnit(iUnit);

          ingredients.insertData(0, auxIngredient);
        }

        auxRecipe.setIngredients(ingredients);

        // Lista de pasos
        cout << "\nLista de Pasos (ingrese '0' para salir):" << endl;
        while (true) {
          cout << "Paso " << cont + 1 << ": ";
          getline(cin, steps);
          if (steps == "0")
            break;

          directions.insertData(cont, steps);
          cont++;
        }
        auxRecipe.setDirections(directions);

        // Insertar la receta
        cout << "Ingrese la posición para insertar: ";
        cin >> pos;
        recipeBook->insertData(pos, auxRecipe);

        cout << "Receta añadida correctamente." << endl;
        cout << "Presione Enter para regresar..." << endl;
        cin.ignore();
        cin.get();
        break;
      }

      case 3: {  // Buscar y modificar receta
        cout << "========== Buscar Receta ==========" << endl;

        if (recipeBook->isEmpty()) {
          cout << "El recetario está vacío." << endl;
          cout << "Presione Enter para regresar..." << endl;
          cin.ignore();
          cin.get();
          break;
        }

        cout << "1. Buscar por nombre" << endl;
        cout << "2. Buscar por tipo" << endl;
        cout << "Seleccione una opción: ";
        cin >> op2;

        if (op2 == 1) {
          cout << "\nIngrese el nombre de la receta: ";
          cin.ignore();
          getline(cin, rName);
          auxRecipe.setName(rName);

          pos = recipeBook->findData(auxRecipe, Recipe::compareByName);
        } else if (op2 == 2) {
          cout << "\nIngrese el tipo de la receta: ";
          cin.ignore();
          getline(cin, auxType);
          auxRecipe.setType(auxType);

          pos = recipeBook->findData(auxRecipe, Recipe::compareByType);
        }

        if (pos != -1) {
          auxRecipe = recipeBook->retrieve(pos);
          cout << "\nReceta encontrada:\n" << auxRecipe.toString() << endl;

          // Modificación
          cout << "\n1. Añadir ingrediente" << endl;
          cout << "2. Eliminar ingrediente" << endl;
          cout << "3. Modificar paso" << endl;
          cout << "Seleccione una opción: ";
          cin >> op4;

          if (op4 == 1) {
            // Añadir ingrediente
            cout << "\nNombre del nuevo ingrediente: ";
            cin.ignore();
            getline(cin, iName);

            cout << "Cantidad: ";
            cin >> iAmount;
            cout << "Medida: ";
            cin.ignore();
            getline(cin, iUnit);

            auxIngredient.setName(iName);
            auxIngredient.setAmount(iAmount);
            auxIngredient.setUnit(iUnit);

            ingredients = auxRecipe.getIngredients();
            ingredients.insertData(0, auxIngredient);

            auxRecipe.setIngredients(ingredients);
            recipeBook->deleteData(pos);
            recipeBook->insertData(pos, auxRecipe);

          } else if (op4 == 2) {
            // Eliminar ingrediente
            cout << "Nombre del ingrediente a eliminar: ";
            cin.ignore();
            getline(cin, iName);

            auxIngredient.setName(iName);
            ingredients = auxRecipe.getIngredients();
            pos2 =
                ingredients.findData(auxIngredient, Ingredient::compareByName);

            if (pos2 != -1) {
              ingredients.deleteData(pos2);
              auxRecipe.setIngredients(ingredients);
              recipeBook->deleteData(pos);
              recipeBook->insertData(pos, auxRecipe);
              cout << "Ingrediente eliminado." << endl;
            } else {
              cout << "Ingrediente no encontrado." << endl;
            }

          } else if (op4 == 3) {
            // Modificar paso
            cout << "Número del paso a modificar: ";
            cin >> pos2;

            directions = auxRecipe.getDirections();
            if (pos2 > 0 && pos2 <= directions.getLastPos() + 1) {
              cout << "Nuevo contenido del paso: ";
              cin.ignore();
              getline(cin, steps);
              directions.deleteData(pos2 - 1);
              directions.insertData(pos2 - 1, steps);

              auxRecipe.setDirections(directions);
              recipeBook->deleteData(pos);
              recipeBook->insertData(pos, auxRecipe);
            } else {
              cout << "Número de paso inválido." << endl;
            }
          }
        } else {
          cout << "Receta no encontrada." << endl;
        }

        cout << "Presione Enter para regresar..." << endl;
        cin.ignore();
        cin.get();
        break;
      }

      case 9:
        cout << "Saliendo del programa..." << endl;
        break;

      default:
        cout << "Opción inválida. Intente nuevamente." << endl;
        break;
    }
  }
}
