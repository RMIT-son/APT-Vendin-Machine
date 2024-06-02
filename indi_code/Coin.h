#ifndef COIN_H
#define COIN_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

// Coin.h defines the coin structure for managing currency in the system.

// The delimiter used in the file to separate the denomination and count.
#define DELIM ','

// The value of each denomination in cents.
#define FIVE_CENTS_VALUE 5
#define TEN_CENTS_VALUE 10
#define TWENTY_CENTS_VALUE 20
#define FIFTY_CENTS_VALUE 50
#define ONE_DOLLAR_VALUE 100
#define TWO_DOLLARS_VALUE 200
#define FIVE_DOLLARS_VALUE 500
#define TEN_DOLLARS_VALUE 1000
#define TWENTY_DOLLARS_VALUE 2000
#define FIFTY_DOLLARS_VALUE 5000
#define DEFAULT_DENOM_COUNT 0

// enumeration representing the various types of currency
// available in the system.
enum Denomination
{
    FIVE_CENTS, TEN_CENTS, TWENTY_CENTS, FIFTY_CENTS, ONE_DOLLAR, 
    TWO_DOLLARS, FIVE_DOLLARS, TEN_DOLLARS, TWENTY_DOLLARS, FIFTY_DOLLARS
};


// represents a coin type stored in the cash register perhaps.
// Each demonination will have exactly one of these in the cash register.
class Coin
{
public:
    explicit Coin(Denomination denom);
    ~Coin();
    // the denomination type
    Denomination denom;

};

class CoinManager
{
public:
    /**
     * @brief Default constructor for CoinManager
     * @details This constructor initializes the CoinManager object.
     */
    CoinManager();

    /**
     * @brief Default destructor for CoinManager
     * @details This destructor clears the CoinManager object.
     */
    ~CoinManager() = default;

    /**
     * @brief Get the coins in the CoinManager object
     * @details This function returns the coins in the CoinManager object.
     * @return The coins in the CoinManager object
     */
    std::unordered_map<Denomination, unsigned> getCoins() const;

    /**
     * @brief Add a coin to the CoinManager object
     * @details This function adds a coin to the CoinManager object.
     * @param denom The denomination of the coin to add
     * @param count The number of coins to add
     * @return True if the coin was added, false otherwise
     */
    bool addCoin(Denomination denom, unsigned count);

    /**
     * @brief Remove a coin from the CoinManager object
     * @details This function removes a coin from the CoinManager object.
     * @param denom The denomination of the coin to remove
     * @param count The number of coins to remove
     * @return True if the coin was removed, false otherwise
     */
    bool removeCoin(Denomination denom, unsigned count);

    /**
     * @brief Read coins from a file
     * @details This function reads coins from a file.
     * @param filename The name of the file to read from
     */
    void readFromFile(const std::string& filename);

    /**
     * @brief Write coins to a file
     * @details This function writes coins to a file.
     * @param filename The name of the file to write to
     * @return True if the coins were written, false otherwise
     */
    bool writeToFile(const std::string& filename) const;

    /**
     * @brief Get the value of a denomination
     * @details This function gets the value of a denomination.
     * @param denom The denomination to get the value of
     * @return The value of the denomination
     */
    static int getValue(Denomination denom);

    /**
     * @brief Get the denomination of a value
     * @details This function gets the denomination of a value.
     * @param value The value to get the denomination of
     * @return The denomination of the value
     */
    static Denomination getDenomination(int value);

    // Coins Map to store the count of each denomination
    std::unordered_map<Denomination, unsigned> coins;
    std::vector<Denomination> calculateChange(unsigned amount);
    void dispenseCoins(const std::vector<Denomination>& denominations);
};

#endif // COIN_H
