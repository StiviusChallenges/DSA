#include "sortedlist.h"

template class SortedList<int>;

template<typename T>
SortedList<T>::SortedList()
{

}

template<typename T>
SortedList<T>::~SortedList()
{
    makeEmpty();
}


template<typename T>
bool SortedList<T>::isFull()
{
    return false;
}

template<typename T>
bool SortedList<T>::isEmpty()
{
    if(m_head == nullptr)
    {
        return true;
    }
    return false;
}

template<typename T>
void SortedList<T>::makeEmpty()
{
    while(m_head)
    {
        Node<T>* temp = m_head->next();
        delete m_head;
        m_head = temp;
    }
}

template<typename T>
void SortedList<T>::addItem(const T& value)
{
    if(isEmpty())
    {
        m_head = new Node<T>(value, nullptr);
    }
    else
    {
        Node<T>* current = m_head;
        Node<T>* previous = nullptr;
        while(current)
        {
            if(current->value() > value)
            {
                if(previous)
                {
                    previous->next() =  new Node<T>(value, current);
                    return;
                }
                else
                {
                    m_head = new Node<T>(value, current);
                    return;
                }
            }
            previous = current;
            current = current->next();
        }
        previous->next() = new Node<T>(value, nullptr);
    }
}

template<typename T>
void SortedList<T>::deleteItem(const T& value)
{
    Node<T>* current = m_head;
    Node<T>* previous = nullptr;
    while(current)
    {
        if(current->value() == value)
        {
            if(previous)
                previous->next() = current->next();
            else
                m_head = current->next();
            delete current;

            std::cout << "Deletion of value " << value << "succeed" << std::endl;
        }
        else
        {
            previous = current;
        }
        current = current->next();
    }
}

template<typename T>
bool SortedList<T>::search(const T& value)
{
    Node<T>* current = m_head;
    while(current)
    {
        if(current->value() == value)
            return true;
        current = current->next();
    }
    return false;
}

template<typename T>
Node<T>* SortedList<T>::retrieve(const T& value)
{
    Node<T>* current = m_head;
    while(current)
    {
        if(current->value() == value)
            return current;
        current = current->next();
    }
    return nullptr;
}

template<typename T>
void SortedList<T>::printList()
{
    Node<T>* current = m_head;
    while(current)
    {
        std::cout << current->value();
        if(current->next())
            std::cout << " --> ";
        current = current->next();
    }
    std::cout << std::endl;
}

template<typename T>
Node<T>* SortedList<T>::nextWithDelete(Node<T>* node)
{
    Node<T>* temp = node->next();
    delete node;
    node = temp;
    return node;
}

template<typename T>
void SortedList<T>::merge(SortedList<T> &other)
{
    if(!other.m_head)
    {
        std::cout << "You've tried to merge empty list" << std::endl;
        return;
    }

    Node<T>* currentNode1stList = m_head;
    Node<T>* currentNode2ndList = other.m_head;
    Node<T>* previousNode1stList = nullptr;
    Node<T>* lastNode1stList = nullptr;

    while(currentNode1stList && currentNode2ndList)
    {
        if(currentNode1stList->value() <= currentNode2ndList->value() &&
                (currentNode1stList->next() == nullptr || currentNode1stList->next()->value() > currentNode2ndList->value()))
        {
            Node<T>* temp = currentNode1stList->next();
            currentNode1stList->next() = new Node<T>(currentNode2ndList->value(), temp);
            currentNode2ndList = nextWithDelete(currentNode2ndList);
        }
        else if(currentNode1stList->value() > currentNode2ndList->value())
        {
            Node<T>* temp = currentNode1stList;
            if(previousNode1stList)
            {
                previousNode1stList->next() = new Node<T>(currentNode2ndList->value(), temp);
                currentNode1stList = previousNode1stList->next();
            }
            else
            {
                m_head = new Node<T>(currentNode2ndList->value(), temp);
                currentNode1stList = m_head;
            }
            currentNode2ndList = nextWithDelete(currentNode2ndList);
        }
        if(!currentNode1stList->next())
            lastNode1stList = currentNode1stList;
        previousNode1stList = currentNode1stList;
        currentNode1stList = currentNode1stList->next();
    }

    if(!currentNode1stList && currentNode2ndList)
    {
        currentNode1stList = lastNode1stList;
        if(!currentNode1stList)
        {
            currentNode1stList = m_head = new Node<T>(currentNode2ndList->value(), nullptr);
            currentNode2ndList = nextWithDelete(currentNode2ndList);
        }
        while(currentNode2ndList)
        {
            currentNode1stList->next() = new Node<T>(currentNode2ndList->value(), nullptr);
            currentNode1stList = currentNode1stList->next();
            currentNode2ndList = nextWithDelete(currentNode2ndList);
        }
    }
    other.m_head = nullptr;
}
