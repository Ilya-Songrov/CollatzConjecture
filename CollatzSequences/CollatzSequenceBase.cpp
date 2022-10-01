#include "CollatzSequenceBase.hpp"


CollatzSequenceBase::CollatzSequenceBase(const std::string &className)
    : _className(className)
{

}

void CollatzSequenceBase::printResult() const
{
    std::cout << "Run: " << _className << std::endl;
    printElapsedTime();
    printLongestCollatzSequence();
}

void CollatzSequenceBase::printElapsedTime() const
{
    std::cout << "Elapsed time = " << std::chrono::duration_cast<std::chrono::milliseconds>(_elapsed_time).count() << " milliseconds" << std::endl;
    std::cout << "Elapsed time = " << std::chrono::duration_cast<std::chrono::microseconds>(_elapsed_time).count() << " microseconds" << std::endl;
    std::cout << "Elapsed time = " << std::chrono::duration_cast<std::chrono::nanoseconds>(_elapsed_time).count() << " nanoseconds" << std::endl;
    std::cout << std::endl;
}

void CollatzSequenceBase::printLongestCollatzSequence() const
{
    std::cout << "Longest Collatz sequence: ";
    if (_num_max_sequence < 1) {
        std::cout << "null";
        return;
    }
    if (_num_max_sequence == 1) {
        std::cout << _num_max_sequence;
        return;
    }
    std::int64_t number = _num_max_sequence;
    std::cout << number;
    while (number > 1) {
        const auto tstbit0 = number & (1 << 0);
        if (tstbit0 == 1) {
            number = number * 3 + 1;
        }
        else{
            number /= 2;
        }
        std::cout << " " << number;
    }
    std::cout << std::endl << std::endl;
}
