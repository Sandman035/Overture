#pragma once

#include <defines.h>
#include <core/log.h>

#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

void assertionFailure(const char* expression, const char* message, const char* file, i32 line);

#define ASSERT(expr)                                                \ 
    {                                                               \
        if (expr) {                                                 \
        } else {                                                    \
            assertionFailure(#expr, "", __FILE__, __LINE__);       \
            debugBreak();                                           \
        }                                                           \
    }

#define ASSERT_MSG(expr, message)                                   \ 
    {                                                               \
        if (expr) {                                                 \
        } else {                                                    \
            assertionFailure(#expr, message, __FILE__, __LINE__);  \
            debugBreak();                                           \
        }                                                           \
    }

#ifdef _DEBUG
#define ASSERT_DEBUG(expr)                                          \ 
    {                                                               \
        if (expr) {                                                 \
        } else {                                                    \
            assertionFailure(#expr, "", __FILE__, __LINE__);  \
            debugBreak();                                           \
        }                                                           \
    }                                            
#else
#define ASSERT_DEBUG(expr)
#endif