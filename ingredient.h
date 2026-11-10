#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QString>

enum class Ingredient {
    Bread, Turkey, Bacon, Lettuce, Tomato, CheddarCheese, Ham, Butter,
    Tortilla, Hummus, Cucumber, CoffeeBeans, Water, Milk, ChocolateSyrup,
    ChaiConcentrate, TeaBags, Ice, ColdBrewConcentrate, LemonJuice, Sugar
};

QString ingredientName(Ingredient ingredient);   // e.g. "Cheddar Cheese"
QString ingredientUnit(Ingredient ingredient);   // e.g. "g", "ml", "slices"

#endif // INGREDIENT_H
