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

#include <Vectors/VECTOR2_GLM.h>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>          // glm::length2, glm::distance2
#include <glm/gtx/compatibility.hpp> // glm::lerp (component-wise)


namespace SproutEngine::Maths
{
    /// =========================================================
    ///                     STATIC CONSTANTS
    /// =========================================================

    const SPROUT_VECTOR2_GLM SPROUT_VECTOR2_GLM::Zero = SPROUT_VECTOR2_GLM{ 0.f, 0.f };
    const SPROUT_VECTOR2_GLM SPROUT_VECTOR2_GLM::One = SPROUT_VECTOR2_GLM{ 1.f, 1.f };
    const SPROUT_VECTOR2_GLM SPROUT_VECTOR2_GLM::UnitX = SPROUT_VECTOR2_GLM{ 1.f, 0.f };
    const SPROUT_VECTOR2_GLM SPROUT_VECTOR2_GLM::UnitY = SPROUT_VECTOR2_GLM{ 0.f, 1.f };


    /// =========================================================
    ///                 ASSIGNMENT OPERATORS
    /// =========================================================

    inline SPROUT_VECTOR2_GLM& SPROUT_VECTOR2_GLM::operator+=(const SPROUT_VECTOR2_GLM& _vector) noexcept
    {
        glmvector += _vector.glmvector;
        return *this;
    }

    inline SPROUT_VECTOR2_GLM& SPROUT_VECTOR2_GLM::operator-=(const SPROUT_VECTOR2_GLM& _vector) noexcept
    {
        glmvector -= _vector.glmvector;
        return *this;
    }

    inline SPROUT_VECTOR2_GLM& SPROUT_VECTOR2_GLM::operator*=(const SPROUT_VECTOR2_GLM& _vector) noexcept
    {
        glmvector *= _vector.glmvector;
        return *this;
    }

    inline SPROUT_VECTOR2_GLM& SPROUT_VECTOR2_GLM::operator/=(const SPROUT_VECTOR2_GLM& _vector) noexcept
    {
        glmvector /= _vector.glmvector;
        return *this;
    }

    inline SPROUT_VECTOR2_GLM& SPROUT_VECTOR2_GLM::operator*=(float _scalar) noexcept
    {
        glmvector *= _scalar;
        return *this;
    }

    inline SPROUT_VECTOR2_GLM& SPROUT_VECTOR2_GLM::operator/=(float _scalar) noexcept
    {
        glmvector /= _scalar;
        return *this;
    }


    /// =========================================================
    ///             LENGTH AND DISTANCE
    /// =========================================================

    float SPROUT_VECTOR2_GLM::Length() const noexcept
    {
        return glm::length(glmvector);
    }

    float SPROUT_VECTOR2_GLM::LengthSquared() const noexcept
    {
        return glm::length2(glmvector); // gtx/norm.hpp 
    }

    float SPROUT_VECTOR2_GLM::Distance(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b) noexcept
    {
        return glm::distance(_a.glmvector, _b.glmvector);
    }

    float SPROUT_VECTOR2_GLM::DistanceSquared(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b) noexcept
    {
        return glm::distance2(_a.glmvector, _b.glmvector); // gtx/norm.hpp
    }


    /// =========================================================
    ///                     NORMALISE
    /// =========================================================

    inline void SPROUT_VECTOR2_GLM::Normalize(SPROUT_VECTOR2_GLM& _result) const noexcept
    {
        _result.glmvector = glm::normalize(glmvector);
    }


    /// =========================================================
    ///                 VECTOR ALGEBRA
    /// =========================================================

    // 2D cross product: returns the scalar z-component of the 3D cross product.
    // Equivalent to: (a.x * b.y) - (a.y * b.x)
    
    // matching XMVector2Cross behaviour.
    inline float SPROUT_VECTOR2_GLM::Cross(const SPROUT_VECTOR2_GLM& _other) const noexcept
    {
        return (glmvector.x * _other.glmvector.y) - (glmvector.y * _other.glmvector.x);
    }


    /// =========================================================
    ///             INTERPOLATION AND CLAMPING
    /// =========================================================

    // glm::mix is GLM's lerp: result = a + t*(b-a), unclamped.
    //  XMVectorLerp behaviour (t is NOT clamped here).
    inline void SPROUT_VECTOR2_GLM::Lerp(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b, float _t, SPROUT_VECTOR2_GLM& _result) noexcept
    {
        _result.glmvector = glm::mix(_a.glmvector, _b.glmvector, _t);
    }

    inline SPROUT_VECTOR2_GLM SPROUT_VECTOR2_GLM::Lerp(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b, float _t) noexcept
    {
        SPROUT_VECTOR2_GLM result;
        Lerp(_a, _b, _t, result);
        return result;
    }

    inline void SPROUT_VECTOR2_GLM::Clamp(const SPROUT_VECTOR2_GLM& _v, const SPROUT_VECTOR2_GLM& _min, const SPROUT_VECTOR2_GLM& _max, SPROUT_VECTOR2_GLM& _result) noexcept
    {
        _result.glmvector = glm::clamp(_v.glmvector, _min.glmvector, _max.glmvector);
    }

    inline SPROUT_VECTOR2_GLM SPROUT_VECTOR2_GLM::Clamp(const SPROUT_VECTOR2_GLM& _v, const SPROUT_VECTOR2_GLM& _min, const SPROUT_VECTOR2_GLM& _max) noexcept
    {
        SPROUT_VECTOR2_GLM result;
        Clamp(_v, _min, _max, result);
        return result;
    }

    inline void SPROUT_VECTOR2_GLM::Min(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b, SPROUT_VECTOR2_GLM& _result) noexcept
    {
        _result.glmvector = glm::min(_a.glmvector, _b.glmvector);
    }

    inline SPROUT_VECTOR2_GLM SPROUT_VECTOR2_GLM::Min(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b) noexcept
    {
        SPROUT_VECTOR2_GLM result;
        Min(_a, _b, result);
        return result;
    }

    inline void SPROUT_VECTOR2_GLM::Max(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b, SPROUT_VECTOR2_GLM& _result) noexcept
    {
        _result.glmvector = glm::max(_a.glmvector, _b.glmvector);
    }

    inline SPROUT_VECTOR2_GLM SPROUT_VECTOR2_GLM::Max(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b) noexcept
    {
        SPROUT_VECTOR2_GLM result;
        Max(_a, _b, result);
        return result;
    }

    // SmoothStep: clamps t to [0,1], applies Hermite curve t*t*(3-2t), then lerps.
   
    inline void SPROUT_VECTOR2_GLM::SmoothStep(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b, float _t, SPROUT_VECTOR2_GLM& _result) noexcept
    {
        _t = (_t > 1.0f) ? 1.0f : ((_t < 0.0f) ? 0.0f : _t);
        _t = _t * _t * (3.f - 2.f * _t);
        _result.glmvector = glm::mix(_a.glmvector, _b.glmvector, _t);
    }

    inline SPROUT_VECTOR2_GLM SPROUT_VECTOR2_GLM::SmoothStep(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b, float _t) noexcept
    {
        SPROUT_VECTOR2_GLM result;
        SmoothStep(_a, _b, _t, result);
        return result;
    }


    /// =========================================================
    ///             REFLECTION AND REFRACTION
    /// =========================================================

    void SPROUT_VECTOR2_GLM::Reflect(const SPROUT_VECTOR2_GLM& _incident, const SPROUT_VECTOR2_GLM& _normal, SPROUT_VECTOR2_GLM& _result) noexcept
    {
        // glm::reflect: I - 2*dot(N,I)*N  
        _result.glmvector = glm::reflect(_incident.glmvector, _normal.glmvector);
    }

    SPROUT_VECTOR2_GLM SPROUT_VECTOR2_GLM::Reflect(const SPROUT_VECTOR2_GLM& _incident, const SPROUT_VECTOR2_GLM& _normal) noexcept
    {
        SPROUT_VECTOR2_GLM result;
        Reflect(_incident, _normal, result);
        return result;
    }

    void SPROUT_VECTOR2_GLM::Refract(const SPROUT_VECTOR2_GLM& _incident, const SPROUT_VECTOR2_GLM& _normal, float _refractionIndex, SPROUT_VECTOR2_GLM& _result) noexcept
    {
        
        _result.glmvector = glm::refract(_incident.glmvector, _normal.glmvector, _refractionIndex);
    }

    SPROUT_VECTOR2_GLM SPROUT_VECTOR2_GLM::Refract(const SPROUT_VECTOR2_GLM& _incident, const SPROUT_VECTOR2_GLM& _normal, float _refractionIndex) noexcept
    {
        SPROUT_VECTOR2_GLM result;
        Refract(_incident, _normal, _refractionIndex, result);
        return result;
    }


    /// =========================================================
    ///             FREE-STANDING BINARY OPERATORS
    /// =========================================================

    SPROUT_VECTOR2_GLM operator+(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b) noexcept
    {
        return SPROUT_VECTOR2_GLM(_a.glmvector + _b.glmvector);
    }

    SPROUT_VECTOR2_GLM operator-(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b) noexcept
    {
        return SPROUT_VECTOR2_GLM(_a.glmvector - _b.glmvector);
    }

    SPROUT_VECTOR2_GLM operator*(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b) noexcept
    {
        return SPROUT_VECTOR2_GLM(_a.glmvector * _b.glmvector);
    }

    SPROUT_VECTOR2_GLM operator*(const SPROUT_VECTOR2_GLM& _a, float _scalar) noexcept
    {
        return SPROUT_VECTOR2_GLM(_a.glmvector * _scalar);
    }

    SPROUT_VECTOR2_GLM operator*(float _scalar, const SPROUT_VECTOR2_GLM& _v) noexcept
    {
        return _v * _scalar;
    }

    SPROUT_VECTOR2_GLM operator/(const SPROUT_VECTOR2_GLM& _a, const SPROUT_VECTOR2_GLM& _b) noexcept
    {
        return SPROUT_VECTOR2_GLM(_a.glmvector / _b.glmvector);
    }

    SPROUT_VECTOR2_GLM operator/(const SPROUT_VECTOR2_GLM& _a, float _scalar) noexcept
    {
        return SPROUT_VECTOR2_GLM(_a.glmvector / _scalar);
    }

} // namespace SproutEngine::Maths