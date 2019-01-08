#ifndef LIST_H
#define LIST_H

#include <iostream>

#include "node.h"

template<typename T> class SortedList
{
public:
    SortedList();
    ~SortedList();

    bool isFull();
    bool isEmpty();
    void makeEmpty();
    void addItem(const T& value);
    void deleteItem(const T& value);
    bool search(const T& value);
    Node<T>* retrieve(const T& value);
    void printList();
    void merge(SortedList<T>& other);

private:
    Node<T>* nextWithDelete(Node<T>* node);

private:
    Node<T>* m_head = nullptr;
};

#endif // LIST_H
