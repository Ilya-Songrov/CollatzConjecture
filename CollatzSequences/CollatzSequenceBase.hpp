#pragma once

#include <iostream>
#include <string>
#include <chrono>

class CollatzSequenceBase
{
public:
    explicit CollatzSequenceBase(const std::string& className);

    virtual void countMaxSequenceFromRange(std::int64_t input) = 0;

    void printResult() const;

protected:
    std::int64_t _num_max_sequence = 0;
    std::chrono::steady_clock::duration _elapsed_time;

private:
    inline void printElapsedTime() const;
    inline void printLongestCollatzSequence() const;

private:
    const std::string _className;
};
