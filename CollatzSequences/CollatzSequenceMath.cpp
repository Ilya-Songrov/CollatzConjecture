#include "CollatzSequenceMath.hpp"

#include <cassert>
#include <chrono>

CollatzSequenceMath::CollatzSequenceMath() : CollatzSequenceBase(__FUNCTION__)
{
    assert(getSequenceLength(-1) == 0);
    assert(getSequenceLength(0) == 0);
    assert(getSequenceLength(1) == 1);
    assert(getSequenceLength(2) == 2);
    assert(getSequenceLength(3) == 8);
    assert(getSequenceLength(4) == 3);
    assert(getMaxSequenceFromRange(-1) == 0);
    assert(getMaxSequenceFromRange(0) == 0);
    assert(getMaxSequenceFromRange(1) == 0);
    assert(getMaxSequenceFromRange(2) == 1);
    assert(getMaxSequenceFromRange(3) == 2);
    assert(getMaxSequenceFromRange(4) == 3);
    assert(getMaxSequenceFromRange(8) == 7);
}

void CollatzSequenceMath::countMaxSequenceFromRange(int64_t input)
{
    const auto start = std::chrono::steady_clock::now();
    _num_max_sequence = getMaxSequenceFromRange(input);
    const auto end = std::chrono::steady_clock::now();
    _elapsed_time = end - start;
}

int64_t CollatzSequenceMath::getMaxSequenceFromRange(int64_t inputRange)
{
    if (inputRange < 2) {
        return 0;
    }
    std::int64_t _top_number    = inputRange - 1;
    std::int64_t _max_number    = _top_number;
    std::int64_t _max_path      = (_top_number & (1 << 0)) ? 0 : getSequenceLength(_top_number);
    _top_number                 = _max_path == 0 ? _top_number : _top_number - 1;

    for (std::int64_t var = _top_number; var > 2;  var -= 2) {
        std::int64_t count = getSequenceLengthInputMore2(var);
        if (count > _max_path) {
            _max_path = count;
            _max_number = var;
        }
    }
    return _max_number;
}

int64_t CollatzSequenceMath::getSequenceLength(int64_t var)
{
    if (var < 1) {
        return 0;
    }
    if (var == 1 || var == 2) {
        return var;
    }
    return getSequenceLengthInputMore2(var);
}

int64_t CollatzSequenceMath::getSequenceLengthInputMore2(int64_t var)
{
    std::int64_t number = var;
    std::int64_t count = 2;
    while (true){
        const auto tstbit0 = number & (1 << 0);
        const auto tstbit1 = number & (1 << 1);
        const bool divisibleByFour = tstbit0 == 0 && tstbit1 == 0;
        if (divisibleByFour) {
            number >>= 2;               // even_even
        }
        else {
            number += (number / 2) + 1; // even_odd or odd_even
        }

        if (number < 3) {
            break;
        }
        count += 2;
    }
    if (number == 2){
        count += 2;
    }
    else if (number == 1){
        ++count;
    }
    return count;
}
