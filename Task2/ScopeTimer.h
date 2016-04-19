//
// Created by arne on 4/19/16.
//

#ifndef TASK2_SCOPETIMER_H
#define TASK2_SCOPETIMER_H

#include <cstdio>
#include <sys/time.h>

class ScopeTimer {
public:
    ScopeTimer();
    ~ScopeTimer();
private:
    static timeval mStartTime;
};


#endif //TASK2_SCOPETIMER_H
