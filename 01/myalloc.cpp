#include "myalloc.h"

void Allocator::makeAllocator(size_t maxSize) {
    if (maked) {
        return;
    }
    ptr = new char[maxSize];
    offset = 0;
    sizeOfAllocator = maxSize;
    maked = true;
}

char* Allocator::alloc(size_t size) {
    if (size > sizeOfAllocator - offset || !maked) {
        return nullptr;
    }
    offset += size;
    return ptr + offset - size;
}

void Allocator::reset() {
    offset = 0;
}

Allocator::~Allocator() {
    if (maked) {
        delete[] ptr;
    }
}
