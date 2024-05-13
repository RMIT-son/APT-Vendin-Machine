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
    static Price readPrice(const std::string& priceStr);
    static std::string priceToString(const Price& price);
    static bool isValidPrice(const std::string& priceStr);
};



#endif //HELPER_H
