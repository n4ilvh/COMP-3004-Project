#include "ingredient.h"

QString ingredientName(Ingredient i)
{
    switch (i) {
    case Ingredient::Bread:               return "Bread";
    case Ingredient::Turkey:              return "Turkey";
    case Ingredient::Bacon:               return "Bacon";
    case Ingredient::Lettuce:             return "Lettuce";
    case Ingredient::Tomato:              return "Tomato";
    case Ingredient::CheddarCheese:       return "Cheddar Cheese";
    case Ingredient::Ham:                 return "Ham";
    case Ingredient::Butter:              return "Butter";
    case Ingredient::Tortilla:            return "Tortilla";
    case Ingredient::Hummus:              return "Hummus";
    case Ingredient::Cucumber:            return "Cucumber";
    case Ingredient::CoffeeBeans:         return "Coffee Beans";
    case Ingredient::Water:               return "Water";
    case Ingredient::Milk:                return "Milk";
    case Ingredient::ChocolateSyrup:      return "Chocolate Syrup";
    case Ingredient::ChaiConcentrate:     return "Chai Concentrate";
    case Ingredient::TeaBags:             return "Tea Bags";
    case Ingredient::Ice:                 return "Ice";
    case Ingredient::ColdBrewConcentrate: return "Cold Brew Concentrate";
    case Ingredient::LemonJuice:          return "Lemon Juice";
    case Ingredient::Sugar:               return "Sugar";
    }
    return "Unknown";
}

QString ingredientUnit(Ingredient i)
{
    switch (i) {
    case Ingredient::Bread:               return "slices";
    case Ingredient::Bacon:               return "strips";
    case Ingredient::Tomato:              return "slices";
    case Ingredient::Tortilla:            return "piece";
    case Ingredient::TeaBags:             return "bags";
    case Ingredient::Water:
    case Ingredient::Milk:
    case Ingredient::ChocolateSyrup:
    case Ingredient::ChaiConcentrate:
    case Ingredient::ColdBrewConcentrate:
    case Ingredient::LemonJuice:          return "ml";
    default:                              return "g";   // meats, cheese, produce, ice, sugar...
    }
}
