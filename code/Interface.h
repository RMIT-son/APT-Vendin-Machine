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
    Interface();
    ~Interface();
    void displayMainMenu();
    void displayFoodMenu(Food &foodList);
    static inline void ltrim(std::string &s);
    static inline void rtrim(std::string &s);
    static inline void trim(std::string &s);
};

#endif // INTERFACE_H