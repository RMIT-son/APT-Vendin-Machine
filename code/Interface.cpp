#include "Interface.h"

Interface::Interface() {

}

Interface::~Interface() {
    delete this;
}

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