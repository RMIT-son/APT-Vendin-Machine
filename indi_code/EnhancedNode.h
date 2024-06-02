//
// Created by Son on 5/31/2024.
//

#ifndef ENHANCEDNODE_H
#define ENHANCEDNODE_H
#include "InnerLinkedList.h"


class EnhancedNode {
public:
    EnhancedNode();
    ~EnhancedNode() = default;
    std::unique_ptr<InnerLinkedList> data;
    std::unique_ptr<EnhancedNode> next;
    std::weak_ptr<EnhancedNode> prev;

    explicit EnhancedNode(std::unique_ptr<InnerLinkedList> data);
};



#endif //ENHANCEDNODE_H
