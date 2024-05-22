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
    static void displayMainMenu();
    static void displayFoodMenu(Food &foodList);
    static void displayBalance(CoinManager &manager);
    static void purchaseMeal(Food &foodList, CoinManager &coinManager);
    static void addFood(Food &foodList);
    static void removeFood(Food &foodList);
};

#endif // INTERFACE_H