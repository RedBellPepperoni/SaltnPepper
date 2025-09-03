/************************************************************************|
|							WindowsPlatform.h							 |
|************************************************************************|
|                                                                        |
|========================================================================|
|				Copyright (c) 2024 - present Abhishek Dalvi.             |
|																		 |
|                                                                        |
|  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       |
|  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    |
|  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.|
|  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  |
|  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  |
|  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     |
|  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                |
**************************************************************************/


#ifndef WINDOWS_PLATFORM_H
#define WINDOWS_PLATFORM_H

#include "../GenericPlatformTypes.h"

#ifndef NOMINMAX
#define NOMINMAX // For windows.h
#endif

// NO explicit changes for now
struct FWindowsPlatformTypes : public FGenericPlatformTypes
{};


/// Static Lib / DLL Defines

#define SPROUT_API
// For later stuff if i decide to make it a dll



/// Break and Assert

// for windows
#define SPROUT_BREAK() __debugbreak()

#define SPROUT_ASSERT(condition, ...)	\
	if(!condition)					\
	{								\
		SPROUT_BREAK();				\
	}	

/// C Style Function MACROS
/* Functions with variable arguments */
#define VARARGS     __cdecl

/* Standard C function */
#define CDECL	    __cdecl	

/* Standard calling convention */
#define STDCALL		__stdcall

/* Force code to be inline */
#define FORCEINLINE __forceinline

/* Force code to NOT be inline */
#define FORCENOINLINE __declspec(noinline)

#endif // !WINDOWS_PLATFORM_H
