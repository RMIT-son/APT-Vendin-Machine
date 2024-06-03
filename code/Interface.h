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
#include "MainLinkedList.h"
#include "Food.h"
#include "Coin.h"

class Interface {
public:
    Interface() : enhancement(false) {}
    ~Interface() = default;
    // Display the main menu options
    void displayMainMenu();

    // Display the current balance of the coin manager
    void displayBalance(CoinManager &manager);

    // Purchase a meal from the food menu
    void purchaseMealEnhancement(MainLinkedList &mainList, CoinManager &coinManager);

    // Add a new food item to the food list
    void addFoodEnhancement(MainLinkedList &mainList);

    // Remove a food item from the food list
    void removeFoodEnhancement(MainLinkedList &mainList);

    void displayFoodMenu(MainLinkedList &mainList);

    void setEnhancement(bool state);

    bool getEnhancement() const; 

    void setColor(bool state);

    bool getColor() const; 
        
private:
    bool enhancement;
    bool color;
};

#endif // INTERFACE_H