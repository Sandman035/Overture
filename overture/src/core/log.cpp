#include <core/log.h>
#include <core/asserts.h>
#include <platform/platform.h>

#include <iostream>
#include <cstring>
#include <string>
#include <stdarg.h>

#include <time.h>

API void logOutput(log_level level, const char * message, ...) {
    std::string level_strings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]:  ", "[INFO]:  ", "[DEBUG]: ", "[TRACE]: "};

    char out_message[32000];
    memset(out_message, 0, sizeof(out_message));

    __builtin_va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_message, 32000, message, arg_ptr);
    va_end(arg_ptr);

	char buff[23];
    struct tm *sTm;

    time_t now = time(0);
    sTm = localtime(&now);

    strftime(buff, sizeof(buff), "[%Y-%m-%d %H:%M:%S] ", sTm);

    std::string output = buff + level_strings[level] + out_message;
    ConsolePrint(output, level);
    
}

void assertionFailure(const char* expression, const char* message, const char* file, i32 line) {
    logOutput(LOG_LEVEL_FATAL, "Assertion Failure: %s, message: '%s', in file: %s, line: %d\n", expression, message, file, line);
}
