#include <iostream>
#include <vector>

#include "testing.hpp"

template<typename T> class A { };
template<template <typename> typename Container> class B { };

int main()
{
    B<A> a;
    DequeArrayImpl<int> dequeArrayImplementation;
//    DequeListImpl<int> dequeListImplementation;

    testing::initTestCases(dequeArrayImplementation);
    testing::runTests();

    return 0;
}
