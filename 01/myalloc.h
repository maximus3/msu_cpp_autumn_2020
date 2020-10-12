#pragma once

#include <iostream>

class Allocator {
private:
    bool maked = false;
    char *ptr;
    ptrdiff_t offset;
    size_t sizeOfAllocator;
public:
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    
    ~Allocator();
};
