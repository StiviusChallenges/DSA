#ifndef SORTINGS_H
#define SORTINGS_H

#include <iostream>

long long count = 0;

template<typename T> void swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template<typename T, typename Comp> void comb_sort(T* array, size_t size, Comp comp)
{
    count = 0;
    int step = size - 1;
    float shrink = 1.3;
    bool sorted = false;

    while(!sorted)
    {
        if(step > 1)
        {
            sorted = false;
        }
        else
        {
            step = 1;
            sorted = true;
        }

        for(int i = 0; i + step < size; i++)
        {
            count++;
            if(comp(array[i], array[i + step]))
            {
                swap(array[i], array[i + step]);
                sorted = false;
            }
        }
        step /= shrink;
    }
}

template<typename T, typename Comp> void shell_sort(T* array, size_t size, Comp comp)
{
    count = 0;
    int d = size / 2;

    while(d > 0)
    {
        for(size_t i = d; i < size; i++)
        {
            T temp = array[i];
            for(size_t j = i; j >= d && comp(array[j - d], temp); j-=d)
            {
                count++;
                swap(array[j], array[j - d]);
            }
        }

        d /= 2;
    }
}

template<typename T, typename Comp> void selection_sort(T* array, size_t size, Comp comp)
{
    count = 0;

    size_t min_index;

    for(size_t i = 0; i != size - 1; i++)
    {
        min_index = i;
        for(size_t j = i + 1; j != size; j++)
        {
            count++;
            if(comp(array[min_index], array[j]))
            {
                min_index = j;
            }
        }

        if(i != min_index)
        {
            swap(array[i], array[min_index]);
        }
    }
}

template<typename T, typename Comp> void insertion_sort(T* array, size_t size, Comp comp)
{
    count = 0;

    for(int i = 1; i != size; i++)
    {
        for(int j = i; j > 0 && !comp(array[j], array[j - 1]); j--)
        {
            count++;
            swap(array[j], array[j - 1]);
        }
    }
}

template<typename T, typename Comp> void coctail_sort(T* array, size_t size, Comp comp)
{
    count = 0;
    size_t first = 0;
    size_t last = size - 1;
    bool swapped;

    while(first < last)
    {
        swapped = false;

        count++;
        for(size_t i = first; i != last; i++)
        {
            if(comp(array[i],array[i + 1]))
            {
                swap(array[i], array[i + 1]);
                swapped = true;
            }
            count++;
        }
        if(!swapped)
            break;

        last--;

        swapped = false;

        for(size_t i = last; i > first; i--)
        {
            if(comp(array[i - 1], array[i]))
            {
                swap(array[i - 1], array[i]);
                swapped = true;
            }
            count++;
        }
        if(!swapped)
            break;

        first++;
    }
}

template<typename T, typename Comp> void bubble_sort_improved(T* array, size_t size, Comp comp)
{
    count = 0;
    for(auto i = 0; i != size; ++i)
    {
        for(auto j = 0; j != size-1-i; ++j)
        {
            ++count;
            if(comp(array[j], array[j + 1]))
            {
                swap(array[j], array[j + 1]);
            }
        }
    }
}

template<typename T, typename Comp> void bubble_sort(T* array, size_t size, Comp comp)
{
    count = 0;
    for(auto i = 0; i != size; ++i)
    {
        for(auto j = 0; j != size-1; ++j)
        {
            ++count;
            if(comp(array[j], array[j + 1]))
            {
                swap(array[j], array[j + 1]);
            }
        }
    }
}

#endif // SORTINGS_H
