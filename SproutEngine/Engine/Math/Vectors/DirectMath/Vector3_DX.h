/************************************************************************|
|						    Vector3_DX.h								 |
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


/*
	DEFINATION OF DIRECTX VECTOR 3
*/


#ifndef VECTOR3_DX_H
#define VECTOR3_DX_H

#include <DirectXMath.h>

using namespace DirectX;

struct Matrix4;

namespace SproutEngine
{
	namespace Maths
	{




		struct Vector3Int;
		struct Quaternion;

		/// <summary>
		///  Structure defining a 16 bit aligned 3 dimentional floating point vector (a Vector 3)
		/// </summary>
		struct SPROUT_VECTOR3_DX 
		{

			// Zero Valued Vector : Vector3_ {0.0f , 0.0f, 0.0f}
			static const SPROUT_VECTOR3_DX Zero;
			// One Valued Vector : Vector3_ {1.0f , 1.0f, 1,0f}
			static const SPROUT_VECTOR3_DX One;
			// Unit Vector with X component as One : Vector3_ {1.0f , 0.0f, 0.0f}
			static const SPROUT_VECTOR3_DX UnitX;
			// Unit Vector with Y component as One : Vector3_ {0.0f , 1.0f, 0.0f}
			static const SPROUT_VECTOR3_DX UnitY;
			// Unit Vector with Y component as One : Vector3_ {0.0f , 0.0f, 1.0f}
			static const SPROUT_VECTOR3_DX UnitZ;

			union
			{
				struct { float x, y, z; };
				struct { float u, v, s; };
				struct { float r, g, b; };
				DirectX::XMFLOAT3A xmvector;
			};


			/// Declarations for Vector3_
			SPROUT_VECTOR3_DX() noexcept : xmvector(0.0f, 0.0f, 0.0f) {}
			constexpr explicit SPROUT_VECTOR3_DX(float _singleValue) noexcept : xmvector(_singleValue, _singleValue, _singleValue) {}
			constexpr SPROUT_VECTOR3_DX(float _valueX, float _valueY, float _valueZ) noexcept : xmvector(_valueX, _valueY, _valueZ) {}


			SPROUT_VECTOR3_DX(const SPROUT_VECTOR3_DX&) = default;
			SPROUT_VECTOR3_DX& operator=(const SPROUT_VECTOR3_DX&) = default;

			SPROUT_VECTOR3_DX(SPROUT_VECTOR3_DX&&) = default;
			SPROUT_VECTOR3_DX& operator=(SPROUT_VECTOR3_DX&&) = default;

			/*
				Gets this value as a XMVECTOR
			*/
			operator XMVECTOR() const noexcept { return XMLoadFloat3(&xmvector); }

			/*
				Creates a new Vector3_ from an FXMVector
			*/
			SPROUT_VECTOR3_DX(FXMVECTOR _vector) noexcept 
			{ 
				XMStoreFloat3A(&xmvector, _vector); 
			}


			// Constructor ALIGNED : Sets both (X, Y) components as the given XMFFLOAT2A's Components
			SPROUT_VECTOR3_DX(const XMFLOAT3A& _xmFloat) noexcept : xmvector(_xmFloat.x, _xmFloat.y, _xmFloat.z) {}

			// Constructor UNALIGHNED: Sets both (X, Y) components as the given XMFFLOAT2's Components
			SPROUT_VECTOR3_DX(const XMFLOAT3& _xmFloat) noexcept : xmvector(_xmFloat.x, _xmFloat.y, _xmFloat.z) {}

			SPROUT_VECTOR3_DX(const XMVECTORF32& _xmVector32) noexcept : xmvector(_xmVector32.f[0], _xmVector32.f[1], _xmVector32.f[2]) {}

			
			SPROUT_VECTOR3_DX& operator= (const XMVECTORF32& _vector) noexcept { x = _vector.f[0]; y = _vector.f[1]; z = _vector.f[2]; return *this; }

			/// Arithmatic
			SPROUT_VECTOR3_DX& operator+= (const SPROUT_VECTOR3_DX& _vector) noexcept;
			SPROUT_VECTOR3_DX& operator-= (const SPROUT_VECTOR3_DX& _vector) noexcept;
			SPROUT_VECTOR3_DX& operator*= (const SPROUT_VECTOR3_DX& _vector) noexcept;
			SPROUT_VECTOR3_DX& operator/= (const SPROUT_VECTOR3_DX& _vector) noexcept;

			SPROUT_VECTOR3_DX& operator*= (float _scalar) noexcept;
			SPROUT_VECTOR3_DX& operator/= (float _scalar) noexcept;

			/// Comparisons
			inline bool operator == (const SPROUT_VECTOR3_DX& _vector) const noexcept
			{
				using namespace DirectX;
				const XMVECTOR vectorOne = XMLoadFloat3A(&this->xmvector);
				const XMVECTOR vectorTwo = XMLoadFloat3A(&_vector.xmvector);
				return XMVector3Equal(vectorOne, vectorTwo);
			}

			inline bool operator != (const SPROUT_VECTOR3_DX& _vector) const noexcept
			{
				using namespace DirectX;
				const XMVECTOR vectorOne = XMLoadFloat3A(&this->xmvector);
				const XMVECTOR vectorTwo = XMLoadFloat3A(&_vector.xmvector);
				return XMVector3NotEqual(vectorOne, vectorTwo);
			}


			/// Negative Value
			inline SPROUT_VECTOR3_DX operator- () const noexcept
			{
				using namespace DirectX;
				const XMVECTOR vectorOne = XMLoadFloat3A(&this->xmvector);
				const XMVECTOR finalVector = XMVectorNegate(vectorOne);
				SPROUT_VECTOR3_DX result;
				XMStoreFloat3A(&result.xmvector, finalVector);
				return result;
			}
			SPROUT_VECTOR3_DX operator+ () const noexcept;


			/// Free-Standing Operators for Left Handeded Operations
			friend SPROUT_VECTOR3_DX operator+ (const SPROUT_VECTOR3_DX& _firstVector, const SPROUT_VECTOR3_DX& _secondVector) noexcept;
			friend SPROUT_VECTOR3_DX operator- (const SPROUT_VECTOR3_DX& _firstVector, const SPROUT_VECTOR3_DX& _secondVector) noexcept;
			friend SPROUT_VECTOR3_DX operator* (const SPROUT_VECTOR3_DX& _firstVector, const SPROUT_VECTOR3_DX& _secondVector) noexcept;
			friend SPROUT_VECTOR3_DX operator* (const SPROUT_VECTOR3_DX& _firstVector, const float _float) noexcept;
			friend SPROUT_VECTOR3_DX operator/ (const SPROUT_VECTOR3_DX& _firstVector, const SPROUT_VECTOR3_DX& _secondVector) noexcept;
			friend SPROUT_VECTOR3_DX operator/ (const SPROUT_VECTOR3_DX& _firstVector, const float _float) noexcept;
		

			/// Length and Distance Functions
			float Length() const noexcept;
			float LengthSquared() const noexcept;

			static float Distance(const SPROUT_VECTOR3_DX& _firstVector, const SPROUT_VECTOR3_DX& _secondVector) noexcept;
			static float DistanceSquared(const SPROUT_VECTOR3_DX& _firstVector, const SPROUT_VECTOR3_DX& _secondVector) noexcept;

			void Normalize() noexcept;
			void Normalize(SPROUT_VECTOR3_DX& _result) const noexcept;

			float Dot(const SPROUT_VECTOR3_DX& _otherVector) const noexcept;
			float Cross(const SPROUT_VECTOR3_DX& _otherVector) const noexcept;


			static void Lerp(const SPROUT_VECTOR3_DX& _vectorOne, const SPROUT_VECTOR3_DX& _vectorTwo, float _lerpFactor, SPROUT_VECTOR3_DX& _result) noexcept;
			static SPROUT_VECTOR3_DX Lerp(const SPROUT_VECTOR3_DX& _vectorOne, const SPROUT_VECTOR3_DX& _vectorTwo, float _lerpFactor) noexcept;

			static void Clamp(const SPROUT_VECTOR3_DX& _vector, const SPROUT_VECTOR3_DX& _vectorMin, const SPROUT_VECTOR3_DX& _vectorMax, SPROUT_VECTOR3_DX& _result) noexcept;
			static SPROUT_VECTOR3_DX Clamp(const SPROUT_VECTOR3_DX& _vector, const SPROUT_VECTOR3_DX& _vectorMin, const SPROUT_VECTOR3_DX& _vectorMax) noexcept;

			static void Min(const SPROUT_VECTOR3_DX& _vectorOne, const SPROUT_VECTOR3_DX& _vectorTwo, SPROUT_VECTOR3_DX& _result) noexcept;
			static SPROUT_VECTOR3_DX Min(const SPROUT_VECTOR3_DX& _vectorOne, const SPROUT_VECTOR3_DX& _vectorTwo) noexcept;

			static void Max(const SPROUT_VECTOR3_DX& _vectorOne, const SPROUT_VECTOR3_DX& _vectorTwo, SPROUT_VECTOR3_DX& _result) noexcept;
			static SPROUT_VECTOR3_DX Max(const SPROUT_VECTOR3_DX& _vectorOne, const SPROUT_VECTOR3_DX& _vectorTwo) noexcept;

			static void SmoothStep(const SPROUT_VECTOR3_DX& _vectorOne, const SPROUT_VECTOR3_DX& _vectorTwo, float _stepFactor, SPROUT_VECTOR3_DX& _result) noexcept;
			static SPROUT_VECTOR3_DX SmoothStep(const SPROUT_VECTOR3_DX& _vectorOne, const SPROUT_VECTOR3_DX& _vectorTwo, float _stepFactor) noexcept;


		};
	}
}

#endif // !VECTOR3_DX_H
