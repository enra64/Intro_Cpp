#include <cstdlib>
#include <iostream>
#include "dynamicobjectlist.hpp"


DynamicObjectList::DynamicObjectList() {
    mCapacity = 16;
    mObjectCount = 0;
    mList = new Object *[mCapacity];
}

DynamicObjectList::~DynamicObjectList() {
    delete[] mList;
    //for (size_t i = 0; i < mObjectCount; i++)
    //    delete mList[i];
}

void DynamicObjectList::reserve(unsigned int capacity) {
    // no
    if (capacity <= mCapacity)
        return;

    // allocate new memory on the heap
    Object **newList = new Object *[capacity];

    // copy pointers
    for (size_t i = 0; i < mObjectCount; i++)
        newList[i] = mList[i];

    // free old memory
    delete[] mList;

    // set pointer to pointer array to new pointer
    mList = newList;
}

Object *DynamicObjectList::createObject_back(char *name) {
    // force enough space being available
    if (mObjectCount == mCapacity) {
        reserve(mCapacity * 2);
        std::cout << "Increasing list size" << std::endl;
    }

    // create new object on heap
    Object *newObject = new Object(name);

    // save pointer in list
    mList[mObjectCount++] = newObject;

    // return pointer to new object
    return newObject;
}

void DynamicObjectList::destroyObject(unsigned int position) {
    // position valid?
    if (position < 0 || position >= mObjectCount) {
        std::cerr << "invalid position for delete at " << position << std::endl;
        return;
    }

    // delete object
    delete mList[position];

    mObjectCount--;

    // close gap
    for (size_t i = position; i < mObjectCount; i++)
        mList[i] = mList[i + 1];
}

Object *DynamicObjectList::getAt(unsigned int position) {
    // position valid?
    if (position < 0 || position >= mObjectCount) {
        std::cerr << "invalid position for access at " << position << std::endl;
        return nullptr;
    }

    // return pointer
    return mList[position];
}











