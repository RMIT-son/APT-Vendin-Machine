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
    bool fileOpened = file.is_open();
    if (fileOpened) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::vector<std::string> fields;
            std::string field;
            while (std::getline(iss, field, FOOD_DELIM)) {
                fields.push_back(field);
            }
            if (fields.size() == 4) {
                std::string id = fields[0];
                if (Helper::isValidId(id)) {
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
                } else {
                    std::cerr << "Invalid ID: " << id << std::endl;
                }
            } else {
                std::cerr << "Invalid line format: " << line << std::endl;
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}


bool Food::writeToFile(const std::string& filename) {
    bool success = false;
    std::ofstream file(filename);
    if (file) {
        Node* current = foodList.getHead();
        while (current != nullptr) {
            file << current->data->id << FOOD_DELIM
                 << current->data->name << FOOD_DELIM
                 << current->data->description << FOOD_DELIM
                 << Helper::priceToString(current->data->price) << std::endl;
            current = current->next.get();
        }
        file.close();
        success = true;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
    return success;
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
    while (newIdStr.length() < ID_DIGITS) {  // Assuming IDs have 4 digits
        newIdStr.insert(newIdStr.begin(), '0');
    }

    // Add 'F' prefix and return
    newIdStr.insert(newIdStr.begin(), ID_PREFIX);
    return newIdStr;
}





