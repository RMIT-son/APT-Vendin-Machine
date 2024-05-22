#include "Interface.h"

// Utility function to trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// Utility function to trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// Utility function to trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

void Interface::displayMainMenu()
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

void Interface::displayFoodMenu(Food &foodList)
{
    const Node *current = foodList.getHead();
    std::cout << "Food Menu\n"
              << "---------\n";
    std::cout << "ID   |Name                                              |Price\n";
    std::cout << "------------------------------------------------------------------\n";
    while (current != nullptr)
    {
        // Trim the name to remove any leading or trailing whitespace or non-visible characters
        std::string foodName = current->data->name;
        trim(foodName);

        // Print the food item details with proper formatting
        std::cout << std::left << std::setw(5) << current->data->id << "|"
                  << std::setw(50) << foodName << "|$"
                  << std::setw(2) << std::right << current->data->price.dollars << "."
                  << std::setfill('0') << std::setw(2) << current->data->price.cents
                  << std::setfill(' ') << std::endl;
        current = current->next.get();
    }
    std::cout << "\n";
}

void Interface::displayBalance(CoinManager &manager)
{
    std::map<Denomination, unsigned> sortedCoins(manager.coins.begin(),
                                                 manager.coins.end());

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
                  << std::setw(7) << std::fixed << std::setprecision(2)
                  << value << std::endl;

        totalValue += value;
    }

    std::cout << "---------------------------\n";
    std::cout << "Total:            $" << std::setw(7) << std::fixed <<
    std::setprecision(2) << totalValue << std::endl;
}

void Interface::purchaseMeal(Food &foodList, CoinManager &coinManager)
{
    // Added CoinManager reference
    bool running = true;

    std::cout << "Purchase Meal" << std::endl;
    std::cout << "-------------" << std::endl;
    while (running) {
        std::cout << "Please enter the ID of the food you wish to purchase: ";
        std::string id = Helper::readInput();
        if (id == "" || std::cin.eof())
            {
                std::cin.clear();
                running = false;
                std::cout << "Option cancelled, returning to menu." << std::endl;
            } else {
                

                if (!std::cin.eof()) {
                    FoodItem *foodItem = foodList.findFood(id);
                    if (foodItem == nullptr)
                    {
                        std::cout << "Item not found. "
                                    "Please check the food ID and try again."
                                    << std::endl;
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
                                    << static_cast<double>(foodItem->price.dollars) +
                                    static_cast<double>(foodItem->price.cents) / 100
                                    << "." << std::endl;
                            std::cout << "Please hand over the money - "
                                        "type in the value of each note/coin in cents."
                                        << std::endl;
                            std::cout << "Please enter ctrl-D or enter on a new line to"

                                        " cancel this purchase." << std::endl;

                            unsigned int totalPaid = 0;
                            bool denominating = true;
                            std::vector<Denomination> addedDenominations;
                            while (denominating)
                            {
                                std::cout << "You still need to give us $"

                                        << std::setw(6) << std::fixed
                                        << std::setprecision(2)
                                        << static_cast<double>(foodItem->price.dollars) +
                                        static_cast<double>(foodItem->price.cents) /
                                        100 - static_cast<double>(totalPaid) / 100
                                        << ": ";
                                std::string denomination = Helper::readInput();

                                if (denomination == "" || std::cin.eof())
                                {
                                    std::cout << std::endl
                                    << "Purchase cancelled." << std::endl;
                                    std::cin.clear();

                                    Helper::processRefund(coinManager, addedDenominations);

                                    running = false;
                                    denominating = false;
                                }


                                else if (!Helper::isNumber(denomination))

                                {
                                    std::cout << std::endl
                                            << "Error: input was not numeric."
                                            << std::endl;
                                }

                                    else if (!Helper::isValidDenomination(denomination))
                                    {
                                        std::cout << "Error: "
                                                    "invalid denomination encountered."

                                                    << std::endl;
                                    }
                                    else
                                    {

                                        Helper::processPayment(foodItem, coinManager, totalPaid, denomination, addedDenominations);
                                        if (totalPaid >= foodItem->price.dollars * 100

                                        + foodItem->price.cents) {
                                            denominating = false;
                                            running = false;
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
        newId = foodList.generateID();
        std::cout << "This new meal item will have the Item ID of "
        << newId << std::endl;

        bool nameValid = true;
        bool descriptionValid = true;
        bool priceValid = true;
        while (nameValid)
        {
            std::cout << "Enter the item name: ";
            std::string foodName = Helper::readInput();
            if (Helper::isValidName(foodName)) {
                newFoodName = foodName;
                nameValid = false;
            }    

            if (foodName == "" || std::cin.eof())
            {
                std::cin.clear();
                running = false;
                nameValid = false;
                descriptionValid = false;
                priceValid = false;
                std::cout << "Option cancelled, returning to menu." << std::endl;
            }
        }
        
        while (descriptionValid) 
        {
            std::cout << "Enter the item description: ";
            std::string foodDescription = Helper::readInput();
            if (Helper::isValidDescription(foodDescription)) {
                newFoodDescription = foodDescription;
                descriptionValid = false;
            }
            if (std::cin.eof() || foodDescription.empty())
            {
                std::cin.clear();
                running = false;
                descriptionValid = false;
                priceValid = false;
                std::cout << "Option cancelled, returning to menu." << std::endl;
            }
        }
        
        while (priceValid)
        {
            std::cout << "Enter the price for this item: ";
            std::string foodPrice = Helper::readInput();
            if (std::cin.eof() || foodPrice == "")
            {
                std::cin.clear();
                running = false;
                priceValid = false;
                std::cout << "Option cancelled, returning to menu." << std::endl;
            }
            if (Helper::isValidPrice(foodPrice))
            {
                running = false;
                priceValid = false;
                std::shared_ptr<FoodItem> newFood = std::make_shared<FoodItem>();
                newFood->id = newId;
                newFood->name = newFoodName;
                newFood->description = newFoodDescription;
                newFood->price = Helper::readPrice(foodPrice);
                foodList.addFood(newFood);
            }
        }
    }
}

void Interface::removeFood(Food &foodList) {
    std::cout << "Enter the food id of the food to remove from the menu: ";
    std::string foodId = Helper::readInput();
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
