#include "TestObject.h"

TestObject::TestObject()
{
    m_NumberOfStrings = 10;
    generateStrings();
}


TestObject::TestObject(const int numberOfStrings)
{
    m_NumberOfStrings = numberOfStrings;
    generateStrings();
    generateStrings();
}


TestObject::~TestObject()
{
    delete[] m_ArrayOfStrings;
}

void TestObject::generateStrings()
{
    if(m_ArrayOfStrings != nullptr)
        delete[] m_ArrayOfStrings;
    m_ArrayOfStrings = new std::string[m_NumberOfStrings];

    for (int i = 0; i < m_NumberOfStrings; i++)
    {
        std::string& currentString = m_ArrayOfStrings[i];

        currentString.resize((unsigned long) (rand() % 30 + 1));
        for (auto& c : currentString)
        {
            c = RandomChar::getRandomChar();
        }
     }
}

void TestObject::swapStrings(std::string& first, std::string& second)
{
    std::string berthold(first);
    first = second;
    second = berthold;
}

const std::string TestObject::readAccess(const int index) const{
    return std::string(m_ArrayOfStrings[index]);
}

void TestObject::printAllStrings() const
{
    for (int i = 0; i < m_NumberOfStrings; i++)
    {
        std::cout << m_ArrayOfStrings[i];
    }
    std::cout << std::endl;
}

// return the number of elements
const int& TestObject::elementCount() const
{
    return m_NumberOfStrings;
}

void TestObject::reverseArray()
{
    for(int i = 0; i < m_NumberOfStrings / 2; i++)
        swapStrings(m_ArrayOfStrings[i], m_ArrayOfStrings[m_NumberOfStrings - 1 - i]);
}