//
// Created by Son on 5/31/2024.
//

#include "EnhancedNode.h"

EnhancedNode::EnhancedNode() {
    this->data = nullptr;
    this->next = nullptr;
}


EnhancedNode::EnhancedNode(std::shared_ptr<FoodItem> data) {
    this->data = std::move(data);
    this->next = nullptr;
}


