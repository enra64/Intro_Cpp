#pragma once
#include <iostream>

class Object
{
public:
	Object(const char* name);
	Object(const Object&);
  ~Object();

  /// Returns ID which was passed in the constructor.
  const char* GetName() const { return m_name; };
  /// Returns whether object is const or not
  const char* GetType() const { return "Const object"; };
  const char* GetType() { return "not const"; };
  /// Implementiert den angegebenen und die verwandten Operatoren
  bool operator==(Object& o)
  {
	  return false;
  }
  Object& operator+=(Object& o);

private:
  char* m_name;
};

std::ostream& operator<<(std::ostream& lhs, const Object& rhs);
std::istream& operator>>(std::istream& lhs, Object& rhs);

bool operator<(Object const& lhs, Object const& rhs);
bool operator>(Object const& lhs, Object const& rhs);