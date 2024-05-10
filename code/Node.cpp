#include "Node.h"

Node::Node(FoodItem* data) {
    this->data = data;
    this->next = nullptr;
}

Node::~Node(){
    delete data;
}