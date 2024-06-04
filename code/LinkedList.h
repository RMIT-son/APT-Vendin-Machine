#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"


class LinkedList {
public:
    /**
     * @brief Construct a new Linked List object
     * @details This constructor initializes the Linked List object.
     */
    LinkedList();

    /**
     * @brief Destroy the Linked List object
     * @details This destructor destroys the Linked List object.
     */
    ~LinkedList();

    /**
     * @brief Clear the list
     * @details This function will clear the list.
     * @return True if the list was cleared successfully, false otherwise.
     */
    bool clearList();

    /**
     * @brief Sort the list
     * @details This function will sort the list.
     * @return True if the list was sorted successfully, false otherwise.
     */
    bool sortList();

    /**
     * @brief Add a node to the list
     * @details This function will add a node to the list.
     * @param data The node to add to the list.
     * @return True if the node was added, false otherwise.
     */
    bool addNode(std::shared_ptr<FoodItem> data);

    /**
     * @brief Add a node to the list in sorted order
     * @details This function will add a node to the list in sorted order.
     * @param data The node to add to the list.
     * @return True if the node was added, false otherwise.
     */
    bool addNodeSorted(std::shared_ptr<FoodItem> data);

    /**
     * @brief Remove a node from the list
     * @details This function will remove a node from the list.
     * @param id The ID of the node to remove.
     * @return True if the node was removed, false otherwise.
     */
    bool removeNode(const std::string& id);

    /**
     * @brief Find a node in the list
     * @details This function will find a node in the list.
     * @param id The ID of the node to find.
     * @return A pointer to the node if it was found, nullptr otherwise.
     */
    [[nodiscard]] Node* findNode(const std::string& id) const;

    /**
     * @brief Get the number of nodes in the list
     * @details This function will return the number of nodes in the list.
     * @return The number of nodes in the list.
     */
    [[nodiscard]] unsigned getCount() const;

    /**
     * @brief Get the head of the list
     * @details This function will return the head of the list.
     * @return The head of the list.
     */
    [[nodiscard]] Node* getHead() const;

private:
    // the beginning of the list
    std::unique_ptr<Node> head;
//    std::unique_ptr<Node> tail;
    Node* tail;
    // how many nodes are there in the list
    unsigned count = 0;
};

#endif  // LINKEDLIST_H


