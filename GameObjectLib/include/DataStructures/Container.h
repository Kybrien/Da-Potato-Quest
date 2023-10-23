#pragma once

template <typename T>
class Container {
public:
    Container();
    Container(size_t initialSize);
    ~Container();
    void push_back(const T& value);
    void pop_back();
    const T& operator[](size_t index) const;
    T& operator[](size_t index);
    size_t getSize() const;
    size_t getCapacity() const;
    void reserve(size_t newCapacity);
    void clear();
    T* getData();

private:
    T* data;
    size_t size;
    size_t capacity;
};

#include "DataStructures/Container.inl"