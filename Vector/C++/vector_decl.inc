#ifndef VECTOR_DECL_H
#define VECTOR_DECL_H

#include <iostream>

template<typename T> class Vector
{
public:
    Vector();
    Vector(size_t size);
    Vector(const std::initializer_list<T>& list);
    Vector(size_t size, const T& value);
    Vector(const Vector<T>& other);
    Vector& operator =(const Vector<T>& other);
    Vector(Vector<T>&& other);
    Vector& operator =(Vector<T>&& other);
    ~Vector();
    bool operator ==(const Vector<T>& other);
    void resize(size_t size);
    void pushBack(const T& value);
    void popBack();
    T operator [](size_t index) const;
    T& operator [](size_t index);
    void print();
    int find(const T& value);
    void clear();
    bool isEmpty() const;
    size_t size() const;
    size_t capacity() const;
    void reserve(size_t nAllocated);
    void shrinkToFit();
    void insert(size_t index, const T& value);
    void erase(size_t index);

private:
    T* m_pData = nullptr;
    size_t m_nUsed = 0;
    size_t m_nAllocated = 10;

};

#endif // VECTOR_DECL_H
