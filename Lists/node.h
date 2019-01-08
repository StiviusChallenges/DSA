#ifndef NODE_H
#define NODE_H

template<typename T> class Node
{
public:
    Node(T _value, Node<T>* _next) : m_value(_value), m_next(_next) { }
    Node<T>*& next() { return m_next; }
    T value() const { return m_value; }

private:
    T m_value;
    Node<T>* m_next = nullptr;

};

#endif // NODE_H
