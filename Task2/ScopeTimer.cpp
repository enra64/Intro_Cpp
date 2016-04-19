//
// Created by arne on 4/19/16.
//

#include "ScopeTimer.h"

ScopeTimer::ScopeTimer() {
    gettimeofday(&mStartTime, nullptr);

}

ScopeTimer::~ScopeTimer() {
    timeval endTime;
    gettimeofday(&endTime, nullptr);
    long seconds = endTime.tv_sec - mStartTime.tv_sec;
    long uSeconds = endTime.tv_usec - mStartTime.tv_usec;
    double timeDifference = ((seconds) * 1000 + uSeconds/1000.0);
    printf("%f seconds elapsed", timeDifference);
}

timeval ScopeTimer::mStartTime;
