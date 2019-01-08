#ifndef DEQUEARRAYIMPL_HPP
#define DEQUEARRAYIMPL_HPP

#include <iostream>
#include <cassert>

#include "dequearrayimpl_decl.inc"

template<typename T>
DequeArrayImpl<T>::DequeArrayImpl()
{
}

template<typename T>
DequeArrayImpl<T>::~DequeArrayImpl()
{
    clear();
}

template<typename T>
bool DequeArrayImpl<T>::isEmpty()
{
    return (m_backUsed == 0 && m_frontUsed == 0);
}

template<typename T>
void DequeArrayImpl<T>::clear()
{
    for(int i = 0; i != m_directorySize; ++i)
    {
        delete[] m_pDirectory[i];
    }

    m_pDirectory.clear();
    m_directorySize = 0;
    m_frontBlockIndex = m_backBlockIndex = INVALID_INDEX;
    m_firstIndex = m_lastIndex = INVALID_INDEX;
    m_frontUsed = m_backUsed = 0;
}

template<typename T>
void DequeArrayImpl<T>::pushFront(const T &value)
{
    if(isEmpty())
    {
        init(ExpandingPolicy::Front);
    }
    else
    {
        if(m_firstIndex - 1 < 0)
            moveToPreviousBlock(m_frontBlockIndex);
        m_firstIndex = getPreviousIndex(m_firstIndex);

        m_frontUsed = m_firstIndex + 1;
        m_backUsed = (m_frontBlockIndex == m_backBlockIndex) ? m_frontUsed : m_backUsed;
    }

    m_pDirectory[m_frontBlockIndex][m_firstIndex] = value;
}

template<typename T>
void DequeArrayImpl<T>::pushBack(const T &value)
{
    if(isEmpty())
    {
        init(ExpandingPolicy::Back);
    }
    else
    {
        if(m_lastIndex + 1 >= m_blockSize)
            moveToNextBlock(m_backBlockIndex);
        m_lastIndex = getNextIndex(m_lastIndex);

        m_backUsed = m_lastIndex + 1;
        m_frontUsed = (m_frontBlockIndex == m_backBlockIndex) ? m_backUsed : m_frontUsed;
    }

    m_pDirectory[m_backBlockIndex][m_lastIndex] = value;
}

template<typename T>
void DequeArrayImpl<T>::popFront()
{
    assert(!isEmpty());

    --m_frontUsed;
    if(m_firstIndex + 1 >= m_blockSize && m_frontBlockIndex != m_backBlockIndex)
    {
        moveToNextBlock(m_frontBlockIndex);
        m_frontUsed = (m_frontBlockIndex == m_backBlockIndex) ? m_backUsed : m_blockSize;
    }

    m_backUsed = (m_frontBlockIndex == m_backBlockIndex) ? m_frontUsed : m_backUsed;
    m_firstIndex = getNextIndex(m_firstIndex);
}

template<typename T>
void DequeArrayImpl<T>::popBack()
{
    assert(!isEmpty());

    --m_backUsed;
    if(m_lastIndex - 1 < 0 && m_frontBlockIndex != m_backBlockIndex)
    {
        moveToPreviousBlock(m_backBlockIndex);
        m_backUsed = (m_frontBlockIndex == m_backBlockIndex) ? m_frontUsed : m_blockSize;
    }

    m_frontUsed = (m_frontBlockIndex == m_backBlockIndex) ? m_backUsed : m_frontUsed;
    m_lastIndex = getPreviousIndex(m_lastIndex);
}

template<typename T>
T& DequeArrayImpl<T>::front()
{
    assert(!isEmpty());

    return m_pDirectory[m_frontBlockIndex][m_firstIndex];
}

template<typename T>
T& DequeArrayImpl<T>::back()
{
    assert(!isEmpty());

    return m_pDirectory[m_backBlockIndex][m_lastIndex];
}

template<typename T>
void DequeArrayImpl<T>::print()
{
    assert(!isEmpty());

    for(int i = m_frontBlockIndex; i <= m_backBlockIndex; ++i)
    {
        int blockSize = (i == m_backBlockIndex) ? m_lastIndex + 1 : m_blockSize;
        int startIndex = (i == m_frontBlockIndex) ? m_firstIndex : 0;
        for(int j = startIndex; j != blockSize; ++j)
        {
            std::cout << m_pDirectory[i][j] << " ";
        }
    }
    std::cout << std::endl;
}

template<typename T>
bool DequeArrayImpl<T>::operator ==(const Vector<T>& test_vector)
{
    if(isEmpty())
        return test_vector.isEmpty();

    for(int i = m_frontBlockIndex, k = 0; i <= m_backBlockIndex; ++i)
    {
        int blockSize = (i == m_backBlockIndex) ? m_lastIndex + 1 : m_blockSize;
        int startIndex = (i == m_frontBlockIndex) ? m_firstIndex : 0;
        for(int j = startIndex; j != blockSize; ++j, ++k)
        {
            if(test_vector[k] != m_pDirectory[i][j])
                return false;
        }
    }

    return true;
}

template<typename T>
void DequeArrayImpl<T>::expand(int newSize, ExpandingPolicy expandingPolicy)
{
    assert(newSize > m_directorySize);

    for(int i = 0; i != EXPANDING_BLOCKS; i++)
    {
        if(expandingPolicy == ExpandingPolicy::Back)
            m_pDirectory.pushBack(nullptr);
        else
            m_pDirectory.insert(0, nullptr);
    }

    m_directorySize = newSize;
}


template<typename T>
void DequeArrayImpl<T>::init(ExpandingPolicy expandingPolicy)
{
    if(m_directorySize == 0)
    {
        expand(m_directorySize + EXPANDING_BLOCKS, expandingPolicy);
        m_pDirectory[0] = new T[m_blockSize];
    }

    m_frontBlockIndex = m_backBlockIndex = 0;
    m_firstIndex = m_lastIndex = 0;
    m_frontUsed = m_backUsed = 1;
}

template<typename T>
int DequeArrayImpl<T>::getNextIndex(int index)
{
    ++index;
    if(index >= m_blockSize)
    {
        index = 0;
    }
    return index;
}

template<typename T>
int DequeArrayImpl<T>::getPreviousIndex(int index)
{
    --index;
    if(index < 0)
    {
        index = m_blockSize - 1;
    }
    return index;
}

template<typename T>
void DequeArrayImpl<T>::moveToNextBlock(int& blockIndex)
{
    if(blockIndex + 1 >= m_directorySize)
        expand(m_directorySize + EXPANDING_BLOCKS, ExpandingPolicy::Back);

    ++blockIndex;
    if(!m_pDirectory[blockIndex])
        m_pDirectory[blockIndex] = new T[m_blockSize];
}

template<typename T>
void DequeArrayImpl<T>::moveToPreviousBlock(int& blockIndex)
{
    if(blockIndex - 1 < 0)
    {
        expand(m_directorySize + EXPANDING_BLOCKS, ExpandingPolicy::Front);
        m_frontBlockIndex += EXPANDING_BLOCKS;
        m_backBlockIndex += EXPANDING_BLOCKS;
    }

    --blockIndex;
    if(!m_pDirectory[blockIndex])
        m_pDirectory[blockIndex] = new T[m_blockSize];
}


#endif // DEQUEARRAYIMPL_HPP
