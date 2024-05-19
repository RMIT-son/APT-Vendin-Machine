//
// Created by Son on 5/13/2024.
//

#include "Helper.h"
#include "Coin.h"
#include "Node.h"
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

Price Helper::readPrice(const std::string& priceStr) {
    // Read the price from a string
    Price price{};
    std::istringstream iss(priceStr);
    std::string dollarStr, centStr;
	// Split the string into dollars and cents
    std::getline(iss, dollarStr, '.');
    std::getline(iss, centStr);
    price.dollars = std::stoi(dollarStr);
    price.cents = std::stoi(centStr);
    return price;
}

std::string Helper::priceToString(const Price& price) {
    std::ostringstream oss;
	// Convert the price to a string with 2 decimal places separated by a period
    oss << price.dollars << "." << std::setfill('0') << std::setw(2)
    << price.cents;
    return oss.str();
}

bool canDispenseCents(int cents, const std::vector<int>& denominations) {
    for (const int denom : denominations) {
        while (cents >= denom) {
            cents -= denom;
        }
    }
    return cents == 0;
}

bool Helper::isValidPrice(const std::string& priceStr) {
    std::istringstream iss(priceStr);
    std::string dollarStr, centStr;

    // Read dollars part and expect a dot
    if (!std::getline(iss, dollarStr, '.') || dollarStr.empty()) {
        return false; // No dot or nothing before the dot
    }

    // Read cents part
    if (!std::getline(iss, centStr)) {
        std::cout << "Error: money is not formatted properly" << std::endl;
        return false; // Nothing after the dot or not exactly two digits for cents
    }

    if(centStr.length() != 2) {
        std::cout << "Error: there are not two digits for cents." << std::endl;
        return false;
    }

    // Check if dollarStr and centStr are numeric
    if (!std::all_of(dollarStr.begin(), dollarStr.end(), ::isdigit) ||
        !std::all_of(centStr.begin(), centStr.end(), ::isdigit)) {
        return false; // Non-digit characters found
    }

    // Convert cents to integer
    int cents;
    try {
        cents = std::stoi(centStr);
    } catch(const std::exception&) {
        return false; // Conversion to integer failed
    }

    // Check if cents can be dispensed
    std::vector<int> denominations = {FIFTY_DOLLARS_VALUE, TWENTY_DOLLARS_VALUE, TEN_DOLLARS_VALUE, FIVE_DOLLARS_VALUE, TWO_DOLLARS_VALUE, ONE_DOLLAR_VALUE, FIFTY_CENTS_VALUE, TWENTY_CENTS_VALUE, TEN_CENTS_VALUE, FIVE_CENTS_VALUE};
    if (!canDispenseCents(cents, denominations)) {
        std::cout << "Error: price is not a valid denomination." << std::endl;
        return false; // Cannot dispense the exact cents amount
    }

    return true; // String can be converted to Price
}

bool Helper::isValidDenomination(const std::string& priceStr) {
    try {
        // Convert the priceStr to an integer
        int value = std::stoi(priceStr);

        // Check if the integer value corresponds to
        // any of the defined denomination values
        switch (value) {
            case FIVE_CENTS_VALUE:
            case TEN_CENTS_VALUE:
            case TWENTY_CENTS_VALUE:
            case FIFTY_CENTS_VALUE:
            case ONE_DOLLAR_VALUE:
            case TWO_DOLLARS_VALUE:
            case FIVE_DOLLARS_VALUE:
            case TEN_DOLLARS_VALUE:
            case TWENTY_DOLLARS_VALUE:
            case FIFTY_DOLLARS_VALUE:
                return true;
            default:
                return false;
        }
    } catch (const std::invalid_argument& e) {
        // If the string is not a valid integer, return false
        return false;
    } catch (const std::out_of_range& e) {
        // If the integer conversion results in an out of range error,
        // also return false
        return false;
    }
}

bool Helper::isValidName(const std::string& name) {
    bool isValid = true;
    if (name.length() > NAMELEN) {
        std::cout << "The maximum length of a food item name is 40 characters" << std::endl;
        isValid = false;
    }
    
    if (name.find('|') != std::string::npos) {
        std::cout << "Invalid character found!" <<std::endl;
        isValid = false;
    }
    return isValid;
}

bool Helper::isValidDescription(const std::string& description) {
    bool isValid = true;
    if (description.length() > DESCLEN) {
        std::cout << "The maximum length of a food item description is 255 characters" << std::endl;
        isValid = false;
    }
    
    if (description.find('|') != std::string::npos) {
        std::cout << "Invalid character found!" <<std::endl;
        isValid = false;
    }
    return isValid;
}