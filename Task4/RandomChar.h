#ifndef  RANDOMCHAR_H
#define RANDOMCHAR_H

#include <stdlib.h>

/// Just for picking a random char from an array of chars.
// also contains errors to fix, see program.cpp for instructions
// SUPER OPTIONAL BONUS: write a better random char generator. ;)
class RandomChar
{
public:
    RandomChar();
    ~RandomChar();

    static const char getRandomChar()
    {
        return m_AllPossibleChars[rand() % m_Length];
    }

private:
    static int const m_Length;
    static char const m_AllPossibleChars[];
};

#endif // ! RANDOMCHAR_H
