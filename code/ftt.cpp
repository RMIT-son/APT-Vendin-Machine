#include <iostream>
#include "LinkedList.h"

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv)
{
    /* validate command line arguments */
    // TODO

    std::cout << "Just a test, nothing implemented yet!" << std::endl;
    
    return EXIT_SUCCESS;
}

void purchaseMeal(LinkedList& foodList, Coin coins[], int numCoins) {
    std::string id;
    std::cout << "Purchase Meal" << std::endl;
    std::cout << "Please enter the ID of the food you wish to purchase: ";
    std::getline(std::cin, id);

    Node* node = foodList.find(id);
    if (node == nullptr) {
        std::cout << "Error: Food item with ID " << id << " not found." << std::endl;
        return;
    }

    if (node->data.on_hand == 0) {
        std::cout << "Error: No more " << node->data.name << " available." << std::endl;
        return;
    }

    std::cout << "You have selected \"" << node->data.name << " - " << node->data.description << "\". This will cost you $"
              << static_cast<double>(node->data.price.dollars) + static_cast<double>(node->data.price.cents) / 100 << "." << std::endl;
    std::cout << "Please hand over the money - type in the value of each note/coin in cents." << std::endl;
    std::cout << "Please enter ctrl-D or enter on a new line to cancel this purchase." << std::endl;

    unsigned totalPaid = 0;
    unsigned denomination;
    std::vector<unsigned> denominations;
    while (true) {
        std::cout << "You still need to give us $"
                  << std::setw(6) << std::fixed << std::setprecision(2)
                  << static_cast<double>(node->data.price.dollars) + static_cast<double>(node->data.price.cents) / 100 - static_cast<double>(totalPaid) / 100
                  << ": ";

        if (!(std::cin >> denomination)) {
            std::cout << std::endl << "Purchase cancelled." << std::endl;
            return;
        }

        if (denomination == 0) {
            std::cout << std::endl << "Purchase cancelled." << std::endl;
            return;
        }

        bool validDenom = false;
        for (int i = 0; i < numCoins; i++) {
            if (coins[i].getValue() == static_cast<int>(denomination)) {
                validDenom = true;
                break;
            }
        }

        if (!validDenom) {
            std::cout << "Error: invalid denomination encountered." << std::endl;
            continue;
        }

        totalPaid += denomination;
        denominations.push_back(denomination);

        if (totalPaid >= node->data.price.dollars * 100 + node->data.price.cents) {
            unsigned change = totalPaid - (node->data.price.dollars * 100 + node->data.price.cents);
            std::cout << "Your change is ";

            for (unsigned int i = 0; i < denominations.size(); i++) {
                unsigned coinValue = denominations[i];
                unsigned coinCount = change / coinValue;
                if (coinCount > 0) {
                    std::cout << coinCount << "x $" << std::setw(2) << std::setfill('0') << std::fixed << std::setprecision(2)
                              << static_cast<double>(coinValue) / 100 << " ";
                    change -= coinCount * coinValue;
                }
            }

            std::cout << std::endl;
            node->data.on_hand--;
            std::cout << "Thank you for your purchase!" << std::endl;
            return;
        }
    }
}

void displayBalance(const Coin coins[], int numCoins) {
    std::cout << "Balance Summary" << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << std::setw(5) << "Denom" << " | "
              << std::setw(10) << "Quantity" << " | "
              << std::setw(6) << "Value" << std::endl;
    std::cout << "---------------------------" << std::endl;

    // Sort the coins in ascending order of denomination
    std::vector<Coin> sortedCoins(coins, coins + numCoins);
    std::sort(sortedCoins.begin(), sortedCoins.end(), [](const Coin& a, const Coin& b) {
        return a.getValue() < b.getValue();
    });

    double totalBalance = 0.0;
    for (const Coin& coin : sortedCoins) {
        if (coin.count > 0) {
            std::cout << std::setw(5) << coin.getValue() << " | "
                      << std::setw(7) << std::right << coin.count << " | $ "
                      << std::setw(6) << std::fixed << std::setprecision(2) << std::right
                      << static_cast<double>(coin.getValue()) * coin.count / 100
                      << std::endl;
            totalBalance += static_cast<double>(coin.getValue()) * coin.count / 100;
        }
    }

    std::cout << "---------------------------" << std::endl;
    std::cout << std::setw(17) << std::right << "$" << std::setw(6) << std::fixed << std::setprecision(2) << totalBalance << std::endl;
}