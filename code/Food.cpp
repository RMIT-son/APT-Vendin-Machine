//
// Created by Son on 5/11/2024.
//

#include "Food.h"

Food::Food()
{
    // Initialize the Food LinkedList
    count = 0;
}

Food::~Food()
{
    // Clear the Food LinkedList
    clearFood();
}

bool Food::addFood(std::shared_ptr<FoodItem> newFood)
{
    // Add a new food item to the Food LinkedList
    return foodList.addNodeSorted(newFood);
}

bool Food::removeFood(std::string &id)
{
    // Purchase a food item from the Food LinkedList
    return foodList.removeNode(id);
}

bool Food::sortFood()
{
    // Sort the Food LinkedList
    return foodList.sortList();
}

bool Food::clearFood()
{
    // Clear the Food LinkedList
    return foodList.clearList();
}

FoodItem *Food::findFood(const std::string &id) const
{
    // Find a food item in the Food LinkedList
    Node *node = foodList.findNode(id);
    return node ? node->data.get() : nullptr;
}

unsigned Food::getFoodCount() const
{
    // Get the number of food items in the Food LinkedList
    return foodList.getCount();
}

Node *Food::getHead()
{
    // Delegate to foodList's getHead() function and return the head node
    return foodList.getHead();
}

std::string Food::generateID()
{
    std::unordered_set<int> idSet;
    Node *current = foodList.getHead();

    // Traverse the linked list and store all IDs in the set
    while (current != nullptr)
    {
        int numericId = std::stoi(current->data->id.substr(1));
        // Skip the first character 'F'
        idSet.insert(numericId);
        current = current->next.get();
    }

    // Find the smallest non-existent ID
    int newId = 1;
    while (idSet.find(newId) != idSet.end())
    {
        newId++;
    }

    // Convert newId to string and pad with leading zeros if necessary
    std::string newIdStr = std::to_string(newId);
    while (newIdStr.length() < ID_DIGITS)
    {
        // Assuming IDs have 4 digits
        newIdStr.insert(newIdStr.begin(), '0');
    }

    // Add 'F' prefix and return
    newIdStr.insert(newIdStr.begin(), ID_PREFIX);
    return newIdStr;
}

void Food::readFromEnhancementFile(const std::string &filename, MainLinkedList &mainList)
{
    // Open the file with the provided filename
    std::ifstream file(filename);
    // Check if the file was successfully opened
    bool fileOpened = file.is_open();
    if (fileOpened)
    {
        std::string line;
        while (std::getline(file, line))
        {
            // Create a string stream to parse each line
            std::istringstream iss(line);
            std::vector<std::string> fields;
            std::string field;
            while (std::getline(iss, field, FOOD_DELIM))
            {
                // Split the line into fields based on the delimiter and store them in a vector
                fields.push_back(field);
            }
            if (fields.size() == 5)
            { // Ensure that there are 6 fields (ID, name, description, dollars, cents, category)
                // Extract the fields
                std::string id = fields[0];
                if (Helper::isValidId(id))
                {
                    std::string name = fields[1];
                    std::string description = fields[2];
                    std::string priceStr = fields[3];
                    std::string category = fields[4];

                    // Create the Price object
                    Price price = Helper::readPrice(priceStr);

                    // Create a shared pointer to a new FoodItem object
                    std::shared_ptr<FoodItem> item = std::make_shared<FoodItem>();
                    item->id = id;
                    item->name = name;
                    item->description = description;
                    item->price = price;

                    // Find the category list in the main list
                    LinkedList *list = mainList.findList(category);
                    if (!list)
                    {
                        // If the category list doesn't exist, create a new one
                        auto newList = std::make_unique<LinkedList>();
                        newList->setCategoryName(category);
                        newList->addNode(item);
                        mainList.addList(std::move(newList));
                    }
                    else
                    {
                        // Add the item to the existing category list
                        list->addNode(item);
                    }
                }
                else
                {
                    // Print an error message for an invalid ID
                    std::cerr << "Invalid ID: " << id << std::endl;
                }
            }
            else if (fields.size() == 4)
            {
                // Extract the fields
                std::string id = fields[0];
                if (Helper::isValidId(id))
                {
                    std::string name = fields[1];
                    std::string description = fields[2];
                    std::string priceStr = fields[3];
                    // Create the Price object
                    Price price = Helper::readPrice(priceStr);

                    // Create a shared pointer to a new FoodItem object
                    std::shared_ptr<FoodItem> item = std::make_shared<FoodItem>();
                    item->id = id;
                    item->name = name;
                    item->description = description;
                    item->price = price;

                    auto newList = std::make_unique<LinkedList>();
                    newList->setCategoryName("Uncategorised");
                    newList->addNode(item);
                    mainList.addList(std::move(newList));
                }
                else
                {
                    // Print an error message for an invalid ID
                    std::cerr << "Invalid ID: " << id << std::endl;
                }
            }
            else
            {
                // Print an error message for an invalid line format
                std::cerr << "Invalid line format: " << line << std::endl;
            }
        }
        // Close the file
        file.close();
    }
    else
    {
        // Print an error message if the file couldn't be opened
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}
