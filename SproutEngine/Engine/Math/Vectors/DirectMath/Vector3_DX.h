/************************************************************************|
|						   Vector3_DX.h 								 |
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

#ifndef VECTOR3_DX_H
#define VECTOR3_DX_H

#include <DirectXMath.h>
#include <MathFunctions.h>

using namespace DirectX;

namespace SproutEngine
{
    namespace Maths
    {

        struct Quaternion;

        /* A 3-dimensional floating point vector backed by DirectXMath.

           Internal storage uses XMFLOAT3 (unaligned) for safe heap allocation
           and STL container compatibility. 

           Coordinate aliases: (x, y, z) | (u, v, s) for UVW texture coords | (r, g, b) for colour use.
        */
        struct SPROUT_VECTOR3_DX
        {
            // @brief Vector with all components set to 0 : (0, 0, 0)
            static const SPROUT_VECTOR3_DX Zero;

            // @brief Vector with all components set to 1 : (1, 1, 1)
            static const SPROUT_VECTOR3_DX One;

            // @brief Unit vector along the X axis : (1, 0, 0)
            static const SPROUT_VECTOR3_DX UnitX;

            // @brief Unit vector along the Y axis : (0, 1, 0)
            static const SPROUT_VECTOR3_DX UnitY;

            // @brief Unit vector along the Z axis : (0, 0, 1)
            static const SPROUT_VECTOR3_DX UnitZ;


            /// =========================================================
            ///                         DATA
            /// =========================================================
            union
            {
                struct { float x, y, z; };  // Spatial coordinate access
                struct { float u, v, s; };  // UVW texture coordinate access
                struct { float r, g, b; };  // Colour access
                DirectX::XMFLOAT3 xmvector; // Underlying DirectXMath storage
            };


            /// =========================================================
            ///                     CONSTRUCTORS
            /// =========================================================

            // @brief Default constructor. Always initialises to (0, 0, 0).
            SPROUT_VECTOR3_DX() noexcept : xmvector(0.0f, 0.0f, 0.0f) {}

            // @brief Scalar constructor. Sets all three components to the same value.
            // @param _singleValue Value applied to X, Y and Z.
            constexpr explicit SPROUT_VECTOR3_DX(float _singleValue) noexcept
                : xmvector(_singleValue, _singleValue, _singleValue) {}

            // @brief Component constructor. Sets X, Y and Z independently.
            // @param _xValue Value for the X component.
            // @param _yValue Value for the Y component.
            // @param _zValue Value for the Z component.
            constexpr SPROUT_VECTOR3_DX(float _xValue, float _yValue, float _zValue) noexcept
                : xmvector(_xValue, _yValue, _zValue) {}


            SPROUT_VECTOR3_DX(const SPROUT_VECTOR3_DX&) = default;
            SPROUT_VECTOR3_DX& operator=(const SPROUT_VECTOR3_DX&) = default;
            SPROUT_VECTOR3_DX(SPROUT_VECTOR3_DX&&) = default;
            SPROUT_VECTOR3_DX& operator=(SPROUT_VECTOR3_DX&&) = default;

            // @brief Implicit conversion to XMVECTOR for DirectXMath interop.
            operator XMVECTOR() const noexcept { return XMLoadFloat3(&xmvector); }

            // @brief Constructs from a raw XMVECTOR. Only X, Y, Z lanes are stored.
            SPROUT_VECTOR3_DX(FXMVECTOR _vector) noexcept
            {
                XMStoreFloat3(&xmvector, _vector);
            }

            // @brief Constructs from an aligned XMFLOAT3A.
            SPROUT_VECTOR3_DX(const XMFLOAT3A& _xmFloat) noexcept
                : xmvector(_xmFloat.x, _xmFloat.y, _xmFloat.z) {}

            // @brief Constructs from an unaligned XMFLOAT3.
            SPROUT_VECTOR3_DX(const XMFLOAT3& _xmFloat) noexcept
                : xmvector(_xmFloat.x, _xmFloat.y, _xmFloat.z) {}

            // @brief Constructs from an XMVECTORF32 constant.
            SPROUT_VECTOR3_DX(const XMVECTORF32& _xmVector32) noexcept
                : xmvector(_xmVector32.f[0], _xmVector32.f[1], _xmVector32.f[2]) {}

            // @brief Assignment from an XMVECTORF32 constant.
            SPROUT_VECTOR3_DX& operator=(const XMVECTORF32& _vector) noexcept
            {
                x = _vector.f[0]; y = _vector.f[1]; z = _vector.f[2];
                return *this;
            }


            /// =========================================================
            ///                 ASSIGNMENT OPERATORS
            /// =========================================================

            // @brief Component-wise addition assignment.
            SPROUT_VECTOR3_DX& operator+=(const SPROUT_VECTOR3_DX& _vector) noexcept;

            // @brief Component-wise subtraction assignment.
            SPROUT_VECTOR3_DX& operator-=(const SPROUT_VECTOR3_DX& _vector) noexcept;

            // @brief Component-wise multiplication assignment.
            SPROUT_VECTOR3_DX& operator*=(const SPROUT_VECTOR3_DX& _vector) noexcept;

            // @brief Component-wise division assignment.
            SPROUT_VECTOR3_DX& operator/=(const SPROUT_VECTOR3_DX& _vector) noexcept;

            // @brief Scalar multiplication assignment. Scales all components uniformly.
            // @param _scalar Scale factor.
            SPROUT_VECTOR3_DX& operator*=(float _scalar) noexcept;

            // @brief Scalar division assignment. Divides all components by _scalar.
            // @param _scalar Divisor. Asserts if _scalar == 0.
            SPROUT_VECTOR3_DX& operator/=(float _scalar) noexcept;


            /// =========================================================
            ///                 COMPARISON OPERATORS
            /// =========================================================

            // @brief Exact equality check using XMVector3Equal.
            // @note For floating-point results of arithmetic chains, prefer NearEqual.
            inline bool operator==(const SPROUT_VECTOR3_DX& _vector) const noexcept
            {
                const XMVECTOR a = XMLoadFloat3(&this->xmvector);
                const XMVECTOR b = XMLoadFloat3(&_vector.xmvector);
                return XMVector3Equal(a, b);
            }

            inline bool operator!=(const SPROUT_VECTOR3_DX& _vector) const noexcept
            {
                const XMVECTOR a = XMLoadFloat3(&this->xmvector);
                const XMVECTOR b = XMLoadFloat3(&_vector.xmvector);
                return XMVector3NotEqual(a, b);
            }

            // @brief Checks near equality within a per-component epsilon tolerance.
            /*  Use this instead of operator== when vectors have gone through
                floating point operations (normalize, lerp, arithmetic chains).
                @param _vector  Vector to compare against.
                @param _epsilon Per-component tolerance. Defaults to a tight epsilon.
            */
            inline bool NearEqual(const SPROUT_VECTOR3_DX& _vector,
                const SPROUT_VECTOR3_DX& _epsilon = SPROUT_VECTOR3_DX(EPSILON)) const noexcept
            {
                const XMVECTOR a = XMLoadFloat3(&this->xmvector);
                const XMVECTOR b = XMLoadFloat3(&_vector.xmvector);
                const XMVECTOR eps = XMLoadFloat3(&_epsilon.xmvector);
                return XMVector3NearEqual(a, b, eps);
            }


            /// =========================================================
            ///                 UNARY OPERATORS
            /// =========================================================

            // @brief Negation.
            inline SPROUT_VECTOR3_DX operator-() const noexcept
            {
                const XMVECTOR v = XMLoadFloat3(&this->xmvector);
                const XMVECTOR result = XMVectorNegate(v);
                SPROUT_VECTOR3_DX out;
                XMStoreFloat3(&out.xmvector, result);
                return out;
            }

            // @brief Unary plus (identity).
            inline SPROUT_VECTOR3_DX operator+() const noexcept { return *this; }


            /// =========================================================
            ///             FREE-STANDING BINARY OPERATORS
            /// =========================================================

            friend SPROUT_VECTOR3_DX operator+(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b) noexcept;
            friend SPROUT_VECTOR3_DX operator-(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b) noexcept;
            friend SPROUT_VECTOR3_DX operator*(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b) noexcept;
            friend SPROUT_VECTOR3_DX operator*(const SPROUT_VECTOR3_DX& _a, float _scalar)               noexcept;
            friend SPROUT_VECTOR3_DX operator*(float _scalar, const SPROUT_VECTOR3_DX& _v)               noexcept;
            friend SPROUT_VECTOR3_DX operator/(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b) noexcept;
            friend SPROUT_VECTOR3_DX operator/(const SPROUT_VECTOR3_DX& _a, float _scalar)               noexcept;


            /// =========================================================
            ///             LENGTH AND DISTANCE
            /// =========================================================

            float Length()        const noexcept;
            float LengthSquared() const noexcept;

            static float Distance(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b) noexcept;
            static float DistanceSquared(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b) noexcept;


            /// =========================================================
            ///                     NORMALISE
            /// =========================================================

            void Normalize() noexcept;
            void Normalize(SPROUT_VECTOR3_DX& _result) const noexcept;


            /// =========================================================
            ///                 VECTOR ALGEBRA
            /// =========================================================

            float               Dot(const SPROUT_VECTOR3_DX& _other) const noexcept;

            // @brief 3D cross product. Returns a vector perpendicular to both inputs.
            // @note Result is NOT a scalar — unlike the 2D cross which collapses to z.
            SPROUT_VECTOR3_DX   Cross(const SPROUT_VECTOR3_DX& _other) const noexcept;


            /// =========================================================
            ///             INTERPOLATION AND CLAMPING
            /// =========================================================

            static void             Lerp(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b, float _t, SPROUT_VECTOR3_DX& _result) noexcept;
            static SPROUT_VECTOR3_DX  Lerp(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b, float _t) noexcept;

            static void             Clamp(const SPROUT_VECTOR3_DX& _v, const SPROUT_VECTOR3_DX& _min, const SPROUT_VECTOR3_DX& _max, SPROUT_VECTOR3_DX& _result) noexcept;
            static SPROUT_VECTOR3_DX  Clamp(const SPROUT_VECTOR3_DX& _v, const SPROUT_VECTOR3_DX& _min, const SPROUT_VECTOR3_DX& _max) noexcept;

            static void             Min(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b, SPROUT_VECTOR3_DX& _result) noexcept;
            static SPROUT_VECTOR3_DX  Min(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b) noexcept;

            static void             Max(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b, SPROUT_VECTOR3_DX& _result) noexcept;
            static SPROUT_VECTOR3_DX  Max(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b) noexcept;

            static void             SmoothStep(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b, float _t, SPROUT_VECTOR3_DX& _result) noexcept;
            static SPROUT_VECTOR3_DX  SmoothStep(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b, float _t) noexcept;


            /// =========================================================
            ///             REFLECTION AND REFRACTION
            /// =========================================================

            static void             Reflect(const SPROUT_VECTOR3_DX& _incident, const SPROUT_VECTOR3_DX& _normal, SPROUT_VECTOR3_DX& _result) noexcept;
            static SPROUT_VECTOR3_DX  Reflect(const SPROUT_VECTOR3_DX& _incident, const SPROUT_VECTOR3_DX& _normal) noexcept;

            static void             Refract(const SPROUT_VECTOR3_DX& _incident, const SPROUT_VECTOR3_DX& _normal, float _refractionIndex, SPROUT_VECTOR3_DX& _result) noexcept;
            static SPROUT_VECTOR3_DX  Refract(const SPROUT_VECTOR3_DX& _incident, const SPROUT_VECTOR3_DX& _normal, float _refractionIndex) noexcept;

            // @brief Rotates this vector by a quaternion.
            static void             Transform(const SPROUT_VECTOR3_DX& _vector, const Quaternion& _quaternion, SPROUT_VECTOR3_DX& _result) noexcept;
            static SPROUT_VECTOR3_DX  Transform(const SPROUT_VECTOR3_DX& _vector, const Quaternion& _quaternion) noexcept;
        };

    } // namespace Maths
} // namespace SproutEngine

#endif // !VECTOR3_DX_H