/************************************************************************|
|						    SPROUT_VECTOR3_DX.h									 |
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
		



		struct SPROUT_VECTOR4_DX
		{
			// Zero Valued Vector : Vector4_ {0.0f}
			static const SPROUT_VECTOR4_DX Zero;
			// One Valued Vector : Vector2 {1.0f}
			static const SPROUT_VECTOR4_DX One;
			// Unit Vector with X component as One : Vector4_ {1.0f , 0.0f, 0.0f, 0.0f}
			static const SPROUT_VECTOR4_DX UnitX;
			// Unit Vector with Y component as One : Vector4_ {0.0f , 1.0f, 0.0f, 0.0f}
			static const SPROUT_VECTOR4_DX UnitY;
			// Unit Vector with Z component as One : Vector4_ {0.0f , 0.0f, 1.0f, 0.0f}
			static const SPROUT_VECTOR4_DX UnitZ;
			// Unit Vector with W component as One : Vector4_ {0.0f , 0.0f, 1.0f, 0.0f}
			static const SPROUT_VECTOR4_DX UnitW;



			union
			{
				struct { float x, y, z, w; };
				struct { float r, g, b, a; };
				struct { float u, v, s, t; };
				DirectX::XMFLOAT4A xmvector;
			};

			/// Declarations for Vector3_
			SPROUT_VECTOR4_DX() noexcept : xmvector(0.0f, 0.0f, 0.0f, 0.0f) {}
			constexpr explicit SPROUT_VECTOR4_DX(float _singleValue) noexcept : xmvector(_singleValue, _singleValue, _singleValue, _singleValue) {}
			constexpr SPROUT_VECTOR4_DX(float _valueX, float _valueY, float _valueZ, float _valueW) noexcept : xmvector(_valueX, _valueY, _valueZ, _valueW) {}

			SPROUT_VECTOR4_DX(const SPROUT_VECTOR4_DX&) = default;
			SPROUT_VECTOR4_DX& operator=(const SPROUT_VECTOR4_DX&) = default;

			SPROUT_VECTOR4_DX(SPROUT_VECTOR4_DX&&) = default;
			SPROUT_VECTOR4_DX& operator=(SPROUT_VECTOR4_DX&&) = default;

			/*
				Gets this value as a XMVECTOR
			*/
			operator XMVECTOR() const noexcept { return XMLoadFloat4(&xmvector); }

			/*
				Creates a new Vector4_ from an FXMVector
			*/
			SPROUT_VECTOR4_DX(FXMVECTOR _vector) noexcept
			{
				XMStoreFloat4A(&xmvector, _vector);
			}


			// Constructor ALIGNED : Sets  (X, Y , Z ,W) components as the given XMFFLOAT4A's Components
			SPROUT_VECTOR4_DX(const XMFLOAT4A& _xmFloat) noexcept : xmvector(_xmFloat.x, _xmFloat.y, _xmFloat.z, _xmFloat.w) {}

			// Constructor UNALIGHNED: Sets both (X, Y, Z ,W) components as the given XMFFLOAT4's Components
			SPROUT_VECTOR4_DX(const XMFLOAT4& _xmFloat) noexcept : xmvector(_xmFloat.x, _xmFloat.y, _xmFloat.z, _xmFloat.w) {}

			SPROUT_VECTOR4_DX(const XMVECTORF32& _xmVector32) noexcept : xmvector(_xmVector32.f[0], _xmVector32.f[1], _xmVector32.f[2], _xmVector32.f[3]) {}

			SPROUT_VECTOR4_DX& operator= (const XMVECTORF32& _vector) noexcept { x = _vector.f[0]; y = _vector.f[1]; z = _vector.f[2]; w = _vector.f[3];  return *this; }

			/// Arithmatic
			SPROUT_VECTOR4_DX& operator+= (const SPROUT_VECTOR4_DX& _vector) noexcept;
			SPROUT_VECTOR4_DX& operator-= (const SPROUT_VECTOR4_DX& _vector) noexcept;
			SPROUT_VECTOR4_DX& operator*= (const SPROUT_VECTOR4_DX& _vector) noexcept;
			SPROUT_VECTOR4_DX& operator/= (const SPROUT_VECTOR4_DX& _vector) noexcept;

			SPROUT_VECTOR4_DX& operator*= (float _scalar) noexcept;
			SPROUT_VECTOR4_DX& operator/= (float _scalar) noexcept;

			/// Comparisons
			inline bool operator == (const SPROUT_VECTOR4_DX& _vector) const noexcept
			{
				using namespace DirectX;
				const XMVECTOR vectorOne = XMLoadFloat4A(&this->xmvector);
				const XMVECTOR vectorTwo = XMLoadFloat4A(&_vector.xmvector);
				return XMVector4Equal(vectorOne, vectorTwo);
			}

			inline bool operator != (const SPROUT_VECTOR4_DX& _vector) const noexcept
			{
				using namespace DirectX;
				const XMVECTOR vectorOne = XMLoadFloat4A(&this->xmvector);
				const XMVECTOR vectorTwo = XMLoadFloat4A(&_vector.xmvector);
				return XMVector4NotEqual(vectorOne, vectorTwo);
			}


			/// Negative Value
			inline SPROUT_VECTOR4_DX operator- () const noexcept
			{
				using namespace DirectX;
				const XMVECTOR vectorOne = XMLoadFloat4A(&this->xmvector);
				const XMVECTOR finalVector = XMVectorNegate(vectorOne);
				SPROUT_VECTOR4_DX result;
				XMStoreFloat4A(&result.xmvector, finalVector);
				return result;
			}

			SPROUT_VECTOR4_DX operator+ () const noexcept;


			/// Free-Standing Operators for Left Handeded Operations
			friend SPROUT_VECTOR4_DX operator+ (const SPROUT_VECTOR4_DX& _firstVector, const SPROUT_VECTOR4_DX& _secondVector) noexcept;
			friend SPROUT_VECTOR4_DX operator- (const SPROUT_VECTOR4_DX& _firstVector, const SPROUT_VECTOR4_DX& _secondVector) noexcept;
			friend SPROUT_VECTOR4_DX operator* (const SPROUT_VECTOR4_DX& _firstVector, const SPROUT_VECTOR4_DX& _secondVector) noexcept;
			friend SPROUT_VECTOR4_DX operator* (const SPROUT_VECTOR4_DX& _firstVector, const float _float) noexcept;
			friend SPROUT_VECTOR4_DX operator/ (const SPROUT_VECTOR4_DX& _firstVector, const SPROUT_VECTOR4_DX& _secondVector) noexcept;
			friend SPROUT_VECTOR4_DX operator/ (const SPROUT_VECTOR4_DX& _firstVector, const float _float) noexcept;



		};


	}
}



#endif //!VECTOR4_H