/************************************************************************|
|						    Vector3_DX.cpp								 |
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


/*
	Implementation of the DIRECT X MATH Vector 3
*/

#include "Vectors/DirectMath/Vector3_DX.h"
#include <Quaternion.h>
#include <../Core/EngineDefines.h>

 
namespace SproutEngine::Maths
{


	const SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::Zero = SPROUT_VECTOR3_DX{ 0.0f, 0.0f, 0.0f };
	const SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::One = SPROUT_VECTOR3_DX{ 1.0f, 1.0f ,1.0f};
	const SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::UnitX = SPROUT_VECTOR3_DX{ 1.0f, 0.0f ,0.0f};
	const SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::UnitY = SPROUT_VECTOR3_DX{ 0.0f, 1.0f ,0.0f};
	const SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::UnitZ = SPROUT_VECTOR3_DX{ 0.0f, 0.0f ,1.0f };

	inline SPROUT_VECTOR3_DX& SPROUT_VECTOR3_DX::operator+=(const SPROUT_VECTOR3_DX& _vector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vector.xmvector);
		const XMVECTOR finalVector = XMVectorAdd(vectorOne, vectorTwo);
		XMStoreFloat3A(&this->xmvector, finalVector);
		return *this;
	}

	inline SPROUT_VECTOR3_DX& SPROUT_VECTOR3_DX::operator-=(const SPROUT_VECTOR3_DX& _vector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vector.xmvector);
		const XMVECTOR finalVector = XMVectorSubtract(vectorOne, vectorTwo);
		XMStoreFloat3A(&this->xmvector, finalVector);
		return *this;
	}

	inline SPROUT_VECTOR3_DX& SPROUT_VECTOR3_DX::operator*=(const SPROUT_VECTOR3_DX& _vector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vector.xmvector);
		const XMVECTOR finalVector = XMVectorMultiply(vectorOne, vectorTwo);
		XMStoreFloat3A(&this->xmvector, finalVector);
		return *this;
	}

	inline SPROUT_VECTOR3_DX& SPROUT_VECTOR3_DX::operator/=(const SPROUT_VECTOR3_DX& _vector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vector.xmvector);
		const XMVECTOR finalVector = XMVectorDivide(vectorOne, vectorTwo);
		XMStoreFloat3A(&this->xmvector, finalVector);
		return *this;
	}


	inline SPROUT_VECTOR3_DX& SPROUT_VECTOR3_DX::operator*=(float _scalar) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR finalVector = XMVectorScale(vectorOne, _scalar);
		XMStoreFloat3A(&this->xmvector, finalVector);
		return *this;
	}

	inline SPROUT_VECTOR3_DX& SPROUT_VECTOR3_DX::operator/=(float _scalar) noexcept
	{
		using namespace DirectX;
		// Check Divide by Zero Edge Case
		SPROUT_ASSERT(_scalar != 0.0f);

		const XMVECTOR thisVector = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR finalVector = XMVectorScale(thisVector, 1.0f / _scalar);

		XMStoreFloat3A(&this->xmvector, finalVector);
		return *this;

	}

	/// Moved to the .h file 

	/*inline bool SPROUT_VECTOR3_DX::operator==(const SPROUT_VECTOR3_DX& _vector) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vector.xmvector);
		return XMVector3Equal(vectorOne, vectorTwo);
	}*/

	//inline bool SPROUT_VECTOR3_DX::operator!=(const SPROUT_VECTOR3_DX& _vector) const noexcept
	//{
	//	using namespace DirectX;
	//	const XMVECTOR vectorOne = XMLoadFloat3A(&this->xmvector);
	//	const XMVECTOR vectorTwo = XMLoadFloat3A(&_vector.xmvector);
	//	return XMVector3NotEqual(vectorOne, vectorTwo);
	//}

	/*inline SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::operator-() const noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR finalVector = XMVectorNegate(vectorOne);
		SPROUT_VECTOR3_DX result;
		XMStoreFloat3A(&result.xmvector, finalVector);
		return result;

	}*/

	inline SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::operator+() const noexcept
	{
		return *this;
	}

	float SPROUT_VECTOR3_DX::Length() const noexcept
	{
		using namespace DirectX;
		const XMVECTOR thisVector = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR finalVector = XMVector3LengthEst(thisVector);
		return XMVectorGetX(finalVector);
	}

	float SPROUT_VECTOR3_DX::LengthSquared() const noexcept
	{
		using namespace DirectX;
		const XMVECTOR thisVector = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR finalVector = XMVector3LengthSq(thisVector);
		return XMVectorGetX(finalVector);
	}

	float SPROUT_VECTOR3_DX::Distance(const SPROUT_VECTOR3_DX& _firstVector, const SPROUT_VECTOR3_DX& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR minVector = XMLoadFloat3A(&_firstVector.xmvector);
		const XMVECTOR maxVector = XMLoadFloat3A(&_secondVector.xmvector);
		const XMVECTOR vectorSubtract = XMVectorSubtract(maxVector, minVector);
		const XMVECTOR finalVector = XMVector3Length(vectorSubtract);
		return XMVectorGetX(finalVector);
	}

	float SPROUT_VECTOR3_DX::DistanceSquared(const SPROUT_VECTOR3_DX& _firstVector, const SPROUT_VECTOR3_DX& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR minVector = XMLoadFloat3A(&_firstVector.xmvector);
		const XMVECTOR maxVector = XMLoadFloat3A(&_secondVector.xmvector);
		const XMVECTOR vectorSubtract = XMVectorSubtract(maxVector, minVector);
		const XMVECTOR finalVector = XMVector3LengthSq(vectorSubtract);
		return XMVectorGetX(finalVector);
	}

	void SPROUT_VECTOR3_DX::Normalize() noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorThis = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR normalizedVector = XMVector3Normalize(vectorThis);
		XMStoreFloat3A(&this->xmvector, normalizedVector);
	}

	void SPROUT_VECTOR3_DX::Normalize(SPROUT_VECTOR3_DX& _result) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorThis = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR normalizedVector = XMVector2Normalize(vectorThis);
		XMStoreFloat3A(&_result.xmvector, normalizedVector);
	}

	float SPROUT_VECTOR3_DX::Dot(const SPROUT_VECTOR3_DX& _otherVector) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR thisvector = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR otherVector = XMLoadFloat3A(&_otherVector.xmvector);
		const XMVECTOR dotVector = XMVector3Dot(thisvector, otherVector);
		return XMVectorGetX(dotVector);
	}

	float SPROUT_VECTOR3_DX::Cross(const SPROUT_VECTOR3_DX& _otherVector) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR thisvector = XMLoadFloat3A(&this->xmvector);
		const XMVECTOR otherVector = XMLoadFloat3A(&_otherVector.xmvector);
		const XMVECTOR crossVector = XMVector3Cross(thisvector, otherVector);
		return XMVectorGetX(crossVector);
	}

	void SPROUT_VECTOR3_DX::Lerp(const SPROUT_VECTOR3_DX& _vectorOne, const SPROUT_VECTOR3_DX& _vectorTwo, float _lerpFactor, SPROUT_VECTOR3_DX& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_vectorOne.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vectorTwo.xmvector);
		const XMVECTOR lerpedVector = XMVectorLerp(vectorOne, vectorTwo, _lerpFactor);
		XMStoreFloat3A(&_result.xmvector, lerpedVector);
	}

	SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::Lerp(const SPROUT_VECTOR3_DX& _vectorOne, const SPROUT_VECTOR3_DX& _vectorTwo, float _lerpFactor) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_vectorOne.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vectorTwo.xmvector);
		const XMVECTOR lerpedVector = XMVectorLerp(vectorOne, vectorTwo, _lerpFactor);

		SPROUT_VECTOR3_DX result;
		XMStoreFloat3A(&result.xmvector, lerpedVector);
		return result;
	}

	void SPROUT_VECTOR3_DX::Clamp(const SPROUT_VECTOR3_DX& _vector, const SPROUT_VECTOR3_DX& _vectorMin, const SPROUT_VECTOR3_DX& _vectorMax, SPROUT_VECTOR3_DX& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vector = XMLoadFloat3A(&_vector.xmvector);
		const XMVECTOR vectorMin = XMLoadFloat3A(&_vectorMin.xmvector);
		const XMVECTOR vectorMax = XMLoadFloat3A(&_vectorMax.xmvector);
		const XMVECTOR clampedVector = XMVectorClamp(_vector, _vectorMin, _vectorMax);
		XMStoreFloat3A(&_result.xmvector, clampedVector);
	}

	SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::Clamp(const SPROUT_VECTOR3_DX& _vector, const SPROUT_VECTOR3_DX& _vectorMin, const SPROUT_VECTOR3_DX& _vectorMax) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vector = XMLoadFloat3A(&_vector.xmvector);
		const XMVECTOR vectorMin = XMLoadFloat3A(&_vectorMin.xmvector);
		const XMVECTOR vectorMax = XMLoadFloat3A(&_vectorMax.xmvector);
		const XMVECTOR clampedVector = XMVectorClamp(_vector, _vectorMin, _vectorMax);

		SPROUT_VECTOR3_DX result;
		XMStoreFloat3A(&result.xmvector, clampedVector);
		return result;
	}

	void SPROUT_VECTOR3_DX::Min(const SPROUT_VECTOR3_DX& _vectorOne, const SPROUT_VECTOR3_DX& _vectorTwo, SPROUT_VECTOR3_DX& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_vectorOne.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vectorTwo.xmvector);
		const XMVECTOR minVector = XMVectorMin(vectorOne, vectorTwo);
		XMStoreFloat3A(&_result.xmvector, minVector);
	}

	SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::Min(const SPROUT_VECTOR3_DX& _vectorOne, const SPROUT_VECTOR3_DX& _vectorTwo) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_vectorOne.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vectorTwo.xmvector);
		const XMVECTOR minVector = XMVectorMin(vectorOne, vectorTwo);

		SPROUT_VECTOR3_DX result;
		XMStoreFloat3A(&result.xmvector, minVector);
		return result;
	}

	void SPROUT_VECTOR3_DX::Max(const SPROUT_VECTOR3_DX& _vectorOne, const SPROUT_VECTOR3_DX& _vectorTwo, SPROUT_VECTOR3_DX& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_vectorOne.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vectorTwo.xmvector);
		const XMVECTOR maxVector = XMVectorMax(vectorOne, vectorTwo);
		XMStoreFloat3A(&_result.xmvector, maxVector);
	}

	SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::Max(const SPROUT_VECTOR3_DX& _vectorOne, const SPROUT_VECTOR3_DX& _vectorTwo) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_vectorOne.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vectorTwo.xmvector);
		const XMVECTOR maxVector = XMVectorMax(vectorOne, vectorTwo);

		SPROUT_VECTOR3_DX result;
		XMStoreFloat3A(&result.xmvector, maxVector);
		return result;
	}

	void SPROUT_VECTOR3_DX::SmoothStep(const SPROUT_VECTOR3_DX& _vectorOne, const SPROUT_VECTOR3_DX& _vectorTwo, float _stepFactor, SPROUT_VECTOR3_DX& _result) noexcept
	{
		using namespace DirectX;
		_stepFactor = (_stepFactor > 1.0f) ? 1.0f : ((_stepFactor < 0.0f) ? 0.0f : _stepFactor);
		_stepFactor = _stepFactor * _stepFactor * (3.f - 2.f * _stepFactor);
		const XMVECTOR vectorOne = XMLoadFloat3A(&_vectorOne.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_vectorTwo.xmvector);
		const XMVECTOR finalVector = XMVectorLerp(vectorOne, vectorTwo, _stepFactor);
		XMStoreFloat3A(&_result.xmvector, finalVector);
	}

	SPROUT_VECTOR3_DX SPROUT_VECTOR3_DX::SmoothStep(const SPROUT_VECTOR3_DX& _vectorOne, const SPROUT_VECTOR3_DX& _vectorTwo, float _stepFactor) noexcept
	{
		SPROUT_VECTOR3_DX result;
		SmoothStep(_vectorOne, _vectorTwo, _stepFactor, result);
		return result;
	}


	SPROUT_VECTOR3_DX operator+(const SPROUT_VECTOR3_DX& _firstVector, const SPROUT_VECTOR3_DX& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_firstVector.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_secondVector.xmvector);
		const XMVECTOR addedVector = XMVectorAdd(vectorOne, vectorTwo);
		SPROUT_VECTOR3_DX finalVector;
		XMStoreFloat3A(&finalVector.xmvector, addedVector);
		return finalVector;
	}

	SPROUT_VECTOR3_DX operator-(const SPROUT_VECTOR3_DX& _firstVector, const SPROUT_VECTOR3_DX& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_firstVector.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_secondVector.xmvector);
		const XMVECTOR subtractedVector = XMVectorSubtract(vectorOne, vectorTwo);
		SPROUT_VECTOR3_DX finalVector;
		XMStoreFloat3A(&finalVector.xmvector, subtractedVector);
		return finalVector;
	}

	SPROUT_VECTOR3_DX operator*(const SPROUT_VECTOR3_DX& _firstVector, const SPROUT_VECTOR3_DX& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_firstVector.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_secondVector.xmvector);
		const XMVECTOR multipliedVector = XMVectorMultiply(vectorOne, vectorTwo);
		SPROUT_VECTOR3_DX finalVector;
		XMStoreFloat3A(&finalVector.xmvector, multipliedVector);
		return finalVector;
	}

	SPROUT_VECTOR3_DX operator*(const SPROUT_VECTOR3_DX& _firstVector, const float _float) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_firstVector.xmvector);
		const XMVECTOR multipliedVector = XMVectorScale(vectorOne, _float);

		SPROUT_VECTOR3_DX finalVector;
		XMStoreFloat3A(&finalVector.xmvector, multipliedVector);
		return finalVector;
	}

	SPROUT_VECTOR3_DX operator/(const SPROUT_VECTOR3_DX& _firstVector, const SPROUT_VECTOR3_DX& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_firstVector.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat3A(&_secondVector.xmvector);
		const XMVECTOR dividedVector = XMVectorDivide(vectorOne, vectorTwo);
		SPROUT_VECTOR3_DX finalVector;
		XMStoreFloat3A(&finalVector.xmvector, dividedVector);
		return finalVector;
	}

	SPROUT_VECTOR3_DX operator/(const SPROUT_VECTOR3_DX& _firstVector, const float _float) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat3A(&_firstVector.xmvector);
		const XMVECTOR multipliedVector = XMVectorScale(vectorOne, 1.0f / _float);

		SPROUT_VECTOR3_DX finalVector;
		XMStoreFloat3A(&finalVector.xmvector, multipliedVector);
		return finalVector;
	}


}