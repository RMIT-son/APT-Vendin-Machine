//
// Created by Son on 5/31/2024.
//

#ifndef ENHANCEDNODE_H
#define ENHANCEDNODE_H
#include "Node.h"


class EnhancedNode {
public:
    EnhancedNode();
    ~EnhancedNode() = default;
    explicit EnhancedNode(std::shared_ptr<FoodItem> data);

    // Data members
    std::shared_ptr<FoodItem> data;
    std::unique_ptr<EnhancedNode> next;
    std::weak_ptr<EnhancedNode> prev;
};


#endif //ENHANCEDNODE_H
