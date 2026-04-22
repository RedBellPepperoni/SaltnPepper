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
#include <MathFunctions.h>
#include <string>

using namespace DirectX;

namespace SproutEngine
{
	namespace Maths
	{

		//struct Vector2Int;
		struct Quaternion;

		

		
		/* A 2-dimensional floating point vector backed by DirectXMath.
			 
			 Internal storage uses XMFLOAT2 (unaligned) for safe heap allocation
			 and STL container compatibility. SIMD operations are performed on
			 the stack via XMVECTOR — alignment is always guaranteed there.
			
			 Coordinate aliases: (x, y) or (u, v) for texture coordinates.
		*/
		
		/// <summary>
		/// Structure defining a 16 bit aligned 2 dimentional floating point vector ( Vector 2)
		/// </summary>
		struct SPROUT_VECTOR2_DX
		{
			// @brief Vector with both components set to 0 : (0, 0)
			static const SPROUT_VECTOR2_DX Zero;

			// @brief Vector with both components set to 1 : (1, 1)
			static const SPROUT_VECTOR2_DX One;

			// @brief Unit vector along the X axis : (1, 0)
			static const SPROUT_VECTOR2_DX UnitX;

			// @brief Unit vector along the Y axis : (0, 1)
			static const SPROUT_VECTOR2_DX UnitY;


			/// =========================================================
			///							DATA
			/// =========================================================
			union
			{
				struct { float x, y; }; // Spatial coordinate access
				struct { float u, v; }; // Texture coordinate access
				DirectX::XMFLOAT2 xmvector; // Underlying DirectXMath storage (unaligned, heap-safe)
			};


			/// =========================================================
			///						CONSTRUCTORS
			/// =========================================================
			
			// @brief Default Constructor : Always constructed as a Vector2_{0.0f}
			SPROUT_VECTOR2_DX() noexcept :  xmvector{ 0.0f, 0.0f } {}

			// @brief Scalar constructor. Sets both X and Y to the same value.
			// @param _singleValue Value applied to both components.
			constexpr explicit SPROUT_VECTOR2_DX(float _singleValue) noexcept : xmvector(_singleValue, _singleValue) {}

			// @brief Component constructor. Sets X and Y independently.
			// @param _xValue Value for the X component.
			// @param _yValue Value for the Y component.
			constexpr explicit SPROUT_VECTOR2_DX(float _xValue, float _yValue) noexcept : xmvector(_xValue, _yValue) {}



			SPROUT_VECTOR2_DX(const SPROUT_VECTOR2_DX&)				= default;
			SPROUT_VECTOR2_DX& operator=(const SPROUT_VECTOR2_DX&)	= default;

			SPROUT_VECTOR2_DX(SPROUT_VECTOR2_DX&&)					= default;
			SPROUT_VECTOR2_DX& operator=(SPROUT_VECTOR2_DX&&)		= default;


			// @brief Implicit conversion to XMVECTOR for DirectXMath interop.
			operator XMVECTOR() const noexcept { return XMLoadFloat2(&xmvector); }

			// @brief Constructs from an aligned XMFLOAT2A.
			// @param _xmFloat Source aligned float2.
			SPROUT_VECTOR2_DX(const XMFLOAT2A& _xmFloat) noexcept 
				: xmvector(_xmFloat.x, _xmFloat.y){ }
			
			// @brief Constructs from an unaligned XMFLOAT2.
			// @param _xmFloat Source unaligned float2.
			SPROUT_VECTOR2_DX(const XMFLOAT2& _xmFloat) noexcept 
				: xmvector(_xmFloat.x, _xmFloat.y) {}

			// @brief Constructs from an XMVECTORF32 constant
			// @param _xmVector32 Source XMVECTORF32.
			SPROUT_VECTOR2_DX(const XMVECTORF32& _xmVector32) noexcept 
				: xmvector(_xmVector32.f[0], _xmVector32.f[1]) {}
			

			// @brief Constructs from a raw XMVECTOR 
			// @param _xmVector Source XMVECTOR. Only the X and Y lanes are stored.
			SPROUT_VECTOR2_DX(FXMVECTOR _xmVector) noexcept
			{
				XMStoreFloat2(&xmvector, _xmVector);
			}

			
			/// =========================================================
			///					  ASSIGNMENT OPERATORS
			/// =========================================================
			// @brief Component-wise addition assignment.
			SPROUT_VECTOR2_DX& operator+= (const SPROUT_VECTOR2_DX& _vector) noexcept;
			
			// @brief Component-wise subtraction assignment.
			SPROUT_VECTOR2_DX& operator-= (const SPROUT_VECTOR2_DX& _vector) noexcept;
			
			// @brief Component-wise multiplication assignment
			SPROUT_VECTOR2_DX& operator*= (const SPROUT_VECTOR2_DX& _vector) noexcept;
			
			// @brief Component-wise division assignment.
			SPROUT_VECTOR2_DX& operator/= (const SPROUT_VECTOR2_DX& _vector) noexcept;
			
			// @brief Scalar multiplication assignment. Scales both components uniformly.
			// @param _scalar Scale factor.
			SPROUT_VECTOR2_DX& operator*= (const float _scalar) noexcept;

			// @brief Scalar division assignment. Divides both components by _scalar.
			// @param _scalar Divisor. Behaviour is undefined if _scalar == 0.
			SPROUT_VECTOR2_DX& operator/= (const float _scalar) noexcept;

			/// =========================================================
			///					COMPARISON OPERATORS
			/// =========================================================
			
			// @brief Exact equality check using XMVector2Equal.
			// @note For floating-point comparisons, prefer a tolerance-based check.
			inline bool operator== (const SPROUT_VECTOR2_DX& _vector) const noexcept
			{
				using namespace DirectX;

				const XMVECTOR thisVector = XMLoadFloat2(&this->xmvector);
				const XMVECTOR inVector = XMLoadFloat2(&_vector.xmvector);
				return XMVector2Equal(thisVector, inVector);
			}

			// @brief Checks near equality within a given epsilon tolerance.
			/*  Use this instead of operator== when vectors have gone through
			    floating point operations (normalize, lerp, arithmetic chains).
				@param _vector  Vector to compare against.
				@param _epsilon Per-component tolerance. Defaults to a tight epsilon.
			*/
			inline bool NearEqual(const SPROUT_VECTOR2_DX& _vector,
				const SPROUT_VECTOR2_DX& _epsilon = SPROUT_VECTOR2_DX(EPSILON)) const noexcept
			{
				const XMVECTOR a = XMLoadFloat2(&this->xmvector);
				const XMVECTOR b = XMLoadFloat2(&_vector.xmvector);
				const XMVECTOR eps = XMLoadFloat2(&_epsilon.xmvector);
				return XMVector2NearEqual(a, b, eps);
			}


			bool operator!= (const SPROUT_VECTOR2_DX& _vector) const noexcept
			{
				using namespace DirectX;

				const XMVECTOR thisVector = XMLoadFloat2(&this->xmvector);
				const XMVECTOR inVector = XMLoadFloat2(&_vector.xmvector);
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
			friend SPROUT_VECTOR2_DX operator* (float _float, const SPROUT_VECTOR2_DX& _vector) noexcept;
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
				const XMVECTOR vectorThis = XMLoadFloat2(&this->xmvector);
				const XMVECTOR normalizedVector = XMVector2Normalize(vectorThis);
				XMStoreFloat2(&this->xmvector, normalizedVector);
			}

			void Normalize(SPROUT_VECTOR2_DX& _result) const noexcept;
			

			/// Vector Algebra

			inline float Dot(const SPROUT_VECTOR2_DX& _otherVector) const noexcept
			{
				using namespace DirectX;
				const XMVECTOR thisvector = XMLoadFloat2(&this->xmvector);
				const XMVECTOR otherVector = XMLoadFloat2(&_otherVector.xmvector);
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
			//static SPROUT_VECTOR2_DX Transform(const SPROUT_VECTOR2_DX& _vector, const Quaternion& _quaternion) noexcept;

			//
			/// ------------------------------------- String Functions --------------------------------------------------

			//TString ToString() const;

		};


		

	}
}



#endif //!VECTOR2_DX_H

