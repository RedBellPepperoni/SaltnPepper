/************************************************************************|
|						    EngineDefines.h						     |
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

#ifndef ENGINEDEFINES_H
#define ENGINEDEFINES_H


#include <../Platform/Platform.h>




/// Deprecated MACRO
#define SPROUT_DEPRECATED													\
 {																		\
	LOG_ERROR("Deprecared : {0} : {1}", __FILE__, __LINE__);			\
 }
																		
#define BIT(x) (1 << x)



#if defined(_MSC_VER)
#define DISABLE_PUSH_WARN __pragma(warning(push))
#define DISABLE_POP_WARN __pragma(warning(pop))
#define DISABLE_WARN(warningNumber) __pragma(warning(disable: warningNumber))
#endif

#define MemoryCopy memcpy
#define MemoryMove memmove
#define MemorySet memset



/// MATH STUFFFFFF
// Uses Direct X Maths (Vectorization using XMVECTOR aligned Registers)
#define MATH_DIRECTX	1

// Uses GLM Library for Maths
#define MATH_GLM		0

// Uses Custom built maths Library (When I get time to actaully DO this ... lmao)
#define MATH_SPROUT		0




#endif // !ENGINEDEFINES_H
