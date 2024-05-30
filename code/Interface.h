#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include <memory>
#include <map>
#include "LinkedList.h"
#include "Food.h"
#include "Coin.h"
#include "Interface.h"

class Interface {
public:
    // Display the main menu options
    static void displayMainMenu();

    // Display the food menu options
    static void displayFoodMenu(const Food &foodList);

    // Display the current balance of the coin manager
    static void displayBalance(CoinManager &manager);

    // Purchase a meal from the food menu
    static void purchaseMeal(const Food &foodList, CoinManager &coinManager);

    // Add a new food item to the food list
    static void addFood(Food &foodList);

    // Remove a food item from the food list
    static void removeFood(Food &foodList);
};

#endif // INTERFACE_H