#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Object.h"
#include <iostream>
Object::Object(const char* name)
{
	m_name = new char[strlen(name)];
	strcpy(m_name, name);
	std::cout << "Created object with name: " << m_name << std::endl;
}
Object::Object(const Object& o) :
m_name(o.m_name)
{
	std::cout << "Copied object with name: " << m_name << std::endl;
}

Object::~Object()
{
  std::cout << "Destroyed object with name: " << m_name << std::endl;
}

std::ostream& operator<< (std::ostream& stream, const Object& o)
{
	stream << "|-|" << o.GetName() << "|-|";
	return stream;
}