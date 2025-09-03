/************************************************************************|
|								Vector.h								 |
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


#ifndef VECTOR_H
#define VECTOR_H


/// ===============  Uses DirectX Maths ============================
#ifdef MATH_DIRECTX

#include <Math/Vectors/Vector2_DX.h>
#include <Math/Vectors/Vector3_DX.h>


using	Vector2 = SproutEngine::Maths::SPROUT_VECTOR2_DX;
using	Vector3 = SproutEngine::Maths::SPROUT_VECTOR3_DX;



#elif defined(MATH_GLM)


#endif




#endif // !VECTOR_H
