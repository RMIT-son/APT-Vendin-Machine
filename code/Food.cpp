//
// Created by Son on 5/11/2024.
//

#include "Food.h"

#include <unordered_set>

Food::Food() {
    // Initialize the Food LinkedList
    count = ZERO;
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
        std::vector<std::string> fields;
        std::string field;
        while (std::getline(iss, field, '|')) {
            // Assuming '|' is the delimiter
            fields.push_back(field);
        }
        if (fields.size() != 4) {
            std::cerr << "Invalid line format: " << line << std::endl;
            continue;
        }
        std::string id = fields[0];
        std::string name = fields[1];
        std::string description = fields[2];
        std::string priceStr = fields[3];
        // Convert double to Price
        Price price = Helper::readPrice(priceStr);
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
    // Use a getter method here
    Node* current = foodList.getHead();
    while (current != nullptr) {
        file << current->data->id << FOOD_DELIM
             << current->data->name << FOOD_DELIM
             << current->data->description << FOOD_DELIM
             << Helper::priceToString(current->data->price) << std::endl;
        current = current->next.get();
    }
    file.close();
    return true;
}

Node* Food::getHead() {
    return foodList.getHead();
}

std::string Food::generateID() {
    std::unordered_set<int> idSet;
    Node* current = foodList.getHead();

    // Traverse the linked list and store all IDs in the set
    while (current != nullptr) {
        int numericId = std::stoi(current->data->id.substr(1));
        // Skip the first character 'F'
        idSet.insert(numericId);
        current = current->next.get();
    }

    // Find the smallest non-existent ID
    int newId = 1;
    while (idSet.find(newId) != idSet.end()) {
        newId++;
    }

    // Convert newId to string and pad with leading zeros if necessary
    std::string newIdStr = std::to_string(newId);
    while (newIdStr.length() < 4) {  // Assuming IDs have 4 digits
        newIdStr.insert(newIdStr.begin(), '0');
    }

    // Add 'F' prefix and return
    newIdStr.insert(newIdStr.begin(), 'F');
    return newIdStr;
}





