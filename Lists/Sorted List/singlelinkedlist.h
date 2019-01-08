#ifndef SINGLELINKEDLIST_H
#define SINGLELINKEDLIST_H

#include <iostream>

#include "node.h"

template<typename T> class SingleLinkedList
{
public:
    SingleLinkedList();
    SingleLinkedList(const SingleLinkedList<T>& other);
    SingleLinkedList& operator =(const SingleLinkedList<T>& other);
    SingleLinkedList(SingleLinkedList<T>&& other);
    SingleLinkedList& operator =(SingleLinkedList<T>&& other);
    ~SingleLinkedList();
    bool operator ==(const SingleLinkedList<T> &other);
    bool empty();
    void clear();
    Node<T>* insertAfter(Node<T>* pos, const T& value);
    void eraseAfter(Node<T>* pos);
    void pushFront(const T& value);
    void popFront();
    Node<T>* find(const T& value);
    void print();

    void resize(size_t size);
    void merge(SingleLinkedList<T>& other);
    void remove(const T& value);
    void unique();
    void reverse();
    void sort();

private:
    Node<T> *nextWithDelete(Node<T> *node);

private:
    Node<T>* m_head = nullptr;
    Node<T>* m_tail = nullptr;
    size_t m_nUsed = 0;

};


#endif // SINGLELINKEDLIST_H
