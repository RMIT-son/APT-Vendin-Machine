#include <iostream>
#include "MainLinkedList.h"
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
    int res = EXIT_SUCCESS;
    if (argc < 3)
    {
        // Check if the command-line arguments are less than 3
        std::cerr << "Usage: " << argv[0] << " <food_file> <coin_file> "
                  << std::endl;
        // Set the result to 1 to indicate an error
        res = EXIT_FAILURE;
    }
    else
    {
        // Get the food file name from command-line argument
        std::string foodFile = argv[1];
        // Get the coin file name from command-line argument
        std::string coinFile = argv[2];

        Interface interface;
        // Flag to control the main loop
        bool running = true;
        // Create an instance of CoinManager class
        CoinManager manager;
        // Read coin data from the coin file
        manager.readFromFile(coinFile);
        // Create an instance of Food class
        Food foodList;

        // Create an instance of MainLinkedList for enhanced food items
        MainLinkedList foodEnhancementList;
    
        // Read enhanced food data from the food file
        foodList.readFromEnhancementFile(foodFile, foodEnhancementList);

        while (running)
        {
            // Display the main menu
            interface.displayMainMenu();
            // Read user input
            std::string input = Helper::readInput();

            if (std::cin.eof())
            {
                // Check if the input stream encountered end-of-file condition
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                '\n');
                std::cout << "Error in input. Please try again." << std::endl;
            }
            else if (Helper::isNumber(input))
            {
                // Check if the input is a numeric value
                const int option = std::stoi(input);
                // Convert the input to an integer

                if (option > 0 && option < 10)
                {
                    // Check if the option is within the valid range

                    if (option == 1)
                    {
                        interface.displayFoodMenu(foodEnhancementList);
                    }
                    else if (option == 2)
                    {
                        interface.purchaseMealEnhancement(foodEnhancementList, manager);
                    }
                    else if (option == 3)
                    {
                        // Stop the main loop
                        running = false;
                        // Write food data to the food file
                        foodEnhancementList.writeToFile(foodFile);
                        // Write coin data to the coin file
                        manager.writeToFile(coinFile);
                    }
                    else if (option == 4)
                    {
                        // Allow the user to add a new food item
                        interface.addFoodEnhancement(foodEnhancementList);
                    }
                    else if (option == 5)
                    {
                        interface.removeFoodEnhancement(foodEnhancementList);
                    }
                    else if (option == 6)
                    {
                        // Display the current coin balance
                        interface.displayBalance(manager);
                    }
                    else if (option == 7)
                    {
                        if (interface.getColor())
                        {
                            interface.setColor(false);
                        }
                        else
                        {
                            interface.setColor(true);
                        }
                    }
                    else if (option == 8)
                    {
                        if (interface.getEnhancement())
                        {
                            interface.setEnhancement(false);
                        }
                        else
                        {
                            interface.setEnhancement(true);
                        }
                    }
                    else if (option == 9)
                    {
                        // Stop the main loop
                        running = false;
                    }
                }
                else
                {
                    std::cout << "Error: number was outside of range."
                              << std::endl;
                }
            }
            else
            {
                std::cout << "Error: input was not numeric." << std::endl;
                std::cout << "Error in input. Please try again." << std::endl;
            }
        }
    }
    // Return the result of the program execution
    return res;
}