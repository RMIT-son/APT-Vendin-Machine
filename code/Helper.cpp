//
// Created by Razer on 5/13/2024.
//

#include "Helper.h"
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <iostream>

Price Helper::readPrice(const std::string& priceStr) {
    // Read the price from a string
    Price price;
    std::istringstream iss(priceStr);
    std::string dollarStr, centStr;
    std::getline(iss, dollarStr, '.');
    std::getline(iss, centStr);
    price.dollars = std::stoi(dollarStr);
    price.cents = std::stoi(centStr);
    return price;
}

std::string Helper::priceToString(const Price& price) {
    std::ostringstream oss;
    oss << price.dollars << "." << std::setfill('0') << std::setw(2) << price.cents;
    return oss.str();
}

bool Helper::isValidPrice(const std::string& priceStr) {
    std::istringstream iss(priceStr);
    std::string dollarStr, centStr;

    // Read dollars part and expect a dot
    if (!std::getline(iss, dollarStr, '.') || dollarStr.empty()) {
        return false; // No dot or nothing before the dot
    }

    // Read cents part
    if (!std::getline(iss, centStr) || centStr.length() != 2) {
        return false; // Nothing after the dot or not exactly two digits for cents
    }

    // Check if dollarStr and centStr are numeric
    if (!std::all_of(dollarStr.begin(), dollarStr.end(), ::isdigit) ||
        !std::all_of(centStr.begin(), centStr.end(), ::isdigit)) {
        return false; // Non-digit characters found
    }

    try {
        std::stoi(dollarStr);
        std::stoi(centStr);
    } catch(const std::exception&) {
        return false; // Conversion to integer failed
    }

    return true; // String can be converted to Price
}
