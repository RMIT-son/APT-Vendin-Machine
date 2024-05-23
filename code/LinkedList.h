#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"



class LinkedList {
public:
    // Default constructor
    LinkedList();

    // Destructor
    ~LinkedList();

    // Clear the entire linked list
    bool clearList();

    // Sort the linked list in ascending order based on the food item names
    bool sortList();

    // Add a new node to the end of the linked list
    bool addNode(std::shared_ptr<FoodItem> newNode);

    /*
     * Add a new node to the linked list in
     * sorted order based on the food item names
     */
    bool addNodeSorted(std::shared_ptr<FoodItem> newNode);

    // Remove a node with the given ID from the linked list
    bool removeNode(std::string& id);

    // Find a node with the given ID in the linked list
    Node* findNode(const std::string& id) const;

    // Get the number of nodes in the linked list
    unsigned getCount() const;

    // Get the head node of the linked list
    Node* getHead();

private:
    // the beginning of the list
    std::unique_ptr<Node> head;
  
    // how many nodes are there in the list
    unsigned count = 0;
};

#endif  // LINKEDLIST_H


