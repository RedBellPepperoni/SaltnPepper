/************************************************************************|
|								Platform.h								 |
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





#ifndef PLATFORM_H
#define PLATFORM_H


#if defined(SPROUT_PLATFORM_WINDOWS) && SPROUT_PLATFORM_WINDOWS
#include "Windows/WindowsPlatform.h"

#elif defined(SPROUT_PLATFORM_LINUX) && SPROUT_PLATFORM_LINUX
#include "Linux/LinuxPlatform.h"

#else
#error "Unsupported platform!"
#endif



#endif // !PLATFORM_H


