#include "dynamicobjectlist.hpp"
#include "object.h"
#include <algorithm>

template<typename T>
DynamicObjectList<T>::DynamicObjectList() :
        m_count(0),
        m_capacity(0),
        m_list(nullptr) {
}

template <typename T>
DynamicObjectList<T>::~DynamicObjectList() {
    delete[] m_list;
}

template<typename T>
void DynamicObjectList<T>::reserve(unsigned int capacity) {
    // Check if anything should happen.
    if (m_capacity >= capacity)
        return;

    // Create new object array with the given capacity.
    Object<T> **newArray = new Object<T> *[capacity];

    // Moves old list contents to new list.
    for (unsigned int i = 0; i < m_count; ++i) {
        newArray[i] = m_list[i];
    }

    // Optional: Set all other pointer to nullptr, just for easier debugging.
    for (unsigned int i = m_count; i < capacity; ++i) {
        newArray[i] = nullptr;
    }

    // delete old array!
    delete[] m_list;

    // Save new data.
    m_list = newArray;
    m_capacity = capacity;
}

template <typename T>
Object<T> *DynamicObjectList<T>::createObject_back(char *name) {
    // Ensure capacity.
    reserve((m_count + 1) * 2);

    // Add new object.
    m_list[m_count] = new Object<T>(name, m_count);

    return m_list[m_count++];
}

template <typename T>
void DynamicObjectList<T>::sort() {
    for (unsigned int j = 1; j < m_count - 2; j++)    // Start with 1 (not 0)
    {
        unsigned int i = 0;
        Object<T> *tmp = m_list[j];
        for (i = j - 1; (i > 0) && (*m_list[i] < *tmp); i--)   // Smaller values move up
        {
            m_list[i + 1] = m_list[i];
        }
        m_list[i + 1] = tmp;    //Put key into its proper location
    }
}

template <typename T>
Object<T> *DynamicObjectList<T>::push_back(Object<T> *a) {
    if (a == nullptr)
        return a;
    // Ensure capacity.
    reserve((m_count + 1) * 2);

    // Add new object.
    m_list[m_count] = a;

    return m_list[m_count++];
}

template <typename T>
Object<T> *DynamicObjectList<T>::createObject_front(char *name) {
    // Ensure capacity.
    reserve((m_count + 1) * 2);

    // Move all other objects.
    for (unsigned int i = m_count; i >= 1; --i) {
        m_list[i] = m_list[i - 1];
    }

    // Add new object.
    m_list[0] = new Object<T>(name, m_count);
    ++m_count;

    return m_list[0];
}

template <typename T>
void DynamicObjectList<T>::destroyObject(unsigned int position) {
    // Does the element exist?
    if (m_count <= position) {
        return;
    }

    // Destroy the object at the given position.
    delete m_list[position];

    // Now we have less objects!
    --m_count;

    // Move all other objects.
    for (unsigned int i = position; i < m_count; ++i) {
        m_list[i] = m_list[i + 1];
    }
    shrink();
    // Optional: Set former back to nullptr for easier debugging.
    m_list[m_count] = nullptr;
}

template <typename T>
Object<T> *DynamicObjectList<T>::getAt(const unsigned int position) const {
    // Does the element exist?
    if (m_count <= position) {
        return nullptr;
    }

    return m_list[position];
}

template <typename T>
DynamicObjectList<T> &DynamicObjectList<T>::operator+=(const Object<T> &a) {
    static Object<T> *ap = new Object<T>(a);
    push_back(ap);
    return *this;
}

template <typename T>
DynamicObjectList<T> &DynamicObjectList<T>::operator+=(Object<T> &a) {
    push_back(&a);
    return *this;
}

template <typename T>
DynamicObjectList<T> &DynamicObjectList<T>::operator|=(const DynamicObjectList<T> &o) {
    DynamicObjectList<T> a(*this);
    DynamicObjectList<T> b(o);

    a.sort();
    b.sort();

    const unsigned int bothCap = a.getCapacity() + b.getCapacity();
    this->reserve(bothCap);

    unsigned int aPos = 0, bPos = 0;
    for (int i = 0; i < bothCap; i++) {
        if (a[i] < b[i])
            m_list[i] = &a[aPos++];
        else
            m_list[i] = &b[bPos++];
    }
    return *this;
}

// due to really good implementation, this lies within O(n^2)
template <typename T>
DynamicObjectList<T> &DynamicObjectList<T>::operator&=(const DynamicObjectList<T> &o) {
    // ~ O(3n)
    DynamicObjectList<T> a(*this);
    DynamicObjectList<T> b(*this);
    DynamicObjectList<T> c(o);

    // O((3*sort)n + n)
    a |= c;

    // O(n^2?)
    for (unsigned int i = 0; i < a.getCount(); i++) {
        bool exists = false;

        for (unsigned int j = 0; j < b.getCount(); j++) {
            if (a[i] == b[j]) {
                exists = true;
                break;
            }
        }

        for (unsigned int k = 0; k < c.getCount(); k++) {
            if (a[i] == c[k] || exists) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            a.destroyObject(i);
        }
    }

    return *this;
}

template <typename T>
Object<T> &DynamicObjectList<T>::operator[](const unsigned int i) const {
    Object<T> &bert = *getAt(i);
    return bert;
}

template <typename T>
Object<T> &DynamicObjectList<T>::operator[](const unsigned int i) {
    Object<T> &abc = *getAt(i);
    return abc;
}

///Shrink allocated memory to max 5*m_count, do not shrink under 2*m_count, only half or double m_capacity
///e.g. [1,2,3,4] with m_capacity=16 has to be shrunk to [1,2,3] with m_capacity=8 if the last element is removed
/// shrink is called when an object is deleted from the list
template <typename T>
void DynamicObjectList<T>::shrink() {

}


template class DynamicObjectList<int>;


