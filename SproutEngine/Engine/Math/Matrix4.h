/************************************************************************|
|						      Matrix.h									 |
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


#ifndef MATRIX_4_H
#define MATRIX_4_H

#include <DirectXMath.h>
#include <vcruntime_string.h>

using namespace DirectX;

namespace SproutEngine
{
	namespace Maths
	{

		struct Matrix3;
		struct Vector3;

		struct Matrix4 : public XMFLOAT4X4
		{
			Matrix4() noexcept : XMFLOAT4X4(1.f, 0, 0, 0,
										   0, 1.f, 0, 0,
										   0, 0, 1.f, 0,
										   0, 0, 0, 1.f)
			{
			}

			constexpr Matrix4(float _m00, float _m01, float _m02, float _m03,
							  float _m10, float _m11, float _m12, float _m13,
							  float _m20, float _m21, float _m22, float _m23,
							  float _m30, float _m31, float _m32, float _m33) noexcept
							 : XMFLOAT4X4(_m00, _m01, _m02, _m03,
										  _m10, _m11, _m12, _m13,
										  _m20, _m21, _m22, _m23,
										  _m30, _m31, _m32, _m33)
			{
			}


			explicit Matrix4(const Vector3& _rowZero, const Vector3& _rowOne, const Vector3& _rowTwo) noexcept;

			Matrix4(const XMFLOAT4X4& _matrix4) noexcept { memcpy(this, &_matrix4, sizeof(XMFLOAT4X4)); }
			Matrix4(const Matrix3& _matrix3) noexcept;
			Matrix4(const XMFLOAT4X3& _matrix4x3) noexcept;

			Matrix4(const Matrix4&) = default;
			Matrix4& operator=(const Matrix4&) = default;

			Matrix4(Matrix4&&) = default;
			Matrix4& operator=(Matrix4&&) = default;

			operator XMMATRIX() const noexcept { return XMLoadFloat4x4(this); }

			bool operator == (const Matrix4& _matrix4) const noexcept;
			bool operator != (const Matrix4& _matrix4) const noexcept;

			Matrix4& operator= (const Matrix3& _matrix3) noexcept;
			Matrix4& operator= (const XMFLOAT4X3& _matrix4x3) noexcept;
			Matrix4& operator+= (const Matrix4& _matrix4) noexcept;
			Matrix4& operator-= (const Matrix4& _matrix4) noexcept;
			Matrix4& operator*= (const Matrix4& _matrix4) noexcept;
			Matrix4& operator*= (float _scalar) noexcept;
			Matrix4& operator/= (float _scalar) noexcept;
		
			
			Matrix4& operator/= (const Matrix4& _matrix4) noexcept;
		
			Matrix4 operator+ () const noexcept;
			Matrix4 operator- () const noexcept;
		};

	}
}


#endif // !MATRIX_4_H
