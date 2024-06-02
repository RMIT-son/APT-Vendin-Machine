//
// Created by Son on 5/31/2024.
//

#ifndef COMMAND_H
#define COMMAND_H
#include "Food.h"
#include "Interface.h"


class Command {
public:
    Command();
    virtual ~Command();
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
};

class DisplayMealOptionsCommand : public Command {
private:
    Food* foodlist;
public:
    explicit DisplayMealOptionsCommand(Food* foodlist): foodlist(foodlist) {}
    void execute() override {
        Interface::displayFoodMenu(*foodlist);
    }
};

class PurchaseMealCommand : public Command {
private:
    Food* foodList;
    CoinManager* coinManager;
public:
    PurchaseMealCommand(Food* foodList, CoinManager* coinManager)
        : foodList(foodList), coinManager(coinManager) {}
    void execute() override {
        Interface::purchaseMeal(*foodList, *coinManager);
    }
};

class SaveAndExitCommand : public Command {
private:
    Food& foodList;
    CoinManager& coinsManager;
    std::string foodFile;
    std::string coinFile;
    bool& running;

public:
    SaveAndExitCommand(Food& fl, CoinManager& cm, const std::string& ff, const std::string& cf, bool& run)
        : foodList(fl), coinsManager(cm), foodFile(ff), coinFile(cf), running(run) {}

    void execute() override {
        if (!foodList.writeToFile(foodFile)) {
            std::cerr << "Error: failed to write to food file." << std::endl;
        }
        if (!coinsManager.writeToFile(coinFile)) {
            std::cerr << "Error: failed to write to coins file." << std::endl;
        }
        running = false;
    }
};

class AddFoodCommand : public Command {
private:
    Food* foodList;
public:
    explicit AddFoodCommand(Food* foodList) : foodList(foodList) {}
    void execute() override {
        Interface::addFood(*foodList);
    }
};

class RemoveFoodCommand : public Command {
private:
    Food* foodList;
public:
    explicit RemoveFoodCommand(Food* foodList) : foodList(foodList) {}
    void execute() override {
        Interface::removeFood(*foodList);
    }
};

class DisplayBalanceCommand : public Command {
private:
    CoinManager* coinManager;
public:
    explicit DisplayBalanceCommand(CoinManager* coinManager)
        : coinManager(coinManager) {}
    void execute() override {
        Interface::displayBalance(*coinManager);
    }
};

class AbortProgramCommand : public Command {
private:
    bool& running;
public:
    explicit AbortProgramCommand(bool& run) : running(run) {}
    void execute() override {
        running = false;
    }
};

#endif //COMMAND_H
