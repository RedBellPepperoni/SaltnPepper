/************************************************************************|
|						    Vector4.h									 |
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

#ifndef VECTOR4_H
#define VECTOR4_H


#include <DirectXMath.h>
#include <string>

using namespace DirectX;

namespace SproutEngine
{
	namespace Maths
	{
		struct Vector2Int;
		struct Quaternion; 



		struct Vector4
		{
			// Zero Valued Vector : Vector4 {0.0f}
			static const Vector4 Zero;
			// One Valued Vector : Vector2 {1.0f}
			static const Vector4 One;
			// Unit Vector with X component as One : Vector4 {1.0f , 0.0f, 0.0f, 0.0f}
			static const Vector4 UnitX;
			// Unit Vector with Y component as One : Vector4 {0.0f , 1.0f, 0.0f, 0.0f}
			static const Vector4 UnitY;
			// Unit Vector with Z component as One : Vector4 {0.0f , 0.0f, 1.0f, 0.0f}
			static const Vector4 UnitZ;
			// Unit Vector with W component as One : Vector4 {0.0f , 0.0f, 1.0f, 0.0f}
			static const Vector4 UnitW;



			union
			{
				struct { float x, y, z, w; };
				struct { float r, g, b, a; };
				struct { float u, v, s, t; };
				DirectX::XMFLOAT4A xmvector;
			};
		};


	}
}



#endif //!VECTOR4_H