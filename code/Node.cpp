#include "Node.h"

// Default constructor for Node class
Node::Node()
{
    this->data = nullptr;
    this->next = nullptr;
    this->prev = nullptr;    // For doubly linked list
    this->subList = nullptr; // For 2D linked list
    this->parent = nullptr;
}

// Constructor with data parameter
Node::Node(const std::shared_ptr<FoodItem> &data)
{
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;    // For doubly linked list
    this->subList = nullptr; // For 2D linked list
    this->parent = nullptr;
}

// Destructor for Node class
Node::~Node()
{
    next = nullptr;
    subList = nullptr;
}

// Default constructor for FoodItem
FoodItem::FoodItem() : id(""), name(""), description(""), price({0, 0}), on_hand(DEFAULT_FOOD_STOCK_LEVEL) {}

// Parameterized constructor for FoodItem
FoodItem::FoodItem(const std::string &id, const std::string &name, const std::string &description, const Price &price, unsigned on_hand)
    : id(id), name(name), description(description), price(price), on_hand(on_hand) {}

// Destructor for FoodItem
FoodItem::~FoodItem()
{
    // Destructor
}
