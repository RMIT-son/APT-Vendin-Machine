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
        head = std::move(newNode);
    } else {
        Node* current = head.get();
        while (current->next) {
            current = current->next.get();
        }
        current->next = std::move(newNode);
    }
    count++;
    // Always return true as the node is always added
    return true;
}

bool LinkedList::addNodeSorted(std::shared_ptr<FoodItem> data) {
    auto newNode = std::make_unique<Node>(std::move(data));
    if (!head || newNode->data->name < head->data->name) {
        newNode->next = std::move(head);
        head = std::move(newNode);
    } else {
        Node* current = head.get();
        while (current->next && current->next->data->name<newNode->data->name)
        {
            current = current->next.get();
        }
        newNode->next = std::move(current->next);
        current->next = std::move(newNode);
    }
    count++;
    return true;
}


bool LinkedList::removeNode(std::string& id) {
    bool isRemoved = false;
    if (head) {
        if (head->data->id == id) {
            head = std::move(head->next);
            count--;
            isRemoved = true;
        } else {
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
    // Return the result of the remove operation
    return isRemoved;
}

Node* LinkedList::findNode(const std::string& id) const {
    Node* foundNode = nullptr;
    for (Node* current = head.get(); current != nullptr
    && foundNode == nullptr; current = current->next.get()) {
        if (current->data->id == id) {
            foundNode = current;
        }
    }
    return foundNode;
}

unsigned LinkedList::getCount() const {
    return count;
}

Node* LinkedList::getHead() {
    return head.get();
}

// Path: code/Node.cpp