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
																		


#if defined(_MSC_VER)
#define DISABLE_PUSH_WARN __pragma(warning(push))
#define DISABLE_POP_WARN __pragma(warning(pop))
#define DISABLE_WARN(warningNumber) __pragma(warning(disable: warningNumber))
#endif

#define MemoryCopy memcpy
#define MemoryMove memmove
#define MemorySet memset



#endif // !ENGINEDEFINES_H
