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
}


TestObject::~TestObject()
{
    delete[] m_ArrayOfStrings;
}

void TestObject::generateStrings()
{
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

std::string TestObject::readAccess(int index){
    return std::string(m_ArrayOfStrings[index]);
}

void TestObject::printAllStrings()
{
    for (int i = 0; i < m_NumberOfStrings; i++)
    {
        std::cout << m_ArrayOfStrings[i];
    }
    std::cout << std::endl;
}


// return the number of elements
int& TestObject::elementCount()
{
    return m_NumberOfStrings;
}

void TestObject::reverseArray()
{
    for(int i = 0; i < m_NumberOfStrings; i++)
        swapStrings(m_ArrayOfStrings[i], m_ArrayOfStrings[m_NumberOfStrings - 1]);
}