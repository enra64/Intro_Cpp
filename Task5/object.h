#pragma once

#include <iostream>
#include <cstring>
#include <string>

template<typename BERT>
class Object {
public:
    Object<BERT>(const char *name, const BERT data);

    Object<BERT>(const Object<BERT> &);

    ~Object();

    /// Returns ID which was passed in the constructor.
    inline const char *GetName() const {
        return m_name;
    };

    inline void setName(char *name) {
        m_name = name;
    }

    /// Returns whether object is const or not
    inline const char *GetType() const {
        return "Const object";
    };

    inline const char *GetType() {
        return "not const";
    };

    inline void setData(BERT &data) {
        mData = data;
    }

    inline const BERT &getData() const {
        return mData;
    }

    /// Implementiert den angegebenen und die verwandten Operatoren
    bool operator==(Object<BERT> &o) {
        if (std::string(m_name) != std::string(o.GetName()))
            return false;
        return mData == o.getData();
    }

    inline bool operator!=(Object &o) {
        return *this != o;
    }

    inline bool operator<(Object &o) {
        return mData < o.getData();
    }

    inline bool operator<=(Object &o) {
        return mData <= o.getData();
    }

    inline bool operator>(Object &o) {
        return mData > o.getData();
    }

    inline bool operator>=(Object &o) {
        return mData >= o.getData();
    }

    Object &operator+=(Object &o);

    Object &operator-=(Object &o);

    Object &operator*=(Object &o);

    Object &operator/=(Object &o);

    Object &operator%=(Object &o);

private:
    char *m_name;
    BERT mData;
};

template <typename BERT>
std::ostream &operator<<(std::ostream &lhs, const Object<BERT> &rhs);

template <typename BERT>
std::istream &operator>>(std::istream &lhs, Object<BERT> &rhs);

template <typename BERT>
bool operator<(Object<BERT> const &lhs, Object<BERT> const &rhs);

template <typename BERT>
bool operator>(Object<BERT> const &lhs, Object<BERT> const &rhs);