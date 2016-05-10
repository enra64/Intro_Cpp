#include <iostream>
#include <string>
#include <cstdlib>
#include "RandomChar.h"

/// contains an array of strings of random chars
class TestObject
{
public:
    TestObject();
    TestObject(int numberOfStrings);
    ~TestObject();

    void swapStrings(std::string& first, std::string& second);

    void printAllStrings() const;

    /// return the number of strings / elements
    const int& elementCount() const;

    void reverseArray();

    const std::string readAccess(int index) const;

private:
    void generateStrings();
    std::string* m_ArrayOfStrings;
    int m_NumberOfStrings;
};
