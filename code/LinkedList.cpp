#include "LinkedList.h"

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
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
        if (head) {
            head->prev = nullptr;
        }
    }
    tail = nullptr;
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
        tail = head.get();
    } else {
        newNode->prev = tail;
        tail->next = std::move(newNode);
        tail = tail->next.get();
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
        if (newNode->next) {
            newNode->next->prev = newNode.get();
        } else {
            tail = newNode.get();
        }
        head = std::move(newNode);
    } else {
        //Traverse the list to find the correct position to insert the new node
        Node* current = head.get();
        while (current->next && current->next->data->name
                < newNode->data->name) {
            current = current->next.get();
        }
        newNode->next = std::move(current->next);
        if (newNode->next) {
            newNode->next->prev = newNode.get();
        } else {
            tail = newNode.get();
        }
        current->next = std::move(newNode);
        current->next->prev = current;
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
            if (head) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
            count--;
            isRemoved = true;
        } else {
            /*
             * Traverse the list to find the node
             * with the given ID and remove it
             */
            Node* current = head.get();

            while (current->next) {
                if (current->next->data->id == id) {
                    current->next = std::move(current->next->next);
                    if (current->next) {
                        current->next->prev = current;
                    } else {
                        tail = current;
                    }
                    count--;
                    isRemoved = true;
                    return  isRemoved;
                }
                current = current->next.get();
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