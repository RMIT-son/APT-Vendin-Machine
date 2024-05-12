#include <iostream>
#include "LinkedList.h"

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options.
 * Make sure free memory and close all files before exiting the program.
 **/

std::string readInput()
{
   std::string input;
   std::getline(std::cin, input);
   std::cout << std::endl;

   return input;
}

bool isNumber(std::string s)
{
   std::string::const_iterator it = s.begin();
   while (it != s.end() && std::isdigit(*it)) ++it;
   return !s.empty() && it == s.end();
}


int main(int argc, char **argv)
{
    bool running = true;

    while (running) {
        std::cout << "Main Menu:" << std::endl;
        std::cout << "   1. Display Meal Options" << std::endl;
        std::cout << "   2. Purchase Meal" << std::endl;
        std::cout << "   3. Save and Exit" << std::endl;
        std::cout << "Administrator-Only Menu:" << std::endl;
        std::cout << "   4. Add Food" << std::endl;
        std::cout << "   5. Remove Food" << std::endl;
        std::cout << "   6. Display Balance" << std::endl;
        std::cout << "   7. Abort Program" << std::endl;
        std::cout << "Select your option (1-7) : ";

        std::string input = readInput();
        if (isNumber(input)) {
            int option = std::stoi(input);
            if (option > 0 && option < 8) {
                if (option == 1) {

                } else if (option == 2) {

                } else if (option == 3) {
                    
                } else if (option == 4) {
                    
                } else if (option == 5) {
                    
                } else if (option == 6) {
                    
                } else if (option == 7) {
                    running = false;
                } else {
                    std::cout << "Error: number was outside of range." << std::endl;
                }
            }
        } else {
            std::cout << "Error: input was not numeric." << std::endl;
            std::cout << "Error in input. Please try again." << std::endl;
        }


    }
    

    return EXIT_SUCCESS;
}

void purchaseMeal(LinkedList& foodList, Coin coins[], int numCoins) {
    std::string id;
    std::cout << "Purchase Meal" << std::endl;
    std::cout << "Please enter the ID of the food you wish to purchase: ";
    std::getline(std::cin, id);

    // Find the food item with the given ID in the foodList
    Node* node = foodList.find(id);
    if (node == nullptr) {
        std::cout << "Error: Food item with ID " << id << " not found." << std::endl;
        return;
    }

    // Check if the food item is in stock
    if (node->data.on_hand == 0) {
        std::cout << "Error: No more " << node->data.name << " available." << std::endl;
        return;
    }

    // Display the selected food item and prompt the user to enter payment
    std::cout << "You have selected \"" << node->data.name << " - " << node->data.description << "\". This will cost you $"
              << static_cast<double>(node->data.price.dollars) + static_cast<double>(node->data.price.cents) / 100 << "." << std::endl;
    std::cout << "Please hand over the money - type in the value of each note/coin in cents." << std::endl;
    std::cout << "Please enter ctrl-D or enter on a new line to cancel this purchase." << std::endl;

    unsigned totalPaid = 0;
    unsigned denomination;
    std::vector<unsigned> denominations;
    while (true) {
        // Display the remaining amount to be paid
        std::cout << "You still need to give us $"
                  << std::setw(6) << std::fixed << std::setprecision(2)
                  << static_cast<double>(node->data.price.dollars) + static_cast<double>(node->data.price.cents) / 100 - static_cast<double>(totalPaid) / 100
                  << ": ";

        // Read the next denomination from the user
        if (!(std::cin >> denomination)) {
            std::cout << std::endl << "Purchase cancelled." << std::endl;
            return;
        }

        // Check if the user wants to cancel the purchase
        if (denomination == 0) {
            std::cout << std::endl << "Purchase cancelled." << std::endl;
            return;
        }

        // Validate the entered denomination
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

        // Add the valid denomination to the total paid and the denominations vector
        totalPaid += denomination;
        denominations.push_back(denomination);

        // Check if the total paid is greater than or equal to the price of the food item
        if (totalPaid >= node->data.price.dollars * 100 + node->data.price.cents) {
            unsigned change = totalPaid - (node->data.price.dollars * 100 + node->data.price.cents);
            std::cout << "Your change is ";

            // Dispense the change to the customer
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
    // Print the header for the balance summary
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

    // Calculate the total balance
    double totalBalance = 0.0;
    for (const Coin& coin : sortedCoins) {
        // Only display coins with a non-zero quantity
        if (coin.count > 0) {
            // Print the denomination, quantity, and value of the coin
            std::cout << std::setw(5) << coin.getValue() << " | "
                      << std::setw(7) << std::right << coin.count << " | $ "
                      << std::setw(6) << std::fixed << std::setprecision(2) << std::right
                      << static_cast<double>(coin.getValue()) * coin.count / 100
                      << std::endl;
            totalBalance += static_cast<double>(coin.getValue()) * coin.count / 100;
        }
    }

    // Print the total balance
    std::cout << "---------------------------" << std::endl;
    std::cout << std::setw(17) << std::right << "$" << std::setw(6) << std::fixed << std::setprecision(2) << totalBalance << std::endl;
}