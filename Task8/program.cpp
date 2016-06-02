#include <random>

#include "target.hpp"
#include "unittests.hpp"

int main()
{
    srand(time(NULL));
    testAll();
}
