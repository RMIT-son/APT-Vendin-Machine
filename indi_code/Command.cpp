//
// Created bSoner on 5/31/2024.
//

#include "Command.h"

Command::Command() = default;

Command::~Command() = default;

// Constructor for DisplayMealOptionsCommand
DisplayMealOptionsCommand::DisplayMealOptionsCommand(Food* foodlist) {
    this->foodlist = foodlist;
}
// Execute the DisplayMealOptionsCommand
void DisplayMealOptionsCommand::execute() {
    Interface::displayFoodMenu(*foodlist);
}

// Constructor for PurchaseMealCommand
PurchaseMealCommand::PurchaseMealCommand(Food* foodList, CoinManager* coinManager, bool& helpToggle, bool& colorToggle):
    helpToggle(helpToggle), colorToggle(colorToggle) {
    this->foodList = foodList;
    this->coinManager = coinManager;
}
// Execute the PurchaseMealCommand
void PurchaseMealCommand::execute() {
    Interface::purchaseMeal(*foodList, *coinManager, helpToggle, colorToggle);
}

// Constructor for SaveAndExitCommand
SaveAndExitCommand::SaveAndExitCommand(Food& fl, CoinManager& cm, std::string ff, std::string cf, bool& run, int& res)
    : foodList(fl), coinsManager(cm), running(run), res(res) {
    foodFile = std::move(ff);
    coinFile = std::move(cf);
}
// Execute the SaveAndExitCommand
void SaveAndExitCommand::execute() {
    if (!foodList.writeToFile(foodFile)) {
        std::cerr << "Error: failed to write to food file." << std::endl;
        res = EXIT_FAILURE;
    }
    if (!coinsManager.writeToFile(coinFile)) {
        std::cerr << "Error: failed to write to coins file." << std::endl;
        res = EXIT_FAILURE;
    }
    running = false;
}

// Constructor for AddFoodCommand
AddFoodCommand::AddFoodCommand(Food* foodList, bool& helpToggle):
    helpToggle(helpToggle) {
    this->foodList = foodList;
}
// Execute the AddFoodCommand
void AddFoodCommand::execute() {
    Interface::addFood(*foodList, helpToggle);
}

// Constructor for RemoveFoodCommand
RemoveFoodCommand::RemoveFoodCommand(Food* foodList, bool& helpToggle):
    helpToggle(helpToggle) {
    this->foodList = foodList;
}
// Execute the RemoveFoodCommand
void RemoveFoodCommand::execute() {
    Interface::removeFood(*foodList, helpToggle);
}

// Constructor for AddCoinsCommand
DisplayBalanceCommand::DisplayBalanceCommand(CoinManager* coinManager) {
    this->coinManager = coinManager;
}
// Execute the AddCoinsCommand
void DisplayBalanceCommand::execute() {
    Interface::displayBalance(*coinManager);
}

// Constructor for AddCoinsCommand
EnhancementsCommand::EnhancementsCommand(bool& helpToggle, bool& colorToggle)
    : helpToggle(helpToggle), colorToggle(colorToggle) {
}
// Execute the AddCoinsCommand
void EnhancementsCommand::execute() {
    Interface::Enhancements(helpToggle, colorToggle);
}

// Constructor for AddCoinsCommand
AbortProgramCommand::AbortProgramCommand(bool& run) : running(run) {}
// Execute the AddCoinsCommand
void AbortProgramCommand::execute() {
    running = false;
}
