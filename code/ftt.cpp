#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include <memory>
#include <map>
#include "LinkedList.h"
#include "Food.h"
#include "Coin.h"

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options.
 * Make sure free memory and close all files before exiting the program.
 **/

std::string readInput()
{
    std::string input;
    if (std::getline(std::cin, input)) {
        std::cout << std::endl;
        return input;
    } else if (std::cin.eof()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "EOF encountered. Please enter a valid input." << std::endl;
        return std::string();
    } else {
        return std::string();
    }
}

bool isNumber(std::string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

void displayMainMenu()
{
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
}

void displayFoodMenu(Food &foodList)
{
    const Node *current = foodList.getHead();
    std::cout << "Food Menu\n"
              << "---------\n";
    std::cout << "ID    |Name                                             |Price\n";
    std::cout << "---------------------------------------------------------------\n";
    while (current != nullptr)
    {
        std::cout << std::left << std::setw(6) << current->data->id
                  << "|" << std::setw(49) << current->data->name
                  << "|" << "$" << current->data->price.dollars << "." << current->data->price.cents
                  << std::endl;
        current = current->next.get();
    }
}

void purchaseMeal(Food &foodList, CoinManager &coinManager)
{ // Added CoinManager reference
    bool running = true;

    std::cout << "Purchase Meal" << std::endl;
    std::cout << "-------------" << std::endl;
    while (running) {
        std::cout << "Please enter the ID of the food you wish to purchase: ";
        std::string id = readInput();
        if (!std::cin.eof()) {
        FoodItem *foodItem = foodList.findFood(id);
            if (foodItem == nullptr)
            {
                std::cout << "Item not found. Please check the food ID and try again." << std::endl;
            }
            else
            {
                if (foodItem->on_hand == 0)
                {
                    std::cout << "Error: No more " << foodItem->name << " available." << std::endl;
                }
                else
                {
                    std::cout << "You have selected \"" << foodItem->name << " - " << foodItem->description << "\". This will cost you $"
                              << static_cast<double>(foodItem->price.dollars) + static_cast<double>(foodItem->price.cents) / 100 << "." << std::endl;
                    std::cout << "Please hand over the money - type in the value of each note/coin in cents." << std::endl;
                    std::cout << "Please enter ctrl-D or enter on a new line to cancel this purchase." << std::endl;

                    unsigned int totalPaid = 0;
                    bool denominating = true;
                    while (denominating)
                    {
                        std::cout << "You still need to give us $"
                                  << std::setw(6) << std::fixed << std::setprecision(2)
                                  << static_cast<double>(foodItem->price.dollars) + static_cast<double>(foodItem->price.cents) / 100 - static_cast<double>(totalPaid) / 100
                                  << ": ";
                        std::string denomination = readInput();

                        if (denomination == "" || std::cin.eof())
                        {
                            std::cout << std::endl
                                      << "Purchase cancelled." << std::endl;
                            std::cin.clear();
                            running = false;
                            denominating = false;
                            continue;
                        }

                        if (!isNumber(denomination))
                        {
                            std::cout << std::endl
                                      << "Error: input was not numeric." << std::endl;
                            continue;
                        }
                        else
                        {
                            if (!Helper::isValidDenomination(denomination))
                            {
                                std::cout << "Error: invalid denomination encountered." << std::endl;
                            }
                            else
                            {
                                Denomination denom = coinManager.getDenomination(std::stoi(denomination));
                                coinManager.addCoin(denom, 1); // Adding the money to the machine
                                totalPaid += std::stoi(denomination);
                                if (totalPaid >= foodItem->price.dollars * 100 + foodItem->price.cents)
                                {
                                    unsigned change = totalPaid - (foodItem->price.dollars * 100 + foodItem->price.cents);
                                    // Calculate and dispense change
                                    std::vector<Denomination> changeDenominations = coinManager.calculateChange(change);
                                    coinManager.dispenseCoins(changeDenominations); // Decrement the counts
                                    std::cout << "Your change is ";
                                    for (auto denom : changeDenominations)
                                    {
                                        unsigned int value = coinManager.getValue(denom);
                                        if (value >= 100)
                                        {                                    // This assumes that any value 100 cents or higher should be displayed in dollars
                                            std::cout << "$" << value / 100; // Divides by 100 to convert cents to dollars
                                        }
                                        else
                                        {
                                            std::cout << value << "c"; // For values less than 100, display as cents
                                        }
                                        std::cout << " "; // Add a space after each denomination for separation
                                    }
                                    std::cout << std::endl; // New line after listing all denominations
                                    std::cout << std::endl;
                                    foodItem->on_hand--;
                                    std::cout << "Thank you for your purchase!" << std::endl;
                                    running = false;
                                    denominating = false;
                                }
                            }
                        }
                    }
                }
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Purchase Cancelled" << std::endl;
            running = false;
            break;
        }
    }
}

void addFood(Food &foodList)
{
    bool running = true;
    while (running)
    {
        std::string newId;
        newId = foodList.generateID();
        std::cout << "This new meal item will have the Item ID of " << newId << std::endl;
        std::cout << "Enter the item name: ";
        std::string foodName = readInput();
        if (std::cin.eof() || foodName == "")
        {
            std::cin.clear();
            // running = false;
            std::cout << "Option cancelled, returning to menu." << std::endl;
            break;
        }

        std::cout << "Enter the item description: ";
        std::string foodDescription = readInput();

        if (std::cin.eof() || foodDescription == "")
        {
            std::cin.clear();
            // running = false;
            std::cout << "Option cancelled, returning to menu." << std::endl;
            break;
        }

        bool priceValid = true;
        while (priceValid)
        {
            std::cout << "Enter the price for this item: ";
            std::string foodPrice = readInput();
            if (Helper::isValidPrice(foodPrice))
            {
                running = false;
                priceValid = false;
                std::shared_ptr<FoodItem> newFood = std::make_shared<FoodItem>();
                newFood->id = newId;
                newFood->name = foodName;
                newFood->description = foodDescription;
                newFood->price = Helper::readPrice(foodPrice);
                foodList.addFood(newFood);
            }
            else
            {
                std::cout << "Error: money is not formatted properly" << std::endl;
            }
        }
    }
}

void removeFood(Food &foodList) {
    std::cout << "Enter the food id of the food to remove from the menu: ";
    std::string foodId = readInput();
    if (!std::cin.eof()) {
        if (foodList.removeFood(foodId)) {
            std::cout << "Food item removed successfully." << std::endl;
        } else {
            std::cout << "Error: food item not found." << std::endl;
        }
    } else {
        std::cin.clear();
        // TODO change this to use a helper function
        std::cout << "Option cancelled. Returning to Menu" << std::endl;
    }
}

void displayBalance(CoinManager &manager)
{
    std::map<Denomination, unsigned> sortedCoins(manager.coins.begin(), manager.coins.end());

    double totalValue = 0.0;
    std::cout << "Balance Summary\n";
    std::cout << "----------------\n";
    std::cout << "Denom | Quantity | Value\n";
    std::cout << "---------------------------\n";

    for (const auto &pair : sortedCoins)
    {
        int denomination = manager.getValue(pair.first);
        unsigned count = pair.second;
        double value = count * (denomination / 100.0);

        std::cout << std::right << std::setw(5) << denomination << " | "
                  << std::setw(8) << count << " |$"
                  << std::setw(7) << std::fixed << std::setprecision(2) << value << std::endl;

        totalValue += value;
    }

    std::cout << "---------------------------\n";
    std::cout << "Total:            $" << std::setw(7) << std::fixed << std::setprecision(2) << totalValue << std::endl;
}

int main(int argc, char **argv)
{

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <food_file> <coin_file>" << std::endl;
        return 1;
    }

    std::string foodFile = argv[1];
    std::string coinFile = argv[2];

    bool running = true;
    CoinManager manager;
    manager.readFromFile(coinFile);
    Food foodList;
    foodList.readFromFile(foodFile);

    while (running) {
        displayMainMenu();
        std::string input = readInput();
        if (std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // TODO use Helper function to replace this
            std::cout << "Error in input. Please try again." << std::endl;
        } else
        if (isNumber(input)) {
            const int option = std::stoi(input);
            if (option > 0 && option < 8)
            {
                if (option == 1)
                {
                    displayFoodMenu(foodList);
                }
                else if (option == 2)
                {
                    purchaseMeal(foodList, manager);
                }
                else if (option == 3)
                {
                    running = false;
                    foodList.writeToFile(foodFile);
                    manager.writeToFile(coinFile);
                }
                else if (option == 4)
                {
                    addFood(foodList);
                }
                else if (option == 5)
                {
                    removeFood(foodList);
                }
                else if (option == 6)
                {
                    displayBalance(manager);
                }
                else if (option == 7)
                {
                    running = false;
                }
            }
            else
            {
                std::cout << "Error: number was outside of range." << std::endl;
            }
        }
            else
            {
                std::cout << "Error: input was not numeric." << std::endl;
                // TODO use Helper function to replace this
                std::cout << "Error in input. Please try again." << std::endl;
            }
        }
    return EXIT_SUCCESS;
}
