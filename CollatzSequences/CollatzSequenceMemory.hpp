#pragma once

#include <iostream>
#include <string>

#include "CollatzSequenceBase.hpp"

class CollatzSequenceMemory : public CollatzSequenceBase
{
public:
    explicit CollatzSequenceMemory();

    void countMaxSequenceFromRange(std::int64_t input) override;

private:
    inline std::int64_t getMaxSequenceFromRange(std::int64_t inputRange);
};
