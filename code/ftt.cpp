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
                    running = false;
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
