#pragma once

#include <iostream>
#include <string>
#include <regex>

#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/uuid/uuid.hpp>


struct Arguments
{
    std::int64_t    input_num = 0;
};

class ArgumentParser
{

public:
    static std::unique_ptr<Arguments> parseArguments(int argc, char **argv)
    {
#ifdef BUILD_DEBUG
    std::vector<const char*> new_argv(argv, argv + argc);
    new_argv.push_back("--input_num");
    new_argv.push_back("123123");
    new_argv.push_back(nullptr); // or NULL if you are using an old compiler
    argv = const_cast<char**>(new_argv.data()); // or &new_argv[0] if you are using an old compiler
    argc = argc + int(new_argv.size() - 2);
#endif
        printArgs(argc, argv);
        auto arguments = std::make_unique<Arguments>();

        namespace po = boost::program_options;
        po::options_description desc("Options description");
        desc.add_options()
                ("help,h", "Print usage information.")
                ("version,v", "Print version string")
                ("input_num",
                    po::value<std::int64_t>(&arguments->input_num)->required(),
                    "any number")
                ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("version"))
        {
            std::cout << APPLICATION_NAME << " version: v" APPLICATION_VERSION << std::endl;
            return nullptr;
        }
        else if (vm.count("help") || argc == 1)
        {
            std::cout << "The Collatz conjecture is one of the most famous unsolved problems in mathematics."
                         " To get Collatz sequence run this app with any number" << std::endl;
            std::cout << desc;
            return nullptr;
        }

        po::notify(vm);

        return arguments;
    }

private:
    static void printArgs(int argc, char** argv)
    {
        std::stringstream ss;
        ss << "Entered arguments: ";
        for (int i = 0; i < argc; ++i)
        {
            ss << argv[i] << ' ';
        }
        std::cout << ss.str() << std::endl << std::endl;
    }
};
