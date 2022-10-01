#pragma once

#include <iostream>
#include <string>

#include "CollatzSequenceBase.hpp"

class CollatzSequenceMath : public CollatzSequenceBase
{
public:
    explicit CollatzSequenceMath();

    void countMaxSequenceFromRange(std::int64_t input) override;

private:
    inline std::int64_t getMaxSequenceFromRange(std::int64_t inputRange);
    inline std::int64_t getSequenceLength(std::int64_t var);
    inline std::int64_t getSequenceLengthInputMore2(std::int64_t var);
};
