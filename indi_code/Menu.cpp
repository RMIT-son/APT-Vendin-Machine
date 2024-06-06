//
// Created by Son on 6/3/2024.
//

#include "Menu.h"

Menu::Menu() {
    this->commands = std::map<int, std::unique_ptr<Command>>();
}

void Menu::setCommand(const int option, std::unique_ptr<Command> command) {
    this->commands[option] = std::move(command);
}

void Menu::executeCommand(const int option) {
    if (this->commands.find(option) != this->commands.end()) {
        this->commands[option]->execute();
    } else {
        std::cout << "Error: number was out of range." << std::endl;
    }
}