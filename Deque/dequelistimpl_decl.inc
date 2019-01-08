#ifndef DEQUELISTIMPL_DECL_HPP
#define DEQUELISTIMPL_DECL_HPP

#include "vector.hpp"
#include "doublelinkedlist.hpp"
#include "constants.hpp"

template<typename T> class DequeListImpl
{
public:
    DequeListImpl();
    ~DequeListImpl();
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
    void expand(ExpandingPolicy expandingPolicy);
    void init(ExpandingPolicy expandingPolicy);

    int getNextIndex(int index);
    int getPreviousIndex(int index);

    void moveToNextBlock(typename DoubleLinkedList<T*>::Node*& node);
    void moveToPreviousBlock(typename DoubleLinkedList<T*>::Node*& node);

private:
    DoubleLinkedList<T*> m_pDirectory;
    int m_frontUsed = 0, m_backUsed = 0;
    int m_directorySize = 0;
    int m_blockSize = BLOCK_SIZE;
    typename DoubleLinkedList<T*>::Node* m_frontBlockNode = nullptr, *m_backBlockNode = nullptr;
    int m_firstIndex = INVALID_INDEX, m_lastIndex = INVALID_INDEX;

};

#endif // DEQUELISTIMPL_DECL_HPP
