#include "Coin.h"

Coin::Coin(Denomination denom) {
    this->denom = denom;
}

Coin::~Coin() {
    delete this;
}

CoinManager::CoinManager() {
    // Initialize the counts for all denominations to 0
    for (int i = FIVE_CENTS; i <= FIFTY_DOLLARS; i++) {
        coins[static_cast<Denomination>(i)] = 0;
    }
}

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

std::unordered_map<Denomination, unsigned> CoinManager::getCoins() const {
    return coins;
}

bool CoinManager::addCoin(Denomination denom, unsigned count) {
    // Add the coin count to the denomination
    coins[denom] += count;
    return true;
}

bool CoinManager::removeCoin(Denomination denom, unsigned count) {
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

        // Read each line from the file and add the coin denomination and count to the coins map
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
                    std::cerr << "Invalid line or coin value: " << line << std::endl;
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


bool CoinManager::writeToFile(const std::string& filename) {
    bool success = false;
    std::ofstream file(filename);

    if (file.is_open()) {
        // Write each coin denomination and count to the file
        if (!coins.empty()) {
            bool allWritesSuccessful = true;

            // Write each coin denomination and count to the file
            for (const auto& pair : coins) {
                int denomination = getValue(pair.first);
                unsigned count = pair.second;
                file << denomination << DELIM << count << "\n";

                // Check if the write was successful
                if (file.fail()) {
                    std::cerr << "Failed to write coin value: " << denomination << " to file: " << filename << std::endl;
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

    for (Denomination denom : denominations) {
        while (amount >= static_cast<unsigned int>(getValue(denom))
        && coins[denom] > 0) {
            amount -= static_cast<unsigned int>(getValue(denom));
            change.push_back(denom);
        }
        if (amount == 0) {
            return change;
        }
    }

    if (amount > 0) {
        std::cerr << "Insufficient change available." << std::endl;
    }

    return change;
}

void CoinManager::dispenseCoins(const std::vector<Denomination>& denominations)
{
    for (const Denomination& denom : denominations) {
        if (coins[denom] > 0) {
            coins[denom]--;
        } else {
            std::cerr<< "Error: Attempt to dispense "
                       "an unavailable denomination of " << getValue(denom)
                       << " cents." << std::endl;
        }
    }
}