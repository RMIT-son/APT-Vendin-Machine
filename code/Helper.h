//
// Created by Son on 5/13/2024.
//

#ifndef HELPER_H
#define HELPER_H


#include "Coin.h"
#include "Food.h"
#include "Node.h"
#include "LinkedList.h"
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <fstream>
#include <limits>
#include <memory>

#define MIN_PRICE 0
#define MAX_PRICE 99
#define ONE_HUNDRED 100

class Helper {
public:
    /**
     * @brief Read a price from a string
     * @details This function will read a price from a string.
     * @param priceStr The string to read the price from.
     * @return The price read from the string.
     */
    static Price readPrice(const std::string& priceStr);

    /**
     * @brief Convert a price to a string
     * @details This function will convert a price to a string.
     * @param price The price to convert to a string.
     * @return The string representation of the price.
     */
    static std::string priceToString(const Price& price);

    /**
     * @brief Check if an ID is valid
     * @details This function will check if an ID is valid.
     * @param id The ID to check.
     * @return True if the ID is valid, false otherwise.
     */
    static bool isValidId(const std::string& id);
    static bool isValidPrice(const std::string& priceStr);
    static bool isValidDenomination(const std::string& priceStr);
    static bool isValidName(const std::string& name);
    static bool isValidDescription(const std::string& description);
    static std::string readInput();
    static bool isNumber(std::string s);
    // static void removeFood(Food &foodList);
    // static void addFood(Food &foodList);
    // static void purchaseMeal(Food &foodList, CoinManager &coinManager);
    static void processRefund(CoinManager& coinManager, const std::vector<Denomination>& addedDenominations);
    static void processPayment(FoodItem* foodItem, CoinManager& coinManager,
                    unsigned int& totalPaid, const std::string& denomination, 
                    std::vector<Denomination>& addedDenominations);
};



#endif //HELPER_H
