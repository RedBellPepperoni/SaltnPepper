/************************************************************************|
|						  SPROUT_VECTOR2_GLM.h							 |
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

#ifndef VECTOR2_GLM_H
#define VECTOR2_GLM_H

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>          // length2, distance2
#include <glm/gtx/compatibility.hpp> // lerp
#include <MathFunctions.h>
#include <string>

namespace SproutEngine
{
    namespace Maths
    {
        struct Quaternion;

        /*  A 2-dimensional floating point vector backed by GLM.

            Internal storage uses glm::vec2 directly 
            Coordinate aliases: (x, y) or (u, v) for texture coordinates.
            API surface mirrors SPROUT_VECTOR2_DX exactly for alias swap compatibility.
        */
        struct SPROUT_VECTOR2_GLM
        {
            // @brief Vector with both components set to 0 : (0, 0)
            static const SPROUT_VECTOR2_GLM Zero;

            // @brief Vector with both components set to 1 : (1, 1)
            static const SPROUT_VECTOR2_GLM One;

            // @brief Unit vector along the X axis : (1, 0)
            static const SPROUT_VECTOR2_GLM UnitX;

            // @brief Unit vector along the Y axis : (0, 1)
            static const SPROUT_VECTOR2_GLM UnitY;


            /// =========================================================
            ///                         DATA
            /// =========================================================
            union
            {
                struct { float x, y; };  // Spatial coordinate access
                struct { float u, v; };  // Texture coordinate access
                glm::vec2 glmvector;     // Underlying GLM storage
            };


            /// =========================================================
            ///                     CONSTRUCTORS
            /// =========================================================

            // @brief Default Constructor : Always constructed as a Vector2_{0.0f}
            SPROUT_VECTOR2_GLM() noexcept : glmvector(0.0f, 0.0f) {}

            // @brief Scalar constructor. Sets both X and Y to the same value.
            // @param _singleValue Value applied to both components.
            constexpr explicit SPROUT_VECTOR2_GLM(float _singleValue) noexcept
                : glmvector(_singleValue, _singleValue) {}

            // @brief Component constructor. Sets X and Y independently.
            // @param _xValue Value for the X component.
            // @param _yValue Value for the Y component.
            constexpr explicit SPROUT_VECTOR2_GLM(float _xValue, float _yValue) noexcept
                : glmvector(_xValue, _yValue) {}


            SPROUT_VECTOR2_GLM(const SPROUT_VECTOR2_GLM&) = default;
            SPROUT_VECTOR2_GLM& operator=(const SPROUT_VECTOR2_GLM&) = default;

            SPROUT_VECTOR2_GLM(SPROUT_VECTOR2_GLM&&) = default;
            SPROUT_VECTOR2_GLM& operator=(SPROUT_VECTOR2_GLM&&) = default;

            // @brief Implicit conversion to glm::vec2 for GLM interop.
            operator glm::vec2() const noexcept { return glmvector; }

            // @brief Constructs from a raw glm::vec2.
            // @param _vec Source glm::vec2.
            SPROUT_VECTOR2_GLM(const glm::vec2& _vec) noexcept
                : glmvector(_vec) {}

            // @brief Constructs from a raw glm::vec2 (move).
            SPROUT_VECTOR2_GLM(glm::vec2&& _vec) noexcept
                : glmvector(std::move(_vec)) {}


            /// =========================================================
            ///                 ASSIGNMENT OPERATORS
            /// =========================================================

            // @brief Component-wise addition assignment.
            SPROUT_VECTOR2_GLM& operator+=(const SPROUT_VECTOR2_GLM& _vector) noexcept;

            // @brief Component-wise subtraction assignment.
            SPROUT_VECTOR2_GLM& operator-=(const SPROUT_VECTOR2_GLM& _vector) noexcept;

            // @brief Component-wise multiplication assignment.
            SPROUT_VECTOR2_GLM& operator*=(const SPROUT_VECTOR2_GLM& _vector) noexcept;

            // @brief Component-wise division assignment.
            SPROUT_VECTOR2_GLM& operator/=(const SPROUT_VECTOR2_GLM& _vector) noexcept;

            // @brief Scalar multiplication assignment.
            // @param _scalar Scale factor.
            SPROUT_VECTOR2_GLM& operator*=(float _scalar) noexcept;

            // @brief Scalar division assignment.
            // @param _scalar Divisor. Behaviour is undefined if _scalar == 0.
            SPROUT_VECTOR2_GLM& operator/=(float _scalar) noexcept;


            /// =========================================================
            ///                 COMPARISON OPERATORS
            /// =========================================================

            // @brief Exact equality check (component-wise ==).
            // @note For floating-point results of arithmetic chains, prefer NearEqual.
            inline bool operator==(const SPROUT_VECTOR2_GLM& _vector) const noexcept
            {
                return glmvector == _vector.glmvector;
            }

            inline bool operator!=(const SPROUT_VECTOR2_GLM& _vector) const noexcept
            {
                return glmvector != _vector.glmvector;
            }

            // @brief Checks near equality within a given epsilon tolerance.
            /*  Use this instead of operator== when vectors have gone through
                floating point operations (normalize, lerp, arithmetic chains).
                @param _vector  Vector to compare against.
                @param _epsilon Per-component tolerance. Defaults to a tight epsilon.
            */
            inline bool NearEqual(const SPROUT_VECTOR2_GLM& _vector,
                const SPROUT_VECTOR2_GLM& _epsilon = SPROUT_VECTOR2_GLM(EPSILON)) const noexcept
            {
                return glm::all(
                    glm::lessThanEqual(
                        glm::abs(glmvector - _vector.glmvector),
                        _epsilon.glmvector)
                );
            }


            /// =========================================================
            ///                 UNARY OPERATORS
            /// =========================================================

            // @brief Negation.
            SPROUT_VECTOR2_GLM operator-() const noexcept { return SPROUT_VECTOR2_GLM(-glmvector); }

            // @brief Unary plus (identity).
            SPROUT_VECTOR2_GLM operator+() const noexcept { return *this; }


            /// =========================================================
            ///             FREE-STANDING BINARY OPERATORS
            /// =========================================================

            friend SPROUT_VECTOR2_GLM operator+(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b) noexcept;
            friend SPROUT_VECTOR2_GLM operator-(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b) noexcept;
            friend SPROUT_VECTOR2_GLM operator*(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b) noexcept;
            friend SPROUT_VECTOR2_GLM operator*(const SPROUT_VECTOR2_GLM& _a, float _scalar)                noexcept;
            friend SPROUT_VECTOR2_GLM operator*(float _scalar, const SPROUT_VECTOR2_GLM& _v)               noexcept;
            friend SPROUT_VECTOR2_GLM operator/(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b) noexcept;
            friend SPROUT_VECTOR2_GLM operator/(const SPROUT_VECTOR2_GLM& _a, float _scalar)               noexcept;


            /// =========================================================
            ///             LENGTH AND DISTANCE
            /// =========================================================

            float Length() const noexcept;
            float LengthSquared() const noexcept;

            static float Distance(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b) noexcept;
            static float DistanceSquared(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b) noexcept;


            /// =========================================================
            ///                 NORMALISE
            /// =========================================================

            inline void Normalize() noexcept
            {
                glmvector = glm::normalize(glmvector);
            }

            void Normalize(SPROUT_VECTOR2_GLM& _result) const noexcept;


            /// =========================================================
            ///                 VECTOR ALGEBRA
            /// =========================================================

            // @brief Dot product.
            inline float Dot(const SPROUT_VECTOR2_GLM& _other) const noexcept
            {
                return glm::dot(glmvector, _other.glmvector);
            }

            // @brief 2D cross product (scalar z-component of the 3D cross).
            float Cross(const SPROUT_VECTOR2_GLM& _other) const noexcept;


            /// =========================================================
            ///             INTERPOLATION AND CLAMPING
            /// =========================================================

            static void Lerp(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b, float _t, SPROUT_VECTOR2_GLM& _result) noexcept;
            static SPROUT_VECTOR2_GLM Lerp(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b, float _t) noexcept;

            static void Clamp(const SPROUT_VECTOR2_GLM& _v, const SPROUT_VECTOR2_GLM& _min, const SPROUT_VECTOR2_GLM& _max, SPROUT_VECTOR2_GLM& _result) noexcept;
            static SPROUT_VECTOR2_GLM Clamp(const SPROUT_VECTOR2_GLM& _v, const SPROUT_VECTOR2_GLM& _min, const SPROUT_VECTOR2_GLM& _max) noexcept;

            static void Min(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b, SPROUT_VECTOR2_GLM& _result) noexcept;
            static SPROUT_VECTOR2_GLM Min(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b) noexcept;

            static void Max(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b, SPROUT_VECTOR2_GLM& _result) noexcept;
            static SPROUT_VECTOR2_GLM Max(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b) noexcept;

            static void SmoothStep(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b, float _t, SPROUT_VECTOR2_GLM& _result) noexcept;
            static SPROUT_VECTOR2_GLM SmoothStep(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b, float _t) noexcept;


            /// =========================================================
            ///             REFLECTION AND REFRACTION
            /// =========================================================

            static void Reflect(const SPROUT_VECTOR2_GLM& _incident, const SPROUT_VECTOR2_GLM& _normal, SPROUT_VECTOR2_GLM& _result) noexcept;
            static SPROUT_VECTOR2_GLM Reflect(const SPROUT_VECTOR2_GLM& _incident, const SPROUT_VECTOR2_GLM& _normal) noexcept;

            static void Refract(const SPROUT_VECTOR2_GLM& _incident, const SPROUT_VECTOR2_GLM& _normal, float _refractionIndex, SPROUT_VECTOR2_GLM& _result) noexcept;
            static SPROUT_VECTOR2_GLM Refract(const SPROUT_VECTOR2_GLM& _incident, const SPROUT_VECTOR2_GLM& _normal, float _refractionIndex) noexcept;

            // Note: Transform(vector, quaternion) is intentionally omitted for Vector2.
            // A quaternion rotation is a 3D operation; promoting a vec2 to vec3,
            // rotating, then truncating gives mathematically ambiguous results.
            // Use Vector3::Transform for quaternion transforms.
        };

    } // namespace Maths
} // namespace SproutEngine

#endif // !VECTOR2_GLM_H