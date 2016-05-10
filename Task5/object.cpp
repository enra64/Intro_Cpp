#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "object.h"

#include <iostream>
#include <cstring>

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

std::istream& operator>>(std::istream& lhs, Object& rhs){

}

bool operator<(Object const& lhs, Object const& rhs){

}

bool operator>(Object const& lhs, Object const& rhs){

}