#include "CollatzSequenceMemory.hpp"

#include <cassert>
#include <chrono>
#include <map>

CollatzSequenceMemory::CollatzSequenceMemory() : CollatzSequenceBase(__FUNCTION__)
{
    assert(getMaxSequenceFromRange(-1) == 0);
    assert(getMaxSequenceFromRange(0) == 0);
    assert(getMaxSequenceFromRange(1) == 0);
    assert(getMaxSequenceFromRange(2) == 1);
    assert(getMaxSequenceFromRange(3) == 2);
    assert(getMaxSequenceFromRange(4) == 3);
    assert(getMaxSequenceFromRange(8) == 7);
}

void CollatzSequenceMemory::countMaxSequenceFromRange(int64_t input)
{
    const auto start = std::chrono::steady_clock::now();
    _num_max_sequence = getMaxSequenceFromRange(input);
    const auto end = std::chrono::steady_clock::now();
    _elapsed_time = end - start;
}

int64_t CollatzSequenceMemory::getMaxSequenceFromRange(int64_t inputRange)
{
    if (inputRange < 2) {
        return 0;
    }
    std::int64_t _top_number       = inputRange - 1;
    std::int64_t _max_number       = _top_number;
    std::int64_t _max_path         = 0;
    std::map<std::int64_t, std::int64_t> mapOdd;
    std::map<std::int64_t, std::int64_t> mapOddTemp;
    std::map<std::int64_t, std::int64_t> mapEven;
    std::map<std::int64_t, std::int64_t> mapEvenTemp;
    for (std::int64_t var = _top_number; var > 0; --var) {
        std::int64_t node_number = var;
        std::int64_t count = 1;

        while (node_number > 1) {
            const auto tstbit0 = node_number & (1 << 0);
            if (tstbit0 == 1) {
                const auto it = mapOdd.find(node_number);
                if (it == mapOdd.end()) {
                    if (node_number < inputRange) { // custom optimization
                        mapOddTemp.insert({node_number, count});
                    }
                    node_number = node_number * 3 + 1;
                }
                else{
                    count += it->second - 1;
                    break;
                }
            }
            else{
                const auto it = mapEven.find(node_number);
                if (it == mapEven.end()) {
                    if (node_number < inputRange) { // custom optimization
                        mapEvenTemp.insert({node_number, count});
                    }
                    node_number /= 2;
                }
                else{
                    count += it->second - 1;
                    break;
                }
            }
            ++count;
        }
        if (count > _max_path) {
            _max_path   = count;
            _max_number = var;
        }
        if (!mapOddTemp.empty()) {
            for (const auto &value : mapOddTemp) {
                mapOdd.insert({value.first, std::int64_t(count - value.second + 1)});
            }
            mapOddTemp.clear();
        }
        if (!mapEvenTemp.empty()) {
            for (const auto &value : mapEvenTemp) {
                mapEven.insert({value.first, std::int64_t(count - value.second + 1)});
            }
            mapEvenTemp.clear();
        }
    }
    return _max_number;
}

