/************************************************************************|
|						    Vector2.hpp						     |
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

#ifndef VECTOR2_H
#define VECTOR2_H


#include <DirectXMath.h>
#include <string>

using namespace DirectX;

namespace SproutEngine
{
	namespace Maths
	{

		struct Vector2Int;
		struct Quaternion;

		

		/// <summary>
		///  Structure defining a 16 bit aligned 2 dimentional floating point vector (a Vector 2)
		/// </summary>
		struct Vector2
		{
			// Zero Valued Vector : Vector2 {0.0f , 0.0f}
			static const Vector2 Zero;
			// One Valued Vector : Vector2 {1.0f , 1.0f}
			static const Vector2 One;
			// Unit Vector with X component as One : Vector2 {1.0f , 0.0f}
			static const Vector2 UnitX;
			// Unit Vector with Y component as One : Vector2 {0.0f , 1.0f}
			static const Vector2 UnitY;


			union
			{
				struct { float x, y; };
				struct { float u, v; };
				DirectX::XMFLOAT2A xmvector;
			};


			/// -----------------------------------------------   Declarations for Vector2  --------------------------------------------

			// Default Constructor : Always constructed as a Vector2{0.0f}
			Vector2() noexcept :  xmvector{ 0.0f, 0.0f } {}

			// Single Value Constructor : Sets both (X, Y) components as the given Value
			constexpr explicit Vector2(float _singleValue) noexcept : xmvector(_singleValue, _singleValue) {}

			// Multi Value Constructor : Sets components according to the given Values
			constexpr explicit Vector2(float _xValue, float _yValue) noexcept : xmvector(_xValue, _yValue) {}



			Vector2(const Vector2&) = default;
			Vector2& operator=(const Vector2&) = default;

			Vector2(Vector2&&) = default;
			Vector2& operator=(Vector2&&) = default;



			operator XMVECTOR() const noexcept { return XMLoadFloat2A(&xmvector); }

			// Constructor ALIGNED : Sets both (X, Y) components as the given XMFFLOAT2A's Components
			Vector2(const XMFLOAT2A& _xmFloat) noexcept : xmvector(_xmFloat.x, _xmFloat.y){ }
			
			// Constructor UNALIGHNED: Sets both (X, Y) components as the given XMFFLOAT2's Components
			Vector2(const XMFLOAT2& _xmFloat) noexcept : xmvector(_xmFloat.x, _xmFloat.y) {}

			Vector2(const XMVECTORF32& _xmVector32) noexcept : xmvector(_xmVector32.f[0], _xmVector32.f[1]) {}
			

			Vector2(FXMVECTOR _xmVector) noexcept
			{
				XMStoreFloat2A(&xmvector, _xmVector);
			}

			
			/// --------------------------------------- Arithmatic Operation ----------------------------------------------------------
			Vector2& operator+= (const Vector2& _vector) noexcept;
			Vector2& operator-= (const Vector2& _vector) noexcept;
			Vector2& operator*= (const Vector2& _vector) noexcept;
			Vector2& operator/= (const Vector2& _vector) noexcept;
			

			Vector2& operator*= (const float _scalar) noexcept;
			Vector2& operator/= (const float _scalar) noexcept;

			/// Comparisons
			inline bool operator== (const Vector2& _vector) const noexcept
			{
				using namespace DirectX;

				const XMVECTOR thisVector = XMLoadFloat2A(&this->xmvector);
				const XMVECTOR inVector = XMLoadFloat2A(&_vector.xmvector);
				return XMVector2Equal(thisVector, inVector);
			}

			bool operator!= (const Vector2& _vector) const noexcept
			{
				using namespace DirectX;

				const XMVECTOR thisVector = XMLoadFloat2A(&this->xmvector);
				const XMVECTOR inVector = XMLoadFloat2A(&_vector.xmvector);
				return XMVector2NotEqual(thisVector, inVector);
			}

			/// Negative Value
			Vector2 operator- () const noexcept;
			Vector2 operator+ () const noexcept;

	
			/// Free-Standing Operators for Left Handeded Operations
			friend Vector2 operator+ (const Vector2& _firstVector, const Vector2& _secondVector)  noexcept;
			friend Vector2 operator- (const Vector2& _firstVector, const Vector2& _secondVector) noexcept;
			friend Vector2 operator* (const Vector2& _firstVector, const Vector2& _secondVector) noexcept;
			friend Vector2 operator* (const Vector2& _firstVector, const float _float) noexcept;
			friend Vector2 operator/ (const Vector2& _firstVector, const Vector2& _secondVector) noexcept;
			friend Vector2 operator/ (const Vector2& _firstVector, const float _float) noexcept;


			/// Length and Distance Functions
			float Length() const noexcept;
			float LengthSquared() const noexcept;

			static float Distance(const Vector2& _firstVector, const Vector2& _secondVector) noexcept;
			static float DistanceSquared(const Vector2& _firstVector, const Vector2& _secondVector) noexcept;


			inline void Normalize() noexcept
			{
				using namespace DirectX;
				const XMVECTOR vectorThis = XMLoadFloat2A(&this->xmvector);
				const XMVECTOR normalizedVector = XMVector2Normalize(vectorThis);
				XMStoreFloat2A(&this->xmvector, normalizedVector);
			}

			void Normalize(Vector2& _result) const noexcept;
			

			/// Vector Algebra

			inline float Dot(const Vector2& _otherVector) const noexcept
			{
				using namespace DirectX;
				const XMVECTOR thisvector = XMLoadFloat2A(&this->xmvector);
				const XMVECTOR otherVector = XMLoadFloat2A(&_otherVector.xmvector);
				const XMVECTOR dotVector = XMVector2Dot(thisvector, otherVector);
				return XMVectorGetX(dotVector);
			}

			float Cross(const Vector2& _otherVector) const noexcept;
			

			static void Lerp(const Vector2& _vectorOne, const Vector2& _vectorTwo, float _lerpFactor, Vector2& _result) noexcept;
			static Vector2 Lerp(const Vector2& _vectorOne, const Vector2& _vectorTwo, float _lerpFactor) noexcept;

			static void Clamp(const Vector2& _vector, const Vector2& _vectorMin, const Vector2& _vectorMax, Vector2& _result) noexcept;
			static Vector2 Clamp(const Vector2& _vector, const Vector2& _vectorMin, const Vector2& _vectorMax) noexcept;

			static void Min(const Vector2& _vectorOne, const Vector2& _vectorTwo, Vector2& _result) noexcept;
			static Vector2 Min(const Vector2& _vectorOne, const Vector2& _vectorTwo) noexcept;

			static void Max(const Vector2& _vectorOne, const Vector2& _vectorTwo, Vector2& _result) noexcept;
			static Vector2 Max(const Vector2& _vectorOne, const Vector2& _vectorTwo) noexcept;
		
			static void SmoothStep(const Vector2& _vectorOne, const Vector2& _vectorTwo, float _stepFactor, Vector2& _result) noexcept;
			static Vector2 SmoothStep(const Vector2& _vectorOne, const Vector2& _vectorTwo, float _stepFactor) noexcept;


			/// Vector reflection and refration

			static void Reflect(const Vector2& _incidentVector, const Vector2& _normalVector, Vector2& _result) noexcept;
			static Vector2 Reflect(const Vector2& _incidentVector, const Vector2& _normalVector) noexcept;

			static void Refract(const Vector2& _incidentVector, const Vector2& _normalVector, float _refractionIndex, Vector2& _result) noexcept;
			static Vector2 Refract(const Vector2& _incidentVector, const Vector2& _normalVector, float _refractionIndex) noexcept;

			static void Transform(const Vector2& _vector, const Quaternion& _quaternion, Vector2& _result) noexcept;
			static Vector2 Transform(const Vector2& _vector, const Quaternion& _quaternion) noexcept;

			
			/// ------------------------------------- String Functions --------------------------------------------------

			std::string ToString() const;

		};


		

	}
}



#endif //!VECTOR2_H

