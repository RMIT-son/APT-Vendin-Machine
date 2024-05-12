#include "Node.h"

Node::Node() {
    this->data = nullptr;
    this->next = nullptr;
}

Node::Node(std::shared_ptr<FoodItem> data) {
    this->data = data;
    this->next = nullptr;
}

Node::~Node(){
    next = nullptr;
}