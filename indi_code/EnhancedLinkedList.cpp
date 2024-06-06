//
// Created by Son on 5/31/2024.
//

#include "EnhancedLinkedList.h"

EnhancedLinkedList::EnhancedLinkedList() {
    // Initialize the head and tail pointers to nullptr
    this->head = nullptr;
    this->tail = nullptr;
    // Initialize the count to 0
    this->count = 0;
}

EnhancedLinkedList::~EnhancedLinkedList() {
    // Clear the list when the list is destroyed
    this->clearList();
}

bool EnhancedLinkedList::clearList() {
    // While the list is not empty, remove the head node
    while (head != nullptr) {
        head = std::move(head->next);
    }
    // Reset the count to 0
    count = 0;
    // Return true to indicate that the list was cleared successfully
    return true;
}

bool EnhancedLinkedList::sortList() const {
    // Initialize a flag to false to indicate whether the list was sorted
    bool isSorted = false;
    // Check if the list is not empty
    if (head) {
        // Bubble sort algorithm
        bool swapped;
        do {
            swapped = false;
            EnhancedNode* current = head.get();
            while (current->next) {
                if (current->data->name > current->next->data->name) {
                    // Swap the data of the current node and the next node
                    const std::shared_ptr<FoodItem> tempData = current->data;
                    current->data = current->next->data;
                    current->next->data = tempData;
                    swapped = true;
                    isSorted = true;
                }
                current = current->next.get();
            }
        } while (swapped);
    }

    // Return true if the list was sorted, false otherwise
    return isSorted;
}


bool EnhancedLinkedList::addNode(std::shared_ptr<FoodItem> data) {
    // Create a new node with the given data
    auto newNode = std::make_unique<EnhancedNode>(std::move(data));
    if (!head) {
        // If the list is empty, make the new node the head and tail
        head = std::move(newNode);
        tail = head.get();
    } else {
        // Add the new node at the end of the list
        tail->next = std::move(newNode);
        // Update the tail pointer
        tail = tail->next.get();
    }
    // Increment the count
    count++;
    // Return true to indicate that the node was added successfully
    return true;
}

bool EnhancedLinkedList::addNodeSorted(std::shared_ptr<FoodItem> data) {
    // Create a new node with the given data
    auto newNode = std::make_unique<EnhancedNode>(std::move(data));
    if (!head || newNode->data->name < head->data->name) {
        // If the list is empty or the new node's name is less than the head node's name
        newNode->next = std::move(head);
        head = std::move(newNode);
        if (!tail) {
            // If the list was empty, the new node is also the tail
            tail = head.get();
        }
    } else {
        // Traverse the list to find the correct position to insert the new node
        EnhancedNode* current = head.get();
        while (current->next && current->next->data->name < newNode->data->name) {
            current = current->next.get();
        }
        // Insert the new node after the current node
        newNode->next = std::move(current->next);
        current->next = std::move(newNode);
    }
    // Increment the count
    count++;
    // Return true to indicate that the node was added successfully
    return true;
}

bool EnhancedLinkedList::removeNode(const std::string& id) {
    // Initialize a flag to false to indicate whether a node was removed
    bool isRemoved = false;
    if (head) {
        if (head->data->id == id) {
            // If the head node matches the given ID, remove it and update the head
            head = std::move(head->next);
            count--;
            isRemoved = true;
        } else {
            // Traverse the list to find the node with the given ID and remove it
            EnhancedNode* current = head.get();
            while (current->next && current->next->data->id != id) {
                current = current->next.get();
            }
            if (current->next) {
                current->next = std::move(current->next->next);
                count--;
                isRemoved = true;
            }
        }
    }
    // Return true if the node was successfully removed, false otherwise
    return isRemoved;
}

EnhancedNode* EnhancedLinkedList::findNode(const std::string& id) const {
    // Initialize a pointer to nullptr to hold the node if it is found
    EnhancedNode* foundNode = nullptr;
    // Traverse the list to find the node with the given ID
    for (EnhancedNode* current = head.get(); current != nullptr && foundNode == nullptr; current = current->next.get()) {
        if (current->data->id == id) {
            foundNode = current;
        }
    }
    // Return the found node if it was found, nullptr otherwise
    return foundNode;
}

unsigned EnhancedLinkedList::getCount() const {
    // Return the count of nodes in the list
    return count;
}

EnhancedNode *EnhancedLinkedList::getHead() const {
    // Return the head of the list
    return head.get();
}




