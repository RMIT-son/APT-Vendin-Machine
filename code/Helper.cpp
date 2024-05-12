//
// Created by Razer on 5/13/2024.
//

#include "Helper.h"

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
