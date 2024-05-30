#ifndef MAINLINKEDLIST_H
#define MAINLINKEDLIST_H

#include <memory>
#include <string>
#include <unordered_set>
#include "LinkedList.h"

class MainLinkedList
{
private:
    struct MainNode
    {
        std::unique_ptr<LinkedList> data;
        std::unique_ptr<MainNode> next;
        MainNode *prev;

        MainNode(std::unique_ptr<LinkedList> data) : data(std::move(data)), next(nullptr), prev(nullptr) {}
    };

    std::unique_ptr<MainNode> head;
    MainNode *tail;
    unsigned count;

public:
    MainLinkedList();
    ~MainLinkedList();
    bool addList(std::unique_ptr<LinkedList> list);
    LinkedList *findList(const std::string &category) const;
    void displayLists() const;
    unsigned getCount() const;
    MainNode *getHead();
    std::string generateID();
    MainNode* getNext(MainNode* node) const;
    LinkedList* getFoodList(MainNode* node) const;

};

#endif // MAINLINKEDLIST_H
