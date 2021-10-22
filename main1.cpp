#include <iostream>
#include <ctime>
#include <string>
#include <regex>
#include <cassert>


#include <gmpxx.h>

void runAsserts();
int checkValidity(const int argc, char *argv[], mpz_class* input);
mpz_class maxSequenceFromRange(const mpz_class size);
mpz_class getSequenceLength(const mpz_class& var);
void printElapsedTime(const clock_t begin, const clock_t end);
void printResult(const mpz_class max_number);

int main(int argc, char *argv[])
{
    runAsserts();

    mpz_class input = 0;
    if (checkValidity(argc, argv, &input)) {
        return EXIT_FAILURE;
    }

    const clock_t begin = clock();
    const mpz_class max_number = maxSequenceFromRange(input);
    const clock_t end = clock();

    printResult(max_number);
    printElapsedTime(begin, end);
    return EXIT_SUCCESS;
}

void runAsserts()
{
    assert(getSequenceLength(-1) == 0);
    assert(getSequenceLength(0) == 0);
    assert(getSequenceLength(1) == 1);
    assert(getSequenceLength(2) == 2);
    assert(getSequenceLength(3) == 8);
    assert(getSequenceLength(4) == 3);
    assert(maxSequenceFromRange(-1) == 0);
    assert(maxSequenceFromRange(0) == 0);
    assert(maxSequenceFromRange(1) == 0);
    assert(maxSequenceFromRange(2) == 1);
    assert(maxSequenceFromRange(3) == 2);
    assert(maxSequenceFromRange(4) == 3);
    assert(maxSequenceFromRange(8) == 7);
}

int checkValidity(const int argc, char *argv[], mpz_class *input)
{
    if(argc < 2 || argc > 2) {
        std::cout << "Not a valid input" << std::endl << std::endl;
        return EXIT_FAILURE;
    }
    const std::string inputStr(argv[1]);
    std::cout << "input: " << inputStr << std::endl << std::endl;
    const std::regex only_num_regex("^[0-9]*$" );
    if (std::regex_match(inputStr, only_num_regex)) {
        *input = mpz_class(inputStr);
        if (*input > 1) {
            return EXIT_SUCCESS;
        }
    }
    std::cout << "Not a valid input" << std::endl << std::endl;
    return EXIT_FAILURE;
}

mpz_class maxSequenceFromRange(const mpz_class size)
{
    if (size < 2) {
        return mpz_class(0);
    }
    mpz_class _top_number       = size - 1;
    mpz_class _max_number       = _top_number;
    mpz_class _max_path         = mpz_tstbit(_top_number.get_mpz_t(), 0) ? 0 : getSequenceLength(_top_number);
    _top_number                 = _max_path == 0 ? _top_number : _top_number - 1;

    for (mpz_class var = _top_number; var > 2;  var -= 2) {
        mpz_class number = var;
        mpz_class count = 2;
        while (true){
            const auto tstbit0 = mpz_tstbit(number.get_mpz_t(), 0);
            const auto tstbit1 = mpz_tstbit(number.get_mpz_t(), 1);
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
        if (count > _max_path) {
            _max_path = count;
            _max_number = var;
        }
    }
    return _max_number;
}

mpz_class getSequenceLength(const mpz_class &var)
{
    if (var < 1) {
        return 0;
    }
    if (var == 1 || var == 2) {
        return var;
    }

    mpz_class number = var;
    mpz_class count = 2;
    while (true){
        const auto tstbit0 = mpz_tstbit(number.get_mpz_t(), 0);
        const auto tstbit1 = mpz_tstbit(number.get_mpz_t(), 1);
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

void printElapsedTime(const clock_t begin, const clock_t end)
{
    const double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Elapsed time = " << elapsed_secs << "secs" << std::endl << std::endl;
}

void printResult(const mpz_class max_number)
{
    mpz_class number = max_number;
    std::cout << "Longest Collatz sequence: " << number;
    while (number > 1) {
        const auto tstbit0 = mpz_tstbit(number.get_mpz_t(), 0);
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
