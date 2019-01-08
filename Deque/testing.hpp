#ifndef TESTS_H
#define TESTS_H

#include <cassert>
#include <functional>

#include "dequelistimpl.hpp"
#include "dequearrayimpl.hpp"

namespace testing {

    struct TestCase {
        std::string testName;
        std::function<void()> testFunction;
    };

    Vector<TestCase> testCases;

    void addTestCase(std::string testName, std::function<void()> testFunction)
    {
        testCases.pushBack(TestCase{testName, testFunction});
    }

    template<typename Deque> void initTestCases(Deque&)
    {
        addTestCase("Empty deque", [=](){
            Deque deque;

            assert(deque == Vector<typename Deque::type>({}));
            assert(deque.isEmpty());
        });

        addTestCase("Add single element to back", [=](){
            Deque deque;

            deque.pushBack(1);

            assert(deque == Vector<typename Deque::type>({1}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add single element to front", [=](){
            Deque deque;

            deque.pushFront(1);

            assert(deque == Vector<typename Deque::type>({1}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add 1 element to front and 1 back", [=](){
            Deque deque;

            deque.pushFront(1);
            deque.pushBack(2);

            assert(deque == Vector<typename Deque::type>({1,2}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add 2 elements back)", [=](){
            Deque deque;

            deque.pushBack(1);
            deque.pushBack(2);

            assert(deque == Vector<typename Deque::type>({1,2}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add 1 element to back and 1 to front", [=](){
            Deque deque;

            deque.pushBack(1);
            deque.pushFront(2);

            assert(deque == Vector<typename Deque::type>({2,1}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add 2 elements front", [=](){
            Deque deque;

            deque.pushFront(1);
            deque.pushFront(2);

            assert(deque == Vector<typename Deque::type>({2,1}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add 2 elements back and delete 1 from front", [=](){
            Deque deque;

            deque.pushBack(1);
            deque.pushBack(2);
            deque.popFront();

            assert(deque == Vector<typename Deque::type>({2}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add 1 element front, 1 to back and delete 1 from front", [=](){
            Deque deque;

            deque.pushFront(1);
            deque.pushBack(2);
            deque.popFront();

            assert(deque == Vector<typename Deque::type>({2}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add 2 elements to back and delete 1 from back", [=](){
            Deque deque;

            deque.pushBack(1);
            deque.pushBack(2);
            deque.popBack();

            assert(deque == Vector<typename Deque::type>({1}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add 1 element front, 1 to back and delete 1 from back", [=](){
            Deque deque;

            deque.pushFront(1);
            deque.pushBack(2);
            deque.popBack();

            assert(deque == Vector<typename Deque::type>({1}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add 2 elements to back and delete 1 from front and 1 from back", [=](){
            Deque deque;

            deque.pushBack(1);
            deque.pushBack(2);
            deque.popFront();
            deque.popBack();

            assert(deque == Vector<typename Deque::type>({}));
            assert(deque.isEmpty());
        });

        addTestCase("Add 2 to back and delete 2 from front", [=](){
            Deque deque;

            deque.pushBack(1);
            deque.pushBack(2);
            deque.popFront();
            deque.popFront();

            assert(deque == Vector<typename Deque::type>({}));
            assert(deque.isEmpty());
        });

        addTestCase("Add 1 to front and 1 to back and delete 1 from front and 1 from back", [=](){
            Deque deque;

            deque.pushFront(1);
            deque.pushBack(2);
            deque.popFront();
            deque.popBack();

            assert(deque == Vector<typename Deque::type>({}));
            assert(deque.isEmpty());
        });

        addTestCase("Add 1 to front and 1 to back and delete 2 from front", [=](){
            Deque deque;

            deque.pushFront(1);
            deque.pushBack(2);
            deque.popFront();
            deque.popFront();

            assert(deque == Vector<typename Deque::type>({}));
            assert(deque.isEmpty());
        });

        addTestCase("Add 1 to front and 1 to back and delete 2 from front then again add 1 to back", [=](){
            Deque deque;

            deque.pushFront(1);
            deque.pushBack(2);
            deque.popFront();
            deque.popFront();
            deque.pushBack(1);

            assert(deque == Vector<typename Deque::type>({1}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add 1 to front and 1 to back and delete 1 from front then again add 1 to back", [=](){
            Deque deque;

            deque.pushFront(1);
            deque.pushBack(2);
            deque.popFront();
            deque.pushBack(1);

            assert(deque == Vector<typename Deque::type>({2,1}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add elements to fill 1st block and then remove from front until 2 remains", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE; i++)
                deque.pushBack(i);
            for(int i = 0; i != BLOCK_SIZE - 2; i++)
                deque.popFront();

            assert(deque == Vector<typename Deque::type>({6,7}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add elements to fill 1st block and then remove from front until 2 remains. "
                    "Then add 1 element to front", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE; i++)
                deque.pushBack(i);
            for(int i = 0; i != BLOCK_SIZE - 2; i++)
                deque.popFront();
            deque.pushFront(5);

            assert(deque == Vector<typename Deque::type>({5,6,7}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add elements to fill 1st block and then remove from front until 2 remains. "
                    "Then add 1 element to back (should move to next block)", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE; i++)
                deque.pushBack(i);
            for(int i = 0; i != BLOCK_SIZE - 2; i++)
                deque.popFront();
            deque.pushBack(1);

            assert(deque == Vector<typename Deque::type>({6,7,1}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add elements to fill 1st block and then remove from front until 2 remains. "
                    "Then add 2 element to back", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE; i++)
                deque.pushBack(i);
            for(int i = 0; i != BLOCK_SIZE - 2; i++)
                deque.popFront();
            deque.pushBack(1);
            deque.pushBack(2);

            assert(deque == Vector<typename Deque::type>({6,7,1,2}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add elements to fill 1st block and then remove from front until 2 remains. "
                    "Then add 1 element to back and 1 to front", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE; i++)
                deque.pushBack(i);
            for(int i = 0; i != BLOCK_SIZE - 2; i++)
                deque.popFront();
            deque.pushBack(1);
            deque.pushFront(0);

            assert(deque == Vector<typename Deque::type>({0,6,7,1}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add elements to fill 1st block and then remove from front until 2 remains. "
                    "Then add 2 element to back and remove 2 from front", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE; i++)
                deque.pushBack(i);
            for(int i = 0; i != BLOCK_SIZE - 2; i++)
                deque.popFront();
            deque.pushBack(1);
            deque.pushBack(2);
            deque.popFront();
            deque.popFront();

            assert(deque == Vector<typename Deque::type>({1,2}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add elements to fill 1st block and then remove from front until 2 remains. "
                    "Then add 2 element to back and remove 2 from front. add 1 to front", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE; i++)
                deque.pushBack(i);
            for(int i = 0; i != BLOCK_SIZE - 2; i++)
                deque.popFront();
            deque.pushBack(1);
            deque.pushBack(2);
            deque.popFront();
            deque.popFront();
            deque.pushFront(0);

            assert(deque == Vector<typename Deque::type>({0,1,2}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add elements to fill 1st block and then remove from front until 2 remains. "
                    "Then add 1 element to back and remove it from back", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE; i++)
                deque.pushBack(i);
            for(int i = 0; i != BLOCK_SIZE - 2; i++)
                deque.popFront();
            deque.pushBack(1);
            deque.popBack();

            assert(deque == Vector<typename Deque::type>({6,7}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add elements to fill 1st block and then remove from front until 2 remains. "
                    "Then add 1 element to back and remove it from back. remove another from front", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE; i++)
                deque.pushBack(i);
            for(int i = 0; i != BLOCK_SIZE - 2; i++)
                deque.popFront();
            deque.pushBack(1);
            deque.popBack();
            deque.popFront();

            assert(deque == Vector<typename Deque::type>({7}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add elements to fill 1st block and then remove from front until 2 remains. "
                    "Then add 1 element to back and remove it from back. remove another from front and back "
                    "(deque should become empty)", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE; i++)
                deque.pushBack(i);
            for(int i = 0; i != BLOCK_SIZE - 2; i++)
                deque.popFront();
            deque.pushBack(1);
            deque.popBack();
            deque.popFront();
            deque.popBack();

            assert(deque == Vector<typename Deque::type>({}));
            assert(deque.isEmpty());
        });

        addTestCase("Add elements to fill 1st block and then remove from front until 2 remains. "
                    "Then add 1 element to back and remove it from back. remove another from front and back "
                    "(deque should become empty)", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE; i++)
                deque.pushBack(i);
            for(int i = 0; i != BLOCK_SIZE - 2; i++)
                deque.popFront();
            deque.pushBack(1);
            deque.popBack();
            deque.popFront();
            deque.popBack();

            assert(deque == Vector<typename Deque::type>({}));
            assert(deque.isEmpty());
        });

        addTestCase("Add elements to fill 1st block and then remove from front until 2 remains. "
                    "Then add 1 element to back and remove it from back. remove 2 elements from front "
                    "(deque should become empty)", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE; i++)
                deque.pushBack(i);
            for(int i = 0; i != BLOCK_SIZE - 2; i++)
                deque.popFront();

            deque.pushBack(1);
            deque.popBack();
            deque.popFront();
            deque.popFront();

            assert(deque == Vector<typename Deque::type>({}));
            assert(deque.isEmpty());
        });

        addTestCase("Add elements to fill 1st block and then remove from front until 2 remains. "
                    "Then add 2 elements to back. remove 2 elements from front. remove 2 elements from back "
                    "(deque should become empty)", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE; i++)
                deque.pushBack(i);
            for(int i = 0; i != BLOCK_SIZE - 2; i++)
                deque.popFront();
            deque.pushBack(1);
            deque.pushBack(2);
            deque.popFront();
            deque.popFront();
            deque.popBack();
            deque.popBack();

            assert(deque == Vector<typename Deque::type>({}));
            assert(deque.isEmpty());
        });

        addTestCase("Add elements to fill 1st block and then remove from front until 2 remains. "
                    "Then add 2 elements to back. remove 1 element from front and 1 from back (twice). "
                    "(deque should become empty)", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE; i++)
                deque.pushBack(i);
            for(int i = 0; i != BLOCK_SIZE - 2; i++)
                deque.popFront();
            deque.pushBack(1);
            deque.pushBack(2);
            deque.popFront();
            deque.popBack();
            deque.popFront();
            deque.popBack();

            assert(deque == Vector<typename Deque::type>({}));
            assert(deque.isEmpty());
        });

        addTestCase("Add elements to fill 1st block and 2nd block", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE * 2; i++)
                deque.pushBack(i);

            assert(deque == Vector<typename Deque::type>({0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add elements to fill 1st block and 2nd block. "
                    "Add 1 element to back (deque should be expanded to back)", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE * 2; i++)
                deque.pushBack(i);
            deque.pushBack(5);

            assert(deque == Vector<typename Deque::type>({0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,5}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add elements to fill 1st block and 2nd block. "
                    "Add 1 element to back (deque should be expanded to back). "
                    "Add 1 element to front (deque should be expanded to front)", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE * 2; i++)
                deque.pushBack(i);
            deque.pushBack(5);
            deque.pushFront(0);

            assert(deque == Vector<typename Deque::type>({0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,5}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add elements to fill 1st block and 2nd block. "
                    "Add 1 element to front (deque should be expanded to front). "
                    "Add 1 element to back (deque should be expanded to back)", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE * 2; i++)
                deque.pushBack(i);
            deque.pushFront(0);
            deque.pushBack(5);

            assert(deque == Vector<typename Deque::type>({0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,5}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add BLOCK_SIZE * 2 + 1 elements to front. "
                    "Deque should be expanded to front twice", [=](){
            Deque deque;

            for(int i = 0; i != (BLOCK_SIZE * 2) + 1; i++)
                deque.pushFront(i);

            assert(deque == Vector<typename Deque::type>({16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add BLOCK_SIZE * 2 + 1 elements to front. "
                    "Deque should be expanded to front twice. "
                    "Add 1 element to front", [=](){
            Deque deque;

            for(int i = 0; i != (BLOCK_SIZE * 2) + 1; i++)
                deque.pushFront(i);
            deque.pushFront(0);

            assert(deque == Vector<typename Deque::type>({0,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0}));
            assert(!deque.isEmpty());
        });


        addTestCase("Add BLOCK_SIZE * 3 elements to back (deque should be expanded to back once). "
                    "Add BLOCK_SIZE - 2 elements to front (deque should be expanded to front). "
                    "Remove BLOCK_SIZE / 2 elements from back", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE * 3; i++)
                deque.pushBack(i);
            for(int i = 0; i != BLOCK_SIZE - 2; i++)
                deque.pushFront(i);
            for(int i = 0; i != BLOCK_SIZE / 2; i++)
                deque.popBack();

            assert(deque == Vector<typename Deque::type>({5,4,3,2,1,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add BLOCK_SIZE * 3 elements to back (deque should be expanded to back once). "
                    "Remove BLOCK_SIZE - 2 elements from front. "
                    "Remove BLOCK_SIZE / 2 elements from back", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE * 3; i++)
                deque.pushBack(i);
            for(int i = 0; i != BLOCK_SIZE - 2; i++)
                deque.popFront();
            for(int i = 0; i != BLOCK_SIZE / 2; i++)
                deque.popBack();

            assert(deque == Vector<typename Deque::type>({6,7,8,9,10,11,12,13,14,15,16,17,18,19}));
            assert(!deque.isEmpty());
        });

        addTestCase("Add 1 element to back and remove it from back", [=](){
            Deque deque;

            deque.pushBack(1);
            deque.popBack();

            assert(deque == Vector<typename Deque::type>({}));
            assert(deque.isEmpty());
        });

        addTestCase("Add 1 element to back and remove it from front", [=](){
            Deque deque;

            deque.pushBack(1);
            deque.popFront();

            assert(deque == Vector<typename Deque::type>({}));
            assert(deque.isEmpty());
        });

        addTestCase("Add 1 element to front and remove it from back", [=](){
            Deque deque;

            deque.pushFront(1);
            deque.popBack();

            assert(deque == Vector<typename Deque::type>({}));
            assert(deque.isEmpty());
        });

        addTestCase("Add 1 element to front and remove it from front", [=](){
            Deque deque;

            deque.pushFront(1);
            deque.popFront();

            assert(deque == Vector<typename Deque::type>({}));
            assert(deque.isEmpty());
        });

        addTestCase("Add 100 elements to back", [=](){
            Deque deque;
            Vector<typename Deque::type> vec;

            for(int i = 0; i != 100; i++)
            {
                deque.pushBack(i);
                vec.pushBack(i);
            }

            assert(deque == vec);
            assert(!deque.isEmpty());
        });

        addTestCase("Add 100 elements to front", [=](){
            Deque deque;
            Vector<typename Deque::type> vec;

            for(int i = 0; i != 100; i++)
            {
                deque.pushFront(i);
                vec.insert(0, i);
            }

            assert(deque == vec);
            assert(!deque.isEmpty());
        });

        addTestCase("Add BLOCK_SIZE + 1 elements to back. Remove BLOCK_SIZE - 2 elements from front. "
                    "Remove 3 elements from back", [=](){
            Deque deque;

            for(int i = 0; i != BLOCK_SIZE + 1; i++)
            {
                deque.pushBack(i);
            }
            for(int i = 0; i != BLOCK_SIZE - 2; i++)
            {
                deque.popFront();
            }
            deque.popBack();
            deque.popBack();
            deque.popBack();

            assert(deque == Vector<typename Deque::type>({}));
            assert(deque.isEmpty());
        });
    }

    void runTests()
    {
        for(size_t i = 0; i != testCases.size(); ++i)
        {
            std::cout << "Test #" << i + 1 << std::endl;
            std::cout << "Test name: " << testCases[i].testName << std::endl;
            std::cout << "Running test" << std::endl;
            testCases[i].testFunction();
            std::cout << "Test #" << i + 1 << " passed" << std::endl;
            std::cout << std::endl;
        }

        std::cout << "All tests passed!" << std::endl;
    }
}

#endif // TESTS_H
