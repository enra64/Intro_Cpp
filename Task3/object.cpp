#include "object.h"
#include <iostream>

Object::Object(char *name) :
        m_name(name) {
    std::cout << "CTOR:  Created object with name: " << m_name << '"' << std::endl;
}

Object::~Object() {
    std::cout << "DTOR:  Destroyed object with name: " << m_name << '"' << std::endl;
}
