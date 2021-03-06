#pragma once

#include <cassert>
#include <string>
#include <stdexcept>

#define NEVER_INLINE  __attribute__((noinline))
#define ALWAYS_INLINE __attribute__((always_inline))
#define UNUSED __attribute__((unused))

#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

#define compiler_barrier() asm volatile("" ::: "memory")

#ifdef NDEBUG
  #define ALWAYS_ASSERT(expr) (likely((expr)) ? (void)0 : abort())
#else
  #define ALWAYS_ASSERT(expr) assert((expr))
#endif

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7)
#define GCC_AT_LEAST_47 1
#else
#define GCC_AT_LEAST_47 0
#endif

// g++-4.6 does not support override
#if GCC_AT_LEAST_47
#define OVERRIDE override
#else
#define OVERRIDE
#endif

#define _STRINGIFY(x) #x
#define _LINEHACK(x) _STRINGIFY(x)

#define _SOURCE_INFO \
  (::std::string(__PRETTY_FUNCTION__) + \
   ::std::string(" (" __FILE__ ":" _LINEHACK(__LINE__) ")"))

#define NOT_REACHABLE \
  do { \
    throw ::std::runtime_error( \
      ::std::string("Should not be reached: ") + \
      _SOURCE_INFO); \
  } while (0)

#define UNIMPLEMENTED \
  do { \
    throw ::std::runtime_error( \
      ::std::string("Not implemented: ") + \
      _SOURCE_INFO); \
  } while (0)

#define CACHELINE_SIZE 64
#define __XCONCAT2(a, b) a ## b
#define __XCONCAT(a, b) __XCONCAT2(a, b)
#define CACHE_PADOUT  \
    char __XCONCAT(__padout, __COUNTER__)[0] __attribute__((aligned(CACHELINE_SIZE)))
