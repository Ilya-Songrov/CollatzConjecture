#include <iostream>
#include <ctime>
#include <string>

#include <gmpxx.h>

int checkValidity(const int argc, char *argv[], mpz_class* input);
void sequence(const mpz_class size, mpz_class* max_number);
mpz_class sequence(const mpz_class var);
void printElapsedTime(const clock_t begin, const clock_t end);
void printResult(const mpz_class max_number);

int main(int argc, char *argv[])
{
    mpz_class input    = 0;
    if (checkValidity(argc, argv, &input)) {
        return EXIT_FAILURE;
    }
    mpz_class max_number    = 0;

    const clock_t begin = clock();
    sequence(input, &max_number);
    const clock_t end = clock();

    printResult(max_number);
    printElapsedTime(begin, end);
    return EXIT_SUCCESS;
}

int checkValidity(const int argc, char *argv[], mpz_class *input)
{
    if(argc < 2 || argc > 2) {
        std::cout << "Not a valid input" << std::endl << std::endl;
        return EXIT_FAILURE;
    }
    const std::string inputStr = argv[1];
    std::cout << "input: " << inputStr << std::endl << std::endl;
    *input = atoi(argv[1]);
    if (*input < 2) {
        std::cout << "Not a valid input" << std::endl << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void sequence(const mpz_class size, mpz_class *max_number)
{
    mpz_class top_number     = size - 1;
    mpz_class _max_number    = top_number;
    mpz_class _max_path      = mpz_tstbit(top_number.get_mpz_t(), 0) ? 0 : sequence(top_number);
    top_number              = _max_path == 0 ? top_number : top_number - 1;

    for (mpz_class var = top_number;  var > 2;  var -= 2) {
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
                number += (number / 2) + 1; // even_even or odd_even
            }

            if (number < 3) {
                break;
            }
            count += 2;
        }

        if (number == 2){
            ++count;
        }
        if (count > _max_path) {
            _max_path = count;
            _max_number = var;
        }
    }
    *max_number     = _max_number;
}

mpz_class sequence(const mpz_class var)
{
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
