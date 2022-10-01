#pragma once

#include <iostream>
#include <string>
#include <chrono>

class CollatzSequenceMath
{
public:
    explicit CollatzSequenceMath();

    void countMaxSequenceFromRange(std::int64_t input);
    void printResult() const;

private:
    inline std::int64_t getMaxSequenceFromRange(std::int64_t inputRange);
    inline std::int64_t getSequenceLength(std::int64_t var);
    inline std::int64_t getSequenceLengthInputMore2(std::int64_t var);
    inline void printElapsedTime() const;
    inline void printLongestCollatzSequence() const;

private:
    std::int64_t _num_max_sequence = 0;
    std::chrono::steady_clock::duration _elapsed_time;
};
