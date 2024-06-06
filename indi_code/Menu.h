//
// Created by Son on 6/3/2024.
//

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <map>
#include <stdexcept>
#include "Command.h"


class Menu {
private:
    std::map<int, std::unique_ptr<Command>> commands;
public:

    /**
     * @brief Menu
     * @details This is the constructor for the Menu class.
     */
    Menu();

    /**
     * @brief ~Menu
     * @details This is the destructor for the Menu class.
     */
    ~Menu() = default;

    /**
     * @brief setCommand
     * @details This function sets a command for a given option.
     * @param option The option to set the command for.
     * @param command The command to set.
     */
    void setCommand(int option, std::unique_ptr<Command> command);

    /**
     * @brief executeCommand
     * @details This function executes the command for a given option.
     * @param option The option to execute the command for.
     */
    void executeCommand(int option);
};



#endif //MENU_H
