#include "RandomChar.h"

int const RandomChar::m_Length = 70;
char const RandomChar::m_AllPossibleChars[m_Length] = { "01234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!$%&?@" };

RandomChar::RandomChar()
{
}

RandomChar::~RandomChar()
{
}