#include "LinkedList.h"

LinkedList::LinkedList() {
    head = nullptr;
    count = 0;
}

LinkedList::~LinkedList() {
    clearList();
}

bool LinkedList::clearList() {
    while (head != nullptr) {
        /*
         * Move the head to the next node,
         * effectively removing the current head node
         */
        head = std::move(head->next);
    }
    count = 0;
    return true;
}

bool LinkedList::sortList() {
    bool swapped = false;
    if (head && head->next) {
        do {
            swapped = false;
            Node* current = head.get();
            while (current->next) {
                if (current->data->name > current->next->data->name) {
                    /*
                     * Swap the data of the current node with
                     * the data of the next node if they are out of order
                     */
                    std::swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next.get();
            }
        } while (swapped);
    }
    return swapped;
}

bool LinkedList::addNode(std::shared_ptr<FoodItem> data) {
    auto newNode = std::make_unique<Node>(std::move(data));
    if (!head) {
        // If the list is empty, make the new node the head
        head = std::move(newNode);
    } else {
        // Traverse to the end of the list and add the new node at the end
        Node* current = head.get();
        while (current->next) {
            current = current->next.get();
        }
        current->next = std::move(newNode);
    }
    count++;
    // Always return true as the node is always added successfully
    return true;
}

bool LinkedList::addNodeSorted(std::shared_ptr<FoodItem> data) {
    auto newNode = std::make_unique<Node>(std::move(data));
    if (!head || newNode->data->name < head->data->name) {
        /*
         * If the list is empty or the new node comes after the head,
         * make it the new head
         */
        newNode->next = std::move(head);
        head = std::move(newNode);
    } else {
        //Traverse the list to find the correct position to insert the new node
        Node* current = head.get();
        while (current->next && current->next->data->name
                < newNode->data->name) {
            current = current->next.get();
        }
        newNode->next = std::move(current->next);
        current->next = std::move(newNode);
    }
    count++;
    // Always return true as the node is always added successfully
    return true;
}

bool LinkedList::removeNode(const std::string& id) {
    bool isRemoved = false;
    if (head) {
        if (head->data->id == id) {
            /*
             * If the head node matches the given ID,
             * remove it and update the head
             */
            head = std::move(head->next);
            count--;
            isRemoved = true;
        } else {
            /*
             * Traverse the list to find the node
             * with the given ID and remove it
             */
            Node* current = head.get();
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

Node* LinkedList::findNode(const std::string& id) const {
    Node* foundNode = nullptr;
    // Traverse the list to find the node with the given ID
    for (Node* current = head.get(); current != nullptr &&
    foundNode == nullptr; current = current->next.get()) {
        if (current->data->id == id) {
            foundNode = current;
        }
    }
    return foundNode;
}

unsigned LinkedList::getCount() const {
    return count;
}

Node* LinkedList::getHead() const {
    return head.get();
}

// Path: code/Node.cpp