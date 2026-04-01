/************************************************************************|
|						    SPROUT_VECTOR2_DX.h							 |
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

#ifndef VECTOR2_DX_H
#define VECTOR2_DX_H


#include <DirectXMath.h>
#include <string>

using namespace DirectX;

namespace SproutEngine
{
	namespace Maths
	{

		//struct Vector2Int;
		//struct Quaternion;

		

		/// <summary>
		///  Structure defining a 16 bit aligned 2 dimentional floating point vector (a Vector 2)
		/// </summary>
		struct SPROUT_VECTOR2_DX
		{
			// Zero Valued Vector : Vector2_ {0.0f , 0.0f}
			static const SPROUT_VECTOR2_DX Zero;
			// One Valued Vector : Vector2_ {1.0f , 1.0f}
			static const SPROUT_VECTOR2_DX One;
			// Unit Vector with X component as One : Vector2_ {1.0f , 0.0f}
			static const SPROUT_VECTOR2_DX UnitX;
			// Unit Vector with Y component as One : Vector2_ {0.0f , 1.0f}
			static const SPROUT_VECTOR2_DX UnitY;


			union
			{
				struct { float x, y; };
				struct { float u, v; };
				DirectX::XMFLOAT2A xmvector;
			};


			/// -----------------------------------------------   Declarations for SPROUT_VECTOR2_DX  --------------------------------------------

			// Default Constructor : Always constructed as a Vector2_{0.0f}
			SPROUT_VECTOR2_DX() noexcept :  xmvector{ 0.0f, 0.0f } {}

			// Single Value Constructor : Sets both (X, Y) components as the given Value
			constexpr explicit SPROUT_VECTOR2_DX(float _singleValue) noexcept : xmvector(_singleValue, _singleValue) {}

			// Multi Value Constructor : Sets components according to the given Values
			constexpr explicit SPROUT_VECTOR2_DX(float _xValue, float _yValue) noexcept : xmvector(_xValue, _yValue) {}



			SPROUT_VECTOR2_DX(const SPROUT_VECTOR2_DX&) = default;
			SPROUT_VECTOR2_DX& operator=(const SPROUT_VECTOR2_DX&) = default;

			SPROUT_VECTOR2_DX(SPROUT_VECTOR2_DX&&) = default;
			SPROUT_VECTOR2_DX& operator=(SPROUT_VECTOR2_DX&&) = default;



			operator XMVECTOR() const noexcept { return XMLoadFloat2A(&xmvector); }

			// Constructor ALIGNED : Sets both (X, Y) components as the given XMFFLOAT2A's Components
			SPROUT_VECTOR2_DX(const XMFLOAT2A& _xmFloat) noexcept : xmvector(_xmFloat.x, _xmFloat.y){ }
			
			// Constructor UNALIGHNED: Sets both (X, Y) components as the given XMFFLOAT2's Components
			SPROUT_VECTOR2_DX(const XMFLOAT2& _xmFloat) noexcept : xmvector(_xmFloat.x, _xmFloat.y) {}

			SPROUT_VECTOR2_DX(const XMVECTORF32& _xmVector32) noexcept : xmvector(_xmVector32.f[0], _xmVector32.f[1]) {}
			

			SPROUT_VECTOR2_DX(FXMVECTOR _xmVector) noexcept
			{
				XMStoreFloat2A(&xmvector, _xmVector);
			}

			
			/// --------------------------------------- Arithmatic Operation ----------------------------------------------------------
			SPROUT_VECTOR2_DX& operator+= (const SPROUT_VECTOR2_DX& _vector) noexcept;
			SPROUT_VECTOR2_DX& operator-= (const SPROUT_VECTOR2_DX& _vector) noexcept;
			SPROUT_VECTOR2_DX& operator*= (const SPROUT_VECTOR2_DX& _vector) noexcept;
			SPROUT_VECTOR2_DX& operator/= (const SPROUT_VECTOR2_DX& _vector) noexcept;
			

			SPROUT_VECTOR2_DX& operator*= (const float _scalar) noexcept;
			SPROUT_VECTOR2_DX& operator/= (const float _scalar) noexcept;

			/// Comparisons
			inline bool operator== (const SPROUT_VECTOR2_DX& _vector) const noexcept
			{
				using namespace DirectX;

				const XMVECTOR thisVector = XMLoadFloat2A(&this->xmvector);
				const XMVECTOR inVector = XMLoadFloat2A(&_vector.xmvector);
				return XMVector2Equal(thisVector, inVector);
			}

			bool operator!= (const SPROUT_VECTOR2_DX& _vector) const noexcept
			{
				using namespace DirectX;

				const XMVECTOR thisVector = XMLoadFloat2A(&this->xmvector);
				const XMVECTOR inVector = XMLoadFloat2A(&_vector.xmvector);
				return XMVector2NotEqual(thisVector, inVector);
			}

			/// Negative Value
			SPROUT_VECTOR2_DX operator- () const noexcept;
			SPROUT_VECTOR2_DX operator+ () const noexcept;

	
			/// Free-Standing Operators for Left Handeded Operations
			friend SPROUT_VECTOR2_DX operator+ (const SPROUT_VECTOR2_DX& _firstVector, const SPROUT_VECTOR2_DX& _secondVector)  noexcept;
			friend SPROUT_VECTOR2_DX operator- (const SPROUT_VECTOR2_DX& _firstVector, const SPROUT_VECTOR2_DX& _secondVector) noexcept;
			friend SPROUT_VECTOR2_DX operator* (const SPROUT_VECTOR2_DX& _firstVector, const SPROUT_VECTOR2_DX& _secondVector) noexcept;
			friend SPROUT_VECTOR2_DX operator* (const SPROUT_VECTOR2_DX& _firstVector, const float _float) noexcept;
			friend SPROUT_VECTOR2_DX operator/ (const SPROUT_VECTOR2_DX& _firstVector, const SPROUT_VECTOR2_DX& _secondVector) noexcept;
			friend SPROUT_VECTOR2_DX operator/ (const SPROUT_VECTOR2_DX& _firstVector, const float _float) noexcept;


			/// Length and Distance Functions
			float Length() const noexcept;
			float LengthSquared() const noexcept;

			static float Distance(const SPROUT_VECTOR2_DX& _firstVector, const SPROUT_VECTOR2_DX& _secondVector) noexcept;
			static float DistanceSquared(const SPROUT_VECTOR2_DX& _firstVector, const SPROUT_VECTOR2_DX& _secondVector) noexcept;


			inline void Normalize() noexcept
			{
				using namespace DirectX;
				const XMVECTOR vectorThis = XMLoadFloat2A(&this->xmvector);
				const XMVECTOR normalizedVector = XMVector2Normalize(vectorThis);
				XMStoreFloat2A(&this->xmvector, normalizedVector);
			}

			void Normalize(SPROUT_VECTOR2_DX& _result) const noexcept;
			

			/// Vector Algebra

			inline float Dot(const SPROUT_VECTOR2_DX& _otherVector) const noexcept
			{
				using namespace DirectX;
				const XMVECTOR thisvector = XMLoadFloat2A(&this->xmvector);
				const XMVECTOR otherVector = XMLoadFloat2A(&_otherVector.xmvector);
				const XMVECTOR dotVector = XMVector2Dot(thisvector, otherVector);
				return XMVectorGetX(dotVector);
			}

			float Cross(const SPROUT_VECTOR2_DX& _otherVector) const noexcept;
			

			static void Lerp(const SPROUT_VECTOR2_DX& _vectorOne, const SPROUT_VECTOR2_DX& _vectorTwo, float _lerpFactor, SPROUT_VECTOR2_DX& _result) noexcept;
			static SPROUT_VECTOR2_DX Lerp(const SPROUT_VECTOR2_DX& _vectorOne, const SPROUT_VECTOR2_DX& _vectorTwo, float _lerpFactor) noexcept;

			static void Clamp(const SPROUT_VECTOR2_DX& _vector, const SPROUT_VECTOR2_DX& _vectorMin, const SPROUT_VECTOR2_DX& _vectorMax, SPROUT_VECTOR2_DX& _result) noexcept;
			static SPROUT_VECTOR2_DX Clamp(const SPROUT_VECTOR2_DX& _vector, const SPROUT_VECTOR2_DX& _vectorMin, const SPROUT_VECTOR2_DX& _vectorMax) noexcept;

			static void Min(const SPROUT_VECTOR2_DX& _vectorOne, const SPROUT_VECTOR2_DX& _vectorTwo, SPROUT_VECTOR2_DX& _result) noexcept;
			static SPROUT_VECTOR2_DX Min(const SPROUT_VECTOR2_DX& _vectorOne, const SPROUT_VECTOR2_DX& _vectorTwo) noexcept;

			static void Max(const SPROUT_VECTOR2_DX& _vectorOne, const SPROUT_VECTOR2_DX& _vectorTwo, SPROUT_VECTOR2_DX& _result) noexcept;
			static SPROUT_VECTOR2_DX Max(const SPROUT_VECTOR2_DX& _vectorOne, const SPROUT_VECTOR2_DX& _vectorTwo) noexcept;
		
			static void SmoothStep(const SPROUT_VECTOR2_DX& _vectorOne, const SPROUT_VECTOR2_DX& _vectorTwo, float _stepFactor, SPROUT_VECTOR2_DX& _result) noexcept;
			static SPROUT_VECTOR2_DX SmoothStep(const SPROUT_VECTOR2_DX& _vectorOne, const SPROUT_VECTOR2_DX& _vectorTwo, float _stepFactor) noexcept;


			/// Vector reflection and refration

			static void Reflect(const SPROUT_VECTOR2_DX& _incidentVector, const SPROUT_VECTOR2_DX& _normalVector, SPROUT_VECTOR2_DX& _result) noexcept;
			static SPROUT_VECTOR2_DX Reflect(const SPROUT_VECTOR2_DX& _incidentVector, const SPROUT_VECTOR2_DX& _normalVector) noexcept;

			static void Refract(const SPROUT_VECTOR2_DX& _incidentVector, const SPROUT_VECTOR2_DX& _normalVector, float _refractionIndex, SPROUT_VECTOR2_DX& _result) noexcept;
			static SPROUT_VECTOR2_DX Refract(const SPROUT_VECTOR2_DX& _incidentVector, const SPROUT_VECTOR2_DX& _normalVector, float _refractionIndex) noexcept;

			static void Transform(const SPROUT_VECTOR2_DX& _vector, const Quaternion& _quaternion, SPROUT_VECTOR2_DX& _result) noexcept;
			static SPROUT_VECTOR2_DX Transform(const SPROUT_VECTOR2_DX& _vector, const Quaternion& _quaternion) noexcept;

			
			/// ------------------------------------- String Functions --------------------------------------------------

			//TString ToString() const;

		};


		

	}
}



#endif //!VECTOR2_DX_H

