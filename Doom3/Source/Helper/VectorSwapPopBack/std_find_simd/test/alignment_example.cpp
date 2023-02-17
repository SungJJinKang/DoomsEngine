#include <cassert>

#include "../fast_find_simd.h"

#ifndef ALIGNMENT_ALLOCATOR_H
#define ALIGNMENT_ALLOCATOR_H

#include <stdlib.h>
#include <malloc.h>
#include <vector>

template <typename T, std::size_t N = 16>
class AlignmentAllocator {
public:
    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    typedef T* pointer;
    typedef const T* const_pointer;

    typedef T& reference;
    typedef const T& const_reference;

public:
    inline AlignmentAllocator() throw () { }

    template <typename T2>
    inline AlignmentAllocator(const AlignmentAllocator<T2, N>&) throw () { }

    inline ~AlignmentAllocator() throw () { }

    inline pointer adress(reference r) {
        return &r;
    }

    inline const_pointer adress(const_reference r) const {
        return &r;
    }

    inline pointer allocate(size_type n) {
        return (pointer)_aligned_malloc(n * sizeof(value_type), N);
    }

    inline void deallocate(pointer p, size_type) {
        _aligned_free(p);
    }

    inline void construct(pointer p, const value_type& wert) {
        new (p) value_type(wert);
    }

    inline void destroy(pointer p) {
        p->~value_type();
    }

    inline size_type max_size() const throw () {
        return size_type(-1) / sizeof(value_type);
    }

    template <typename T2>
    struct rebind {
        typedef AlignmentAllocator<T2, N> other;
    };

    bool operator!=(const AlignmentAllocator<T, N>& other) const {
        return !(*this == other);
    }

    // Returns true if and only if storage allocated from *this
    // can be deallocated from other, and vice versa.
    // Always returns true for stateless allocators.
    bool operator==(const AlignmentAllocator<T, N>& other) const {
        return true;
    }
};

#endif

int main()
{
    {
        std::vector<long long, AlignmentAllocator<long long, 4>> a;
        a.reserve(10000001);
        for (unsigned long long i = 0; i <= 10000000; i++)
        {
            a.push_back(i);
        }

        for (long long i = 500000; i < 500050; i++)
        {
            auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (long long)i);
            assert(iter == a.begin() + i);
        }
    }
    

    {
        std::vector<char, AlignmentAllocator<char, 2>> a;
        a.reserve(120);
        for (unsigned long long i = 0; i <= 120; i++)
        {
            a.push_back(i);
        }

        for (char i = 0; i < 120; i++)
        {
            auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (char)i);
            assert(iter == a.begin() + i);
        }
    }

    {
        std::vector<int, AlignmentAllocator<int, 2>> a;
        a.reserve(120);
        for (unsigned long long i = 0; i <= 120; i++)
        {
            a.push_back(i);
        }

        for (int i = 80; i < 120; i++)
        {
            auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (int)i);
            assert(iter == a.begin() + i);
        }
    }
    
}