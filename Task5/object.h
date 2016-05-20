#pragma once
#include <iostream>


class Object {
public:
    Object(const char* name);
    Object(const Object&);
    ~Object();

    /// Returns ID which was passed in the constructor.
    const char* getName() const {
        return m_name;
    }

    /// Returns whether object is const or not
    const char* getType() const {
        return "Const object";
    }

    const char* getType() {
        return "not const";
    }

    const inline std::string getData() const {
        if(m_name == nullptr)
            return std::string("");
        return std::string(m_name);
    }

    inline bool operator==(Object& o) const {
        return getData() == o.getData();
    }

    inline bool operator!=(Object &o)  const {
        return getData() != o.getData();
    }

    inline bool operator<(Object &o)  const {
        return getData() < o.getData();
    }

    inline bool operator<=(Object &o)  const {
        return getData() <= o.getData();
    }

    inline bool operator>(Object &o)  const {
        return getData() > o.getData();
    }

    inline bool operator>=(Object &o)  const {
        return getData() >= o.getData();
    }

    Object &operator+=(Object &o);
//    none of these make sense
//    Object &operator-=(Object &o);
//    Object &operator*=(Object &o);
//    Object &operator/=(Object &o);
//    Object &operator%=(Object &o);

    friend std::ostream& operator>> (std::ostream& stream, const Object&);

private:
    char* m_name;
};

std::ostream& operator<< (std::ostream& stream, const Object&);

