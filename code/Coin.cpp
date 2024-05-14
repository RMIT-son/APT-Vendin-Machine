#include "Coin.h"
 // implement functions for managing coins

Coin::Coin(Denomination denom) {
    this->denom = denom;
}

Coin::~Coin() {
    delete this;
}


int CoinManager::getValue(Denomination denom) const {
    int value = 0;
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
    return value;
}

Denomination CoinManager::getDenomination(int value) {
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
        throw std::invalid_argument("Invalid coin value");
    }

    return denom;
}



CoinManager::CoinManager() {
    // Initialize the counts for all denominations to 0
    for (int i = FIVE_CENTS; i <= TWENTY_DOLLARS; i++) {
        coins[static_cast<Denomination>(i)] = 0;
    }
}

std::unordered_map<Denomination, unsigned> CoinManager::getCoins() const {
    return coins;
}
bool CoinManager::addCoin(Denomination denom, unsigned count) {
    // Increment the count for the specified denomination
    if (count < 0) {
        return false;
    }
    coins[denom] += count;
    return true;
}

bool CoinManager::removeCoin(Denomination denom, unsigned count) {
    // Decrement the count for the specified denomination, but don't go below 0
    if (coins[denom] >= count) {
        coins[denom] -= count;
        return true;
    } else {
        coins[denom] = 0;
        return false;
    }
}


void CoinManager::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string valueStr, countStr;
        std::getline(ss, valueStr, DELIM);
        std::getline(ss, countStr, DELIM);
        int value = std::stoi(valueStr);
        unsigned count = std::stoul(countStr);
        Denomination denom;
        try {
            denom = getDenomination(value);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid coin value: " << value << std::endl;
        }
        coins[denom] = count;
    }
    file.close();
}

bool CoinManager::writeToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    if (coins.empty()) {
        std::cerr << "No coins to write to file." << std::endl;
        return false;
    }

    for (const auto& pair : coins) {
        // Directly use the denomination and count from the coins map
        int denomination = getValue(pair.first);
        unsigned count = pair.second;
        file << denomination << DELIM << count << "\n";
        if (file.fail()) {
            std::cerr << "Failed to write to file: " << filename << std::endl;
            return false;
        }

        std::cout << "Wrote denomination: " << denomination << " count: "
        << count << " to file." << std::endl;
    }

    file.close();
    if (file.fail()) {
        std::cerr << "Failed to close file: " << filename << std::endl;
        return false;
    }

    return true;
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
        if (amount == 0) break;
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
            // Depending on system design,
            // you might want to handle the error differently
            // throw std::runtime_error
            // ("Attempt to dispense an unavailable denomination.");
        }
    }
}