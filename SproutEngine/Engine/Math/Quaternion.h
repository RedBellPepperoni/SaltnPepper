/************************************************************************|
|						    Quaternion.hpp						     |
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

#ifndef QUATERNION_H
#define QUATERNION_H

#include <DirectXMath.h>

using namespace DirectX;

namespace SproutEngine
{
	namespace Maths
	{
		struct Vector2;
		struct Vector3;
		struct Vector4;


		struct Quaternion : public XMFLOAT4A
		{
			Quaternion() noexcept : XMFLOAT4A{ 0,0,0,1.0f } {}
			constexpr Quaternion(float _valueX, float _valueY, float _valueZ, float _valueW) noexcept : XMFLOAT4A(_valueX, _valueY, _valueZ, _valueW) {};

			Quaternion(const Quaternion&) = default;
			Quaternion& operator=(const Quaternion&) = default;

			Quaternion(Quaternion&&) = default;
			Quaternion& operator=(Quaternion&&) = default;

			explicit Quaternion(const Vector4& _vector) noexcept;
			explicit Quaternion(const Vector3& _vector, float _scalar) noexcept;
			Quaternion(FXMVECTOR _fxmVector) noexcept { XMStoreFloat4A(this, _fxmVector); }
			Quaternion(const XMFLOAT4A& _quatVector) noexcept { this->x = _quatVector.x; this->y = _quatVector.y; this->z = _quatVector.z; this->w = _quatVector.w; }
			explicit Quaternion(const XMVECTORF32& _f32Vector) noexcept { this->x = _f32Vector.f[0]; this->y = _f32Vector.f[1]; this->z = _f32Vector.f[2]; this->w = _f32Vector.f[3]; }

			operator XMVECTOR() const noexcept { return XMLoadFloat4A(this); }

			

			/// Arithmatic
			Quaternion& operator= (const XMVECTORF32& _f32Vector) noexcept { x = _f32Vector.f[0]; y = _f32Vector.f[1]; z = _f32Vector.f[2]; w = _f32Vector.f[3]; return *this; }
			Quaternion& operator+= (const Quaternion& _quaternion) noexcept;
			Quaternion& operator-= (const Quaternion& _quaternion) noexcept;
			Quaternion& operator*= (const Quaternion& _quaternion) noexcept;
			Quaternion& operator*= (float _scalar) noexcept;
			Quaternion& operator/= (const Quaternion& _quaternion) noexcept;

			/// Comparisons
			bool operator == (const Quaternion& _quaternion) const noexcept;
			bool operator != (const Quaternion& _quaternion) const noexcept;

			/// Negative Value
			Quaternion operator- () const noexcept;
			Quaternion operator+ () const  noexcept;
			
			/// Free-Standing Operators for Left Handeded Operations
			friend Quaternion operator+ (const Quaternion& _quatOne, const Quaternion& _quatTwo) noexcept;
			friend Quaternion operator- (const Quaternion& _quatOne, const Quaternion& _quatTwo) noexcept;
			friend Quaternion operator* (const Quaternion& _quatOne, const Quaternion& _quatTwo) noexcept;
			friend Quaternion operator* (const Quaternion& _quaternion, float _scalar) noexcept;
			friend Quaternion operator/ (const Quaternion& _quatOne, const Quaternion& _quatTwo) noexcept;
			friend Quaternion operator* (float _scalar, const Quaternion& _quaternion) noexcept;
		
			
			float Length() const noexcept;
			float LengthSquared() const noexcept;

			bool IsFinite() const noexcept;
			void Inverse(Quaternion& _result) const noexcept;
			Quaternion Inverse() noexcept;

			void Normalize() noexcept;
			void Normalize(Quaternion& _result) const noexcept;
			bool IsNormalized() const noexcept;

			void Conjugate() noexcept;
			void Conjugate(Quaternion& _result) const noexcept;

			void Log(Quaternion& _result) const noexcept;
			Quaternion Log()  noexcept;

			void Exponent(Quaternion& _result) const noexcept;
			Quaternion Exponent()  noexcept;
		
		};
	}
}

#endif // !QUATERNION_H

