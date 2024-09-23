#pragma once
#include <iostream>
//it simulates std::share_pointer in STL
template <typename T>
class SmartPointer {
private:
    T* ptr;               // Actual pointer
    unsigned* ref_count;  // Reference count

public:
    // Constructor
    SmartPointer(T* p = nullptr) : ptr(p) {
        ref_count = new unsigned;
        if (ptr) {
            *ref_count = 1; // Initialize reference count to 1
        } else {
            *ref_count = 0;
        }
    }

    // Copy constructor (increments reference count)
    SmartPointer(const SmartPointer<T>& sp) {
        ptr = sp.ptr;
        ref_count = sp.ref_count;
        if (ptr) {
            (*ref_count)++;
        }
    }

    // Assignment operator (increments reference count for new assignment and decrements for old one)
    SmartPointer<T>& operator=(const SmartPointer<T>& sp) {
        if (this != &sp) {
            // Decrement the old object's reference count
            if (ptr && --(*ref_count) == 0) {
                delete ptr;
                delete ref_count;
            }

            // Copy new pointer and reference count
            ptr = sp.ptr;
            ref_count = sp.ref_count;
            if (ptr) {
                (*ref_count)++;
            }
        }
        return *this;
    }

    // Destructor (decrements reference count, and deletes memory if count becomes zero)
    ~SmartPointer() {
        if (ptr && --(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
    }

    // Overload dereference operator
    T& operator*() const {
        return *ptr;
    }

    // Overload arrow operator
    T* operator->() const {
        return ptr;
    }

    // Get the reference count
    unsigned getRefCount() const {
        return *ref_count;
    }

    // Check if the pointer is valid
    bool isNull() const {
        return ptr == nullptr;
    }
};
