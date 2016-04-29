#pragma once

class Object;

/// \brief A dynamic list of objects.
///
/// It is similar to the inner workings of Java's ArrayList.  
/// Intentionally, it is not possible to add existing objects.
/// This way DynamicObjectList is responsible for deleting and creating new objects.
class DynamicObjectList
{
public:
  /// Constructs a new, empty dynamic object list.
  DynamicObjectList();  // TODO: Implement in cpp.

  /// Destroys the list and all objects it contains.
  ~DynamicObjectList();  // TODO: Implement in cpp.


  /// Returns the number of valid objects.
  unsigned int getCount(); // TODO: Implement inline.

  /// Returns the capacity of the internal array.
  unsigned int getCapacity(); // TODO: Implement inline.


  /// Reallocates the internal array to at least a given capacity.
  /// \param capacity
  ///   After this call the capacity will be at least this value.
  ///   If the current capacity is equal or greater, nothing will happen.
  void reserve(unsigned int capacity); // TODO: Implement in cpp.

  /// \brief Creates a new object at the end of the list.
  ///
  /// If the capacity is too small, the internal array will be reallocated with the double size. 
  /// \param name
  ///   The name of the object.
  /// \return 
  ///   The created object.
  Object* createObject_back(char* name); // TODO: Implement in cpp.

  /// \brief Destroys an object at a given position.
  /// 
  /// Will relocate all objects after this position (greater than position) to avoid a gap.
  /// It will not reallocate any memory - meaning: The capacity stays the same.
  ///
  /// \param position
  ///    Index of the object that should be deleted. If the list does not have this many objects, nothing will happen.
  void destroyObject(unsigned int position); // TODO: Implement in cpp.

  /// \brief Returns the object at the given position index.
  /// \param position
  ///    Index of the queried object. 
  /// \return
  ///    Object pointer at position or nullptr if there is no such object.
  Object* getAt(unsigned int position); // TODO: Implement in cpp.
 

private:
  /// The current number of objects, contained in this list
  unsigned int m_count;

  /// The current size of the internal object array.
  unsigned int m_capacity;

  /// The internal list of object pointers. A array of size m_capacity.
  Object** m_list;
};
