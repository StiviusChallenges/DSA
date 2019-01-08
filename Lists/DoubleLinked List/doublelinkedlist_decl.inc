#ifndef DOUBLELINKEDLIST_DECL_H
#define DOUBLELINKEDLIST_DECL_H

template<typename T> class DoubleLinkedList
{
public:
    class Node
    {
    public:
        Node(T _value, Node* _next, Node* _previous) : m_value(_value), m_next(_next), m_previous(_previous) { }
        Node*& next() { return m_next; }
        Node*& previous() { return m_previous; }
        T value() const { return m_value; }
        T& value() { return m_value; }

    private:
        T m_value;
        Node* m_next = nullptr;
        Node* m_previous = nullptr;

    };

    DoubleLinkedList();
    DoubleLinkedList(DoubleLinkedList<T>&& other);
    DoubleLinkedList& operator =(DoubleLinkedList<T>&& other);
    ~DoubleLinkedList();
    bool operator ==(const DoubleLinkedList<T> &other);
    bool empty();
    void clear();
    Node* insert(Node* pos, const T& value);
    void erase(Node* pos);
    void pushFront(const T& value);
    void popFront();
    Node* front();
    void pushBack(const T& value);
    void popBack();
    Node* back();
    Node* find(const T& value);
    void print();

private:
    Node* m_head = nullptr;
    Node* m_tail = nullptr;
    size_t m_nUsed = 0;

};

#endif // DOUBLELINKEDLIST_DECL_H
