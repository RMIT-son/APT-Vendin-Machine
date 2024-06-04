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
    return foodList.addNodeSorted(std::move(newFood));
}

bool Food::removeFood(const std::string& id) {
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
    const Node* node = foodList.findNode(id);
    return node ? node->data.get() : nullptr;
}

unsigned Food::getFoodCount() const {
    // Get the number of food items in the Food LinkedList
    return foodList.getCount();
}

void Food::readFromFile(const std::string& filename) {
    // Open the file with the provided filename
    std::ifstream file(filename);
    // Check if the file was successfully opened
    bool fileOpened = file.is_open();
    if (fileOpened) {
        std::string line;
        while (std::getline(file, line)) {
            // Create a string stream to parse each line
            std::istringstream iss(line);
            std::vector<std::string> fields;
            std::string field;
            while (std::getline(iss, field, FOOD_DELIM)) {
                /*
                 * Split the line into fields based on
                 * the delimiter and store them in a vector
                 */
                fields.push_back(field);
            }
                if (fields.size() == FOOD_FIELDS) {
                // Extract the ID field
                std::string id = fields[0];
                if (Helper::isValidId(id)) {
                    // Extract the name field
                    std::string name = fields[1];
                    // Extract the description field
                    std::string description = fields[2];
                    // Extract the price field as a string
                    std::string priceStr = fields[3];
                    // Convert the price string to a Price object
                    Price price = Helper::readPrice(priceStr);

                    // Create a shared pointer to a new FoodItem object
                    auto item = std::make_shared<FoodItem>();
                    item->id = id;
                    item->name = name;
                    item->description = description;
                    item->price = price;

                    // Add the new FoodItem to the foodList in sorted order
                    foodList.addNodeSorted(item);
                } else {
                    // Print an error message for an invalid ID
                    std::cerr << "Invalid ID: " << id << std::endl;
                }
            } else {
                // Print an error message for an invalid line format
                std::cerr << "Invalid line format: " << line << std::endl;
            }
        }
        // Close the file
        file.close();
    } else {
        // Print an error message if the file couldn't be opened
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

bool Food::writeToFile(const std::string& filename) const {
    // Initialize the success flag as false
    bool success = false;
    // Open the file with the provided filename for writing
    std::ofstream file(filename);
    if (file) {
        // Get the head node of the foodList
        const Node* current = foodList.getHead();
        while (current != nullptr) {
            /*
             * Write the fields of the current FoodItem to the file,
             * separated by the delimiter
             */
            file << current->data->id << FOOD_DELIM
                 << current->data->name << FOOD_DELIM
                 << current->data->description << FOOD_DELIM
                 << Helper::priceToString(current->data->price) << std::endl;
            // Move to the next node in the foodList
            current = current->next.get();
        }
        // Close the file
        file.close();
        //Set the success flag as true since writing to the file was successful
        success = true;
    } else {
        // Print an error message if the file couldn't be opened
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
    // Return the success flag indicating whether writing to the file was successful
    return success;
}

Node* Food::getHead() const {
    // Delegate to foodList's getHead() function and return the head node
    return foodList.getHead();
}

std::string Food::generateID() const {
    std::unordered_set<int> idSet;
    const Node* current = foodList.getHead();

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
    while (newIdStr.length() < ID_DIGITS) {
        // Assuming IDs have 4 digits
        newIdStr.insert(newIdStr.begin(), '0');
    }

    // Add 'F' prefix and return
    newIdStr.insert(newIdStr.begin(), ID_PREFIX);
    return newIdStr;
}
