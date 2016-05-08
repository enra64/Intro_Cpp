#pragma once

#include "object.h"

//class Object;

/// \brief A dynamic list of objects.
///
/// It is similar to the inner workings of Java's ArrayList.  
/// Intentionally, it is not possible to add existing objects.
/// This way DynamicObjectList is responsible for deleting and creating new objects.
class DynamicObjectList {
public:
    /// Constructs a new, empty dynamic object list.
    DynamicObjectList();

    /// Destroys the list and all objects it contains.
    ~DynamicObjectList();


    /// Returns the number of valid objects.
    inline unsigned int getCount() {
        return mObjectCount;
    }

    /// Returns the capacity of the internal array.
    inline unsigned int getCapacity() {
        return mCapacity;
    }


    /// Reallocates the internal array to at least a given capacity.
    /// \param capacity
    ///   After this call the capacity will be at least this value.
    ///   If the current capacity is equal or greater, nothing will happen.
    void reserve(unsigned int capacity);

    /// \brief Creates a new object at the end of the list.
    ///
    /// If the capacity is too small, the internal array will be reallocated with the double size.
    /// \param name
    ///   The name of the object.
    /// \return
    ///   The created object.
    Object *createObject_back(char *name);

    /// \brief Destroys an object at a given position.
    ///
    /// Will relocate all objects after this position (greater than position) to avoid a gap.
    /// It will not reallocate any memory - meaning: The capacity stays the same.
    ///
    /// \param position
    ///    Index of the object that should be deleted. If the list does not have this many objects, nothing will happen.
    void destroyObject(unsigned int position);

    /// \brief Returns the object at the given position index.
    /// \param position
    ///    Index of the queried object.
    /// \return
    ///    Object pointer at position or nullptr if there is no such object.
    Object *getAt(unsigned int position);


private:
    /// The current number of objects, contained in this list
    unsigned int mObjectCount;

    /// The current size of the internal object array.
    unsigned int mCapacity;

    /// The internal list of object pointers. A array of size mCapacity.
    Object **mList;
};
