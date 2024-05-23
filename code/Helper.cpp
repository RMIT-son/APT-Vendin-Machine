//
// Created by Son on 5/13/2024.
//

#include "Helper.h"

Price Helper::readPrice(const std::string &priceStr)
{
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

std::string Helper::priceToString(const Price &price)
{
    std::ostringstream oss;

    // Convert the price to a string with 2 decimal places separated by a period

    oss << price.dollars << "." << std::setfill('0') << std::setw(2)
        << price.cents;
    return oss.str();
}

std::string Helper::readInput()
{
    std::string input;
    if (std::getline(std::cin, input))
    {
        std::cout << std::endl;
    }
    else if (std::cin.eof())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "EOF encountered. Please enter a valid input." << std::endl;
        input = std::string();
    }
    else
    {
        input = std::string();
    }
    return input;
}

bool Helper::isNumber(std::string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

bool canDispenseCents(int cents, const std::vector<int> &denominations)
{
    for (const int denom : denominations)
    {
        while (cents >= denom)
        {
            cents -= denom;
        }
    }
    return cents == 0;
}

bool Helper::isValidPrice(const std::string &priceStr)
{
    bool isValid = true;
    std::istringstream iss(priceStr);
    std::string dollarStr, centStr;


    if (!std::getline(iss, dollarStr, '.') || dollarStr.empty())
    {
        isValid = false;

    }
    else if (!std::getline(iss, centStr))
    {
        std::cout << "Error: money is not formatted properly" << std::endl;

        isValid = false;

    }
    else if (centStr.length() != 2)
    {
        std::cout << "Error: there are not two digits for cents." << std::endl;

        isValid = false;
    }
    else if (!std::all_of(dollarStr.begin(), dollarStr.end(), ::isdigit) ||
             !std::all_of(centStr.begin(), centStr.end(), ::isdigit))
    {
        isValid = false;

    }
    else
    {
        int dollars;
        int cents;
        try
        {
            dollars = std::stoi(dollarStr);
            cents = std::stoi(centStr);
        }
        catch (const std::exception &)
        {
            isValid = false;
        }


        if (isValid)
        {
            if (dollars == 0 && cents == 0)
            {
                std::cout << "Error: the price must be greater than 0.00" << std::endl;
                isValid = false;
            }
            else if (dollars > 99)
            {
                std::cout << "Error: the price must be smaller than 100.00" << std::endl;
                isValid = false;
            }
            else
            {
                std::vector<int> denominations = {FIFTY_DOLLARS_VALUE, TWENTY_DOLLARS_VALUE, TEN_DOLLARS_VALUE, FIVE_DOLLARS_VALUE, TWO_DOLLARS_VALUE, ONE_DOLLAR_VALUE, FIFTY_CENTS_VALUE, TWENTY_CENTS_VALUE, TEN_CENTS_VALUE, FIVE_CENTS_VALUE};
                if (!canDispenseCents(cents, denominations))
                {
                    std::cout << "Error: price is not a valid denomination." << std::endl;
                    isValid = false;
                }
            }
        }
    }

    return isValid;
}

bool Helper::isValidDenomination(const std::string &priceStr)
{
    bool isValid = false;
    try
    {
        // Convert the priceStr to an integer
        int value = std::stoi(priceStr);

        // Check if the integer value corresponds to any of the defined denomination values
        if (value == FIVE_CENTS_VALUE ||
            value == TEN_CENTS_VALUE ||
            value == TWENTY_CENTS_VALUE ||
            value == FIFTY_CENTS_VALUE ||
            value == ONE_DOLLAR_VALUE ||
            value == TWO_DOLLARS_VALUE ||
            value == FIVE_DOLLARS_VALUE ||
            value == TEN_DOLLARS_VALUE ||
            value == TWENTY_DOLLARS_VALUE ||
            value == FIFTY_DOLLARS_VALUE)
        {
            isValid = true;
        }
    }
    catch (const std::invalid_argument &e)
    {
        // If the string is not a valid integer, set isValid to false
        isValid = false;
    }
    catch (const std::out_of_range &e)
    {
        // If the integer conversion results in an out of range error, set isValid to false
        isValid = false;
    }
    return isValid;
}

bool Helper::isValidName(const std::string &name)
{
    bool isValid = true;

    if (name.length() > NAMELEN)
    {
        std::cout << "The maximum length of a food item name is 40 characters" << std::endl;
        isValid = false;
    }

    if (name.find(FOOD_DELIM) != std::string::npos)
    {
        std::cout << "Invalid character found!" << std::endl;
        isValid = false;
    }
    return isValid;
}

bool Helper::isValidDescription(const std::string &description)
{
    bool isValid = true;
    if (description.length() > DESCLEN)
    {
        std::cout << "The maximum length of a food item description is 255 characters" << std::endl;

        isValid = false;
    }

    if (description.find(FOOD_DELIM) != std::string::npos)
    {
        std::cout << "Invalid character found!" << std::endl;
        isValid = false;
    }
    return isValid;
}

void Helper::processPayment(FoodItem *foodItem, CoinManager &coinManager,
                            unsigned int &totalPaid, const std::string &denomination,
                            std::vector<Denomination> &addedDenominations)
{
    Denomination denom = coinManager.getDenomination(std::stoi(denomination));
    coinManager.addCoin(denom, 1); // Adding the money to the machine
    totalPaid += std::stoi(denomination);
    addedDenominations.push_back(denom);

    if (totalPaid >= foodItem->price.dollars * 100 + foodItem->price.cents)
    {
        unsigned change = totalPaid -
                          (foodItem->price.dollars * 100 + foodItem->price.cents);
        // Calculate and dispense change
        std::vector<Denomination> changeDenominations =
            coinManager.calculateChange(change);
        coinManager.dispenseCoins(changeDenominations); // Decrement the counts
        std::sort(changeDenominations.begin(), changeDenominations.end());
        std::cout << "Your change is ";
        for (auto denom : changeDenominations)
        {
            unsigned int value = coinManager.getValue(denom);
            if (value >= 100)
            {
                std::cout << "$" << value / 100;
            }
            else
            {
                std::cout << value << "c";
            }
            std::cout << " ";
        }
        std::cout << std::endl;

        foodItem->on_hand--;
        std::cout << "Thank you for your purchase!" << std::endl;
    }
}

void Helper::processRefund(CoinManager &coinManager, const std::vector<Denomination> &addedDenominations)
{
    std::cout << "Refund: ";
    for (const auto &denom : addedDenominations)
    {
        coinManager.removeCoin(denom, 1); // Remove the money from the machine
        unsigned int value = coinManager.getValue(denom);
        if (value >= 100)
        {
            std::cout << "$" << value / 100;
        }
        else
        {
            std::cout << value << "c";
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}