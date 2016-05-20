#include "dynamicobjectlist.hpp"
#include "object.h"
#include <algorithm>

DynamicObjectList::DynamicObjectList() :
    m_count(0),
    m_capacity(0),
    m_list(nullptr) {
}

/// copy assignment -> the object was previously initialized
DynamicObjectList &DynamicObjectList::operator= (const DynamicObjectList& o) {
    delete[] m_list;
    m_count = 0;
    m_capacity = 0;
    reserve(o.m_capacity);

    for(unsigned int i = 0; i < o.m_count; i++)
        push_back(new Object(*o.getAt(i)));
    return *this;
}

/// (move assignment) look at me
DynamicObjectList &DynamicObjectList::operator= (DynamicObjectList && o) {
    m_count = 0;
    m_capacity = 0;
    reserve(o.m_capacity);
    // this is my pointer now
    for(unsigned int i = 0; i < o.m_count; i++)
        push_back(o.getAt(i));
    return *this;
}

/// copy constructor -> initialize the object
DynamicObjectList::DynamicObjectList(const DynamicObjectList& o) {
    m_count = 0;
    m_capacity = 0;
    reserve(o.m_capacity);

    for(unsigned int i = 0; i < o.m_count; i++)
        push_back(new Object(*o.getAt(i)));
}

DynamicObjectList::~DynamicObjectList() {
    delete[] m_list;
}

void DynamicObjectList::reserve(unsigned int capacity) {
    // Check if anything should happen.
    if(m_capacity >= capacity)
        return;

    // Create new object array with the given capacity.
    Object** newArray = new Object*[capacity];

    // Moves old list contents to new list.
    for(unsigned int i = 0; i < m_count; ++i) {
        newArray[i] = m_list[i];
    }

    // Optional: Set all other pointer to nullptr, just for easier debugging.
    for(unsigned int i = m_count; i < capacity; ++i) {
        newArray[i] = nullptr;
    }

    // delete old array!
    if(m_list != nullptr)
    delete[] m_list;

    // Save new data.
    m_list = newArray;
    m_capacity = capacity;
}

///Shrink allocated memory to max 5*m_count, do not shrink under 2*m_count, only half or double m_capacity
///e.g. [1,2,3,4] with m_capacity=16 has to be shrunk to [1,2,3] with m_capacity=8 if the last element is removed

/// shrink is called when an object is deleted from the list
void DynamicObjectList::shrink() {
    if(m_capacity > 5*m_count && (m_capacity / 2 >= 2*m_count)){
        unsigned int capacity = m_capacity / 2;

        // Create new object array with the given capacity.
        Object** newArray = new Object*[capacity];

        // Moves old list contents to new list.
        for(unsigned int i = 0; i < m_count; ++i) {
            newArray[i] = m_list[i];
        }

        // Optional: Set all other pointer to nullptr, just for easier debugging.
        for(unsigned int i = m_count; i < capacity; ++i) {
            newArray[i] = nullptr;
        }

        // delete old array!
        if(m_list != nullptr)
        delete[] m_list;

        // Save new data.
        m_list = newArray;
        m_capacity = capacity;
    }
}

Object* DynamicObjectList::createObject_back(char* name) {
    // Ensure capacity.
    reserve((m_count + 1) * 2);

    // Add new object.
    m_list[m_count] = new Object(name);

    return m_list[m_count++];
}

void DynamicObjectList::sort() {
    if(m_count == 0)
        return;
    for (unsigned int j = 1; j < m_count-2; j++) {  // Start with 1 (not 0)
        unsigned int i = 0;
        Object *tmp = m_list[j];
        for (i = j - 1; (i > 0 && i < m_count) && (*m_list[i] < *tmp); i--) { // Smaller values move up
            m_list[i + 1] = m_list[i];
        }
        m_list[i + 1] = tmp;    //Put key into its proper location
    }
}

Object* DynamicObjectList::push_back(Object *a) {
    if (a == nullptr)
        return a;
    // Ensure capacity.
    reserve((m_count + 1) * 2);

    // Add new object.
    m_list[m_count] = a;

    return m_list[m_count++];
}

Object* DynamicObjectList::createObject_front(char* name) {
    // Ensure capacity.
    reserve((m_count + 1) * 2);

    // Move all other objects.
    for (unsigned int i = m_count; i >= 1; --i) {
        m_list[i] = m_list[i - 1];
    }

    // Add new object.
    m_list[0] = new Object(name);
    ++m_count;

    return m_list[0];
}

void DynamicObjectList::destroyObject(unsigned int position) {
    // Does the element exist?
    if(m_count <= position) {
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

Object* DynamicObjectList::getAt(unsigned int position) {
    // Does the element exist?
    if (m_count <= position) {
        return nullptr;
    }

    return m_list[position];
}

Object* DynamicObjectList::getAt(const unsigned int position) const {
    // Does the element exist?
    if (m_count <= position) {
        return nullptr;
    }

    return m_list[position];
}

Object &DynamicObjectList::operator[](const unsigned int i) const {
    static Object bert = *getAt(i);
    return bert;
}

Object &DynamicObjectList::operator[](const unsigned int i) {
    return *getAt(i);
}

DynamicObjectList &DynamicObjectList::operator+=(const Object &a) {
    static Object *ap = new Object(a);
    push_back(ap);
    return *this;
}


DynamicObjectList &DynamicObjectList::operator+=(Object &a) {
    push_back(&a);
    return *this;
}

DynamicObjectList &DynamicObjectList::operator|=(const DynamicObjectList &o) {
    reserve(getCount() + o.getCount());

    for(unsigned int i = 0; i < o.getCount(); i++)
        push_back(o.getAt(i));

    return *this;
}

DynamicObjectList &DynamicObjectList::operator&=(const DynamicObjectList &o) {
    for(int i = m_count - 1; i >= 0; i--){
        bool existsInO = false;
        const Object& oo = *getAt(i);
        for(unsigned int j = 0; j < o.getCount(); j++){
            if(oo == *o.getAt(j)){
                existsInO = true;
                break;
            }
        }
        if(!existsInO)
            destroyObject(i);
    }
    return *this;
}

DynamicObjectList &DynamicObjectList::operator/=(const DynamicObjectList &o) {
    sort();

    for (unsigned int i = 0; i < getCount(); i++) {
        for(unsigned int j = 0; j < o.getCount(); i++){
            if(*getAt(i) == *o.getAt(j)){
                destroyObject(i);
                break;
            }
        }
    }

    return *this;
}
