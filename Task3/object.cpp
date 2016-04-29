#include "Object.h"
#include <iostream>

Object::Object(char* name) :
  m_name(name)
{
  std::cout << "Created object with name: " << m_name << std::endl;
}

Object::~Object()
{
  std::cout << "Destroyed object with name: " << m_name << std::endl;
}
