#ifndef CORE_BASE_H
#define CORE_BASE_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h> /* strrchr */


#define UNUSED(x_) (void)(x_)

#define BIT(x_) (1U << (x_))

#define SWAP(T_, x_, y_) {T_ t_ = (x_), (x_) = (y_), (y_) = (t_)}

#define FILENAME (strrchr("/" __FILE__, '/'))

#define _STR(x_) #x_
#define STR(x_) _STR(x_)

#define _CAT(x_, y_) x_##y_
#define CAT(x_, y_) _CAT(x_, y_)


/* Platform and compiler detection */

#define PLATFORM_UNIX    0
#define PLATFORM_POSIX   0
#define PLATFORM_WINDOWS 0
#define PLATFORM_WIN64   0
#define PLATFORM_WIN32   0
#define PLATFORM_APPLE   0
#define PLATFORM_OSX     0
#define PLATFORM_IOS     0
#define PLATFORM_ANDROID 0
#define PLATFORM_LINUX   0
#define PLATFORM_UNKNOWN 0

#if __unix__ || defined(__APPLE__)
    #undef PLATFORM_UNIX
    #define PLATFORM_UNIX 1
    #include <unistd.h>
    #if defined(_POSIX_VERSION)
        #undef PLATFORM_POSIX
        #define PLATFORM_POSIX 1
    #endif
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #undef PLATFORM_WINDOWS
    #define PLATFORM_WINDOWS 1
    #ifdef _WIN64
        #undef PLATFORM_WIN64
        #define PLATFORM_WIN64 1
    #else
        #undef PLATFORM_WIN32
        #define PLATFORM_WIN32 1
    #endif
#elif __APPLE__
    #undef PLATFORM_APPLE
    #define PLATFORM_APPLE 1
    #include <TargetConditionals.h>
    #if TARGET_OS_MAC
        #undef PLATFORM_OSX
        #define PLATFORM_OSX 1
    #elif TARGET_OS_IOS
        #undef PLATFORM_IOS
        #define PLATFORM_IOS 1
    #endif
#elif __ANDROID__
    #undef PLATFORM_ANDROID
    #define PLATFORM_ANDROID 1
#elif __linux__
    #undef PLATFORM_LINUX
    #define PLATFORM_LINUX 1
#else
    #warning "Unknown OS"
    #undef PLATFORM_UNKNOWN
    #define PLATFORM_UNKNOWN 1
#endif

#define COMPILER_CLANG   0
#define COMPILER_GCC     0
#define COMPILER_MSVC    0
#define COMPILER_MINGW   0
#define COMPILER_MINGW64 0
#define COMPILER_MINGW32 0
#define COMPILER_UNKNOWN 0

#if defined(__clang__)
    #undef COMPILER_CLANG
    #define COMPILER_CLANG 1
#elif defined(__GNUC__)
    #undef COMPILER_GCC
    #define COMPILER_GCC 1
#elif defined(_MSC_VER)
    #undef COMPILER_MSVC
    #define COMPILER_MSVC 1
#elif defined(__MINGW32__)
    #define COMPILER_MINGW 1
    #if defined(__MINGW64__)
        #undef COMPILER_MINGW64
        #define COMPILER_MINGW64 1
    #else
        #undef COMPILER_MINGW32
        #define COMPILER_MINGW32 1
    #endif
#else
    #warning "Unknown compiler"
    #undef COMPILER_UNKNOWN
    #define COMPILER_UNKNOWN 1
#endif

#endif /* _CE_CORE_BASE_H_ */
