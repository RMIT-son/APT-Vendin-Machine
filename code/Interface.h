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
    Interface() : enhancement(false) {}
    ~Interface() = default;
    // Display the main menu options
    void displayMainMenu();

    // Display the food menu options
    void displayFoodMenu(Food &foodList);

    // Display the current balance of the coin manager
    void displayBalance(CoinManager &manager);

    // Purchase a meal from the food menu
    void purchaseMeal(Food &foodList, CoinManager &coinManager);

    // Add a new food item to the food list
    void addFood(Food &foodList);

    // Remove a food item from the food list
    void removeFood(Food &foodList);

    void setEnhancement(bool state);

    bool getEnhancement() const;  

    void purchaseMealEnhancement(MainLinkedList &mainList, CoinManager &coinManager);

    void addFoodEnhancement(MainLinkedList &mainList);

    void removeFoodEnhancement(MainLinkedList &mainList);
private:
    bool enhancement;
};

#endif // INTERFACE_H