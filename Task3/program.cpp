#include <iostream>

#include "dynamicobjectlist.hpp"
#include "object.h"

int main()
{
  DynamicObjectList list;

  std::cout << "Created object back, with the name \"" << list.createObject_back("first")->GetName() << std::endl;
  std::cout << "Created object back, with the name \"" << list.createObject_back("second")->GetName() << std::endl;

  std::cout << "The list has now " << list.getCount() << " elements and a capacity of " << list.getCapacity() << std::endl;

  list.reserve(10);

  std::cout << "Created object back, with the name \"" << list.createObject_back("blub")->GetName() << "\"" << std::endl;
  std::cout << "Created object back, with the name \"" << list.createObject_back("inner cookie")->GetName() << "\"" << std::endl;
  std::cout << "Created object back, with the name \"" << list.createObject_back("back cookie")->GetName() << "\"" << std::endl;


  std::cout << "The list has now " << list.getCount() << " elements and a capacity of " << list.getCapacity() << std::endl;

  // Print out entire content.
  std::cout << std::endl << "Current content:" << std::endl;
  for (unsigned int i = 0; i < list.getCount(); ++i)
  {
    Object* object = list.getAt(i);
    if (object == nullptr)
    {
      std::cout << "Object number "<< i <<" does not exist! This is unexpected!" << std::endl;
    }
    else
    {
      std::cout << "Object number " << i << " has the name " << object->GetName() << std::endl;
    }
  }


  // Destroy first.
  list.destroyObject(0);
  // Destroy last
  list.destroyObject(list.getCount() - 1);
  // Destroy in between
  list.destroyObject(list.getCount() / 2);
  // Destroy invalid
  list.destroyObject(list.getCount());


  std::cout << "The list has now " << list.getCount() << " elements and a capacity of " << list.getCapacity() << std::endl;


  // Get first object and print out index.
  Object* object = list.getAt(0);
  if (object == nullptr)
  {
    std::cout << "Object number 0 does not exist! This is unexpected!" << std::endl;
  }
  else
  {
    std::cout << "Object number 0 has the name \"" << object->GetName() << "\""<< std::endl;
  }

  // Get invalid
  object = list.getAt((unsigned int)(-1));
  if (object == nullptr)
  {
    std::cout << "Object number " << (unsigned int)(-1) << " does not exist." << std::endl;
  }
  else
  {
    std::cout << "Object number 0 has the name \"" << object->GetName() << "\"" << std::endl;
  }

  // Print out entire content.
  std::cout << std::endl << "Current content:" << std::endl;
  for (unsigned int i = 0; i < list.getCount(); ++i)
  {
    Object* object = list.getAt(i);
    if (object == nullptr)
    {
      std::cout << "Object number " << i << " does not exist! This is unexpected!" << std::endl;
    }
    else
    {
      std::cout << "Object number " << i << " has the name " << object->GetName() << std::endl;
    }
  }

	return 0;
}