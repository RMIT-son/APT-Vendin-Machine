//
// Created by Son on 5/13/2024.
//

#ifndef HELPER_H
#define HELPER_H

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
#include "Coin.h"
#include "Food.h"
#include "Node.h"
#include "LinkedList.h"


#define MIN_PRICE 0
#define MAX_PRICE 99

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

    /**
     * @brief Reads input from the user
     * @details This function will read input from the user.
     * @return std::string The input read from the user.
     */
    static std::string readInput();

    /**
     * @brief Check if a price is valid
     * @details This function will check if a price is valid.
     * @param priceStr The price to check.
     * @return True if the price is valid, false otherwise.
     */
    static bool isValidPrice(const std::string& priceStr);

    /**
     * @brief Check if a denomination is valid
     * @details This function will check if a denomination is valid.
     * @param priceStr The denomination to check.
     * @return True if the denomination is valid, false otherwise.
     */
    static bool isValidDenomination(const std::string& priceStr);

    /**
     * @brief Check if a name is valid
     * @details This function will check if a name is valid.
     * @param name The name to check.
     * @return True if the name is valid, false otherwise.
     */
    static bool isValidName(const std::string& name);

    /**
     * @brief Check if a description is valid
     * @details This function will check if a description is valid.
     * @param description The description to check.
     * @return True if the description is valid, false otherwise.
     */
    static bool isValidDescription(const std::string& description);

    /**
     * @brief Check if a number is valid
     * @details This function will check if a number is valid.
     * @param s The number to check.
     * @return True if the number is valid, false otherwise.
     */
    static bool isNumber(std::string s);

    /**
     * @brief Process a refund
     * @details This function will process a refund by returning the coins to the user.
     * @param coinManager The coins available in the vending machine.
     * @param addedDenominations The coins added by the user.
     */
    static void processRefund(CoinManager& coinManager, const std::vector<Denomination>& addedDenominations);

    /**
     * @brief Process a payment
     * @details This function will process a payment by adding the coins to the vending machine.
     * @param foodItem The food item to be purchased.
     * @param coinManager The coins available in the vending machine.
     * @param totalPaid The total amount paid by the user.
     * @param denomination The denomination of the coin added by the user.
     * @param addedDenominations The coins added by the user.
     */
    static void processPayment(FoodItem* foodItem, CoinManager& coinManager,
                    unsigned int& totalPaid, const std::string& denomination, 
                    std::vector<Denomination>& addedDenominations);
};



#endif //HELPER_H
