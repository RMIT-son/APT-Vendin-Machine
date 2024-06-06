#include <iostream>
#include "Food.h"
#include "Coin.h"
#include "Menu.h"
#include "Command.h"

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options.
 * Make sure free memory and close all files after exiting the program.
 **/
int main(const int argc, char **argv) {
    int res = EXIT_SUCCESS;
    if (argc < 3) {
        // Check if the command-line arguments are less than 3
        std::cerr << "Usage: " << argv[0] << " <food_file> <coin_file>"
                  << std::endl;
        // Set the result to 1 to indicate an error
        res = EXIT_FAILURE;
    } else {
        // Get the food file name from command-line argument
        const std::string foodFile = argv[1];
        // Get the coin file name from command-line argument
        const std::string coinFile = argv[2];

        // Flag to control the main loop
        bool running = true;
        // Flags to control the enhancements
        bool helpToggle = false;
        bool colorToggle = false;
        // Create an instance of CoinManager class
        CoinManager coinsManager;
        // Read coin data from the coin file
        coinsManager.readFromFile(coinFile);
        // Create an instance of Food class
        Food foodList;
        // Read food data from the food file
        foodList.readFromFile(foodFile);

        Menu menu;
        // Set the commands for the menu
        menu.setCommand(1, std::make_unique<DisplayMealOptionsCommand>(&foodList));
        menu.setCommand(2, std::make_unique<PurchaseMealCommand>(&foodList, &coinsManager,
                                                                                helpToggle, colorToggle));
        menu.setCommand(3, std::make_unique<SaveAndExitCommand>(foodList,
                                                                                coinsManager,
                                                                                foodFile,
                                                                                coinFile,
                                                                                running,
                                                                                res));
        menu.setCommand(4, std::make_unique<AddFoodCommand>(&foodList, helpToggle));
        menu.setCommand(5, std::make_unique<RemoveFoodCommand>(&foodList, helpToggle));
        menu.setCommand(6, std::make_unique<DisplayBalanceCommand>(&coinsManager));
        menu.setCommand(7, std::make_unique<AbortProgramCommand>(running));
        menu.setCommand(8, std::make_unique<EnhancementsCommand>(helpToggle, colorToggle));
        while (running) {
            // Display the main menu
            Interface::displayMainMenu();
            // Read user input
            std::string input = Helper::readInput();
            if (std::cin.eof()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error in input. Please try again." << std::endl;
            } else if (helpToggle && input == HELP_COMMAND) {
                Interface::help(MAIN_MENU);
            } else if (Helper::isNumber(input)) {
                const int option = std::stoi(input);
                menu.executeCommand(option);
            } else {
                std::cout << "Error: input was not numeric." << std::endl;
                std::cout << "Error in input. Please try again." << std::endl;
            }
        }
    }
    return res;
}
