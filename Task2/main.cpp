#include <iostream>
#include "ScopeTimer.h"

using namespace std;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
int main() {
    ScopeTimer p;
    {
        ScopeTimer* timer = new ScopeTimer();

        delete(timer);
    }
    cout << "Hello, World!" << endl;
    return 0;
}
#pragma clang diagnostic pop