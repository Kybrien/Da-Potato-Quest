//#include <stdexcept>
//#include <algorithm>
//#include "DataStructures/Container.h"
//
//template <typename T>
//Container<T>::Container() : data(nullptr), size(0), capacity(0) {}
//
//template <typename T>
//Container<T>::Container(size_t initialSize) : data(nullptr), size(0), capacity(0) {
//    reserve(initialSize);
//}
//
//template <typename T>
//Container<T>::~Container() {
//    delete[] data;
//}
//
//template <typename T>
//void Container<T>::push_back(const T& value) {
//    if (size >= capacity) {
//        reserve(std::max(static_cast<size_t>(1), capacity * 2));
//    }
//    data[size++] = value;
//}
//
//template <typename T>
//void Container<T>::pop_back() {
//    if (size > 0) {
//        size--;
//    }
//}
//
//template <typename T>
//const T& Container<T>::operator[](size_t index) const {
//    if (index >= size) {
//        throw std::out_of_range("Index out of range");
//    }
//    return data[index];
//}
//
//template <typename T>
//T& Container<T>::operator[](size_t index) {
//    if (index >= size) {
//        throw std::out_of_range("Index out of range");
//    }
//    return data[index];
//}
//
//template <typename T>
//size_t Container<T>::getSize() const {
//    return size;
//}
//
//template <typename T>
//void Container<T>::reserve(size_t newCapacity) {
//    if (newCapacity > capacity) {
//        T* newData = new T[newCapacity];
//        for (size_t i = 0; i < size; i++) {
//            newData[i] = data[i];
//        }
//        capacity = newCapacity;
//        delete[] data;
//        data = newData;
//    }
//}
//
//template <typename T>
//void Container<T>::clear() {
//    size = 0;
//}
//
//template <typename T>
//T* Container<T>::getData() {
//    return data;
//}