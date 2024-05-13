//
// Created by Son on 5/11/2024.
//

#include "Food.h"

Food::Food() {
    // Initialize the Food LinkedList
    count = 0;
}

Food::~Food() {
    // Clear the Food LinkedList
    clearFood();
}

bool Food::addFood(std::shared_ptr<FoodItem> newFood) {
    // Add a new food item to the Food LinkedList
    return foodList.addNodeSorted(newFood);
}

bool Food::removeFood(std::string& id) {
    // Purchase a food item from the Food LinkedList
    return foodList.removeNode(id);
}

bool Food::sortFood() {
    // Sort the Food LinkedList
    return foodList.sortList();
}

bool Food::clearFood() {
    // Clear the Food LinkedList
    return foodList.clearList();
}

FoodItem* Food::findFood(const std::string& id) const {
    // Find a food item in the Food LinkedList
    Node* node = foodList.findNode(id);
    return node ? node->data.get() : nullptr;
}

unsigned Food::getFoodCount() const {
    // Get the number of food items in the Food LinkedList
    return foodList.getCount();
}

void Food::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string id, name, description, priceStr;
        std::getline(iss, id, '|');
        std::getline(iss, name, '|');
        std::getline(iss, description, '|');
        std::getline(iss, priceStr, '|');
        Price price = Helper::readPrice(priceStr); // Convert double to Price
        std::shared_ptr<FoodItem> item = std::make_shared<FoodItem>();
        item->id = id;
        item->name = name;
        item->description = description;
        item->price = price;
        foodList.addNodeSorted(item);
    }
    file.close();
}

bool Food::writeToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return false;
    }
    Node* current = foodList.getHead(); // Use a getter method here
    while (current != nullptr) {
        file << current->data->id << "|"
             << current->data->name << "|"
             << current->data->description << "|"
             << Helper::priceToString(current->data->price) << std::endl;
        current = current->next.get();
    }
    file.close();
    return true;
}

Node* Food::getHead() {
    return foodList.getHead();
}





