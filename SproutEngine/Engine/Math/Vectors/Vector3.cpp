/************************************************************************|
|						    Vector3.cpp						     |
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

#include "Vectors/Vector3.hpp"
#include <Quaternion.hpp>
#include <../Core/EngineDefines.hpp>

 
namespace SproutEngine::Maths
{


	const Vector3 Vector3::Zero = Vector3{ 0.0f, 0.0f, 0.0f };
	const Vector3 Vector3::One = Vector3{ 1.0f, 1.0f ,1.0f};
	const Vector3 Vector3::UnitX = Vector3{ 1.0f, 0.0f ,0.0f};
	const Vector3 Vector3::UnitY = Vector3{ 0.0f, 1.0f ,0.0f};
	const Vector3 Vector3::UnitZ = Vector3{ 0.0f, 0.0f ,1.0f };

	inline Vector3& Vector3::operator+=(const Vector3& _vector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vector.xmvector);
		const XMVECTOR finalVector = XMVectorAdd(vectorOne, vectorTwo);
		XMStoreFloat3A(&this->xmvector, finalVector);
		return *this;
	}

	inline Vector3& Vector3::operator-=(const Vector3& _vector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vector.xmvector);
		const XMVECTOR finalVector = XMVectorSubtract(vectorOne, vectorTwo);
		XMStoreFloat3A(&this->xmvector, finalVector);
		return *this;
	}

	inline Vector3& Vector3::operator*=(const Vector3& _vector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vector.xmvector);
		const XMVECTOR finalVector = XMVectorMultiply(vectorOne, vectorTwo);
		XMStoreFloat3A(&this->xmvector, finalVector);
		return *this;
	}

	inline Vector3& Vector3::operator/=(const Vector3& _vector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vector.xmvector);
		const XMVECTOR finalVector = XMVectorDivide(vectorOne, vectorTwo);
		XMStoreFloat3A(&this->xmvector, finalVector);
		return *this;
	}


	inline Vector3& Vector3::operator*=(float _scalar) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR finalVector = XMVectorScale(vectorOne, _scalar);
		XMStoreFloat3A(&this->xmvector, finalVector);
		return *this;
	}

	inline Vector3& Vector3::operator/=(float _scalar) noexcept
	{
		using namespace DirectX;
		// Check Divide by Zero Edge Case
		SPROUT_ASSERT(_scalar != 0.0f);

		const XMVECTOR thisVector = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR finalVector = XMVectorScale(thisVector, 1.0f / _scalar);

		XMStoreFloat3A(&this->xmvector, finalVector);
		return *this;

	}

	/*inline bool Vector3::operator==(const Vector3& _vector) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vector.xmvector);
		return XMVector3Equal(vectorOne, vectorTwo);
	}*/

	//inline bool Vector3::operator!=(const Vector3& _vector) const noexcept
	//{
	//	using namespace DirectX;
	//	const XMVECTOR vectorOne = XMLoadFloat3A(&this->xmvector);
	//	const XMVECTOR vectorTwo = XMLoadFloat3A(&_vector.xmvector);
	//	return XMVector3NotEqual(vectorOne, vectorTwo);
	//}

	/*inline Vector3 Vector3::operator-() const noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR finalVector = XMVectorNegate(vectorOne);
		Vector3 result;
		XMStoreFloat3A(&result.xmvector, finalVector);
		return result;

	}*/

	inline Vector3 Vector3::operator+() const noexcept
	{
		return *this;
	}

	float Vector3::Length() const noexcept
	{
		using namespace DirectX;
		const XMVECTOR thisVector = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR finalVector = XMVector3LengthEst(thisVector);
		return XMVectorGetX(finalVector);
	}

	float Vector3::LengthSquared() const noexcept
	{
		using namespace DirectX;
		const XMVECTOR thisVector = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR finalVector = XMVector3LengthSq(thisVector);
		return XMVectorGetX(finalVector);
	}

	float Vector3::Distance(const Vector3& _firstVector, const Vector3& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR minVector = XMLoadFloat3A(&_firstVector.xmvector);
		const XMVECTOR maxVector = XMLoadFloat3A(&_secondVector.xmvector);
		const XMVECTOR vectorSubtract = XMVectorSubtract(maxVector, minVector);
		const XMVECTOR finalVector = XMVector3Length(vectorSubtract);
		return XMVectorGetX(finalVector);
	}

	float Vector3::DistanceSquared(const Vector3& _firstVector, const Vector3& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR minVector = XMLoadFloat3A(&_firstVector.xmvector);
		const XMVECTOR maxVector = XMLoadFloat3A(&_secondVector.xmvector);
		const XMVECTOR vectorSubtract = XMVectorSubtract(maxVector, minVector);
		const XMVECTOR finalVector = XMVector3LengthSq(vectorSubtract);
		return XMVectorGetX(finalVector);
	}

	void Vector3::Normalize() noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorThis = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR normalizedVector = XMVector3Normalize(vectorThis);
		XMStoreFloat3A(&this->xmvector, normalizedVector);
	}

	void Vector3::Normalize(Vector3& _result) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorThis = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR normalizedVector = XMVector2Normalize(vectorThis);
		XMStoreFloat3A(&_result.xmvector, normalizedVector);
	}

	float Vector3::Dot(const Vector3& _otherVector) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR thisvector = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR otherVector = XMLoadFloat3A(&_otherVector.xmvector);
		const XMVECTOR dotVector = XMVector3Dot(thisvector, otherVector);
		return XMVectorGetX(dotVector);
	}

	float Vector3::Cross(const Vector3& _otherVector) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR thisvector = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR otherVector = XMLoadFloat3A(&_otherVector.xmvector);
		const XMVECTOR crossVector = XMVector3Cross(thisvector, otherVector);
		return XMVectorGetX(crossVector);
	}

	void Vector3::Lerp(const Vector3& _vectorOne, const Vector3& _vectorTwo, float _lerpFactor, Vector3& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_vectorOne.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vectorTwo.xmvector);
		const XMVECTOR lerpedVector = XMVectorLerp(vectorOne, vectorTwo, _lerpFactor);
		XMStoreFloat3A(&_result.xmvector, lerpedVector);
	}

	Vector3 Vector3::Lerp(const Vector3& _vectorOne, const Vector3& _vectorTwo, float _lerpFactor) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_vectorOne.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vectorTwo.xmvector);
		const XMVECTOR lerpedVector = XMVectorLerp(vectorOne, vectorTwo, _lerpFactor);

		Vector3 result;
		XMStoreFloat3A(&result.xmvector, lerpedVector);
		return result;
	}

	void Vector3::Clamp(const Vector3& _vector, const Vector3& _vectorMin, const Vector3& _vectorMax, Vector3& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vector = XMLoadFloat3A(&_vector.xmvector);
		const XMVECTOR vectorMin = XMLoadFloat3A(&_vectorMin.xmvector);
		const XMVECTOR vectorMax = XMLoadFloat3A(&_vectorMax.xmvector);
		const XMVECTOR clampedVector = XMVectorClamp(_vector, _vectorMin, _vectorMax);
		XMStoreFloat3A(&_result.xmvector, clampedVector);
	}

	Vector3 Vector3::Clamp(const Vector3& _vector, const Vector3& _vectorMin, const Vector3& _vectorMax) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vector = XMLoadFloat3A(&_vector.xmvector);
		const XMVECTOR vectorMin = XMLoadFloat3A(&_vectorMin.xmvector);
		const XMVECTOR vectorMax = XMLoadFloat3A(&_vectorMax.xmvector);
		const XMVECTOR clampedVector = XMVectorClamp(_vector, _vectorMin, _vectorMax);

		Vector3 result;
		XMStoreFloat3A(&result.xmvector, clampedVector);
		return result;
	}

	void Vector3::Min(const Vector3& _vectorOne, const Vector3& _vectorTwo, Vector3& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_vectorOne.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vectorTwo.xmvector);
		const XMVECTOR minVector = XMVectorMin(vectorOne, vectorTwo);
		XMStoreFloat3A(&_result.xmvector, minVector);
	}

	Vector3 Vector3::Min(const Vector3& _vectorOne, const Vector3& _vectorTwo) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_vectorOne.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vectorTwo.xmvector);
		const XMVECTOR minVector = XMVectorMin(vectorOne, vectorTwo);

		Vector3 result;
		XMStoreFloat3A(&result.xmvector, minVector);
		return result;
	}

	void Vector3::Max(const Vector3& _vectorOne, const Vector3& _vectorTwo, Vector3& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_vectorOne.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vectorTwo.xmvector);
		const XMVECTOR maxVector = XMVectorMax(vectorOne, vectorTwo);
		XMStoreFloat3A(&_result.xmvector, maxVector);
	}

	Vector3 Vector3::Max(const Vector3& _vectorOne, const Vector3& _vectorTwo) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_vectorOne.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vectorTwo.xmvector);
		const XMVECTOR maxVector = XMVectorMax(vectorOne, vectorTwo);

		Vector3 result;
		XMStoreFloat3A(&result.xmvector, maxVector);
		return result;
	}

	void Vector3::SmoothStep(const Vector3& _vectorOne, const Vector3& _vectorTwo, float _stepFactor, Vector3& _result) noexcept
	{
		using namespace DirectX;
		_stepFactor = (_stepFactor > 1.0f) ? 1.0f : ((_stepFactor < 0.0f) ? 0.0f : _stepFactor);
		_stepFactor = _stepFactor * _stepFactor * (3.f - 2.f * _stepFactor);
		const XMVECTOR vectorOne = XMLoadFloat3A(&_vectorOne.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vectorTwo.xmvector);
		const XMVECTOR finalVector = XMVectorLerp(vectorOne, vectorTwo, _stepFactor);
		XMStoreFloat3A(&_result.xmvector, finalVector);
	}

	Vector3 Vector3::SmoothStep(const Vector3& _vectorOne, const Vector3& _vectorTwo, float _stepFactor) noexcept
	{
		Vector3 result;
		SmoothStep(_vectorOne, _vectorTwo, _stepFactor, result);
		return result;
	}


	Vector3 operator+(const Vector3& _firstVector, const Vector3& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_firstVector.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_secondVector.xmvector);
		const XMVECTOR addedVector = XMVectorAdd(vectorOne, vectorTwo);
		Vector3 finalVector;
		XMStoreFloat3A(&finalVector.xmvector, addedVector);
		return finalVector;
	}

	Vector3 operator-(const Vector3& _firstVector, const Vector3& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_firstVector.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_secondVector.xmvector);
		const XMVECTOR subtractedVector = XMVectorSubtract(vectorOne, vectorTwo);
		Vector3 finalVector;
		XMStoreFloat3A(&finalVector.xmvector, subtractedVector);
		return finalVector;
	}

	Vector3 operator*(const Vector3& _firstVector, const Vector3& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_firstVector.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_secondVector.xmvector);
		const XMVECTOR multipliedVector = XMVectorMultiply(vectorOne, vectorTwo);
		Vector3 finalVector;
		XMStoreFloat3A(&finalVector.xmvector, multipliedVector);
		return finalVector;
	}

	Vector3 operator*(const Vector3& _firstVector, const float _float) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_firstVector.xmvector);
		const XMVECTOR multipliedVector = XMVectorScale(vectorOne, _float);

		Vector3 finalVector;
		XMStoreFloat3A(&finalVector.xmvector, multipliedVector);
		return finalVector;
	}

	Vector3 operator/(const Vector3& _firstVector, const Vector3& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_firstVector.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_secondVector.xmvector);
		const XMVECTOR dividedVector = XMVectorDivide(vectorOne, vectorTwo);
		Vector3 finalVector;
		XMStoreFloat3A(&finalVector.xmvector, dividedVector);
		return finalVector;
	}

	Vector3 operator/(const Vector3& _firstVector, const float _float) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_firstVector.xmvector);
		const XMVECTOR multipliedVector = XMVectorScale(vectorOne, 1.0f / _float);

		Vector3 finalVector;
		XMStoreFloat3A(&finalVector.xmvector, multipliedVector);
		return finalVector;
	}
}