#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include "object.h"
#include <string>



template <typename BERT>
Object<BERT>::Object(const Object<BERT> &o) :
        m_name(o.m_name) {
    std::cout << "Copied object with name: " << m_name << std::endl;
}

template <typename BERT>
Object<BERT>::~Object() {
    std::cout << "Destroyed object with name: " << m_name << std::endl;
}
template <typename BERT>
Object<BERT> &Object<BERT>::operator+=(Object<BERT> &o) {
    mData += o.getData();
    return *this;
}
template <typename BERT>
Object<BERT> &Object<BERT>::operator-=(Object<BERT> &o) {
    mData -= o.getData();
    return *this;
}
template <typename BERT>
Object<BERT> &Object<BERT>::operator*=(Object<BERT> &o) {
    mData *= o.getData();
    return *this;
}
template <typename BERT>
Object<BERT> &Object<BERT>::operator/=(Object<BERT> &o) {
    mData /= o.getData();
    return *this;
}
template <typename BERT>
Object<BERT> &Object<BERT>::operator%=(Object<BERT> &o) {
    mData %= o.getData();
    return *this;
}

template <typename BERT>
Object<BERT>::Object(const char *name, const BERT data) {
    m_name = new char[strlen(name)];
    mData = data;
    strcpy(m_name, name);
    std::cout << "Created object with name: " << m_name << std::endl;
}

template <typename BERT>
std::ostream &operator<<(std::ostream &stream, const Object<BERT> &o) {
    stream << "|-|" << o.GetName() << ":" << o.getData() << "|-|";
    return stream;
}
template <typename BERT>
std::istream &operator>>(std::istream &lhs, Object<BERT> &rhs) {
    std::string input;
    lhs >> input;
    const char* name = input.substr(0, input.find(":")).c_str();
    char nonConstName[input.find(":") + 1];
    memcpy(nonConstName, name, input.find(":"));
    rhs.setName(nonConstName);
    BERT data = input.substr(input.find(":"), std::string::npos);
    rhs.setData(data);
    delete name;
    return lhs;
}
template <typename BERT>
bool operator<(Object<BERT> const &lhs, Object<BERT> const &rhs) {
    return lhs.GetName() < rhs.GetName();
}
template <typename BERT>
bool operator>(Object<BERT> const &lhs, Object<BERT> const &rhs) {
    return lhs.GetName() > rhs.GetName();
}

template class Object<int>;
// when you implement templated whatever in the source instead of the header file, you have to force instantiation using
// this sh*t which kinda makes me question splitting my programs to header and source
template std::ostream &operator<<(std::ostream &stream, const Object<int> &o);
