//
// Created by Son on 5/13/2024.
//

#ifndef HELPER_H
#define HELPER_H
#include <string>
#include <iomanip>
#include <sstream>
#include "Node.h"



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
};



#endif //HELPER_H
