#include "ArgumentParser.hpp"
#include "CollatzSequences/CollatzSequenceMath.hpp"

int main(int argc, char *argv[])
{
    const auto arguments = ArgumentParser::parseArguments(argc, argv);
    if (!arguments)
    {
        return EXIT_FAILURE;
    }

    CollatzSequenceMath collatzSequenceMath;
    collatzSequenceMath.countMaxSequenceFromRange(arguments->input_num);
    collatzSequenceMath.printResult();

    return EXIT_SUCCESS;
}
