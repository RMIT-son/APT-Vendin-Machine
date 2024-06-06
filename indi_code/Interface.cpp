#include "Interface.h"

// Utility function to trim from start (in place)
static void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](const unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// Utility function to trim from end (in place)
static void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](const unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// Utility function to trim from both ends (in place)
static void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

void Interface::displayMainMenu()
{
    // Display the main menu options
    std::cout << "Main Menu:" << std::endl;
    std::cout << "   1. Display Meal Options" << std::endl;
    std::cout << "   2. Purchase Meal" << std::endl;
    std::cout << "   3. Save and Exit" << std::endl;

    // Display the administrator-only menu options
    std::cout << "Administrator-Only Menu:" << std::endl;
    std::cout << "   4. Add Food" << std::endl;
    std::cout << "   5. Remove Food" << std::endl;
    std::cout << "   6. Display Balance" << std::endl;
    std::cout << "   7. Abort Program" << std::endl;
    std::cout << "   8. Enhancements Menu" << std::endl;

    // Prompt the user to select an option
    std::cout << "Select your option (1-8) : ";
}

void Interface::displayFoodMenu(const Food &foodList)
{
    const EnhancedNode *current = foodList.getHead();

    // Display the food menu header
    std::cout << "Food Menu\n"
              << "---------\n";
    std::cout << "ID   |Name                                              |Price\n";
    std::cout << "------------------------------------------------------------------\n";

    while (current != nullptr)
    {
        /*
         * Trim the name to remove any leading
         * or trailing whitespace or non-visible characters*/
        std::string foodName = current->data->name;
        trim(foodName);

        // Print the food item details with proper formatting
        std::cout << std::left << std::setw(5) << current->data->id << "|"
                  << std::setw(50) << foodName << "|$"
                  << std::setw(2) << std::right
                  << current->data->price.dollars << "."
                  << std::setfill('0') << std::setw(2)
                  << current->data->price.cents
                  << std::setfill(' ') << std::endl;

        current = current->next.get();
    }
    std::cout << "\n";
}

void Interface::displayBalance(CoinManager &manager)
{
    // Sort the coins in ascending order based on their denomination
    const std::map<Denomination, unsigned> sortedCoins(manager.coins.begin(),
                                                       manager.coins.end());

    double totalValue = 0.0;

    // Display the balance summary header
    std::cout << "Balance Summary\n";
    std::cout << "----------------\n";
    std::cout << "Denom | Quantity | Value\n";
    std::cout << "---------------------------\n";

    // Iterate through the sorted coins and display their details
    for (const auto &pair : sortedCoins)
    {
        const int denomination = CoinManager::getValue(pair.first);
        const unsigned count = pair.second;
        const double value = count * (denomination / 100.0);

        // Print the denomination, quantity, and value of the coin
        std::cout << std::right << std::setw(5) << denomination << " | "
                  << std::setw(8) << count << " |$"
                  << std::setw(7) << std::fixed << std::setprecision(2)
                  << value << std::endl;
        totalValue += value;
    }

    // Display the total balance value
    std::cout << "---------------------------\n";
    std::cout << "Total:            $" << std::setw(7) << std::fixed <<
              std::setprecision(2) << totalValue << std::endl;
}
void Interface::purchaseMeal(const Food &foodList, CoinManager &coinManager, bool& helpToggle, bool& colorToggle)
{
    // Added CoinManager reference
    bool running = true;

    std::cout << "Purchase Meal" << std::endl;
    std::cout << "-------------" << std::endl;
  
    while (running) {
        std::cout << "Please enter the ID of the food you wish to purchase: ";
        std::string id = Helper::readInput();

        if (helpToggle && id == HELP_COMMAND) {
            help(PURCHASE_ID);

        // Check if input is empty or EOF (end of file)
        } else if (id.empty() || std::cin.eof()) {
            std::cin.clear();
            running = false;
            std::cout << "Option cancelled, returning to menu." << std::endl;
        } else {
            // Input is not empty or EOF
            if (!std::cin.eof()) {
                // Find the food item based on the provided ID
                FoodItem *foodItem = foodList.findFood(id);

                if (foodItem == nullptr)
                {
                    std::cout << "Item not found. Please check the food ID"
                                 " and try again." << std::endl;
                }
                else
                {
                    if (foodItem->on_hand == 0)
                    {
                        std::cout << "Error: No more " << foodItem->name
                        << " available." << std::endl;
                    }
                    else
                    {
                        std::cout << "You have selected \"" << foodItem->name
                                  << " - " << foodItem->description
                                  << "\". This will cost you $"
                                  << Helper::priceToString(foodItem->price)
                                  << std::endl;
                        std::cout << "Please hand over the money - "
                                     "type in the value of each note/"
                                     "coin in cents." << std::endl;
                        std::cout << "Please enter ctrl-D or enter on a new "
                                     "line to cancel this purchase."
                                     << std::endl;

                        unsigned int totalPaid = 0;
                        bool denominating = true;
                        std::vector<Denomination> addedDenominations;

                        /*
                         * Loop to handle denominations
                         * until the total payment is sufficient
                         */
                        while (denominating)
                        {
                            if (colorToggle) {
                                std::cout << "You still need to give us $"
                                          << GREEN
                                          << std::setw(6) << std::fixed
                                          << std::setprecision(2)
                                          << Helper::priceToString({
                                              (foodItem->price.dollars * 100 +foodItem->price.cents - totalPaid) / 100,
                                              (foodItem->price.dollars * 100 + foodItem->price.cents - totalPaid) % 100})
                                          << ESCAPE
                                          << ": ";
                            } else {
                                std::cout << "You still need to give us $"
                                          << std::setw(6) << std::fixed
                                          << std::setprecision(2)
                                          << Helper::priceToString({
                                              (foodItem->price.dollars * 100 +foodItem->price.cents - totalPaid) / 100,
                                              (foodItem->price.dollars * 100 + foodItem->price.cents - totalPaid) % 100})
                                          << ": ";
                            }
                            std::string denomination = Helper::readInput();

                            if (helpToggle && denomination == HELP_COMMAND) {
                                help(PURCHASE_DENOMINATION);
                            // Check if input is empty or EOF
                            } else if (denomination.empty() || std::cin.eof()) {
                                std::cout << std::endl << "Purchase cancelled."
                                << std::endl;
                                std::cin.clear();

                                // Process refund for added denominations
                                Helper::processRefund(coinManager,
                                                      addedDenominations);
                                running = false;
                                denominating = false;
                            }
                            else if (!Helper::isNumber(denomination))
                            {
                                std::cout << std::endl << "Error: input was "
                                                          "not numeric."
                                                          << std::endl;
                            }
                            else if(!Helper::isValidDenomination(denomination))
                            {
                                std::cout << "Error: invalid denomination"
                                             " encountered." << std::endl;
                            }
                            else
                            {
                                // Process payment and update total paid
                                Helper::processPayment(foodItem, coinManager,
                                                       totalPaid,
                                                       denomination,
                                                       addedDenominations);

                                // Check if total payment is sufficient
                                if (totalPaid >= foodItem->price.dollars * 100
                                + foodItem->price.cents)
                                {
                                    denominating = false;
                                    running = false;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                // Clear input and ignore remaining characters in the line
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                '\n');
                std::cout << "Purchase Cancelled" << std::endl;
                running = false;
            }
        }
    }
}

void Interface::addFood(Food &foodList, const bool& helpToggle)
{
    bool running = true;
    while (running)
    {
        std::string newId;
        std::string newFoodName;
        std::string newFoodDescription;

        // Generate a new ID for the food item
        newId = foodList.generateID();
        std::cout << "This new meal item will have the Item ID of "
        << newId << std::endl;

        bool nameValid = true;
        bool descriptionValid = true;
        bool priceValid = true;

        // Loop to get a valid name for the food item
        while (nameValid)
        {
            std::cout << "Enter the item name: ";
            std::string foodName = Helper::readInput();
            if (helpToggle && foodName == HELP_COMMAND) {
                help(ADD_FOOD_NAME);
            } else if (Helper::isValidName(foodName)) {
                newFoodName = foodName;
                nameValid = false;
            }

            // Check if input is empty or EOF
            if (foodName.empty() || std::cin.eof())
            {
                std::cin.clear();
                running = false;
                nameValid = false;
                descriptionValid = false;
                priceValid = false;
                std::cout<< "Option cancelled, returning to menu."<< std::endl;
            }
        }

        // Loop to get a valid description for the food item
        while (descriptionValid)
        {
            std::cout << "Enter the item description: ";
            std::string foodDescription = Helper::readInput();

            if (helpToggle && foodDescription == HELP_COMMAND) {
                help(ADD_FOOD_DESCRIPTION);
            } else if (Helper::isValidDescription(foodDescription)) {
                newFoodDescription = foodDescription;
                descriptionValid = false;
            }

            // Check if input is empty or EOF
            if (std::cin.eof() || foodDescription.empty())
            {
                std::cin.clear();
                running = false;
                descriptionValid = false;
                priceValid = false;
                std::cout<< "Option cancelled, returning to menu."<< std::endl;
            }
        }

        // Loop to get a valid price for the food item
        while (priceValid)
        {
            std::cout << "Enter the price for this item: ";
            std::string foodPrice = Helper::readInput();
            if (helpToggle && foodPrice == HELP_COMMAND) {
                help(ADD_FOOD_PRICE);

            // Check if input is empty or EOF
            } else if (std::cin.eof() || foodPrice.empty()) {
                std::cin.clear();
                running = false;
                priceValid = false;
                std::cout<< "Option cancelled, returning to menu."<< std::endl;
            } else if (Helper::isValidPrice(foodPrice)) {
                running = false;

                // Create a new FoodItem object with the entered details
                const auto newFood = std::make_shared<FoodItem>();
                newFood->id = newId;
                newFood->name = newFoodName;
                newFood->description = newFoodDescription;
                newFood->price = Helper::readPrice(foodPrice);

                // Add the new food item to the food list
                foodList.addFood(newFood);
                priceValid = false;
            }
        }
    }
}

void Interface::removeFood(Food &foodList, const bool& helpToggle)
{
    std::cout << "Enter the food id of the food to remove from the menu: ";
    const std::string foodId = Helper::readInput();

    if (!std::cin.eof())
    {
        // Check if the food item exists and remove it
        if (helpToggle && foodId == HELP_COMMAND) {
            help(REMOVE_FOOD_ID);
        } else if (foodList.removeFood(foodId)) {
            std::cout << "Food item removed successfully." << std::endl;
        }
        else {
            std::cout << "Error: food item not found." << std::endl;
        }
    }
    else
    {
        std::cin.clear();
        std::cout << "Option cancelled. Returning to Menu" << std::endl;
    }
}

void Interface::displayEnhancementsMenu() {
    // Display the enhancements menu options
    std::cout << "Enhancements Menu" << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << "1. Help Toggle" << std::endl;
    std::cout << "2. Color Toggle" << std::endl;
    std::cout << "3. Return to Main Menu" << std::endl;
}

void Interface::Enhancements(bool& helpToggle, bool& colorToggle) {
    bool running = true;
    while (running) {
        displayEnhancementsMenu();
        std::cout << "Select your option (1-3) : ";
        std::string input = Helper::readInput();
        if (input.empty() || std::cin.eof()) {
            std::cin.clear();
            std::cout << "Option cancelled. Returning to Menu" << std::endl;
            running = false;
        } else if (helpToggle && input == HELP_COMMAND) {
            help(ENHANCEMENTS_MENU);
        } else if (Helper::isNumber(input)) {
            const int option = std::stoi(input);
            if (option == 1) {
                // Toggle Help
                helpToggle = !helpToggle;
                std::cout << "Help is now " << (helpToggle ? "enabled" : "disabled") << std::endl;
            } else if (option == 2) {
                // Toggle Color
                colorToggle = !colorToggle;
                std::cout << "Color is now " << (colorToggle ? "enabled" : "disabled") << std::endl;
            } else if (option == 3) {
                // Return to Main Menu
                running = false;
            } else {
                std::cout << "Error: number was outside of range." << std::endl;
            }
        } else {
            std::cout << "Error: input was not numeric." << std::endl;
            std::cout << "Error in input. Please try again." << std::endl;
        }
    }
}

void Interface::help(const context context) {
    if (context == MAIN_MENU) {
        std::cout << "Press 1 to see the Menu\n"
                     "Press 2 to purchase a meal\n"
                     "Press 3 to Save & Exit\n"
                     "Press 4 to add a new food item\n"
                     "Press 5 to remove a food item\n"
                     "Press 6 to display the current coin balance\n"
                     "Press 7 to display the enhancements menu\n"
                     "Press 8 to exit the program\n";
    } else if (context == PURCHASE_ID) {
        std::cout << "Enter the ID of the food item you wish to purchase\n"
                     "The ID must be in the format 'F****' where * are numbers\n";
    } else if (context == PURCHASE_DENOMINATION) {
        std::cout << "Enter the denomination of the coin you wish to insert\n"
                     "The denomination must be in cents\n"
                     "Valid denominations are\n";

        // Print the valid coin denominations
        int denominations[] = {FIVE_CENTS_VALUE,
                                 TEN_CENTS_VALUE,
                                 TWENTY_CENTS_VALUE,
                                 FIFTY_CENTS_VALUE,
                                 ONE_DOLLAR_VALUE,
                                 TWO_DOLLARS_VALUE,
                                 FIVE_DOLLARS_VALUE,
                                 TEN_DOLLARS_VALUE,
                                 TWENTY_DOLLARS_VALUE,
                                 FIFTY_DOLLARS_VALUE};

        for (const int denomination : denominations) {
            std::cout << denomination << "\n";
        }
    } else if (context == ADD_FOOD_NAME) {
        std::cout << "Enter the name of the food item you wish to add\n"
                     "The name must be between 1 and 40 characters\n";
    } else if (context == ADD_FOOD_DESCRIPTION) {
        std::cout << "Enter the description of the food item you wish to add\n"
                     "The description must be between 1 and 255 characters\n";
    } else if (context == ADD_FOOD_PRICE) {
        std::cout << "Enter the price of the food item you wish to add\n"
                     "The price must be in the format 'D.CC' where D is dollars and C is cents\n";
    } else if (context == REMOVE_FOOD_ID) {
        std::cout << "Enter the ID of the food item you wish to remove\n"
                     "The ID must be in the format 'F****' where * are numbers\n";
    } else if (context == ENHANCEMENTS_MENU) {
        std::cout << "Press 1 to toggle help\n"
                     "Press 2 to toggle color\n"
                     "Press 3 to return to the main menu\n";
    }
}



