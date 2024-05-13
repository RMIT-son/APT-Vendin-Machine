#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <algorithm>
#include <memory>
#include "LinkedList.h"
#include "Food.h"

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

void displayMainMenu() {
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

void displayFoodMenu(Food& foodList) {
    const Node* current = foodList.getHead();
    std::cout << "Food Menu\n" << "---------\n";
    std::cout << "ID   |Name                                              |Price\n";
    std::cout << "---------------------------------------------------------------\n";
    while (current != nullptr) {
        std::cout << std::left << std::setw(6) << current->data->id
          << "|" << std::setw(49) << current->data->name  
          << "|" << "$" << current->data->price.dollars << "." << current->data->price.cents    
          << std::endl;
        current = current->next.get();
    }
}

void purchaseMeal(Food& foodList) {
    bool running = true;

    while (running) {
        std::cout << "Purchase Meal" << std::endl;
        std::cout << "-------------" << std::endl;
        std::cout << "Please enter the ID of the food you wish to purchase: ";
        std::string id = readInput();

        
        FoodItem* foodItem = foodList.findFood(id);
        if (foodItem == nullptr) {
            std::cout << "Error: Food item with ID " << id << " not found." << std::endl;
            return;
        }


        if (foodItem->on_hand == 0) {
            std::cout << "Error: No more " << foodItem->name << " available." << std::endl;
            return;
        }

        std::cout << "You have selected \"" << foodItem->name << " - " << foodItem->description << "\". This will cost you $"
                << static_cast<double>(foodItem->price.dollars) + static_cast<double>(foodItem->price.cents) / 100 << "." << std::endl;
        std::cout << "Please hand over the money - type in the value of each note/coin in cents." << std::endl;
        std::cout << "Please enter ctrl-D or enter on a new line to cancel this purchase." << std::endl;

        unsigned totalPaid = 0;
        bool denominating = true;
        std::vector<unsigned> denominations;
        while (denominating) {
            std::cout << "You still need to give us $"
                    << std::setw(6) << std::fixed << std::setprecision(2)
                    << static_cast<double>(foodItem->price.dollars) + static_cast<double>(foodItem->price.cents) / 100 - static_cast<double>(totalPaid) / 100
                    << ": ";
            std::string denomination = readInput();

            if (denomination == "") {
                std::cout << std::endl << "Purchase cancelled." << std::endl;
                running = false;
                denominating = false;
            }

            if (!isNumber(denomination)) {
                std::cout << std::endl << "Error: input was not numeric." << std::endl;
            } 
        }
    }
}

void addFood(Food& foodList) {
    bool running = true;
    while(running) {
        std::cout << "This new meal item will have the Item id of F000" << "" << std::endl; 
        std::cout << "Enter the item name: "; 
        std::string foodName = readInput();
        std::cout << "Enter the item description: ";
        std::string foodDescription = readInput();

        bool priceValid = true;
        while (priceValid) {
            std::cout << "Enter the price for this item: ";
            std::string foodPrice = readInput();
            if(Helper::isValidPrice(foodPrice)) {
                running = false;
                priceValid = false;
                std::shared_ptr<FoodItem> newFood = std::make_shared<FoodItem>();
                newFood->id = "F1234";
                newFood->name = foodName;
                newFood->description = foodDescription;
                newFood->price = Helper::readPrice(foodPrice); 

                foodList.addFood(newFood);
            } else {
                std::cout << "Error: money is not formatted properly" << std::endl;
            }
        }
    }
}

void removeFood(Food& foodList) {
    const Node* current = foodList.getHead();
    std::cout << "Enter the food id of the food to remove from the menu: "; 
    std::string foodId = readInput();
    while (current != nullptr) {
        if (current->data->id == foodId) {
            std::cout << "'" 
            << current->data->id 
            << " - " 
            << current->data->name 
            << " - " 
            << current->data->description 
            << "' " 
            <<"has been removed from the system."
            << std::endl;
            foodList.removeFood(current->data->id);
        }
        current = current->next.get();
    }
}

void displayBalance(const Coin coins[], int numCoins) {
    std::cout << "Balance Summary\n";
    std::cout << "---------------\n";
    std::cout << "Denom  | Quantity | Value\n";
    std::cout << "---------------------------\n";

    double totalValue = 0;
    for (int i = 0; i < numCoins; i++) {
        double value = coins[i].getValue();
        totalValue += value;

        std::cout << std::right << std::setw(5) << coins[i].denom << "   | "
                  << std::setw(8) << coins[i].count << "   |$"
                  << std::setw(7) << std::fixed << std::setprecision(2) << value << std::endl;
    }

    std::cout << "---------------------------\n";
    std::cout << "                   $" << std::setw(7) << std::setprecision(2) << totalValue << std::endl;
}


int main(int argc, char **argv)
{
    bool running = true;
    Food foodList;
    foodList.readFromFile("foods.dat");

    while (running) {
        displayMainMenu();
        std::string input = readInput();
        if (isNumber(input)) {
            int option = std::stoi(input);
            if (option > 0 && option < 8) {
                if (option == 1) {
                    displayFoodMenu(foodList);
                } else if (option == 2) {
                    purchaseMeal(foodList);
                } else if (option == 3) {
                    running = false;
                } else if (option == 4) {
                    addFood(foodList);
                } else if (option == 5) {
                    removeFood(foodList);
                } else if (option == 6) {
                
                } else if (option == 7) {
                    running = false;
                } 
            } else {
                    std::cout << "Error: number was outside of range." << std::endl;
            }
        } else {
            std::cout << "Error: input was not numeric." << std::endl;
            std::cout << "Error in input. Please try again." << std::endl;
        }
    }
    

    return EXIT_SUCCESS;
}
