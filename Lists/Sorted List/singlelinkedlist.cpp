#include "singlelinkedlist.h"

template class SingleLinkedList<int>;

template<typename T>
SingleLinkedList<T>::SingleLinkedList()
{
}

template<typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T>& other)
{
    Node<T>* currentNode = other.m_head;
    Node<T>* insertedNode = nullptr;

    while(currentNode)
    {
        if(empty())
        {
            pushFront(currentNode->value());
            insertedNode = m_head;
        }
        else
        {
            insertedNode = insertAfter(insertedNode, currentNode->value());
        }
        currentNode = currentNode->next();
    }
}

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator =(const SingleLinkedList<T>& other)
{
    clear();
    Node<T>* currentNode = other.m_head;
    Node<T>* insertedNode = nullptr;

    while(currentNode)
    {
        if(empty())
        {
            pushFront(currentNode->value());
            insertedNode = m_head;
        }
        else
        {
            insertedNode = insertAfter(insertedNode, currentNode->value());
        }
        currentNode = currentNode->next();
    }
    return *this;
}

template<typename T>
SingleLinkedList<T>::SingleLinkedList(SingleLinkedList<T>&& other)
{
    m_head = other.m_head;
    m_tail = other.m_tail;
    m_nUsed = other.m_nUsed;

    other.m_head = nullptr;
    other.m_tail = nullptr;
}

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator =(SingleLinkedList<T>&& other)
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
SingleLinkedList<T>::~SingleLinkedList()
{
    clear();
}

template<typename T>
bool SingleLinkedList<T>::operator ==(const SingleLinkedList<T>& other)
{
    if(m_head == other.m_head && m_tail == other.m_tail)
        return true;

    return false;
}

template<typename T>
bool SingleLinkedList<T>::empty()
{
    if(m_head == nullptr && m_tail == nullptr)
        return true;
    return false;
}

template<typename T>
void SingleLinkedList<T>::clear()
{
    while(m_head)
    {
        Node<T>* nextNode = m_head->next();
        delete m_head;
        m_head = nextNode;
        --m_nUsed;
    }
    m_head = m_tail = nullptr;
}

template<typename T>
Node<T>* SingleLinkedList<T>::insertAfter(Node<T>* pos, const T& value)
{
    if(!pos)
        throw std::invalid_argument("node is null");

    Node<T>* nextNode = pos->next();
    pos->next() = new Node<T>(value, nextNode);
    ++m_nUsed;

    if(!nextNode)
        m_tail = pos->next();

    return pos->next();
}

template<typename T>
void SingleLinkedList<T>::eraseAfter(Node<T>* pos)
{
    if(!pos || pos == m_tail)
        return;

    Node<T>* nextAfterNext = pos->next()->next();
    delete pos->next();
    pos->next() = nextAfterNext;
    --m_nUsed;

    if(!nextAfterNext)
        m_tail = pos;
}

template<typename T>
void SingleLinkedList<T>::pushFront(const T& value)
{
    if(empty())
    {
        m_head = m_tail = new Node<T>(value, nullptr);
    }
    else
    {
        Node<T>* currentHead = m_head;
        m_head = new Node<T>(value, currentHead);
    }
    ++m_nUsed;
}

template<typename T>
void SingleLinkedList<T>::popFront()
{
    if(!empty())
    {
        Node<T>* nextNode = m_head->next();
        delete m_head;
        m_head = nextNode;
        --m_nUsed;
        if(!m_head) m_tail = nullptr;
    }
}

template<typename T>
Node<T>* SingleLinkedList<T>::find(const T& value)
{
    Node<T>* currentNode = m_head;
    while(currentNode)
    {
        if(currentNode->value() == value)
            return currentNode;
        currentNode = currentNode->next();
    }
    return nullptr;
}

template<typename T>
void SingleLinkedList<T>::print()
{
    Node<T>* currentNode = m_head;
    while(currentNode)
    {
        std::cout << currentNode->value();
        if(currentNode->next())
            std::cout << " --> ";
        currentNode = currentNode->next();
    }
    std::cout << std::endl;
}

template<typename T>
void SingleLinkedList<T>::remove(const T& value)
{
    Node<T>* currentNode = m_head;
    Node<T>* previous = nullptr;
    while(currentNode)
    {
        if(currentNode->value() == value)
        {
            if(currentNode == m_head)
            {
                popFront();
                currentNode = m_head;
            }
            else
            {
                eraseAfter(previous);
                currentNode = previous->next();
            }
        }
        else
        {
            previous = currentNode;
            currentNode = currentNode->next();
        }
    }
}

template<typename T>
void SingleLinkedList<T>::reverse()
{
    SingleLinkedList<T> temp;
    Node<T>* currentNode = m_head;
    while(currentNode)
    {
        temp.pushFront(currentNode->value());
        currentNode = currentNode->next();
    }

    *this = std::move(temp);
}

template<typename T>
void SingleLinkedList<T>::unique()
{
    Node<T>* currentNode = m_head;
    Node<T>* previous = nullptr;
    while(currentNode)
    {
        if(previous)
        {
            if(previous->value() == currentNode->value())
            {
                eraseAfter(previous);
                currentNode = previous;
            }
        }
        previous = currentNode;
        currentNode = currentNode->next();
    }
}

template<typename T>
void SingleLinkedList<T>::resize(size_t size)
{
    if(size > m_nUsed)
    {
        while(size > m_nUsed)
        {
            insertAfter(m_tail, T());
        }
    }
    else
    {
        size_t count = 1;
        Node<T>* currentNode = m_head;
        Node<T>* previous = nullptr;
        while(currentNode)
        {
            if(count > size)
            {
                if(currentNode == m_head)
                {
                    popFront();
                    currentNode = m_head;
                }
                else
                {
                    eraseAfter(previous);
                    currentNode = previous->next();
                }
            }
            else
            {
                previous = currentNode;
                currentNode = currentNode->next();
            }
            ++count;
        }
    }
}

template<typename T>
void SingleLinkedList<T>::sort()
{
    for(size_t i = 0; i != m_nUsed; i++)
    {
        Node<T>* currentNode = m_head;
        Node<T>* previous = nullptr;

        while(currentNode)
        {
            if(currentNode->next() && currentNode->value() > currentNode->next()->value())
            {
                Node<T>* tempNext = currentNode->next();
                T val = tempNext->value();
                Node<T>* nextNode = new Node<T>(currentNode->value(), tempNext->next());
                delete currentNode;
                delete tempNext;
                currentNode = new Node<T>(val, nextNode);

                if(previous)
                {
                    previous->next() = currentNode;
                }
                else
                {
                    m_head = currentNode;
                }
            }
            previous = currentNode;
            currentNode = currentNode->next();
        }
    }
}

template<typename T>
void SingleLinkedList<T>::merge(SingleLinkedList<T> &other)
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

template<typename T>
Node<T>* SingleLinkedList<T>::nextWithDelete(Node<T>* node)
{
    Node<T>* temp = node->next();
    delete node;
    node = temp;
    return node;
}
