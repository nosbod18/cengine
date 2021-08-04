#ifndef _CE_CENGINE_BASE_H_
#define _CE_CENGINE_BASE_H_

#include <stdint.h>
#include <stddef.h>
#include <string.h>

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;


#define CE__STR(x_) #x_
#define CE_STR(x_) CE__STR(x_)

#define CE__CAT(x_, y_) x_##y_
#define CE_CAT(x_, y_) CE__CAT(x_, y_)

/* Gets just the file name and extension instead of full path */
#define FILENAME (strrchr("/" __FILE__, '/') + 1)


#define CE_DEBUG_PARAMS_DEF , const char* file, int line, const char* func
#define CE_DEBUG_PARAMS_IMP , FILENAME, __LINE__, __func__


/* Platform and compiler detection */

#define CE_PLATFORM_UNIX    0
#define CE_PLATFORM_POSIX   0
#define CE_PLATFORM_WINDOWS 0
#define CE_PLATFORM_WIN64   0
#define CE_PLATFORM_WIN32   0
#define CE_PLATFORM_APPLE   0
#define CE_PLATFORM_OSX     0
#define CE_PLATFORM_IOS     0
#define CE_PLATFORM_ANDROID 0
#define CE_PLATFORM_LINUX   0
#define CE_PLATFORM_UNKNOWN 0

#if __unix__ || defined(__APPLE__)
    #undef CE_PLATFORM_UNIX
    #define CE_PLATFORM_UNIX 1
    #include <unistd.h>
    #if defined(_POSIX_VERSION)
        #undef CE_PLATFORM_POSIX
        #define CE_PLATFORM_POSIX 1
    #endif
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #undef CE_PLATFORM_WINDOWS
    #define CE_PLATFORM_WINDOWS 1
    #ifdef _WIN64
        #undef CE_PLATFORM_WIN64
        #define CE_PLATFORM_WIN64 1
    #else
        #undef CE_PLATFORM_WIN32
        #define CE_PLATFORM_WIN32 1
    #endif
#elif __APPLE__
    #undef CE_PLATFORM_APPLE
    #define CE_PLATFORM_APPLE 1
    #include <TargetConditionals.h>
    #if TARGET_OS_MAC
        #undef CE_PLATFORM_OSX
        #define CE_PLATFORM_OSX 1
    #elif TARGET_OS_IOS
        #undef CE_PLATFORM_IOS
        #define CE_PLATFORM_IOS 1
    #endif
#elif __ANDROID__
    #undef CE_PLATFORM_ANDROID
    #define CE_PLATFORM_ANDROID 1
#elif __linux__
    #undef CE_PLATFORM_LINUX
    #define CE_PLATFORM_LINUX 1
#else
    #warning "Unknown OS"
    #undef CE_PLATFORM_UNKNOWN
    #define CE_PLATFORM_UNKNOWN 1
#endif

#define CE_COMPILER_CLANG   0
#define CE_COMPILER_GCC     0
#define CE_COMPILER_MSVC    0
#define CE_COMPILER_MINGW   0
#define CE_COMPILER_MINGW64 0
#define CE_COMPILER_MINGW32 0
#define CE_COMPILER_UNKNOWN 0

#if defined(__clang__)
    #undef CE_COMPILER_CLANG
    #define CE_COMPILER_CLANG 1
#elif defined(__GNUC__)
    #undef CE_COMPILER_GCC
    #define CE_COMPILER_GCC 1
#elif defined(_MSC_VER)
    #undef CE_COMPILER_MSVC
    #define CE_COMPILER_MSVC 1
#elif defined(__MINGW32__)
    #define CE_COMPILER_MINGW 1
    #if defined(__MINGW64__)
        #undef CE_COMPILER_MINGW64
        #define CE_COMPILER_MINGW64 1
    #else
        #undef CE_COMPILER_MINGW32
        #define CE_COMPILER_MINGW32 1
    #endif
#else
    #warning "Unknown compiler"
    #undef CE_COMPILER_UNKNOWN
    #define CE_COMPILER_UNKNOWN 1
#endif

#endif /* _CE_CENGINE_BASE_H_ */
