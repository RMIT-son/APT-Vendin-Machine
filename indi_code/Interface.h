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

#define HELP_COMMAND "help"
#define GREEN "\033[32m"
#define ESCAPE "\033[0m"

class Interface {
public:
    // Display the main menu options
    static void displayMainMenu();

    // Display the food menu options
    static void displayFoodMenu(const Food &foodList);

    // Display the current balance of the coin manager
    static void displayBalance(CoinManager &manager);

    // Purchase a meal from the food menu
    static void purchaseMeal(const Food &foodList, CoinManager &coinManager, bool& helpToggle, bool& colorToggle);

    // Add a new food item to the food list
    static void addFood(Food &foodList, const bool& helpToggle);

    // Remove a food item from the food list
    static void removeFood(Food &foodList, const bool& helpToggle);

    /**
     * @brief Display the enhancements menu
     * @details Displays the enhancements menu with the available options.
     */
    static void displayEnhancementsMenu();

    /**
     * @brief Handle the enhancements menu
     * @details Handles the user input for the enhancements menu.
     * @param helpToggle A reference to the help toggle variable.
     * @param colorToggle A reference to the color toggle variable.
     */
    static void Enhancements(bool& helpToggle, bool& colorToggle);

    /**
     * @brief Display the help menu
     * @details Displays the help menu with the available options.
     * @param context The context in which the help menu is being displayed.
     */
    static void help(context context);
};

#endif // INTERFACE_H