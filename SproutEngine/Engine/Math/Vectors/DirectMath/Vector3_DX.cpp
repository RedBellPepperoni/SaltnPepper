/************************************************************************|
|						   Vector3_DX.cpp								 |
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

#include <Vectors/DirectMath/Vector3_DX.h>
#include <Quaternion.h>
#include <../Core/EngineDefines.h>

namespace SproutEngine::Maths
{
    /// =========================================================
    ///                     STATIC CONSTANTS
    /// =========================================================

    const SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::Zero = SPROUT_VECTOR3_DX{ 0.0f, 0.0f, 0.0f };
    const SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::One = SPROUT_VECTOR3_DX{ 1.0f, 1.0f, 1.0f };
    const SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::UnitX = SPROUT_VECTOR3_DX{ 1.0f, 0.0f, 0.0f };
    const SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::UnitY = SPROUT_VECTOR3_DX{ 0.0f, 1.0f, 0.0f };
    const SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::UnitZ = SPROUT_VECTOR3_DX{ 0.0f, 0.0f, 1.0f };


    /// =========================================================
    ///                 ASSIGNMENT OPERATORS
    /// =========================================================

    inline SPROUT_VECTOR3_DX& SPROUT_VECTOR3_DX::operator+=(const SPROUT_VECTOR3_DX& _vector) noexcept
    {
        const XMVECTOR a = XMLoadFloat3(&this->xmvector);
        const XMVECTOR b = XMLoadFloat3(&_vector.xmvector);
        const XMVECTOR result = XMVectorAdd(a, b);
        XMStoreFloat3(&this->xmvector, result);
        return *this;
    }

    inline SPROUT_VECTOR3_DX& SPROUT_VECTOR3_DX::operator-=(const SPROUT_VECTOR3_DX& _vector) noexcept
    {
        const XMVECTOR a = XMLoadFloat3(&this->xmvector);
        const XMVECTOR b = XMLoadFloat3(&_vector.xmvector);
        const XMVECTOR result = XMVectorSubtract(a, b);
        XMStoreFloat3(&this->xmvector, result);
        return *this;
    }

    inline SPROUT_VECTOR3_DX& SPROUT_VECTOR3_DX::operator*=(const SPROUT_VECTOR3_DX& _vector) noexcept
    {
        const XMVECTOR a = XMLoadFloat3(&this->xmvector);
        const XMVECTOR b = XMLoadFloat3(&_vector.xmvector);
        const XMVECTOR result = XMVectorMultiply(a, b);
        XMStoreFloat3(&this->xmvector, result);
        return *this;
    }

    inline SPROUT_VECTOR3_DX& SPROUT_VECTOR3_DX::operator/=(const SPROUT_VECTOR3_DX& _vector) noexcept
    {
        const XMVECTOR a = XMLoadFloat3(&this->xmvector);
        const XMVECTOR b = XMLoadFloat3(&_vector.xmvector);
        const XMVECTOR result = XMVectorDivide(a, b);
        XMStoreFloat3(&this->xmvector, result);
        return *this;
    }

    inline SPROUT_VECTOR3_DX& SPROUT_VECTOR3_DX::operator*=(float _scalar) noexcept
    {
        const XMVECTOR a = XMLoadFloat3(&this->xmvector);
        const XMVECTOR result = XMVectorScale(a, _scalar);
        XMStoreFloat3(&this->xmvector, result);
        return *this;
    }

    inline SPROUT_VECTOR3_DX& SPROUT_VECTOR3_DX::operator/=(float _scalar) noexcept
    {
        SPROUT_ASSERT(_scalar != 0.0f);
        const XMVECTOR a = XMLoadFloat3(&this->xmvector);
        const XMVECTOR result = XMVectorScale(a, 1.0f / _scalar);
        XMStoreFloat3(&this->xmvector, result);
        return *this;
    }


    /// =========================================================
    ///             LENGTH AND DISTANCE
    /// =========================================================

    float SPROUT_VECTOR3_DX::Length() const noexcept
    {
        const XMVECTOR v = XMLoadFloat3(&this->xmvector);
        return XMVectorGetX(XMVector3LengthEst(v));
    }

    float SPROUT_VECTOR3_DX::LengthSquared() const noexcept
    {
        const XMVECTOR v = XMLoadFloat3(&this->xmvector);
        return XMVectorGetX(XMVector3LengthSq(v));
    }

    float SPROUT_VECTOR3_DX::Distance(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b) noexcept
    {
        const XMVECTOR va = XMLoadFloat3(&_a.xmvector);
        const XMVECTOR vb = XMLoadFloat3(&_b.xmvector);
        const XMVECTOR diff = XMVectorSubtract(vb, va);
        return XMVectorGetX(XMVector3LengthEst(diff));
    }

    float SPROUT_VECTOR3_DX::DistanceSquared(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b) noexcept
    {
        const XMVECTOR va = XMLoadFloat3(&_a.xmvector);
        const XMVECTOR vb = XMLoadFloat3(&_b.xmvector);
        const XMVECTOR diff = XMVectorSubtract(vb, va);
        return XMVectorGetX(XMVector3LengthSq(diff));
    }


    /// =========================================================
    ///                     NORMALISE
    /// =========================================================

    void SPROUT_VECTOR3_DX::Normalize() noexcept
    {
        const XMVECTOR v = XMLoadFloat3(&this->xmvector);
        XMStoreFloat3(&this->xmvector, XMVector3Normalize(v));
    }

    void SPROUT_VECTOR3_DX::Normalize(SPROUT_VECTOR3_DX& _result) const noexcept
    {
        // BUG FIX: was XMVector2Normalize — must be XMVector3Normalize
        const XMVECTOR v = XMLoadFloat3(&this->xmvector);
        XMStoreFloat3(&_result.xmvector, XMVector3Normalize(v));
    }


    /// =========================================================
    ///                 VECTOR ALGEBRA
    /// =========================================================

    float SPROUT_VECTOR3_DX::Dot(const SPROUT_VECTOR3_DX& _other) const noexcept
    {
        const XMVECTOR a = XMLoadFloat3(&this->xmvector);
        const XMVECTOR b = XMLoadFloat3(&_other.xmvector);
        return XMVectorGetX(XMVector3Dot(a, b));
    }

    // BUG FIX: Cross must return SPROUT_VECTOR3_DX, not float.
    // The 3D cross product produces a perpendicular vector, not a scalar.
    SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::Cross(const SPROUT_VECTOR3_DX& _other) const noexcept
    {
        const XMVECTOR a = XMLoadFloat3(&this->xmvector);
        const XMVECTOR b = XMLoadFloat3(&_other.xmvector);
        SPROUT_VECTOR3_DX result;
        XMStoreFloat3(&result.xmvector, XMVector3Cross(a, b));
        return result;
    }


    /// =========================================================
    ///             INTERPOLATION AND CLAMPING
    /// =========================================================

    void SPROUT_VECTOR3_DX::Lerp(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b, float _t, SPROUT_VECTOR3_DX& _result) noexcept
    {
        const XMVECTOR va = XMLoadFloat3(&_a.xmvector);
        const XMVECTOR vb = XMLoadFloat3(&_b.xmvector);
        XMStoreFloat3(&_result.xmvector, XMVectorLerp(va, vb, _t));
    }

    SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::Lerp(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b, float _t) noexcept
    {
        SPROUT_VECTOR3_DX result;
        Lerp(_a, _b, _t, result);
        return result;
    }

    // BUG FIX: was passing SPROUT_VECTOR3_DX refs to XMVectorClamp instead of XMVECTOR locals.
    void SPROUT_VECTOR3_DX::Clamp(const SPROUT_VECTOR3_DX& _v, const SPROUT_VECTOR3_DX& _min, const SPROUT_VECTOR3_DX& _max, SPROUT_VECTOR3_DX& _result) noexcept
    {
        const XMVECTOR vv = XMLoadFloat3(&_v.xmvector);
        const XMVECTOR vmi = XMLoadFloat3(&_min.xmvector);
        const XMVECTOR vma = XMLoadFloat3(&_max.xmvector);
        XMStoreFloat3(&_result.xmvector, XMVectorClamp(vv, vmi, vma));
    }

    SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::Clamp(const SPROUT_VECTOR3_DX& _v, const SPROUT_VECTOR3_DX& _min, const SPROUT_VECTOR3_DX& _max) noexcept
    {
        SPROUT_VECTOR3_DX result;
        Clamp(_v, _min, _max, result);
        return result;
    }

    void SPROUT_VECTOR3_DX::Min(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b, SPROUT_VECTOR3_DX& _result) noexcept
    {
        const XMVECTOR va = XMLoadFloat3(&_a.xmvector);
        const XMVECTOR vb = XMLoadFloat3(&_b.xmvector);
        XMStoreFloat3(&_result.xmvector, XMVectorMin(va, vb));
    }

    SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::Min(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b) noexcept
    {
        SPROUT_VECTOR3_DX result;
        Min(_a, _b, result);
        return result;
    }

    void SPROUT_VECTOR3_DX::Max(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b, SPROUT_VECTOR3_DX& _result) noexcept
    {
        const XMVECTOR va = XMLoadFloat3(&_a.xmvector);
        const XMVECTOR vb = XMLoadFloat3(&_b.xmvector);
        XMStoreFloat3(&_result.xmvector, XMVectorMax(va, vb));
    }

    SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::Max(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b) noexcept
    {
        SPROUT_VECTOR3_DX result;
        Max(_a, _b, result);
        return result;
    }

    void SPROUT_VECTOR3_DX::SmoothStep(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b, float _t, SPROUT_VECTOR3_DX& _result) noexcept
    {
        _t = (_t > 1.0f) ? 1.0f : ((_t < 0.0f) ? 0.0f : _t);
        _t = _t * _t * (3.f - 2.f * _t);
        const XMVECTOR va = XMLoadFloat3(&_a.xmvector);
        const XMVECTOR vb = XMLoadFloat3(&_b.xmvector);
        XMStoreFloat3(&_result.xmvector, XMVectorLerp(va, vb, _t));
    }

    SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::SmoothStep(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b, float _t) noexcept
    {
        SPROUT_VECTOR3_DX result;
        SmoothStep(_a, _b, _t, result);
        return result;
    }


    /// =========================================================
    ///             REFLECTION AND REFRACTION
    /// =========================================================

    void SPROUT_VECTOR3_DX::Reflect(const SPROUT_VECTOR3_DX& _incident, const SPROUT_VECTOR3_DX& _normal, SPROUT_VECTOR3_DX& _result) noexcept
    {
        const XMVECTOR i = XMLoadFloat3(&_incident.xmvector);
        const XMVECTOR n = XMLoadFloat3(&_normal.xmvector);
        XMStoreFloat3(&_result.xmvector, XMVector3Reflect(i, n));
    }

    SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::Reflect(const SPROUT_VECTOR3_DX& _incident, const SPROUT_VECTOR3_DX& _normal) noexcept
    {
        SPROUT_VECTOR3_DX result;
        Reflect(_incident, _normal, result);
        return result;
    }

    void SPROUT_VECTOR3_DX::Refract(const SPROUT_VECTOR3_DX& _incident, const SPROUT_VECTOR3_DX& _normal, float _refractionIndex, SPROUT_VECTOR3_DX& _result) noexcept
    {
        const XMVECTOR i = XMLoadFloat3(&_incident.xmvector);
        const XMVECTOR n = XMLoadFloat3(&_normal.xmvector);
        XMStoreFloat3(&_result.xmvector, XMVector3Refract(i, n, _refractionIndex));
    }

    SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::Refract(const SPROUT_VECTOR3_DX& _incident, const SPROUT_VECTOR3_DX& _normal, float _refractionIndex) noexcept
    {
        SPROUT_VECTOR3_DX result;
        Refract(_incident, _normal, _refractionIndex, result);
        return result;
    }

    void SPROUT_VECTOR3_DX::Transform(const SPROUT_VECTOR3_DX& _vector, const Quaternion& _quaternion, SPROUT_VECTOR3_DX& _result) noexcept
    {
        const XMVECTOR v = XMLoadFloat3(&_vector.xmvector);
        const XMVECTOR q = XMLoadFloat4(&_quaternion);
        XMStoreFloat3(&_result.xmvector, XMVector3Rotate(v, q));
    }

    SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::Transform(const SPROUT_VECTOR3_DX& _vector, const Quaternion& _quaternion) noexcept
    {
        SPROUT_VECTOR3_DX result;
        Transform(_vector, _quaternion, result);
        return result;
    }


    /// =========================================================
    ///             FREE-STANDING BINARY OPERATORS
    /// =========================================================

    SPROUT_VECTOR3_DX operator+(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b) noexcept
    {
        SPROUT_VECTOR3_DX out;
        XMStoreFloat3(&out.xmvector, XMVectorAdd(XMLoadFloat3(&_a.xmvector), XMLoadFloat3(&_b.xmvector)));
        return out;
    }

    SPROUT_VECTOR3_DX operator-(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b) noexcept
    {
        SPROUT_VECTOR3_DX out;
        XMStoreFloat3(&out.xmvector, XMVectorSubtract(XMLoadFloat3(&_a.xmvector), XMLoadFloat3(&_b.xmvector)));
        return out;
    }

    SPROUT_VECTOR3_DX operator*(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b) noexcept
    {
        SPROUT_VECTOR3_DX out;
        XMStoreFloat3(&out.xmvector, XMVectorMultiply(XMLoadFloat3(&_a.xmvector), XMLoadFloat3(&_b.xmvector)));
        return out;
    }

    SPROUT_VECTOR3_DX operator*(const SPROUT_VECTOR3_DX& _a, float _scalar) noexcept
    {
        SPROUT_VECTOR3_DX out;
        XMStoreFloat3(&out.xmvector, XMVectorScale(XMLoadFloat3(&_a.xmvector), _scalar));
        return out;
    }

    // Commutative scalar multiply: 2.0f * vec == vec * 2.0f
    SPROUT_VECTOR3_DX operator*(float _scalar, const SPROUT_VECTOR3_DX& _v) noexcept
    {
        return _v * _scalar;
    }

    SPROUT_VECTOR3_DX operator/(const SPROUT_VECTOR3_DX& _a, const SPROUT_VECTOR3_DX& _b) noexcept
    {
        SPROUT_VECTOR3_DX out;
        XMStoreFloat3(&out.xmvector, XMVectorDivide(XMLoadFloat3(&_a.xmvector), XMLoadFloat3(&_b.xmvector)));
        return out;
    }

    SPROUT_VECTOR3_DX operator/(const SPROUT_VECTOR3_DX& _a, float _scalar) noexcept
    {
        SPROUT_VECTOR3_DX out;
        XMStoreFloat3(&out.xmvector, XMVectorScale(XMLoadFloat3(&_a.xmvector), 1.0f / _scalar));
        return out;
    }

} // namespace SproutEngine::Maths