#ifndef ENGINEDEFINES_H
#define ENGINEDEFINES_H


#ifdef SNP_PLATFORM_WINDOWS
#ifndef NOMINMAX
#define NOMINMAX // For windows.h
#endif // SNP_PLATFORM_WINDOWS
#endif

/// Static Lib / DLL Defines
#ifdef SNP_PLATFORM_WINDOWS
#define SNP_API
// For later stuff if i decide to make it a dll
#endif // SNP_PLATFORM_WINDOWS


/// Debug Break calls
#ifdef SNP_PLATFORM_WINDOWS
#define SNP_API
// For later stuff if i decide to make it a dll
#endif // SNP_PLATFORM_WINDOWS



/// Break and Assert
#ifdef SNP_PLATFORM_WINDOWS
// for windows
#define SNP_BREAK() __debugbreak()
#else
// for linux
#define SNP_BREAK() raise(SIGTRAP)
#endif


#define SNP_ASSERT(condition, ...)	\
	if(!condition)					\
	{								\
		SNP_BREAK();				\
	}	



#define SNP_API
// For later stuff if i decide to make it a dll


/// Deprecated MACRO
#define SNP_DEPRECATED													\
 {																		\
	LOG_ERROR("Deprecared : {0} : {1}", __FILE__, __LINE__);			\
 }
																		

#define BYTES(n) (n)
#define KILOBYTES(n) (n << 10)
#define BEGABYTES(n) (n << 20)
#define GIGABYTES(n) (((unsigned int)n) << 30)
#define TERABYTES(n) (((unsigned int)n) << 40)


#if defined(_MSC_VER)
#define DISABLE_PUSH_WARN __pragma(warning(push))
#define DISABLE_POP_WARN __pragma(warning(pop))
#define DISABLE_WARN(warningNumber) __pragma(warning(disable: warningNumber))
#endif

#define MemoryCopy memcpy
#define MemoryMove memmove
#define MemorySet memset

#define NONCOPYABLE(className)                       \
    className(const className&)            = delete; \
    className& operator=(const className&) = delete;

#define NONCOPYABLEANDMOVE(className)                \
    className(const className&)            = delete; \
    className& operator=(const className&) = delete; \
    className(className&&)                 = delete; \
    className& operator=(className&&)      = delete;

#define NODISCARD [[nodiscard]]


#endif // !ENGINEDEFINES_H
