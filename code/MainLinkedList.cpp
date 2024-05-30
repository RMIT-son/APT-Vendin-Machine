#include "MainLinkedList.h"
#include <iostream>

// Constructor
MainLinkedList::MainLinkedList()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

// Destructor
MainLinkedList::~MainLinkedList()
{
    MainNode *temp = head.get();
    while (temp != nullptr)
    {
        MainNode *next = temp->next.get();
        delete temp;
        temp = next;
    }
}

// Add list to main list
bool MainLinkedList::addList(std::unique_ptr<LinkedList> list)
{
    auto newNode = std::make_unique<MainNode>(std::move(list));
    if (!head)
    {
        head = std::move(newNode);
        tail = head.get();
    }
    else
    {
        tail->next = std::move(newNode);
        tail->next->prev = tail;
        tail = tail->next.get();
    }
    count++;
    return true;
}

// Find list by category name
// Find list by category name
LinkedList *MainLinkedList::findList(const std::string &category) const
{
    MainNode *current = head.get();
    while (current)
    {
        if (current->data->getCategoryName() == category)
        {
            return current->data.get();
        }
        current = current->next.get();
    }
    return nullptr;
}

// Display all lists
void MainLinkedList::displayLists() const
{
    MainNode *temp = head.get();
    std::cout << "Food Menu\n"
              << "---------\n";
    while (temp)
    {
        std::cout << temp->data->getCategoryName() << std::endl;
        temp->data->displayItems();
        temp = temp->next.get();
    }
}

// Get the count of lists
unsigned MainLinkedList::getCount() const
{
    return count;
}

// Get the head node
MainLinkedList::MainNode *MainLinkedList::getHead()
{
    return head.get();
}

MainLinkedList::MainNode *MainLinkedList::getNext(MainNode *node) const
{
    return node->next.get();
}

LinkedList *MainLinkedList::getFoodList(MainNode *node) const
{
    return node->data.get();
}

std::string MainLinkedList::generateID()
{
    std::unordered_set<int> idSet;
    auto categoryNode = getHead();

    // Traverse the main linked list and store all IDs in the set
    while (categoryNode != nullptr)
    {
        auto foodList = getFoodList(categoryNode);
        auto foodNode = foodList->getHead();

        // Traverse the food linked list
        while (foodNode != nullptr)
        {
            int numericId = std::stoi(foodNode->data->id.substr(1)); // Skip the first character
            idSet.insert(numericId);
            foodNode = foodList->getNext(foodNode);
        }
        categoryNode = getNext(categoryNode);
    }

    // Find the smallest non-existent ID
    int newId = 1;
    while (idSet.find(newId) != idSet.end())
    {
        newId++;
    }

    // Convert newId to string and pad with leading zeros if necessary
    std::string newIdStr = std::to_string(newId);
    const int ID_DIGITS = 4;
    const char ID_PREFIX = 'F';
    while (newIdStr.length() < ID_DIGITS)
    {
        newIdStr.insert(newIdStr.begin(), '0');
    }

    // Add prefix and return
    newIdStr.insert(newIdStr.begin(), ID_PREFIX);
    return newIdStr;
}

static std::string priceToString(const Price &price) {
    // Create an output string stream to build the price string
    std::ostringstream oss;

    // Convert the price to a string with 2 decimal places separated by a period
    oss << price.dollars << "." << std::setfill('0') << std::setw(2)
        << price.cents;
    // Return the built price string
    return oss.str();
}

bool MainLinkedList::writeToFile(const std::string &filename)
{
    bool success = false;
    std::ofstream file(filename);

    if (file)
    {
        MainNode *categoryNode = getHead();

        while (categoryNode != nullptr)
        {
            LinkedList *foodList = getFoodList(categoryNode);
            Node *current = foodList->getHead();

            while (current != nullptr)
            {
                file << current->data->id << "|"
                     << current->data->name << "|"
                     << current->data->description << "|"
                     << priceToString(current->data->price) << "|" 
                     << categoryNode->data->getCategoryName() << std::endl;
                current = foodList->getNext(current);
            }

            categoryNode = getNext(categoryNode);
        }

        file.close();
        success = true;
    }
    else
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }

    return success;
}