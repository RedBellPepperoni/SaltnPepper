/************************************************************************|
|							     Vector2.cpp						     |
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


#include <Math/Vectors/Vector2.hpp>
#include <Math/Quaternion.hpp>
#include <Core/EngineDefines.hpp>
#include <Utilities/Logging/Log.hpp>


namespace SproutEngine::Maths
{
	/// Vector 2 Stuff


	const Vector2 Vector2::Zero  = Vector2{ 0.f, 0.f };
	const Vector2 Vector2::One   = Vector2{ 1.f, 1.f };
	const Vector2 Vector2::UnitX = Vector2{ 1.f, 0.f };
	const Vector2 Vector2::UnitY = Vector2{ 0.f, 1.f };


	inline Vector2& Vector2::operator+=(const Vector2& _vector) noexcept
	{
		using namespace DirectX;

		const XMVECTOR thisVector = XMLoadFloat2A(this);
		const XMVECTOR inVector = XMLoadFloat2A(&_vector);
		const XMVECTOR finalVector = XMVectorAdd(thisVector, inVector);

		XMStoreFloat2A(this, finalVector);
		return *this;
	}

	inline Vector2& Vector2::operator-=(const Vector2& _vector) noexcept
	{
		using namespace DirectX;

		const XMVECTOR thisVector = XMLoadFloat2A(this);
		const XMVECTOR inVector = XMLoadFloat2A(&_vector);
		const XMVECTOR finalVector = XMVectorSubtract(thisVector, inVector);

		XMStoreFloat2A(this, finalVector);
		return *this;
	}

	inline Vector2& Vector2::operator*=(const Vector2& _vector) noexcept
	{
		using namespace DirectX;

		const XMVECTOR thisVector = XMLoadFloat2A(this);
		const XMVECTOR inVector = XMLoadFloat2A(&_vector);
		const XMVECTOR finalVector = XMVectorMultiply(thisVector, inVector);

		XMStoreFloat2A(this, finalVector);
		return *this;
	}

	// Questionable if vector division is gonna be used 
	// But using an operator overload anyway
	inline Vector2& Vector2::operator/=(const Vector2& _vector) noexcept
	{
		using namespace DirectX;

		const XMVECTOR thisVector = XMLoadFloat2A(this);
		const XMVECTOR inVector = XMLoadFloat2A(&_vector);
		const XMVECTOR finalVector = XMVectorDivide(thisVector, inVector);

		XMStoreFloat2A(this, finalVector);
		return *this;
	}

	

	inline Vector2& Vector2::operator*=(const float _scalar) noexcept
	{
		using namespace DirectX;

		const XMVECTOR thisVector = XMLoadFloat2A(this);
		const XMVECTOR finalVector = XMVectorScale(thisVector, _scalar);

		XMStoreFloat2A(this, finalVector);
		return *this;
	}

	inline Vector2& Vector2::operator/=(const float _scalar) noexcept
	{
		using namespace DirectX;

		// Check Divide by Zero Edge Case
		SPROUT_ASSERT(_scalar != 0.0f);

		const XMVECTOR thisVector = XMLoadFloat2A(this);
		const XMVECTOR finalVector = XMVectorScale(thisVector, 1.0f / _scalar);

		XMStoreFloat2A(this, finalVector);
		return *this;
	}


	
	inline bool Vector2::operator==(const Vector2& _vector) const noexcept
	{
		using namespace DirectX;

		const XMVECTOR thisVector = XMLoadFloat2A(this);
		const XMVECTOR inVector = XMLoadFloat2A(&_vector);
		return XMVector2Equal(thisVector, inVector);
	}

	inline bool Vector2::operator!=(const Vector2& _vector) const noexcept
	{
		using namespace DirectX;

		const XMVECTOR thisVector = XMLoadFloat2A(this);
		const XMVECTOR inVector = XMLoadFloat2A(&_vector);
		return XMVector2NotEqual(thisVector, inVector);
	}

	
	 
	Vector2 Vector2::operator-() const noexcept
	{
		return Vector2{ -this->x,-this->y };
	}

	Vector2 Vector2::operator+() const noexcept
	{
		return *this;
	}

	
	float Vector2::Length() const noexcept
	{
		using namespace DirectX;
		const XMVECTOR thisVector = XMLoadFloat2A(this);
		const XMVECTOR finalVector = XMVector2LengthEst(thisVector);
		return XMVectorGetX(finalVector);
	}

	float Vector2::LengthSquared() const noexcept
	{
		using namespace DirectX;
		const XMVECTOR thisVector = XMLoadFloat2A(this);
		const XMVECTOR finalVector = XMVector2LengthSq(thisVector);
		return XMVectorGetX(finalVector);
	}

	float Vector2::Distance(const Vector2& _firstVector, const Vector2& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR minVector = XMLoadFloat2A(&_firstVector);
		const XMVECTOR maxVector = XMLoadFloat2A(&_secondVector);
		const XMVECTOR vectorSubtract = XMVectorSubtract(maxVector, minVector);
		const XMVECTOR finalVector = XMVector2LengthEst(vectorSubtract);
		return XMVectorGetX(finalVector);
	}

	float Vector2::DistanceSquared(const Vector2& _firstVector, const Vector2& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR minVector = XMLoadFloat2A(&_firstVector);
		const XMVECTOR maxVector = XMLoadFloat2A(&_secondVector);
		const XMVECTOR vectorSubtract = XMVectorSubtract(maxVector, minVector);
		const XMVECTOR finalVector = XMVector2LengthSq(vectorSubtract);
		return XMVectorGetX(finalVector);
		
	}

	inline void Vector2::Normalize() noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorThis = XMLoadFloat2A(this);
		const XMVECTOR normalizedVector = XMVector2Normalize(vectorThis);
		XMStoreFloat2A(this, normalizedVector);
	}

	inline void Vector2::Normalize(Vector2& _result) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorThis = XMLoadFloat2A(this);
		const XMVECTOR normalizedVector = XMVector2Normalize(vectorThis);
		XMStoreFloat2A(&_result, normalizedVector);
	}

	inline float Vector2::Dot(const Vector2& _otherVector) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR thisvector = XMLoadFloat2A(this);
		const XMVECTOR otherVector = XMLoadFloat2A(&_otherVector);
		const XMVECTOR dotVector = XMVector2Dot(thisvector, otherVector);
		return XMVectorGetX(dotVector);
	}

	inline float Vector2::Cross(const Vector2& _otherVector) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR thisvector = XMLoadFloat2A(this);
		const XMVECTOR otherVector = XMLoadFloat2A(&_otherVector);
		const XMVECTOR crossVector = XMVector2Cross(thisvector, otherVector);
		return XMVectorGetX(crossVector);
	}

	inline void Vector2::Lerp(const Vector2& _vectorOne, const Vector2& _vectorTwo, float _lerpFactor, Vector2& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat2A(&_vectorOne);
		const XMVECTOR vectorTwo = XMLoadFloat2A(&_vectorTwo);
		const XMVECTOR lerpedVector = XMVectorLerp(vectorOne, vectorTwo, _lerpFactor);
		XMStoreFloat2A(&_result, lerpedVector);
	}

	inline Vector2 Vector2::Lerp(const Vector2& _vectorOne, const Vector2& _vectorTwo, float _lerpFactor) noexcept
	{
		Vector2 result;
		Lerp(_vectorOne,_vectorTwo,_lerpFactor,result);
		return result;
	}

	inline void Vector2::Clamp(const Vector2& _vector, const Vector2& _vectorMin, const Vector2& _vectorMax, Vector2& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vector = XMLoadFloat2A(&_vector);
		const XMVECTOR vectorMin = XMLoadFloat2A(&_vectorMin);
		const XMVECTOR vectorMax = XMLoadFloat2A(&_vectorMax);
		const XMVECTOR clampedVector = XMVectorClamp(_vector, _vectorMin, _vectorMax);
		XMStoreFloat2A(&_result, clampedVector);
	}

	inline Vector2 Vector2::Clamp(const Vector2& _vector, const Vector2& _vectorMin, const Vector2& _vectorMax) noexcept
	{
		Vector2 result;
		Clamp(_vector,_vectorMin,_vectorMax,result);
		return result;
	}


	inline void Vector2::Min(const Vector2& _vectorOne, const Vector2& _vectorTwo, Vector2& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat2A(&_vectorOne);
		const XMVECTOR vectorTwo = XMLoadFloat2A(&_vectorTwo);
		const XMVECTOR minVector = XMVectorMin(vectorOne, vectorTwo);
		XMStoreFloat2A(&_result, minVector);
	}

	inline Vector2 Vector2::Min(const Vector2& _vectorOne, const Vector2& _vectorTwo) noexcept
	{
		Vector2 result;
		Min(_vectorOne,_vectorTwo,result);
		return result;
	}

	inline void Vector2::Max(const Vector2& _vectorOne, const Vector2& _vectorTwo, Vector2& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat2A(&_vectorOne);
		const XMVECTOR vectorTwo = XMLoadFloat2A(&_vectorTwo);
		const XMVECTOR finalVector = XMVectorMax(vectorOne, vectorTwo);
		XMStoreFloat2A(&_result, finalVector);
	}

	inline Vector2 Vector2::Max(const Vector2& _vectorOne, const Vector2& _vectorTwo) noexcept
	{

		Vector2 result;
		Max(_vectorOne,_vectorTwo,result);
		return result;
	}

	
	inline void Vector2::SmoothStep(const Vector2& _vectorOne, const Vector2& _vectorTwo, float _stepFactor, Vector2& _result) noexcept
	{

		using namespace DirectX;
		_stepFactor = (_stepFactor > 1.0f) ? 1.0f : ((_stepFactor < 0.0f) ? 0.0f : _stepFactor);  
		_stepFactor = _stepFactor * _stepFactor * (3.f - 2.f * _stepFactor);
		const XMVECTOR vectorOne = XMLoadFloat2A(&_vectorOne);
		const XMVECTOR vectorTwo = XMLoadFloat2A(&_vectorTwo);
		const XMVECTOR finalVector = XMVectorLerp(vectorOne, vectorTwo, _stepFactor);
		XMStoreFloat2A(&_result, finalVector);

	}

	inline Vector2 Vector2::SmoothStep(const Vector2& _vectorOne, const Vector2& _vectorTwo, float _stepFactor) noexcept
	{
		Vector2 result;
		SmoothStep(_vectorOne,_vectorTwo,_stepFactor,result);
		return result;
	}

	void Vector2::Reflect(const Vector2& _incidentVector, const Vector2& _normalVector, Vector2& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR incidentVector = XMLoadFloat2A(&_incidentVector);
		const XMVECTOR normalVector = XMLoadFloat2A(&_normalVector);
		const XMVECTOR reflectedVector = XMVector2Reflect(incidentVector, normalVector);
		XMStoreFloat2A(&_result, reflectedVector);
	}

	Vector2 Vector2::Reflect(const Vector2& _incidentVector, const Vector2& _normalVector) noexcept
	{
		Vector2 result;
		Reflect(_incidentVector,_normalVector,result);
		return result;
	}

	void Vector2::Refract(const Vector2& _incidentVector, const Vector2& _normalVector, float _refractionIndex, Vector2& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR incidentVector = XMLoadFloat2A(&_incidentVector);
		const XMVECTOR normalVector = XMLoadFloat2A(&_normalVector);
		const XMVECTOR refractedVector = XMVector2Refract(incidentVector, normalVector, _refractionIndex);
		XMStoreFloat2A(&_result, refractedVector);
	}

	Vector2 Vector2::Refract(const Vector2& _incidentVector, const Vector2& _normalVector, float _refractionIndex) noexcept
	{
		using namespace DirectX;
		const XMVECTOR incidentVector = XMLoadFloat2A(&_incidentVector);
		const XMVECTOR normalVector = XMLoadFloat2A(&_normalVector);
		const XMVECTOR refractedVector = XMVector2Refract(incidentVector, normalVector, _refractionIndex);
		
		Vector2 result;
		XMStoreFloat2A(&result, refractedVector);
		return result;
	}

	void Vector2::Transform(const Vector2& _vector, const Quaternion& _quaternion, Vector2& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vector = XMLoadFloat2A(&_vector);
		const XMVECTOR quaternion = XMLoadFloat4A(&_quaternion);
		const XMVECTOR transformedVector = XMVector3Rotate(vector, quaternion);
		XMStoreFloat2A(&_result, transformedVector);
	}

	Vector2 Vector2::Transform(const Vector2& _vector, const Quaternion& _quaternion) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vector = XMLoadFloat2A(&_vector);
		const XMVECTOR quaternion = XMLoadFloat4A(&_quaternion);
		const XMVECTOR transformedVector = XMVector3Rotate(vector, quaternion);

		Vector2 result;
		XMStoreFloat2A(&result, transformedVector);
		return result;
	}


	// Cannot Inline this for some weird reason
	

	Vector2 operator+(const Vector2& _firstVector, const Vector2& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat2A(&_firstVector);
		const XMVECTOR vectorTwo = XMLoadFloat2A(&_secondVector);
		const XMVECTOR addedVector = XMVectorAdd(vectorOne, vectorTwo);
		Vector2 finalVector;
		XMStoreFloat2A(&finalVector, addedVector);
		return finalVector;
	}

	// Cannot Inline this for some weird reason
	Vector2 operator-(const Vector2& _firstVector, const Vector2& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat2A(&_firstVector);
		const XMVECTOR vectorTwo = XMLoadFloat2A(&_secondVector);
		const XMVECTOR subtractedVector = XMVectorSubtract(vectorOne, vectorTwo);
		Vector2 finalVector;
		XMStoreFloat2A(&finalVector, subtractedVector);
		return finalVector;
	}

	Vector2 operator*(const Vector2& _firstVector, const Vector2& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat2A(&_firstVector);
		const XMVECTOR vectorTwo = XMLoadFloat2A(&_secondVector);
		const XMVECTOR multipliedVector = XMVectorMultiply(vectorOne, vectorTwo);
		Vector2 finalVector;
		XMStoreFloat2A(&finalVector, multipliedVector);
		return finalVector;
	}

	Vector2 operator*(const Vector2& _firstVector, const float _float) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat2A(&_firstVector);
		const XMVECTOR multipliedVector = XMVectorScale(vectorOne,_float);
		
		Vector2 finalVector;
		XMStoreFloat2A(&finalVector, multipliedVector);
		return finalVector;
	}

	Vector2 operator/(const Vector2& _firstVector, const Vector2& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat2A(&_firstVector);
		const XMVECTOR vectorTwo = XMLoadFloat2A(&_secondVector);
		const XMVECTOR dividedVector = XMVectorDivide(vectorOne, vectorTwo);
		Vector2 finalVector;
		XMStoreFloat2A(&finalVector, dividedVector);
		return finalVector;
	}

	Vector2 operator/(const Vector2& _firstVector, const float _float) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat2A(&_firstVector);
		const XMVECTOR multipliedVector = XMVectorScale(vectorOne, 1.0f / _float);

		Vector2 finalVector;
		XMStoreFloat2A(&finalVector, multipliedVector);
		return finalVector;
	}

	/// !End of Vector 2 Stuff
}