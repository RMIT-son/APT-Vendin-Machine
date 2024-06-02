#include "Coin.h"

// Constructor for the Coin class
Coin::Coin(const Denomination denom) {
    this->denom = denom;
}

// Destructor for the Coin class
Coin::~Coin() {
    delete this;
}

// Constructor for the CoinManager class
CoinManager::CoinManager() {
    // Initialize the counts for all denominations to 0
    for (int i = FIVE_CENTS; i <= FIFTY_DOLLARS; i++) {
        coins[static_cast<Denomination>(i)] = DEFAULT_DENOM_COUNT;
    }
}

// Get the value of a coin based on its denomination
int CoinManager::getValue(const Denomination denom) {
    int value;
    if (denom == FIVE_CENTS) {
        value = FIVE_CENTS_VALUE;
    } else if (denom == TEN_CENTS) {
        value = TEN_CENTS_VALUE;
    } else if (denom == TWENTY_CENTS) {
        value = TWENTY_CENTS_VALUE;
    } else if (denom == FIFTY_CENTS) {
        value = FIFTY_CENTS_VALUE;
    } else if (denom == ONE_DOLLAR) {
        value = ONE_DOLLAR_VALUE;
    } else if (denom == TWO_DOLLARS) {
        value = TWO_DOLLARS_VALUE;
    } else if (denom == FIVE_DOLLARS) {
        value = FIVE_DOLLARS_VALUE;
    } else if (denom == TEN_DOLLARS) {
        value = TEN_DOLLARS_VALUE;
    } else if (denom == TWENTY_DOLLARS) {
        value = TWENTY_DOLLARS_VALUE;
    } else if (denom == FIFTY_DOLLARS) {
        value = FIFTY_DOLLARS_VALUE;
    }
    else {
        throw std::invalid_argument("Invalid coin denomination");
    }
    return value;
}

/*
 *Given an integer value, this function maps it to a corresponding denomination
 * If the value matches one of the predefined constants
 * it assigns the corresponding denomination to the 'denom' variable.
 * If the value does not match any predefined denomination,
 * it throws an exception.
 */
Denomination CoinManager::getDenomination(const int value) {
    Denomination denom;
    if (value == FIVE_CENTS_VALUE) {
        denom = FIVE_CENTS;
    } else if (value == TEN_CENTS_VALUE) {
        denom = TEN_CENTS;
    } else if (value == TWENTY_CENTS_VALUE) {
        denom = TWENTY_CENTS;
    } else if (value == FIFTY_CENTS_VALUE) {
        denom = FIFTY_CENTS;
    } else if (value == ONE_DOLLAR_VALUE) {
        denom = ONE_DOLLAR;
    } else if (value == TWO_DOLLARS_VALUE) {
        denom = TWO_DOLLARS;
    } else if (value == FIVE_DOLLARS_VALUE) {
        denom = FIVE_DOLLARS;
    } else if (value == TEN_DOLLARS_VALUE) {
        denom = TEN_DOLLARS;
    } else if (value == TWENTY_DOLLARS_VALUE) {
        denom = TWENTY_DOLLARS;
    } else if (value == FIFTY_DOLLARS_VALUE) {
        denom = FIFTY_DOLLARS;
    } else {
        throw std::invalid_argument("Invalid denomination value");
    }
    return denom;
}

/*
 * Returns an unordered map containing coin denominations (keys)
 * and the number of coins of each denomination (values).
 */
std::unordered_map<Denomination, unsigned> CoinManager::getCoins() const {
    return coins;
}

bool CoinManager::addCoin(const Denomination denom, const unsigned count) {
    // Add the coin count to the denomination
    coins[denom] += count;
    // Successfully added the coins
    return true;
}

bool CoinManager::removeCoin(const Denomination denom, const unsigned count) {
    bool success = false;

    // Check if there are enough coins of the denomination to remove
    if (coins[denom] >= count) {
        coins[denom] -= count;
        success = true;
    }
    return success;
}



void CoinManager::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    bool fileOpened = file.is_open();

    if (fileOpened) {
        std::string line;

        /*
         * Read each line from the file and add the coin denomination
         * and count to the coins map
         */
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string valueStr, countStr;
            std::getline(ss, valueStr, DELIM);
            std::getline(ss, countStr, DELIM);

            // Check if the value and count are not empty
            if (!valueStr.empty() && !countStr.empty()) {
                try {
                    int value = std::stoi(valueStr);
                    unsigned count = std::stoul(countStr);
                    Denomination denom = getDenomination(value);
                    coins[denom] = count;
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid line or coin value: "
                    << line << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Value out of range: " << line << std::endl;
                }
            } else {
                std::cerr << "Invalid line format: " << line << std::endl;
            }
        }
        file.close();
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
}


bool CoinManager::writeToFile(const std::string& filename) const {
    bool success = false;
    std::ofstream file(filename);

    if (file.is_open()) {
        // Write each coin denomination and count to the file
        if (!coins.empty()) {
            bool allWritesSuccessful = true;

            // Copy the elements from the coins map to a vector of pairs
            std::vector<std::pair<Denomination, unsigned>> coinVector(coins.begin(), coins.end());

            // Sort the vector in descending order based on the denomination
            std::sort(coinVector.begin(), coinVector.end(), [](const auto& a, const auto& b) {
                return a.first > b.first;
            });

            // Write each coin denomination and count to the file
            for (const auto& pair : coinVector) {
                const int denomination = getValue(pair.first);
                const unsigned count = pair.second;
                file << denomination << DELIM << count << "\n";

                // Check if the write was successful
                if (file.fail()) {
                    std::cerr << "Failed to write coin value: " << denomination
                    << " to file: " << filename << std::endl;
                    allWritesSuccessful = false;
                }
            }
            success = allWritesSuccessful;
        } else {
            std::cerr << "No coins to write to file." << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }

    return success;
}



std::vector<Denomination> CoinManager::calculateChange(unsigned int amount) {
    std::vector<Denomination> change;
    std::vector<Denomination> denominations = {FIFTY_DOLLARS, TWENTY_DOLLARS,
                                               TEN_DOLLARS, FIVE_DOLLARS,
                                               TWO_DOLLARS, ONE_DOLLAR,
                                               FIFTY_CENTS, TWENTY_CENTS,
                                               TEN_CENTS, FIVE_CENTS};

    bool exactAmountReached = false;

    // Calculate change using available denominations
    for (Denomination denom : denominations) {
        while (amount >= static_cast<unsigned int>(getValue(denom))
               && coins[denom] > DEFAULT_DENOM_COUNT
               && !exactAmountReached) {
            // Subtract denomination value
            amount -= static_cast<unsigned int>(getValue(denom));
            // Add denomination to change vector
            change.push_back(denom);

            if (amount == DEFAULT_DENOM_COUNT) {
                // Exact amount reached
                exactAmountReached = true;
            }
        }
    }

    if (amount > DEFAULT_DENOM_COUNT) {
        std::cerr << "Insufficient change available." << std::endl;
        // Clear the change vector if insufficient change is available
        change.clear();
    }

    /*
     * Return change (empty if insufficient change,
     * otherwise contains change denominations)
     */
    return change;
}

/*
 * The dispenseCoins function is responsible for dispensing coins
 * based on the specified denominations.
*/
void CoinManager::dispenseCoins(const std::vector<Denomination>& denominations)
{
    for (const Denomination& denom : denominations) {
        if (coins[denom] > DEFAULT_DENOM_COUNT) {
            // Decrement the count for the specified denomination
            coins[denom]--;
        } else {
            //Print an error message if insufficient coins of this denomination
            std::cerr<< "Error: Attempt to dispense "
                       "an unavailable denomination of " << getValue(denom)
                       << " cents." << std::endl;
        }
    }
}