#include <iostream>
#include "LinkedList.h"
#include "Food.h"
#include "Coin.h"
#include "Interface.h"

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options.
 * Make sure free memory and close all files before exiting the program.
 **/

int main(int argc, char **argv)
{
    int res = 0;
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <food_file> <coin_file>"
        << std::endl;
        res = 1;
    } else {

    std::string foodFile = argv[1];
    std::string coinFile = argv[2];

    bool running = true;
    CoinManager manager;
    manager.readFromFile(coinFile);
    Food foodList;
    foodList.readFromFile(foodFile);

    while (running) {
        Interface::displayMainMenu();
        std::string input = Helper::readInput();
        if (std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                            '\n');
            std::cout << "Error in input. Please try again." << std::endl;
        } else
        if (Helper::isNumber(input)) {
            const int option = std::stoi(input);
            if (option > 0 && option < 8)
            {
                if (option == 1)
                {
                    Interface::displayFoodMenu(foodList);
                }
                else if (option == 2)
                {
                    Interface::purchaseMeal(foodList, manager);
                }
                else if (option == 3)
                {
                    running = false;
                    foodList.writeToFile(foodFile);
                    manager.writeToFile(coinFile);
                }
                else if (option == 4)
                {
                    Interface::addFood(foodList);
                }
                else if (option == 5)
                {
                    Interface::removeFood(foodList);
                }
                else if (option == 6)
                {
                    Interface::displayBalance(manager);
                }
                else if (option == 7)
                {
                    running = false;
                }
            }
            else
            {
                std::cout << "Error: number was outside of range."<< std::endl;
            }
        }
            else
            {
                std::cout << "Error: input was not numeric." << std::endl;
                // TODO use Helper function to replace this
                std::cout << "Error in input. Please try again." << std::endl;
            }
        }
    }
    return res;
}
