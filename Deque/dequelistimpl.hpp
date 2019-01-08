#ifndef DEQUELISTIMPL_HPP
#define DEQUELISTIMPL_HPP

#include <iostream>
#include <cassert>

#include "dequelistimpl_decl.inc"

template<typename T>
DequeListImpl<T>::DequeListImpl()
{
}

template<typename T>
DequeListImpl<T>::~DequeListImpl()
{
    clear();
}

template<typename T>
bool DequeListImpl<T>::isEmpty()
{
    return (m_backUsed == 0 && m_frontUsed == 0);
}

template<typename T>
void DequeListImpl<T>::clear()
{
    auto currentNode = m_pDirectory.front();
    while(currentNode)
    {
        if(currentNode->value())
            delete[] currentNode->value();
        currentNode = currentNode->next();
    }

    m_pDirectory.clear();
    m_directorySize = 0;
    m_frontBlockNode = m_backBlockNode = nullptr;
    m_firstIndex = m_lastIndex = INVALID_INDEX;
    m_frontUsed = m_backUsed = 0;
}

template<typename T>
T& DequeListImpl<T>::front()
{
    assert(!isEmpty());

    return m_frontBlockNode->value()[m_firstIndex];
}

template<typename T>
T& DequeListImpl<T>::back()
{
    assert(!isEmpty());

    return m_backBlockNode->value()[m_lastIndex];
}

template<typename T>
void DequeListImpl<T>::pushFront(const T &value)
{
    if(isEmpty())
    {
        init(ExpandingPolicy::Front);
    }
    else
    {
        if(m_firstIndex - 1 < 0)
            moveToPreviousBlock(m_frontBlockNode);
        m_firstIndex = getPreviousIndex(m_firstIndex);

        m_frontUsed = m_firstIndex + 1;
        m_backUsed = (m_frontBlockNode == m_backBlockNode) ? m_frontUsed : m_backUsed;
    }

    m_frontBlockNode->value()[m_firstIndex] = value;
}

template<typename T>
void DequeListImpl<T>::pushBack(const T &value)
{
    if(isEmpty())
    {
        init(ExpandingPolicy::Back);
    }
    else
    {
        if(m_lastIndex + 1 >= m_blockSize)
            moveToNextBlock(m_backBlockNode);
        m_lastIndex = getNextIndex(m_lastIndex);

        m_backUsed = m_lastIndex + 1;
        m_frontUsed = (m_frontBlockNode == m_backBlockNode) ? m_backUsed : m_frontUsed;
    }

    m_backBlockNode->value()[m_lastIndex] = value;
}

template<typename T>
void DequeListImpl<T>::popFront()
{
    assert(!isEmpty());

    --m_frontUsed;
    if(m_firstIndex + 1 >= m_blockSize && m_frontBlockNode != m_backBlockNode)
    {
        moveToNextBlock(m_frontBlockNode);
        m_frontUsed = (m_frontBlockNode == m_backBlockNode) ? m_backUsed : m_blockSize;
    }

    m_backUsed = (m_frontBlockNode == m_backBlockNode) ? m_frontUsed : m_backUsed;
    m_firstIndex = getNextIndex(m_firstIndex);
}

template<typename T>
void DequeListImpl<T>::popBack()
{
    assert(!isEmpty());

    --m_backUsed;
    if(m_lastIndex - 1 < 0 && m_frontBlockNode != m_backBlockNode)
    {
        moveToPreviousBlock(m_backBlockNode);
        m_backUsed = (m_frontBlockNode == m_backBlockNode) ? m_frontUsed : m_blockSize;
    }

    m_frontUsed = (m_frontBlockNode == m_backBlockNode) ? m_backUsed : m_frontUsed;
    m_lastIndex = getPreviousIndex(m_lastIndex);
}

template<typename T>
void DequeListImpl<T>::print()
{
    assert(!isEmpty());

    auto currentNode = m_frontBlockNode;
    while(currentNode != m_backBlockNode->next())
    {
        int blockSize = (currentNode == m_backBlockNode) ? m_lastIndex + 1 : m_blockSize;
        int startIndex = (currentNode == m_frontBlockNode) ? m_firstIndex : 0;
        for(int j = startIndex; j != blockSize; ++j)
        {
            std::cout << currentNode->value()[j] << " ";
        }
        currentNode = currentNode->next();
    }
    std::cout << std::endl;
}

template<typename T>
bool DequeListImpl<T>::operator ==(const Vector<T>& test_vector)
{
    if(isEmpty())
        return test_vector.isEmpty();

    int i = 0;
    auto currentNode = m_frontBlockNode;
    while(currentNode != m_backBlockNode->next())
    {
        int blockSize = (currentNode == m_backBlockNode) ? m_lastIndex + 1 : m_blockSize;
        int startIndex = (currentNode == m_frontBlockNode) ? m_firstIndex : 0;
        for(int j = startIndex; j != blockSize; ++j, ++i)
        {
           if(test_vector[i] != currentNode->value()[j])
               return false;
        }
        currentNode = currentNode->next();
    }
    return true;
}

template<typename T>
void DequeListImpl<T>::expand(ExpandingPolicy expandingPolicy)
{
    if(expandingPolicy == ExpandingPolicy::Back)
    {
        m_pDirectory.pushBack(new T[m_blockSize]);
    }
    else
    {
        m_pDirectory.pushFront(new T[m_blockSize]);
    }
    ++m_directorySize;
}

template<typename T>
void DequeListImpl<T>::init(ExpandingPolicy expandingPolicy)
{
    if(m_directorySize == 0)
        expand(expandingPolicy);

    m_frontBlockNode = m_backBlockNode = m_pDirectory.front();
    m_firstIndex = m_lastIndex = 0;
    m_frontUsed = m_backUsed = 1;
}

template<typename T>
int DequeListImpl<T>::getNextIndex(int index)
{
    ++index;
    if(index >= m_blockSize)
    {
        index = 0;
    }
    return index;
}

template<typename T>
int DequeListImpl<T>::getPreviousIndex(int index)
{
    --index;
    if(index < 0)
    {
        index = m_blockSize - 1;
    }
    return index;
}

template<typename T>
void DequeListImpl<T>::moveToNextBlock(typename DoubleLinkedList<T*>::Node*& node)
{
    if(node->next() == nullptr)
        expand(ExpandingPolicy::Back);

    node = node->next();
}

template<typename T>
void DequeListImpl<T>::moveToPreviousBlock(typename DoubleLinkedList<T*>::Node*& node)
{
    if(node->previous() == nullptr)
        expand(ExpandingPolicy::Front);

    node = node->previous();
}

#endif // DEQUELISTIMPL_HPP
