#include "Interface.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <stdexcept>

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
    std::cout << "\nType 'help' for assistance." << std::endl;

    // Prompt the user to select an option
    std::cout << "\nSelect your option (1-7) : ";
}

void Interface::displayFoodMenu(const Food &foodList)
{
    const Node *current = foodList.getHead();

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

void Interface::purchaseMeal(const Food &foodList, CoinManager &coinManager)
{
    // Added CoinManager reference
    bool running = true;

    std::cout << "Purchase Meal" << std::endl;
    std::cout << "-------------" << std::endl;

    while (running) {
        std::cout << "Please enter the ID of the food you wish to purchase: ";
        std::string id = Helper::readInput();

        // Check if input is empty or EOF (end of file)
        if (id.empty() || std::cin.eof())
        {
            std::cin.clear();
            running = false;
            std::cout << "Option cancelled, returning to menu." << std::endl;
        }
        else
        {
            // Input is not empty or EOF
            if (!std::cin.eof())
            {
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
                                  << ANSI_COLOR_BLUE
                                  << Helper::priceToString(foodItem->price)
                                  << ANSI_COLOR_RESET
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
                            std::cout << "You still need to give us $"
                                      << std::setw(6) << std::fixed
                                      << std::setprecision(2)
                                      << ANSI_COLOR_RED
                                      << Helper::priceToString({
                                          (foodItem->price.dollars * 100 +foodItem->price.cents - totalPaid) / 100,
                                          (foodItem->price.dollars * 100 + foodItem->price.cents - totalPaid) % 100})
                                      << ANSI_COLOR_RESET
                                      << ": ";
                            std::string denomination = Helper::readInput();

                            // Check if input is empty or EOF
                            if (denomination.empty() || std::cin.eof())
                            {
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

void Interface::addFood(Food &foodList)
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
            if (Helper::isValidName(foodName))
            {
                newFoodName = foodName;
                nameValid = false;
            } else {
                std::cout << "Error: Invalid name. Please enter a valid name." << std::endl;
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

            if (Helper::isValidDescription(foodDescription))
            {
                newFoodDescription = foodDescription;
                descriptionValid = false;
            } else {
                std::cout << "Error: Invalid description. Please enter a valid description." << std::endl;
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

            // Check if input is empty or EOF
            if (std::cin.eof() || foodPrice.empty())
            {
                std::cin.clear();
                running = false;
                priceValid = false;
                std::cout<< "Option cancelled, returning to menu."<< std::endl;
            }

            if (Helper::isValidPrice(foodPrice))
            {
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
            } else {
                std::cout << "Error: Invalid price. Please enter a valid price." << std::endl;
            }
        }
    }
}

void Interface::removeFood(Food &foodList)
{
    std::cout << "Enter the food id of the food to remove from the menu: ";
    const std::string foodId = Helper::readInput();

    if (!std::cin.eof())
    {
        // Check if the food item exists and remove it
        if (foodList.removeFood(foodId))
        {
            std::cout << "Food item removed successfully." << std::endl;
        }
        else
        {
            std::cout << "Error: Food item not found. "
                         "Please check the food ID and try again." <<std::endl;
        }
    }
    else
    {
        std::cin.clear();
        std::cout << "Option cancelled. Returning to Menu" << std::endl;
    }
}
void Interface::displayHelp() {
    std::cout << "Command List:" << std::endl;
    std::cout << "1. Display food menu: "
                 "Shows the available food items." << std::endl;
    std::cout << "2. Purchase a meal: Allows you to buy"
                 " a meal from the food menu." << std::endl;
    std::cout << "3. Exit program: Terminates the "
                 "program and saves the data." << std::endl;
    std::cout << "4. Add a new food item: Lets you add "
                 "a new food item to the menu." << std::endl;
    std::cout << "5. Remove a food item: Allows you to "
                 "remove a food item from the menu." << std::endl;
    std::cout << "6. Display coin balance: Shows your "
                 "current balance of coins." << std::endl;
    std::cout << "7. Exit program without saving: "
                 "Terminates the program without saving the data." <<std::endl;
    std::cout << std::endl;
    std::cout << "Enter the corresponding number "
                 "to execute a command." << std::endl;

    std::string input;
    std::getline(std::cin, input);

    if (input == "1") {
        std::cout << std::endl;
        std::cout << "Display food menu:" << std::endl;
        std::cout << "If you want to see the food list, you can see all the "
                     "detail of food in the menu to purchase" << std::endl;
    }
    else if (input == "2") {
        std::cout << std::endl;
        std::cout << "Purchase a Meal:" << std::endl;
        std::cout << "To purchase a meal, follow these steps:" << std::endl;
        std::cout << "1. Enter the corresponding number "
                     "for the meal you want to buy." << std::endl;
        std::cout << "Remember that for the amount you pay, "
                     "it must have the following denominations: " << std::endl;
        std::cout << FIVE_CENTS_VALUE << " is 5 cents" <<std::endl;
        std::cout << TEN_CENTS_VALUE << " is 10 cents" <<std::endl;
        std::cout << TWENTY_CENTS_VALUE << " is 20 cents" <<std::endl;
        std::cout << FIFTY_CENTS_VALUE << " is 50 cents" <<std::endl;
        std::cout << ONE_DOLLAR_VALUE << " is 1 dollar" <<std::endl;
        std::cout << TWO_DOLLARS_VALUE << " is 2 dollars" <<std::endl;
        std::cout << FIVE_DOLLARS_VALUE << " is 5 dollars" <<std::endl;
        std::cout << TEN_DOLLARS_VALUE << " is 10 dollars" <<std::endl;
        std::cout << TWENTY_DOLLARS_VALUE << " is 20 dollars" <<std::endl;
        std::cout << FIFTY_DOLLARS_VALUE << " is 50 dollars" <<std::endl;
        std::cout << "2. If the meal requires payment, ensure you have"
                     " enough coins in your balance." << std::endl;
        std::cout << "3. Confirm the purchase by following"
                     " the on-screen prompts." << std::endl;
        std::cout << "4. Enjoy your meal!" << std::endl;
        std::cout << "\nIf you encounter any issues or need further assistance,"
                     " please let us know." << std::endl;
    }
    else if (input == "3") {
        std::cout << std::endl;
        std::cout << "Save and Exit:" << std::endl;
        std::cout << "When you purchased a meal, the program "
                     "will save that food taken out." << std::endl;
        std::cout << "Also, it will deduct the balance"
                     " in the coins data." << std::endl;
        std::cout << "After all, all the data will be saved in the data"
                     " files and then exit the program" << std::endl;
    }
    else if (input == "4") {
        std::cout << std::endl;
        std::cout << "Add a New Food Item:" << std::endl;
        std::cout << "To add a new food item to the menu, "
                     "follow these steps:" << std::endl;
        std::cout << "1. Enter the name of the new food item." << std::endl;
        std::cout << "2. Provide a description or additional "
                     "details about the food item." << std::endl;
        std::cout << "3. Specify the price of the food item." << std::endl;
        std::cout << "4. The new food item will now be "
                     "available in the food menu." << std::endl;
        std::cout << "\nIf you encounter any issues or need further assistance,"
                     " please let us know." << std::endl;
    }
    else if (input == "5") {
        std::cout << std::endl;
        std::cout << "Remove a Food Item:" << std::endl;
        std::cout << "To remove a food item from the menu,"
                     " follow these steps:" << std::endl;
        std::cout << "1. Enter the corresponding number for the "
                     "food item you want to remove." << std::endl;
        std::cout << "2. Confirm the removal of the food item." << std::endl;
        std::cout << "3. The selected food item will be removed"
                     " from the food menu." << std::endl;
        std::cout << "\nIf you encounter any issues or need further assistance,"
                     " please let us know." << std::endl;
    }
    else if (input == "6") {
        std::cout << std::endl;
        std::cout << "Display Balance:" << std::endl;
        std::cout << "When you want to check the balance, it will appear how many coins left." << std::endl;
        std::cout << "This will help you purchase the meal and give back excess money" << std::endl;
    }
    else if (input == "7") {
        std::cout << std::endl;
        std::cout << "Abort Program:" << std::endl;
        std::cout << "If you don't want to save any data that you have changed "
                     "before, this will help exit the program "
                     "without any changes." << std::endl;
    }
}
