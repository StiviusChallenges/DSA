#ifndef DEQUEARRAYIMPL_DECL_HPP
#define DEQUEARRAYIMPL_DECL_HPP

#include "vector.hpp"
#include "constants.hpp"

template<typename T> class DequeArrayImpl
{
public:
    DequeArrayImpl();
    ~DequeArrayImpl();
    bool isEmpty();
    void clear();
    void pushFront(const T& value);
    void popFront();
    void pushBack(const T& value);
    void popBack();
    T& front();
    T& back();
    void print();
    bool operator ==(const Vector<T>& test_vector);
    using type = T;

private:
    void expand(int newSize, ExpandingPolicy expandingPolicy);
    void init(ExpandingPolicy expandingPolicy);

    int getNextIndex(int index);
    int getPreviousIndex(int index);

    void moveToNextBlock(int& blockIndex);
    void moveToPreviousBlock(int& blockIndex);

private:
    Vector<T*> m_pDirectory;
    int m_frontUsed = 0, m_backUsed = 0;
    int m_directorySize = 0;
    int m_blockSize = BLOCK_SIZE;
    int m_frontBlockIndex = INVALID_INDEX, m_backBlockIndex = INVALID_INDEX;
    int m_firstIndex = INVALID_INDEX, m_lastIndex = INVALID_INDEX;

};

#endif // DEQUEARRAYIMPL_DECL_HPP
