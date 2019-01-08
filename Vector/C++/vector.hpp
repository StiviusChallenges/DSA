#ifndef VECTOR_H
#define VECTOR_H

#include "vector_decl.inc"
#include "constants.hpp"

template<typename T>
Vector<T>::Vector()
{
    m_pData = new T[m_nAllocated];
}

template<typename T>
Vector<T>::Vector(size_t size)
{
    if(size == 0)
        throw std::bad_array_new_length();

    m_pData = new T[size];
    m_nAllocated = m_nUsed = size;
}

template<typename T>
Vector<T>::Vector(const std::initializer_list<T> &list) : Vector()
{
    for(const auto& i : list)
    {
        pushBack(i);
    }
}

template<typename T>
Vector<T>::Vector(size_t size, const T& value) : Vector(size)
{
    std::fill(m_pData, m_pData + m_nUsed, value);
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
    m_nAllocated = other.m_nAllocated;
    m_nUsed = other.m_nUsed;
    m_pData = new T[m_nAllocated];

    std::copy(other.m_pData, other.m_pData + other.m_nUsed, m_pData);
}

template<typename T>
Vector<T>& Vector<T>::operator =(const Vector<T>& other)
{
    if(*this == other)
        throw std::logic_error("Self-assignment");

    m_nAllocated = other.m_nAllocated;
    m_nUsed = other.m_nUsed;

    if(m_pData) delete[] m_pData;
    m_pData = new T[m_nAllocated];

    std::copy(other.m_pData, other.m_pData + other.m_nUsed, m_pData);
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator =(Vector<T>&& other)
{
    if(*this == other)
        throw std::logic_error("Self-assignment");

    m_nAllocated = other.m_nAllocated;
    m_nUsed = other.m_nUsed;

    if(m_pData) delete[] m_pData;
    m_pData = other.m_pData;
    other.m_pData = nullptr;

    return *this;
}

template<typename T>
Vector<T>::Vector(Vector<T>&& other)
{
    m_nAllocated = other.m_nAllocated;
    m_nUsed = other.m_nUsed;
    m_pData = other.m_pData;
    other.m_pData = nullptr;
}

template<typename T>
Vector<T>::~Vector()
{
    if(m_pData) delete[] m_pData;
    m_nAllocated = 0;
    m_nUsed = 0;
}


template<typename T>
bool Vector<T>::operator ==(const Vector<T>& other)
{
    if(m_nUsed != other.m_nUsed)
        return false;

    for(size_t i = 0; i != m_nUsed; i++)
    {
        if(m_pData[i] != other.m_pData[i])
            return false;
    }
    return true;
}

template<typename T>
void Vector<T>::resize(size_t size)
{
    if(size == m_nUsed) return;

    if(size > m_nAllocated)
    {
        reserve(size * 2);
        std::fill(m_pData + m_nUsed, m_pData + size, T());
    }
    else if(size < m_nUsed)
    {
        for(size_t i = size; i != m_nUsed; i++)
            m_pData[i] = T();
    }
    else
    {
        std::fill(m_pData + m_nUsed, m_pData + size, T());
    }
    m_nUsed = size;
}

template<typename T>
void Vector<T>::pushBack(const T& value)
{
    if(m_nUsed >= m_nAllocated)
        reserve(m_nAllocated * 2);

    m_pData[m_nUsed++] = value;
}

template<typename T>
void Vector<T>::popBack()
{
    if(m_nUsed > 0)
    {
        m_pData[--m_nUsed] = 0;
    }
}

template<typename T>
T Vector<T>::operator[](size_t index) const
{
    return m_pData[index];
}

template<typename T>
T& Vector<T>::operator[](size_t index)
{
    return m_pData[index];
}

template<typename T>
void Vector<T>::Vector::print()
{
    for(size_t i = 0; i != m_nUsed; i++)
        std::cout << m_pData[i] << std::endl;
}

template<typename T>
int Vector<T>::find(const T& value)
{
    for(size_t i = 0; i != m_nUsed; i++)
        if(m_pData[i] == value)
            return i;
    return INVALID_INDEX;
}

template<typename T>
void Vector<T>::clear()
{
    for(size_t i = 0; i != m_nUsed; i++)
        m_pData[i] = T();
    m_nUsed = 0;
}

template<typename T>
size_t Vector<T>::size() const
{
    return m_nUsed;
}

template<typename T>
bool Vector<T>::isEmpty() const
{
    return (m_nUsed == 0) ? true : false;
}

template<typename T>
size_t Vector<T>::capacity() const
{
    return m_nAllocated;
}

template<typename T>
void Vector<T>::reserve(size_t nAllocated)
{
    if(nAllocated < m_nUsed || nAllocated == m_nAllocated)
        throw std::bad_alloc();

    m_nAllocated = nAllocated;
    T* pTempData = new T[m_nAllocated];
    std::copy(m_pData, m_pData + m_nUsed, pTempData);
    delete[] m_pData;
    m_pData = pTempData;
}

template<typename T>
void Vector<T>::shrinkToFit()
{
    reserve(m_nUsed);
}

template<typename T>
void Vector<T>::insert(size_t index, const T& value)
{
    if(index > m_nUsed-1)
        throw std::out_of_range("Out of range");

    if(m_nUsed + 1 >= m_nAllocated)
        reserve(m_nAllocated * 2);

    std::copy(m_pData + index, m_pData + m_nUsed, m_pData + (index + 1));
    m_pData[index] = value;

    m_nUsed++;
}

template<typename T>
void Vector<T>::erase(size_t index)
{
    if(index > m_nUsed-1)
        throw std::out_of_range("Out of range");

    std::copy(m_pData + (index + 1), m_pData + m_nUsed, m_pData + index);
    m_nUsed--;
}

#endif // VECTOR_H
