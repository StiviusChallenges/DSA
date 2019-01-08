#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <iostream>

#include "doublelinkedlist_decl.inc"

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList()
{
}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList<T>&& other)
{
    m_head = other.m_head;
    m_tail = other.m_tail;
    m_nUsed = other.m_nUsed;

    other.m_head = nullptr;
    other.m_tail = nullptr;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator =(DoubleLinkedList<T>&& other)
{
    if(*this == other)
        throw std::logic_error("Self-assignment");

    m_head = other.m_head;
    m_tail = other.m_tail;
    m_nUsed = other.m_nUsed;

    other.m_head = nullptr;
    other.m_tail = nullptr;

    return *this;
}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
    clear();
}

template<typename T>
bool DoubleLinkedList<T>::operator ==(const DoubleLinkedList<T>& other)
{
    if(m_head == other.m_head && m_tail == other.m_tail)
        return true;

    return false;
}

template<typename T>
bool DoubleLinkedList<T>::empty()
{
    if(m_head == nullptr && m_tail == nullptr)
        return true;

    return false;
}

template<typename T>
void DoubleLinkedList<T>::clear()
{
    while(m_head)
    {
        Node* nextNode = m_head->next();
        delete m_head;
        m_head = nextNode;
        --m_nUsed;
    }
    m_head = m_tail = nullptr;
}

template<typename T>
typename DoubleLinkedList<T>::Node* DoubleLinkedList<T>::insert(Node* pos, const T& value)
{
    if(!pos)
        throw std::invalid_argument("Node is null");

    Node* newNode = nullptr;
    if(pos == m_head)
    {
        pushFront(value);
        newNode = m_head;
    }
    else
    {
        newNode = new Node(value, pos, pos->previous());
        pos->previous()->next() = newNode;
        pos->previous() = newNode;
        ++m_nUsed;
    }

    return newNode;
}

template<typename T>
void DoubleLinkedList<T>::erase(Node* pos)
{
    if(!pos)
        throw std::invalid_argument("node is null");

    Node* nextNode = pos->next();
    Node* prevNode = pos->previous();

    if(nextNode == nullptr)
    {
        popBack();
    }
    else if(prevNode == nullptr)
    {
        popFront();
    }
    else
    {
        delete pos;
        prevNode->next() = nextNode;
        nextNode->previous() = prevNode;
        --m_nUsed;
    }
}

template<typename T>
void DoubleLinkedList<T>::pushFront(const T& value)
{
    if(empty())
    {
        m_head = m_tail = new Node(value, nullptr, nullptr);
    }
    else
    {
        Node* currentHead = m_head;
        Node* newNode =  new Node(value, currentHead, nullptr);
        currentHead->previous() = newNode;
        m_head = newNode;
    }
    ++m_nUsed;
}

template<typename T>
void DoubleLinkedList<T>::popFront()
{
    if(!empty())
    {
        Node* nextNode = m_head->next();
        delete m_head;
        m_head = nextNode;
        if(m_head) m_head->previous() = nullptr;
        if(!m_head) m_tail = nullptr;
        --m_nUsed;
    }
}

template<typename T>
typename DoubleLinkedList<T>::Node* DoubleLinkedList<T>::front()
{
    return m_head;
}

template<typename T>
void DoubleLinkedList<T>::pushBack(const T& value)
{
    if(empty())
    {
        m_head = m_tail = new Node(value, nullptr, nullptr);
    }
    else
    {
        Node* currentTail = m_tail;
        Node* newNode =  new Node(value, nullptr, currentTail);
        currentTail->next() = newNode;
        m_tail = newNode;
    }
    ++m_nUsed;
}

template<typename T>
void DoubleLinkedList<T>::popBack()
{
    if(!empty())
    {
        Node* prevNode = m_tail->previous();
        delete m_tail;
        m_tail = prevNode;
        if(m_tail) m_tail->next() = nullptr;
        if(!m_tail) m_head = nullptr;
        --m_nUsed;
    }
}

template<typename T>
typename DoubleLinkedList<T>::Node* DoubleLinkedList<T>::back()
{
    return m_tail;
}

template<typename T>
typename DoubleLinkedList<T>::Node* DoubleLinkedList<T>::find(const T& value)
{
    Node* currentNode = m_head;
    while(currentNode)
    {
        if(currentNode->value() == value)
            return currentNode;

        currentNode = currentNode->next();
    }
    return nullptr;
}

template<typename T>
void DoubleLinkedList<T>::print()
{
    Node* currentNode = m_head;
    while(currentNode)
    {
        std::cout << currentNode->value();
        if(currentNode->next())
            std::cout << " <--> ";
        currentNode = currentNode->next();
    }
    std::cout << std::endl;
}

#endif // DOUBLELINKEDLIST_H
