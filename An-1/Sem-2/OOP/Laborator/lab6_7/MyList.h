
#pragma once
#include <stdexcept>

template<typename T>
class MyList {
private:
    T* elems;
    int cap;
    int len;

    void ensure_capacity() {
        if (len < cap) return;
        cap *= 2;
        T* newElems = new T[cap];
        for (int i = 0; i < len; ++i)
            newElems[i] = elems[i];
        delete[] elems;
        elems = newElems;
    }

public:
    MyList(int capacity = 10) : cap(capacity), len(0) {
        elems = new T[cap];
    }

    ~MyList() {
        delete[] elems;
    }

    MyList(const MyList& other) : cap(other.cap), len(other.len) {
        elems = new T[cap];
        for (int i = 0; i < len; ++i) {
            elems[i] = other.elems[i];  // Copy elements
        }
    }
    MyList& operator=(const MyList& other) {
        if (this != &other) {
            delete[] elems;
            cap = other.cap;
            len = other.len;
            elems = new T[cap];
            for (int i = 0; i < len; ++i) {
                elems[i] = other.elems[i];
            }
        }
        return *this;
    }

    void add(const T& elem) {
        ensure_capacity();
        elems[len++] = elem;
    }


    MyList(MyList&& other) noexcept
        : elems(other.elems), cap(other.cap), len(other.len) {
        other.elems = nullptr;
        other.cap = 0;
        other.len = 0;
    }

    MyList& operator=(MyList&& other) noexcept {
        if (this != &other) {
            delete[] elems;
            elems = other.elems;
            cap = other.cap;
            len = other.len;

            other.elems = nullptr;
            other.cap = 0;
            other.len = 0;
        }
        return *this;
    }



    void remove(int index) {
        if (index < 0 || index >= len)
            throw std::out_of_range("Index invalid");
        for (int i = index; i < len - 1; ++i)
            elems[i] = elems[i + 1];
        len--;
    }

    void update(int index, const T& elem) {
        if (index < 0 || index >= len)
            throw std::out_of_range("Index invalid");
        elems[index] = elem;
    }

    T& operator[](int index) {
        if (index < 0 || index >= len)
            throw std::out_of_range("Index invalid");
        return elems[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= len)
            throw std::out_of_range("Index invalid");
        return elems[index];
    }

    int size() const {
        return len;
    }

    void clear() {
        len = 0;
    }
    bool empty() const {
        return len == 0;
    }
    void setAll(const T& newValue) {
        std::fill(elems.begin(), elems.end(), newValue);
    }
    T* begin() {
        return elems;
    }

    T* end() {
        return elems + len;
    }
};
