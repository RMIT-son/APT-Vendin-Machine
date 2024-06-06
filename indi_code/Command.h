//
// Created by Son on 5/31/2024.
//

#ifndef COMMAND_H
#define COMMAND_H

#include <utility>
#include "Food.h"
#include "Interface.h"

/**
 * @brief The Command class
 * @details This class is an abstract class that represents a command that can be executed.
*/
class Command {
public:
    Command();
    virtual ~Command();
    virtual void execute() = 0;
};

/**
 * @brief The DisplayMealOptionsCommand class
 * @details This class represents a command to display the meal options.
 */
class DisplayMealOptionsCommand : public Command {
public:
    explicit DisplayMealOptionsCommand(Food* foodlist);
    void execute() override;
private:
    Food* foodlist;
};

/**
 * @brief The PurchaseMealCommand class
 * @details This class represents a command to purchase a meal.
 */
class PurchaseMealCommand : public Command {
public:
    PurchaseMealCommand(Food* foodList, CoinManager* coinManager, bool& helpToggle, bool& colorToggle);
    void execute() override;
private:
    Food* foodList;
    CoinManager* coinManager;
    bool& helpToggle;
    bool& colorToggle;
};

/**
 * @brief The SaveAndExitCommand class
 * @details This class represents a command to save and exit the program.
 */
class SaveAndExitCommand : public Command {
public:
    SaveAndExitCommand(Food& fl, CoinManager& cm, std::string  ff, std::string  cf, bool& run, int& res);
    void execute() override;
private:
    Food& foodList;
    CoinManager& coinsManager;
    std::string foodFile;
    std::string coinFile;
    bool& running;
    int& res;
};

/**
 * @brief The AddFoodCommand class
 * @details This class represents a command to add a food item.
 */
class AddFoodCommand : public Command {
public:
    explicit AddFoodCommand(Food* foodList, bool& helpToggle);
    void execute() override;
private:
    Food* foodList;
    bool& helpToggle;
};

/**
 * @brief The RemoveFoodCommand class
 * @details This class represents a command to remove a food item.
 */
class RemoveFoodCommand : public Command {
public:
    explicit RemoveFoodCommand(Food* foodList, bool& helpToggle);
    void execute() override;
private:
    Food* foodList;
    bool& helpToggle;
};

/**
 * @brief The DisplayBalanceCommand class
 * @details This class represents a command to display the balance.
 */
class DisplayBalanceCommand : public Command {
public:
    explicit DisplayBalanceCommand(CoinManager* coinManager);
    void execute() override;
private:
    CoinManager* coinManager;
};

/**
 * @brief The EnhancementsCommand class
 * @details This class represents a command to display the enhancements menu.
 */
class EnhancementsCommand : public Command {
public:
    EnhancementsCommand(bool& helpToggle, bool& colorToggle);
    void execute() override;
private:
    bool& helpToggle;
    bool& colorToggle;
};

/**
 * @brief The AbortProgramCommand class
 * @details This class represents a command to abort the program.
 */
class AbortProgramCommand : public Command {
public:
    explicit AbortProgramCommand(bool& run);
    void execute() override;
private:
    bool& running;
};

#endif //COMMAND_H
