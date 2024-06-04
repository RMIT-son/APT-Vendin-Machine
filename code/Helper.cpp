//
// Created by Son on 5/13/2024.
//

#include "Helper.h"

// Read the price from a string
Price Helper::readPrice(const std::string &priceStr) {
    // Create a Price struct to store the price information
    Price price{};
    // Create an input string stream to read from the price string
    std::istringstream iss(priceStr);
    // Split the string into dollars and cents
    std::string dollarStr, centStr;

    // Read the dollar portion of the price string
    std::getline(iss, dollarStr, '.');
    // Read the cent portion of the price string
    std::getline(iss, centStr);
    // Convert the dollar string to an integer and assign it to price.dollars
    price.dollars = std::stoi(dollarStr);
    // Convert the cent string to an integer and assign it to price.cents
    price.cents = std::stoi(centStr);
    // Return the Price struct containing the parsed price information
    return price;
}

std::string Helper::priceToString(const Price &price) {
    // Create an output string stream to build the price string
    std::ostringstream oss;

    // Convert the price to a string with 2 decimal places separated by a period
    oss << price.dollars << "." << std::setfill('0') << std::setw(2)
        << price.cents;
    // Return the built price string
    return oss.str();
}

bool Helper::isValidId(const std::string& id) {
    bool isValid = true;

    // Check if the ID starts with 'F' and has exactly 5 characters
    if (id.size() != ID_LENGTH || id[0] != ID_PREFIX) {
        isValid = false;
    }

    // Check if the remaining characters are digits
    for (std::size_t i = 1; i < id.size() && isValid; ++i) {
        if (!std::isdigit(id[i])) {
            isValid = false;
        }
    }

    return isValid;
}


std::string Helper::readInput()
{
    std::string input;
    if (std::getline(std::cin, input))
    {
        // Remove any leading or trailing whitespace
        const size_t end = input.find_last_not_of(" \t\n\r\f\v");
        if (end != std::string::npos) {
            input = input.substr(0, end + 1);
        }
        std::cout << std::endl;
        // Check if the input stream encountered an end-of-file condition
    } else if (std::cin.eof()) {
        std::cin.clear();
        // Clear the input stream and ignore any remaining characters in the buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // Set the input string to an empty string
        input = std::string();
    } else {
        // Set the input string to an empty string
        input = std::string();
    }
    // Return the user input string
    return input;
}

bool Helper::isNumber(std::string s) {
    std::string::const_iterator it = s.begin();

    while (it != s.end() && std::isdigit(*it))
        ++it;
    // Iterate through each character of the input string and check if it is a digit

    return !s.empty() && it == s.end();
    // Return true if the input string is not empty and all characters were digits
}

bool canDispenseCents(int cents, const std::vector<int> &denominations) {
    for (const int denom : denominations) {
        // Iterate through each denomination in the vector

        while (cents >= denom) {
            /*
             * Keep subtracting the denomination from the remaining cents as long as
             * the remaining cents are greater than or equal to the denomination
             */
            cents -= denom;
        }
    }

    return cents == MIN_PRICE;
    /*
     * Return true if the remaining cents are equal to zero, indicating that the
     * given denominations can be used to dispense the original amount of cents
    */
}

bool Helper::isValidPrice(const std::string &priceStr) {
    // Initialize the validity flag as true
    bool isValid = true;
    // Create an input string stream to read from the price string
    std::istringstream iss(priceStr);
    std::string dollarStr, centStr;

    // Attempt to read the dollar portion of the price string
    if (!std::getline(iss, dollarStr, '.') || dollarStr.empty()) {
        isValid = false;
    }
    // Attempt to read the cent portion of the price string
    else if (!std::getline(iss, centStr)) {
        std::cout << "Error: money is not formatted properly" << std::endl;
        std::cout << "Please enter a valid price. \n For example: 1.00";
        isValid = false;
    }
    // Check if the cent portion has exactly two digits
    else if (centStr.length() != 2) {
        std::cout << "Error: there are not two digits for cents." << std::endl;
        std::cout << "Please enter a valid price. \n For example: 1.50";
        isValid = false;
    }
    // Check if both the dollar and cent portions consist of only digits
    else if (!std::all_of(dollarStr.begin(), dollarStr.end(), isdigit) ||
             !std::all_of(centStr.begin(), centStr.end(), isdigit)) {
        isValid = false;
    }
    /*
     * If all previous checks pass,
     * attempt to convert dollar and cent strings to integers
     */
    else {
        int dollars;
        int cents;
        try {
            dollars = std::stoi(dollarStr);
            cents = std::stoi(centStr);
        } catch (const std::exception &) {
            isValid = false;
        }

        // Further checks for the validity of the price
        if (isValid) {
            // Check if the price is zero
            if (dollars == MIN_PRICE && cents == MIN_PRICE) {
                std::cout << "Error: the price must be greater than 0.00"
                << std::endl;
                isValid = false;
            }
            // Check if the price exceeds 99.99
            else if (dollars > MAX_PRICE) {
                std::cout << "Error: the price must be smaller than 100.00"
                << std::endl;
                isValid = false;
            }
            // Check if the given denominations can dispense the cents amount
            else {
                std::vector<int> denominations = {FIFTY_DOLLARS_VALUE,
                                                  TWENTY_DOLLARS_VALUE,
                                                  TEN_DOLLARS_VALUE,
                                                  FIVE_DOLLARS_VALUE,
                                                  TWO_DOLLARS_VALUE,
                                                  ONE_DOLLAR_VALUE,
                                                  FIFTY_CENTS_VALUE,
                                                  TWENTY_CENTS_VALUE,
                                                  TEN_CENTS_VALUE,
                                                  FIVE_CENTS_VALUE};
                if (!canDispenseCents(cents, denominations)) {
                    std::cout << "Error: price is not a valid denomination."
                    << std::endl;
                    isValid = false;
                }
            }
        }
    }
    // Return the validity flag
    return isValid;
}

bool Helper::isValidDenomination(const std::string &priceStr)
{
    bool isValid = false;
    try
    {
        // Convert the priceStr to an integer
        int value = std::stoi(priceStr);

        /*
         * Check if the integer value corresponds
         * to any of the defined denomination values
         */
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
        /*
         * If the integer conversion results in an out of range error,
         * set isValid to false
         */
        isValid = false;
    }
    return isValid;
}

bool Helper::isValidName(const std::string &name) {
    // Initialize the validity flag as true
    bool isValid = true;

    // Check if the length of the name exceeds the maximum allowed length
    if (name.length() > NAMELEN) {
        std::cout << "The maximum length of a food item name"
                     " is 40 characters" << std::endl;
        isValid = false;
    }

    // Check if the name contains the invalid character '|'
    if (name.find(FOOD_DELIM) != std::string::npos)
    {
        std::cout << "Invalid character found!" << std::endl;
        isValid = false;
    }
    // Return the validity flag
    return isValid;
}

bool Helper::isValidDescription(const std::string &description) {
    // Initialize the validity flag as true
    bool isValid = true;

    // Check if the length of the description exceeds the maximum allowed length
    if (description.length() > DESCLEN) {
        std::cout << "The maximum length of a food item description"
                     " is 255 characters" << std::endl;
        isValid = false;
    }

    // Check if the description contains the invalid character '|'
    if (description.find(FOOD_DELIM) != std::string::npos)
    {
        std::cout << "Invalid character found!" << std::endl;
        isValid = false;
    }
    // Return the validity flag
    return isValid;
}

void Helper::processPayment(FoodItem *foodItem, CoinManager &coinManager,
                            unsigned int &totalPaid,
                            const std::string &denomination,
                            std::vector<Denomination> &addedDenominations) {
    // Get the denomination object based on the provided denomination value
    const Denomination denom = CoinManager::getDenomination(std::stoi(denomination));

    // Add the coin to the coin manager
    coinManager.addCoin(denom, 1);

    // Update the total amount paid
    totalPaid += std::stoi(denomination);

    // Add the denomination to the list of added denominations
    addedDenominations.push_back(denom);

    // Check if the total amount paid is sufficient for the food item price
    if (totalPaid >= foodItem->price.dollars * 100 + foodItem->price.cents) {
        // Calculate the change to be given back to the customer
        const unsigned change = totalPaid - (foodItem->price.dollars * 100 +
                                             foodItem->price.cents);

        // Calculate the denominations needed for the change
        std::vector<Denomination> changeDenominations =
            coinManager.calculateChange(change);

        // Dispense the coins for the change
        coinManager.dispenseCoins(changeDenominations);

        // Sort the change denominations in ascending order
        std::sort(changeDenominations.begin(), changeDenominations.end());

        // Print the change denominations
        std::cout << "Your change is ";
        for (auto denom : changeDenominations) {
            unsigned int value = CoinManager::getValue(denom);
            if (value >= ONE_DOLLAR_VALUE) {
                std::cout << "$" << value / 100;
            } else {
                std::cout << value << "c";
            }
            std::cout << " ";
        }
        std::cout << std::endl;

        // Decrease the quantity of the food item on hand
        foodItem->on_hand--;

        // Print a thank you message for the purchase
        std::cout << "Thank you for your purchase!" << std::endl;
    }
}

void Helper::processRefund(CoinManager &coinManager,
                           const std::vector<Denomination>
                                   &addedDenominations) {
    std::cout << "Refund: ";
    for (const auto &denom : addedDenominations) {
        // Remove the coin from the coin manager
        coinManager.removeCoin(denom, 1);

        // Get the value of the denomination
        unsigned int value = CoinManager::getValue(denom);

        // Print the value of the denomination in dollars or cents
        if (value >= ONE_DOLLAR_VALUE) {
            std::cout << "$" << value / 100;
        } else {
            std::cout << value << "c";
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}