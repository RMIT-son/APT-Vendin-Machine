#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include "Node.h"



class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    bool clearList();
    bool sortList();
    bool addNode(std::shared_ptr<FoodItem> newNode);
    bool addNodeSorted(std::shared_ptr<FoodItem> newNode);
    bool removeNode(std::string& id);
    Node* findNode(const std::string& id) const;
    unsigned getCount() const;
    Node* getHead();

private:
    // the beginning of the list
    std::unique_ptr<Node> head;
  
    // how many nodes are there in the list
    unsigned count = 0;
};

#endif  // LINKEDLIST_H


