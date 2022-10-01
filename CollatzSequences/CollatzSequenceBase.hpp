#pragma once

#include <iostream>
#include <string>
#include <chrono>

class CollatzSequenceBase
{
public:
    explicit CollatzSequenceBase() {}

    virtual void countMaxSequenceFromRange(std::int64_t input) = 0;

protected:
    std::int64_t _input = 0;
    std::int64_t _result = 0;
    std::chrono::steady_clock::duration _elapsed_time;
};
