#include "Node.h"
// Default constructor for Node class

Node::Node() {
    // Initialize data pointer to nullptr
    this->data = nullptr;
    // Initialize next pointer to nullptr
    this->next = nullptr;
}

// Constructor for Node class with data parameter
Node::Node(std::shared_ptr<FoodItem> data) {
    // Set data pointer to the provided data
    this->data = data;
    // Initialize next pointer to nullptr
    this->next = nullptr;
}

// Destructor for Node class
Node::~Node(){
    /*
     * Set next pointer to nullptr,
     * effectively breaking the link to the next node
     */
    next = nullptr;
}