#include "ArgumentParser.hpp"
#include "CollatzSequences/CollatzSequenceMath.hpp"
#include "CollatzSequences/CollatzSequenceMemory.hpp"

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

    CollatzSequenceMemory collatzSequenceMemory;
    collatzSequenceMemory.countMaxSequenceFromRange(arguments->input_num);
    collatzSequenceMemory.printResult();

    return EXIT_SUCCESS;
}
