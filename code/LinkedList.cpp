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
    if (!head || !head->next) {
        return false; // List is empty or has only one node, no need to sort
    }
    bool swapped;
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
    return true;
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
    return true;
}

bool LinkedList::addNodeSorted(std::shared_ptr<FoodItem> data) {
    auto newNode = std::make_unique<Node>(std::move(data));
    if (!head || newNode->data->name < head->data->name) {
        newNode->next = std::move(head);
        head = std::move(newNode);
    } else {
        Node* current = head.get();
        while (current->next && current->next->data->name < newNode->data->name) {
            current = current->next.get();
        }
        newNode->next = std::move(current->next);
        current->next = std::move(newNode);
    }
    count++;
    return true;
}

// bool LinkedList::removeNode(Node* node) {
//     if (node == nullptr) {
//         return false;
//     }
//     if (head == node) {
//         head = node->next;
//         delete node;
//         count--;
//         return true;
//     }
//     Node* current = head;
//     while (current->next != nullptr) {
//         if (current->next == node) {
//             current->next = node->next;
//             delete node;
//             count--;
//             return true;
//         }
//         current = current->next;
//     }
//     return false;
// }

bool LinkedList::removeNode(std::string& id) {
    if (!head) {
        return false;
    }
    if (head->data->id == id) {
        head = std::move(head->next);
        count--;
        return true;
    }
    Node* current = head.get();
    while (current->next && current->next->data->id != id) {
        current = current->next.get();
    }
    if (current->next) {
        current->next = std::move(current->next->next);
        count--;
        return true;
    }
    return false;
}

Node* LinkedList::findNode(const std::string& id) const {
    Node* current = head.get();
    while (current != nullptr) {
        if (current->data->id == id) {
            return current;
        }
        current = current->next.get();
    }
    return nullptr;
}

unsigned LinkedList::getCount() const {
    return count;
}

Node* LinkedList::getHead() {
    return head.get();
}

// Path: code/Node.cpp

