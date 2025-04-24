/************************************************************************|
|						    Vector3.hpp						     |
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

#ifndef VECTOR3_H
#define VECTOR3_H

#include <DirectXMath.h>

using namespace DirectX;

struct Matrix4;

namespace SproutEngine
{
	namespace Maths
	{
		struct Vector3 : public XMFLOAT3A
		{


			/// Declarations for Vector3
			Vector3() noexcept : XMFLOAT3A(0.0f, 0.0f, 0.0f) {}
			constexpr explicit Vector3(float _singleValue) noexcept : XMFLOAT3A(_singleValue, _singleValue, _singleValue) {}
			constexpr Vector3(float _valueX, float _valueY, float _valueZ) noexcept : XMFLOAT3A(_valueX, _valueY, _valueZ) {}


			Vector3(const Vector3&) = default;
			Vector3& operator=(const Vector3&) = default;

			Vector3(Vector3&&) = default;
			Vector3& operator=(Vector3&&) = default;

			/*
				Gets this value as a XMVECTOR
			*/
			operator XMVECTOR() const noexcept { return XMLoadFloat3(this); }

			/*
				Creates a new Vector3 from an FXMVector
			*/
			Vector3(FXMVECTOR _vector) noexcept 
			{ 
				XMStoreFloat3(this, _vector); 
			}


			/*
				Creates a new Vector3 from an XMFLOT3
			*/
			Vector3(const XMFLOAT3& _vector) noexcept 
			{ 
				this->x = _vector.x; 
				this->y = _vector.y; 
				this->z = _vector.z; 
			}
			
			/*
				Creates a Vector3 from a XMVECTORF32
			*/
			explicit Vector3(const XMVECTORF32& _vector) noexcept 
			{ 
				this->x = _vector.f[0]; 
				this->y = _vector.f[1]; 
				this->z = _vector.f[2]; 
			}
			
			Vector3& operator= (const XMVECTORF32& _vector) noexcept { x = _vector.f[0]; y = _vector.f[1]; z = _vector.f[2]; return *this; }

			/// Arithmatic
			Vector3& operator+= (const Vector3& _vector) noexcept;
			Vector3& operator-= (const Vector3& _vector) noexcept;
			Vector3& operator*= (const Vector3& _vector) noexcept;
			Vector3& operator/= (const Vector3& _vector) noexcept;

			Vector3& operator*= (float _scalar) noexcept;
			Vector3& operator/= (float _scalar) noexcept;

			/// Comparisons
			bool operator == (const Vector3& _vector) const noexcept;
			bool operator != (const Vector3& _vector) const noexcept;


			/// Negative Value
			Vector3 operator- () const noexcept;
			Vector3 operator+ () const noexcept;


			/// Free-Standing Operators for Left Handeded Operations
			friend Vector3 operator+ (const Vector3& _firstVector, const Vector3& _secondVector) noexcept;
			friend Vector3 operator- (const Vector3& _firstVector, const Vector3& _secondVector) noexcept;
			friend Vector3 operator* (const Vector3& _firstVector, const Vector3& _secondVector) noexcept;
			friend Vector3 operator* (const Vector3& _firstVector, const float _float) noexcept;
			friend Vector3 operator/ (const Vector3& _firstVector, const Vector3& _secondVector) noexcept;
			friend Vector3 operator/ (const Vector3& _firstVector, const float _float) noexcept;
		

			/// Length and Distance Functions
			float Length() const noexcept;
			float LengthSquared() const noexcept;

			static float Distance(const Vector3& _firstVector, const Vector3& _secondVector) noexcept;
			static float DistanceSquared(const Vector3& _firstVector, const Vector3& _secondVector) noexcept;

			void Normalize() noexcept;
			void Normalize(Vector3& _result) const noexcept;

			float Dot(const Vector3& _otherVector) const noexcept;
			float Cross(const Vector3& _otherVector) const noexcept;


			static void Lerp(const Vector3& _vectorOne, const Vector3& _vectorTwo, float _lerpFactor, Vector3& _result) noexcept;
			static Vector3 Lerp(const Vector3& _vectorOne, const Vector3& _vectorTwo, float _lerpFactor) noexcept;

			static void Clamp(const Vector3& _vector, const Vector3& _vectorMin, const Vector3& _vectorMax, Vector3& _result) noexcept;
			static Vector3 Clamp(const Vector3& _vector, const Vector3& _vectorMin, const Vector3& _vectorMax) noexcept;

			static void Min(const Vector3& _vectorOne, const Vector3& _vectorTwo, Vector3& _result) noexcept;
			static Vector3 Min(const Vector3& _vectorOne, const Vector3& _vectorTwo) noexcept;

			static void Max(const Vector3& _vectorOne, const Vector3& _vectorTwo, Vector3& _result) noexcept;
			static Vector3 Max(const Vector3& _vectorOne, const Vector3& _vectorTwo) noexcept;

			static void SmoothStep(const Vector3& _vectorOne, const Vector3& _vectorTwo, float _stepFactor, Vector3& _result) noexcept;
			static Vector3 SmoothStep(const Vector3& _vectorOne, const Vector3& _vectorTwo, float _stepFactor) noexcept;


		};
	}
}

#endif // !VECTOR3_H
