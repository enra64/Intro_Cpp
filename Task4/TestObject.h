// This also has a few bugs and things missing.
// TODO: Identify and fix errors / bugs / mistakes

// TODO: Identify functions and return values that should be const
// also see instructions in programm.cpp, if you haven't already

//#include "TestObject.h"
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

    void printAllStrings();

    /// return the number of strings / elements
    int& elementCount();

    void reverseArray();

    std::string readAccess(int index);

private:
    void generateStrings();
    std::string* m_ArrayOfStrings;
    int m_NumberOfStrings;
};
