#ifndef INTERFACE_H
#define INTERFACE_H

#define ANSI_COLOR_BLACK "\033[30m"
#define ANSI_COLOR_RED "\033[31m"
#define ANSI_COLOR_GREEN "\033[32m"
#define ANSI_COLOR_YELLOW "\033[33m"
#define ANSI_COLOR_BLUE "\033[34m"
#define ANSI_COLOR_MAGENTA "\033[35m"
#define ANSI_COLOR_CYAN "\033[36m"
#define ANSI_COLOR_WHITE "\033[37m"
#define ANSI_COLOR_RESET "\033[0m"

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


    static void displayHelp();
};

#endif // INTERFACE_H