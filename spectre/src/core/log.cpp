#include <core/log.h>

#include <iostream>
#include <string>

API void log_output(log_level level, const char * message) {
    std::string level_strings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]:  ", "[INFO]:  ", "[DEBUG]: ", "[TRACE]: "};

    std::string output = level_strings[level] + message;
    std::cout << output << "\n";
}