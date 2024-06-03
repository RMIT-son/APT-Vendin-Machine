#include "Interface.h"

// Utility function to trim from start (in place)
static inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                    { return !std::isspace(ch); }));
}

// Utility function to trim from end (in place)
static inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                         { return !std::isspace(ch); })
                .base(),
            s.end());
}

// Utility function to trim from both ends (in place)
static inline void trim(std::string &s)
{
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
    if (enhancement && color)
    {
        std::cout << "   7. Turn off price color" << std::endl;
        std::cout << "   8. Turn off 2D Linked List" << std::endl;
    }
    else if (enhancement && !color)
    {
        std::cout << "   7. Turn on price color" << std::endl;
        std::cout << "   8. Turn off 2D Linked List" << std::endl;
    }
    else if (!enhancement && color)
    {
        std::cout << "   7. Turn off price color" << std::endl;
        std::cout << "   8. Turn on 2D Linked List" << std::endl;
    }
    else
    {
        std::cout << "   7. Turn on price color" << std::endl;
        std::cout << "   8. Turn on 2D Linked List" << std::endl;
    }
    std::cout << "   9. Abort Program" << std::endl;

    // Prompt the user to select an option
    std::cout << "Select your option (1-9) : ";
}

// Display all lists
void Interface::displayFoodMenu(MainLinkedList &mainList)
{
    auto *temp = mainList.getHead();
    std::cout << "Food Menu\n"
              << "---------\n";

    if (enhancement)
    {
        while (temp)
        {
            std::cout << temp->data->getCategoryName() << std::endl;
            std::cout << "ID   |Name                                              |Price\n";
            std::cout << "------------------------------------------------------------------\n";
            Node *itemTemp = temp->data->getHead();
            while (itemTemp != nullptr)
            {
                // Trim the name to remove any leading or trailing whitespace or non-visible characters
                std::string foodName = itemTemp->data->name;
                trim(foodName);
                if (color)
                {
                    // Print the food item details with proper formatting and color enhancement
                    std::cout << std::left << std::setw(5) << itemTemp->data->id << "|"
                              << std::setw(50) << foodName << "|" << "\033[32m" << "$"
                              << std::setw(2) << std::right
                              << itemTemp->data->price.dollars << "."
                              << std::setfill('0') << std::setw(2)
                              << itemTemp->data->price.cents
                              << std::setfill(' ') << std::endl
                              << "\033[0m";
                }
                else
                {
                    // Print the food item details with proper formatting and color enhancement
                    std::cout << std::left << std::setw(5) << itemTemp->data->id << "|"
                              << std::setw(50) << foodName << "|" << "$"
                              << std::setw(2) << std::right
                              << itemTemp->data->price.dollars << "."
                              << std::setfill('0') << std::setw(2)
                              << itemTemp->data->price.cents
                              << std::setfill(' ') << std::endl;
                }
                itemTemp = itemTemp->next.get();
            }
            temp = temp->next.get();
            std::cout << std::endl;
        }
    }
    else
    {
        std::cout << "ID   |Name                                              |Price\n";
        std::cout << "------------------------------------------------------------------\n";
        while (temp)
        {
            Node *itemTemp = temp->data->getHead();
            while (itemTemp != nullptr)
            {
                // Trim the name to remove any leading or trailing whitespace or non-visible characters
                std::string foodName = itemTemp->data->name;
                trim(foodName);
                if (color)
                {
                    // Print the food item details with proper formatting
                    std::cout << std::left << std::setw(5) << itemTemp->data->id << "|"
                              << std::setw(50) << foodName << "|" << "\033[32m" << "$"
                              << std::setw(2) << std::right
                              << itemTemp->data->price.dollars << "."
                              << std::setfill('0') << std::setw(2)
                              << itemTemp->data->price.cents
                              << std::setfill(' ') << std::endl
                              << "\033[0m";
                }
                else
                {
                    // Print the food item details with proper formatting
                    std::cout << std::left << std::setw(5) << itemTemp->data->id << "|"
                              << std::setw(50) << foodName << "|" << "$"
                              << std::setw(2) << std::right
                              << itemTemp->data->price.dollars << "."
                              << std::setfill('0') << std::setw(2)
                              << itemTemp->data->price.cents
                              << std::setfill(' ') << std::endl;
                }
                itemTemp = itemTemp->next.get();
            }
            temp = temp->next.get();
        }
        std::cout << "\n";
    }
}

void Interface::displayBalance(CoinManager &manager)
{
    // Sort the coins in ascending order based on their denomination
    std::map<Denomination, unsigned> sortedCoins(manager.coins.begin(),
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
        int denomination = manager.getValue(pair.first);
        unsigned count = pair.second;
        double value = count * (denomination / 100.0);

        // Print the denomination, quantity, and value of the coin
        std::cout << std::right << std::setw(5) << denomination << " | "
                  << std::setw(8) << count << " |$"
                  << std::setw(7) << std::fixed << std::setprecision(2)
                  << value << std::endl;
        totalValue += value;
    }

    // Display the total balance value
    std::cout << "---------------------------\n";
    std::cout << "Total:            $" << std::setw(7) << std::fixed << std::setprecision(2) << totalValue << std::endl;
}

void Interface::purchaseMealEnhancement(MainLinkedList &mainList, CoinManager &coinManager)
{
    bool running = true;

    std::cout << "Purchase Meal" << std::endl;
    std::cout << "-------------" << std::endl;

    while (running)
    {
        std::cout << "Please enter the ID of the food you wish to purchase: ";
        std::string id = Helper::readInput();

        // Check if input is empty or EOF (end of file)
        if (id == "" || std::cin.eof())
        {
            std::cin.clear();
            running = false;
            std::cout << "Option cancelled, returning to menu." << std::endl;
        }
        else
        {
            FoodItem *foodItem = nullptr;

            // Loop through mainList to find the food item
            auto *categoryNode = mainList.getHead();
            while (categoryNode != nullptr)
            {
                LinkedList *foodList = categoryNode->data.get();
                Node *foodNode = foodList->getHead();
                while (foodNode != nullptr)
                {
                    FoodItem *currentFoodItem = foodNode->data.get();
                    if (currentFoodItem->id == id)
                    {
                        foodItem = currentFoodItem;
                        break;
                    }
                    foodNode = foodNode->next.get();
                }
                if (foodItem != nullptr)
                {
                    break;
                }
                categoryNode = categoryNode->next.get();
            }

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
                    if (color)
                    {
                        std::cout << "You have selected \"" << foodItem->name << " - " << foodItem->description
                                  << "\". This will cost you " << "\033[32m" << "$"
                                  << static_cast<double>(foodItem->price.dollars) +
                                         static_cast<double>(foodItem->price.cents) / 100.0
                                  << "\033[0m" << "." << std::endl;
                    }
                    else
                    {
                        std::cout << "You have selected \"" << foodItem->name << " - " << foodItem->description
                                  << "\". This will cost you " << "$"
                                  << static_cast<double>(foodItem->price.dollars) +
                                         static_cast<double>(foodItem->price.cents) / 100.0
                                  << "." << std::endl;
                    }
                    std::cout << "Please hand over the money - type in the value of each note/coin in cents."
                              << std::endl;
                    std::cout << "Please enter ctrl-D or enter on a new line to cancel this purchase."
                              << std::endl;

                    unsigned int totalPaid = 0;
                    bool denominating = true;
                    std::vector<Denomination> addedDenominations;

                    while (denominating)
                    {
                        if (color)
                        {
                            std::cout << "You still need to give us " << "\033[32m" << "$"
                                      << std::setw(4) << std::fixed << std::setprecision(2)
                                      << static_cast<double>(foodItem->price.dollars) +
                                             static_cast<double>(foodItem->price.cents) / 100.0 -
                                             static_cast<double>(totalPaid) / 100.0
                                      << "\033[0m" << ": ";
                        }
                        else
                        {
                            std::cout << "You still need to give us " << "$"
                                      << std::setw(4) << std::fixed << std::setprecision(2)
                                      << static_cast<double>(foodItem->price.dollars) +
                                             static_cast<double>(foodItem->price.cents) / 100.0 -
                                             static_cast<double>(totalPaid) / 100.0
                                      << ": ";
                        }
                        std::string denomination = Helper::readInput();

                        // Check if input is empty or EOF
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
                                      << "Error: input was not numeric." << std::endl;
                        }
                        else if (!Helper::isValidDenomination(denomination))
                        {
                            std::cout << "Error: invalid denomination encountered." << std::endl;
                        }
                        else
                        {
                            Helper::processPayment(foodItem, coinManager, totalPaid, denomination, addedDenominations);

                            if (totalPaid >= foodItem->price.dollars * 100 + foodItem->price.cents)
                            {
                                denominating = false;
                                running = false;
                            }
                        }
                    }
                }
            }
        }
    }
}

void Interface::addFoodEnhancement(MainLinkedList &mainList)
{
    bool running = true;
    while (running)
    {
        std::string newId;
        std::string newFoodName;
        std::string newFoodDescription;
        std::string newCategoryName;
        Price newPrice;

        // Generate a new ID for the food item
        newId = mainList.generateID(); // Assuming this method exists in MainLinkedList
        std::cout << "This new meal item will have the Item ID of " << newId << std::endl;

        bool nameValid = true;
        bool descriptionValid = true;
        bool priceValid = true;
        bool categoryValid = true;

        // Loop to get a valid name for the food item
        while (nameValid)
        {
            std::cout << "Enter the item name: ";
            std::string foodName = Helper::readInput();
            if (Helper::isValidName(foodName))
            {
                newFoodName = foodName;
                nameValid = false;
            }

            // Check if input is empty or EOF
            if (foodName == "" || std::cin.eof())
            {
                std::cin.clear();
                running = false;
                nameValid = false;
                descriptionValid = false;
                priceValid = false;
                categoryValid = false;
                std::cout << "Option cancelled, returning to menu." << std::endl;
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
            }

            // Check if input is empty or EOF
            if (std::cin.eof() || foodDescription.empty())
            {
                std::cin.clear();
                running = false;
                descriptionValid = false;
                priceValid = false;
                categoryValid = false;
                std::cout << "Option cancelled, returning to menu." << std::endl;
            }
        }

        // Loop to get a valid price for the food item
        while (priceValid)
        {
            std::cout << "Enter the price for this item: ";
            std::string foodPrice = Helper::readInput();

            // Check if input is empty or EOF
            if (std::cin.eof() || foodPrice == "")
            {
                std::cin.clear();
                running = false;
                priceValid = false;
                categoryValid = false;
                std::cout << "Option cancelled, returning to menu." << std::endl;
            }

            if (Helper::isValidPrice(foodPrice))
            {
                newPrice = Helper::readPrice(foodPrice);
                running = false;
                priceValid = false;
            }
        }

        while (categoryValid)
        {
            std::cout << "Enter the category name: ";
            std::string categoryName = Helper::readInput();

            if (Helper::isValidName(categoryName))
            {
                newCategoryName = categoryName;
                bool categoryExists = false;
                auto *categoryNode = mainList.getHead();
                while (categoryNode != nullptr)
                {
                    LinkedList *foodList = mainList.getFoodList(categoryNode);
                    if (foodList != nullptr && foodList->getCategoryName() == categoryName)
                    {
                        categoryExists = true;
                        break;
                    }
                    categoryNode = mainList.getNext(categoryNode);
                }

                // If the category does not exist, create a new LinkedList and add to mainList
                if (!categoryExists)
                {
                    auto newFoodList = std::make_unique<LinkedList>();
                    newFoodList->setCategoryName(categoryName);
                    mainList.addList(std::move(newFoodList));
                    std::cout << "New category created: " << categoryName << std::endl;
                }

                categoryValid = false;

                // Check if input is empty or EOF
                if (categoryName == "" || std::cin.eof())
                {
                    std::cin.clear();
                    running = false;
                    categoryValid = false;
                    std::cout << "Option cancelled, returning to menu." << std::endl;
                }
            }
        }
        running = false;

        // Create a new FoodItem object with the entered details
        std::shared_ptr<FoodItem> newFood = std::make_shared<FoodItem>();
        newFood->id = newId;
        newFood->name = newFoodName;
        newFood->description = newFoodDescription;
        newFood->price = newPrice;

        // Add the new food item to the appropriate food list in the main list
        auto *categoryNode = mainList.getHead();
        while (categoryNode != nullptr)
        {
            LinkedList *foodList = mainList.getFoodList(categoryNode);
            if (foodList != nullptr && foodList->getCategoryName() == newCategoryName)
            {
                foodList->addNode(newFood);
                std::cout << "Food item added to the existing category: " << newCategoryName << std::endl;
                break;
            }
            categoryNode = mainList.getNext(categoryNode);
        }
    }
}

void Interface::removeFoodEnhancement(MainLinkedList &mainList)
{
    std::cout << "Enter the food id of the food to remove from the menu: ";
    std::string foodId = Helper::readInput();

    if (!std::cin.eof())
    {
        bool foodRemoved = false;

        // Traverse the main list to find and remove the food item
        auto *categoryNode = mainList.getHead();
        while (categoryNode != nullptr && !foodRemoved)
        {
            LinkedList *foodList = mainList.getFoodList(categoryNode);
            if (foodList != nullptr && foodList->removeNode(foodId))
            {
                foodRemoved = true;
                std::cout << "Food item removed successfully." << std::endl;
            }
            categoryNode = mainList.getNext(categoryNode);
        }

        if (!foodRemoved)
        {
            std::cout << "Error: food item not found." << std::endl;
        }
    }
    else
    {
        std::cin.clear();
        std::cout << "Option cancelled. Returning to Menu" << std::endl;
    }
}

void Interface::setEnhancement(bool state)
{
    enhancement = state;
}

bool Interface::getEnhancement() const
{
    return enhancement;
}

void Interface::setColor(bool state)
{
    color = state;
}

bool Interface::getColor() const
{
    return color;
}