#include "dynamicobjectlist.hpp"
#include "object.h"
#include <algorithm>
DynamicObjectList::DynamicObjectList() :
m_count(0),
m_capacity(0),
m_list(nullptr)
{
}

DynamicObjectList::~DynamicObjectList()
{
  delete[] m_list;
}

void DynamicObjectList::reserve(unsigned int capacity)
{
  // Check if anything should happen.
  if(m_capacity >= capacity)
    return;

  // Create new object array with the given capacity.
  Object** newArray = new Object*[capacity];

  // Moves old list contents to new list.
  for(unsigned int i = 0; i < m_count; ++i)
  {
    newArray[i] = m_list[i];
  }

  // Optional: Set all other pointer to nullptr, just for easier debugging.
  for(unsigned int i = m_count; i < capacity; ++i)
  {
    newArray[i] = nullptr;
  }

  // delete old array!
  delete[] m_list;

  // Save new data.
  m_list = newArray;
  m_capacity = capacity;
}
Object* DynamicObjectList::createObject_back(char* name)
{
	// Ensure capacity.
	reserve((m_count + 1) * 2);

	// Add new object.
	m_list[m_count] = new Object(name);

	return m_list[m_count++];
}

void DynamicObjectList::sort()
{
	for (unsigned int j = 1; j < m_count-2; j++)    // Start with 1 (not 0)
	{
		unsigned int i = 0;
		Object *tmp = m_list[j];
		for (i = j - 1; (i >= 0) && (*m_list[i] < *tmp); i--)   // Smaller values move up
		{
			m_list[i + 1] = m_list[i];
		}
		m_list[i + 1] = tmp;    //Put key into its proper location
	}
}

Object* DynamicObjectList::push_back(Object *a)
{
	if (a == nullptr)
		return a;
	// Ensure capacity.
	reserve((m_count + 1) * 2);

	// Add new object.
	m_list[m_count] = a;

	return m_list[m_count++];
}

Object* DynamicObjectList::createObject_front(char* name)
{
  // Ensure capacity.
  reserve((m_count + 1) * 2);

  // Move all other objects.
  for (unsigned int i = m_count; i >= 1; --i)
  {
    m_list[i] = m_list[i - 1];
  }

  // Add new object.
  m_list[0] = new Object(name);
  ++m_count;

  return m_list[0];
}

void DynamicObjectList::destroyObject(unsigned int position)
{
  // Does the element exist?
  if(m_count <= position)
  {
    return;
  }

  // Destroy the object at the given position.
  delete m_list[position];

  // Now we have less objects!
  --m_count;

  // Move all other objects.
  for (unsigned int i = position; i < m_count; ++i)
  {
    m_list[i] = m_list[i + 1];
  }
  shrink();
  // Optional: Set former back to nullptr for easier debugging.
  m_list[m_count] = nullptr;
}

Object* DynamicObjectList::getAt(const unsigned int position) const
{
    // Does the element exist?
    if (m_count <= position)
    {
        return nullptr;
    }

    return m_list[position];
}

DynamicObjectList &DynamicObjectList::operator+=(const Object &a) {
    static Object* ap = new Object(a);
    push_back(ap);
    return *this;
}

DynamicObjectList &DynamicObjectList::operator+=(Object &a) {
    push_back(&a);
    return *this;
}

DynamicObjectList &DynamicObjectList::operator |= (const DynamicObjectList &o) {
    DynamicObjectList a(*this);
    DynamicObjectList b(o);

    a.sort();
    b.sort();

    const unsigned int bothCap = a.getCapacity() + b.getCapacity();
    this->reserve(bothCap);

    unsigned int aPos = 0, bPos = 0;
    for(int i = 0; i < bothCap; i++){
        if(a[i] < b[i])
            m_list[i] = &a[aPos++];
        else
            m_list[i] = &b[bPos++];
    }
    return *this;
}

// due to really good implementation, this lies within O(n^2)
DynamicObjectList &DynamicObjectList::operator &= (const DynamicObjectList &o) {
    // ~ O(3n)
    DynamicObjectList a(*this);
    DynamicObjectList b(*this);
    DynamicObjectList c(o);

    // O((3*sort)n + n)
    a |= c;

    // O(n^2?)
    for(unsigned int i = 0; i < a.getCount(); i++){
        bool exists = false;

        for(unsigned int j = 0; j < b.getCount(); j++){
            if(a[i] == b[j]){
                exists = true;
                break;
            }
        }

        for(unsigned int k = 0; k < c.getCount(); k++){
            if(a[i] == c[k] || exists){
                exists = true;
                break;
            }
        }

        if(!exists){
            a.destroyObject(i);
        }
    }

    return *this;
}

Object &DynamicObjectList::operator[](const unsigned int i) const {
    Object& bert = *getAt(i);
    return bert;
}

Object &DynamicObjectList::operator[](const unsigned int i) {
    Object& abc = *getAt(i);
    return abc;
}



