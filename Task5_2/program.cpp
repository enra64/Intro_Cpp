/**
* Unterschied a()&&b()/a()&b(); erläutern, welche Probleme können auftreten?*
* Wozu dient folgendes in Object.cpp?
* #ifdef _MSC_VER
* #define _CRT_SECURE_NO_WARNINGS
* #endif
*
* error C4996: 'strncpy': This function or variable may be unsafe. Consider using strncpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
*
* Parameter Validation. Parameters passed to CRT functions are validated, in both secure functions and in many preexisting versions of functions. These validations include:
Checking for NULL values passed to the functions.
Checking enumerated values for validity.
Checking that integral values are in valid ranges.
For more information, see Parameter Validation.
A handler for invalid parameters is also accessible to the developer. When an encountering an invalid parameter, instead of asserting and exiting the application, the CRT provides a way to check these problems with the _set_invalid_parameter_handler function.
Sized Buffers. The secure functions require that the buffer size be passed to any function that writes to a buffer. The secure versions validate that the buffer is large enough before writing to it, helping to avoid dangerous buffer overrun errors that could allow malicious code to execute. These functions usually return an errno type of error code and invoke the invalid parameter handler if the size of the buffer is too small. Functions that read from input buffers, such as gets, have secure versions that require you to specify a maximum size.
Null termination. Some functions that left potentially non-terminated strings have secure versions which ensure that strings are properly null terminated.
Enhanced error reporting. The secure functions return error codes with more error information than was available with the preexisting functions. The secure functions and many of the preexisting functions now set errno and often return an errno code type as well, to provide better error reporting.
Filesystem security. Secure file I/O APIs support secure file access in the default case.
Windows security. Secure process APIs enforce security policies and allow ACLs to be specified.
Format string syntax checking. Invalid strings are detected, for example, using incorrect type field characters in printf format strings.
*
* Korrigiert den Runtimefehler in dynamicObjectList.sort()
*
*
*
**/


#include <iostream>
#include <stdlib.h>
#include "dynamicobjectlist.hpp"
#include "object.h"
#include <string.h>

int main()
{
	std::cout << "PART 1"<<std::endl;
	DynamicObjectList list1;
	DynamicObjectList list2;

  list1 += *(new Object("a"));
  list1 += *(new Object("b"));
  std::cout << "The list1 has now " << list1.getCount() << " elements and a capacity of " << list1.getCapacity() << std::endl;
  list1.reserve(10);

  list2 += *(new Object("v"));
  list2 += *(new Object("w"));
  list2 += *(new Object("x"));
  list2 += *(new Object("y"));
  list2 += *(new Object("z"));

  std::cout << "list2 has now " << list2.getCount() << " elements and a capacity of " << list2.getCapacity() << std::endl;

  // Print out entire content.
  std::cout << std::endl << "Current content of list 1:" << std::endl;
  for (unsigned int i = 0; i < list1.getCount(); ++i)
  {
    Object* object = list1.getAt(i);
    if (object == nullptr)
    {
      std::cout << "Object number "<< i <<" does not exist! This is unexpected!" << std::endl;
    }
    else
    {
      std::cout << "Object number " << i << " has the name " << *object << std::endl;
    }
  }


  std::cout << "merging lists\n";
  const DynamicObjectList list3(list2);
  list1 |= list3;

  std::cout << "List list1 has " << list1.getCount() << (list1.getCount() != 7 ? "members. SHOULD BE 7" : "members. CORRECT") << std::endl;
  std::cout << "Object at 3 is" << list1[3] << (strcmp(list1[3].getName(),"w")  ? ". SHOULD BE w" : ". CORRECT") << std::endl;

  std::cout << std::endl << "Current content of list 1:" << std::endl;
  for (unsigned int i = 0; i < list1.getCount(); ++i)
  {
	  Object* object = list1.getAt(i);
	  if (object == nullptr)
	  {
		  std::cout << "Object number " << i << " does not exist! This is unexpected!" << std::endl;
	  }
	  else
	  {
		  std::cout << "Object number " << i << " has the name " << *object << std::endl;
	  }
  }

  // Destroy first.
  list1.destroyObject(0);
  // Destroy last
  list1.destroyObject(list1.getCount() - 1);
  // Destroy in between
  list1.destroyObject(list1.getCount() / 2);
  // Destroy invalid
  list1.destroyObject(list1.getCount());


  std::cout << "The list has now " << list1.getCount() << " elements and a capacity of " << list1.getCapacity() << std::endl;

  std::cout << "PART 2, intersecting lists" << std::endl;

  DynamicObjectList l1, l2;
  for (int i = 0; i < 10; i++)
  {
	  l1 += *new Object(std::to_string(i).c_str());
	  l2 += *new Object(std::to_string(2*i).c_str());
  }
  for (int i = 30; i < 50; i++)
  {
	  l1 += *new Object(std::to_string(i).c_str());
  }
  std::cout << "li&=l2"<<std::endl;
  l1 &= l2;
  std::cout << "List l1 has size " << l1.getCapacity() << (l1.getCapacity() > 30 ? ". SHOULD BE <=30" : ". CORRECT") << std::endl;
  std::cout << "List l1 has " << l1.getCount() << (l1.getCount() > 5 ? "members. SHOULD BE 5" : "members. CORRECT") << std::endl;
  std::cout << std::endl << "Current content of list 1:" << std::endl;
  for (unsigned int i = 0; i < l1.getCount(); ++i)
  {
	  Object* object = l1.getAt(i);
	  if (object == nullptr)
	  {
		  std::cout << "Object number " << i << " does not exist! This is unexpected!" << std::endl;
	  }
	  else
	  {
		  std::cout << "Object number " << i << " has the name " << *object << std::endl;
	  }
  }
  std::cout << "The list has now " << l1.getCount() << " elements and a capacity of " << l1.getCapacity() << std::endl;


  DynamicObjectList li1;
  for (int i = 30; i < 40; i++)
  {
	  li1 += *new Object(std::to_string(i).c_str());
  }
  for (int i = 0; i < 10; i++)
  {
	  li1 += *new Object(std::to_string(i).c_str());
  }
  std::cout << "li1.sort()" << std::endl;
  li1.sort();
  std::cout << "List li1 has size " << li1.getCapacity() << (li1.getCapacity() > 100 ? ". SHOULD BE <=100" : ". CORRECT") << std::endl;
  std::cout << "List li1 has " << li1.getCount() << (li1.getCount() !=20 ? "members. SHOULD BE 20" : "members. CORRECT") << std::endl;
  std::cout << std::endl << "Current content of list 1:" << std::endl;
  for (unsigned int i = 0; i < li1.getCount(); ++i)
  {
	  Object* object = li1.getAt(i);
	  if (object == nullptr)
	  {
		  std::cout << "Object number " << i << " does not exist! This is unexpected!" << std::endl;
	  }
	  else
	  {
		  std::cout << "Object number " << i << " has the name " << *object << std::endl;
	  }
  }

  std::cout << "testing const" << std::endl;
  const DynamicObjectList constList(li1);
  std::cout << "element [2] is :" << li1[2]<<std::endl;
  std::cout << "size of list :" << li1.getCapacity() << std::endl;
  std::cout << "#objects :" << li1.getCount() << std::endl;
	return 0;
}
