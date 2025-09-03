/************************************************************************|
|							     SPROUT_VECTOR2_DX.cpp						     |
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


#include <Vectors/VECTOR2_DX.h>
#include <Quaternion.hpp>
#include <../Core/EngineDefines.h>

#include <sstream> 


namespace SproutEngine::Maths
{
	/// Vector 2 Stuff


	const SPROUT_VECTOR2_DX SPROUT_VECTOR2_DX::Zero  = SPROUT_VECTOR2_DX{ 0.f, 0.f };
	const SPROUT_VECTOR2_DX SPROUT_VECTOR2_DX::One   = SPROUT_VECTOR2_DX{ 1.f, 1.f };
	const SPROUT_VECTOR2_DX SPROUT_VECTOR2_DX::UnitX = SPROUT_VECTOR2_DX{ 1.f, 0.f };
	const SPROUT_VECTOR2_DX SPROUT_VECTOR2_DX::UnitY = SPROUT_VECTOR2_DX{ 0.f, 1.f };


	inline SPROUT_VECTOR2_DX& SPROUT_VECTOR2_DX::operator+=(const SPROUT_VECTOR2_DX& _vector) noexcept
	{
		using namespace DirectX;

		const XMVECTOR thisVector = XMLoadFloat2A(&this->xmvector);
		const XMVECTOR inVector = XMLoadFloat2A(&_vector.xmvector);
		const XMVECTOR finalVector = XMVectorAdd(thisVector, inVector);

		XMStoreFloat2A(&this->xmvector, finalVector);
		return *this;
	}

	inline SPROUT_VECTOR2_DX& SPROUT_VECTOR2_DX::operator-=(const SPROUT_VECTOR2_DX& _vector) noexcept
	{
		using namespace DirectX;

		const XMVECTOR thisVector = XMLoadFloat2A(&this->xmvector);
		const XMVECTOR inVector = XMLoadFloat2A(&_vector.xmvector);
		const XMVECTOR finalVector = XMVectorSubtract(thisVector, inVector);

		XMStoreFloat2A(&this->xmvector, finalVector);
		return *this;
	}

	inline SPROUT_VECTOR2_DX& SPROUT_VECTOR2_DX::operator*=(const SPROUT_VECTOR2_DX& _vector) noexcept
	{
		using namespace DirectX;

		const XMVECTOR thisVector = XMLoadFloat2A(&this->xmvector);
		const XMVECTOR inVector = XMLoadFloat2A(&_vector.xmvector);
		const XMVECTOR finalVector = XMVectorMultiply(thisVector, inVector);

		XMStoreFloat2A(&this->xmvector, finalVector);
		return *this;
	}

	// Questionable if vector division is gonna be used 
	// But using an operator overload anyway
	inline SPROUT_VECTOR2_DX& SPROUT_VECTOR2_DX::operator/=(const SPROUT_VECTOR2_DX& _vector) noexcept
	{
		using namespace DirectX;

		const XMVECTOR thisVector = XMLoadFloat2A(&this->xmvector);
		const XMVECTOR inVector = XMLoadFloat2A(&_vector.xmvector);
		const XMVECTOR finalVector = XMVectorDivide(thisVector, inVector);

		XMStoreFloat2A(&this->xmvector, finalVector);
		return *this;
	}

	

	inline SPROUT_VECTOR2_DX& SPROUT_VECTOR2_DX::operator*=(const float _scalar) noexcept
	{
		using namespace DirectX;

		const XMVECTOR thisVector = XMLoadFloat2A(&this->xmvector);
		const XMVECTOR finalVector = XMVectorScale(thisVector, _scalar);

		XMStoreFloat2A(&this->xmvector, finalVector);
		return *this;
	}

	inline SPROUT_VECTOR2_DX& SPROUT_VECTOR2_DX::operator/=(const float _scalar) noexcept
	{
		using namespace DirectX;

		// Check Divide by Zero Edge Case
		//SPROUT_ASSERT(_scalar == 0.0f);


		const XMVECTOR thisVector = XMLoadFloat2A(&this->xmvector);
		const XMVECTOR finalVector = XMVectorScale(thisVector, 1.0f / _scalar);

		XMStoreFloat2A(&this->xmvector, finalVector);
		return *this;
	}


	
	/*inline bool SPROUT_VECTOR2_DX::operator==(const SPROUT_VECTOR2_DX& _vector) const noexcept
	{
		using namespace DirectX;

		const XMVECTOR thisVector = XMLoadFloat2A(&this->xmvector);
		const XMVECTOR inVector = XMLoadFloat2A(&_vector.xmvector);
		return XMVector2Equal(thisVector, inVector);
	}

	inline bool SPROUT_VECTOR2_DX::operator!=(const SPROUT_VECTOR2_DX& _vector) const noexcept
	{
		using namespace DirectX;

		const XMVECTOR thisVector = XMLoadFloat2A(&this->xmvector);
		const XMVECTOR inVector = XMLoadFloat2A(&_vector.xmvector);
		return XMVector2NotEqual(thisVector, inVector);
	}*/

	
	 
	SPROUT_VECTOR2_DX SPROUT_VECTOR2_DX::operator-() const noexcept
	{
		return SPROUT_VECTOR2_DX{ -this->x,-this->y };
	}

	SPROUT_VECTOR2_DX SPROUT_VECTOR2_DX::operator+() const noexcept
	{
		return *this;
	}

	
	float SPROUT_VECTOR2_DX::Length() const noexcept
	{
		using namespace DirectX;
		const XMVECTOR thisVector = XMLoadFloat2A(&this->xmvector);
		const XMVECTOR finalVector = XMVector2LengthEst(thisVector);
		return XMVectorGetX(finalVector);
	}

	float SPROUT_VECTOR2_DX::LengthSquared() const noexcept
	{
		using namespace DirectX;
		const XMVECTOR thisVector = XMLoadFloat2A(&this->xmvector);
		const XMVECTOR finalVector = XMVector2LengthSq(thisVector);
		return XMVectorGetX(finalVector);
	}

	float SPROUT_VECTOR2_DX::Distance(const SPROUT_VECTOR2_DX& _firstVector, const SPROUT_VECTOR2_DX& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR minVector = XMLoadFloat2A(&_firstVector.xmvector);
		const XMVECTOR maxVector = XMLoadFloat2A(&_secondVector.xmvector);
		const XMVECTOR vectorSubtract = XMVectorSubtract(maxVector, minVector);
		const XMVECTOR finalVector = XMVector2LengthEst(vectorSubtract);
		return XMVectorGetX(finalVector);
	}

	float SPROUT_VECTOR2_DX::DistanceSquared(const SPROUT_VECTOR2_DX& _firstVector, const SPROUT_VECTOR2_DX& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR minVector = XMLoadFloat2A(&_firstVector.xmvector);
		const XMVECTOR maxVector = XMLoadFloat2A(&_secondVector.xmvector);
		const XMVECTOR vectorSubtract = XMVectorSubtract(maxVector, minVector);
		const XMVECTOR finalVector = XMVector2LengthSq(vectorSubtract);
		return XMVectorGetX(finalVector);
		
	}

	//inline void SPROUT_VECTOR2_DX::Normalize() noexcept
	//{
	//	using namespace DirectX;
	//	const XMVECTOR vectorThis = XMLoadFloat2A(&this->xmvector);
	//	const XMVECTOR normalizedVector = XMVector2Normalize(vectorThis);
	//	XMStoreFloat2A(&this->xmvector, normalizedVector);
	//}

	inline void SPROUT_VECTOR2_DX::Normalize(SPROUT_VECTOR2_DX& _result) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorThis = XMLoadFloat2A(&this->xmvector);
		const XMVECTOR normalizedVector = XMVector2Normalize(vectorThis);
		XMStoreFloat2A(&_result.xmvector, normalizedVector);
	}

	/*inline float SPROUT_VECTOR2_DX::Dot(const SPROUT_VECTOR2_DX& _otherVector) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR thisvector = XMLoadFloat2A(&this->xmvector);
		const XMVECTOR otherVector = XMLoadFloat2A(&_otherVector.xmvector);
		const XMVECTOR dotVector = XMVector2Dot(thisvector, otherVector);
		return XMVectorGetX(dotVector);
	}*/

	inline float SPROUT_VECTOR2_DX::Cross(const SPROUT_VECTOR2_DX& _otherVector) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR thisvector = XMLoadFloat2A(&this->xmvector);
		const XMVECTOR otherVector = XMLoadFloat2A(&_otherVector.xmvector);
		const XMVECTOR crossVector = XMVector2Cross(thisvector, otherVector);
		return XMVectorGetX(crossVector);
	}

	inline void SPROUT_VECTOR2_DX::Lerp(const SPROUT_VECTOR2_DX& _vectorOne, const SPROUT_VECTOR2_DX& _vectorTwo, float _lerpFactor, SPROUT_VECTOR2_DX& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat2A(&_vectorOne.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat2A(&_vectorTwo.xmvector);
		const XMVECTOR lerpedVector = XMVectorLerp(vectorOne, vectorTwo, _lerpFactor);
		XMStoreFloat2A(&_result.xmvector, lerpedVector);
	}

	inline SPROUT_VECTOR2_DX SPROUT_VECTOR2_DX::Lerp(const SPROUT_VECTOR2_DX& _vectorOne, const SPROUT_VECTOR2_DX& _vectorTwo, float _lerpFactor) noexcept
	{
		SPROUT_VECTOR2_DX result;
		Lerp(_vectorOne,_vectorTwo,_lerpFactor,result);
		return result;
	}

	inline void SPROUT_VECTOR2_DX::Clamp(const SPROUT_VECTOR2_DX& _vector, const SPROUT_VECTOR2_DX& _vectorMin, const SPROUT_VECTOR2_DX& _vectorMax, SPROUT_VECTOR2_DX& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vector = XMLoadFloat2A(&_vector.xmvector);
		const XMVECTOR vectorMin = XMLoadFloat2A(&_vectorMin.xmvector);
		const XMVECTOR vectorMax = XMLoadFloat2A(&_vectorMax.xmvector);
		const XMVECTOR clampedVector = XMVectorClamp(_vector, _vectorMin, _vectorMax);
		XMStoreFloat2A(&_result.xmvector, clampedVector);
	}

	inline SPROUT_VECTOR2_DX SPROUT_VECTOR2_DX::Clamp(const SPROUT_VECTOR2_DX& _vector, const SPROUT_VECTOR2_DX& _vectorMin, const SPROUT_VECTOR2_DX& _vectorMax) noexcept
	{
		SPROUT_VECTOR2_DX result;
		Clamp(_vector,_vectorMin,_vectorMax,result);
		return result;
	}


	inline void SPROUT_VECTOR2_DX::Min(const SPROUT_VECTOR2_DX& _vectorOne, const SPROUT_VECTOR2_DX& _vectorTwo, SPROUT_VECTOR2_DX& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat2A(&_vectorOne.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat2A(&_vectorTwo.xmvector);
		const XMVECTOR minVector = XMVectorMin(vectorOne, vectorTwo);
		XMStoreFloat2A(&_result.xmvector, minVector);
	}

	inline SPROUT_VECTOR2_DX SPROUT_VECTOR2_DX::Min(const SPROUT_VECTOR2_DX& _vectorOne, const SPROUT_VECTOR2_DX& _vectorTwo) noexcept
	{
		SPROUT_VECTOR2_DX result;
		Min(_vectorOne,_vectorTwo,result);
		return result;
	}

	inline void SPROUT_VECTOR2_DX::Max(const SPROUT_VECTOR2_DX& _vectorOne, const SPROUT_VECTOR2_DX& _vectorTwo, SPROUT_VECTOR2_DX& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat2A(&_vectorOne.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat2A(&_vectorTwo.xmvector);
		const XMVECTOR finalVector = XMVectorMax(vectorOne, vectorTwo);
		XMStoreFloat2A(&_result.xmvector, finalVector);
	}

	inline SPROUT_VECTOR2_DX SPROUT_VECTOR2_DX::Max(const SPROUT_VECTOR2_DX& _vectorOne, const SPROUT_VECTOR2_DX& _vectorTwo) noexcept
	{

		SPROUT_VECTOR2_DX result;
		Max(_vectorOne,_vectorTwo,result);
		return result;
	}

	
	inline void SPROUT_VECTOR2_DX::SmoothStep(const SPROUT_VECTOR2_DX& _vectorOne, const SPROUT_VECTOR2_DX& _vectorTwo, float _stepFactor, SPROUT_VECTOR2_DX& _result) noexcept
	{

		using namespace DirectX;
		_stepFactor = (_stepFactor > 1.0f) ? 1.0f : ((_stepFactor < 0.0f) ? 0.0f : _stepFactor);  
		_stepFactor = _stepFactor * _stepFactor * (3.f - 2.f * _stepFactor);
		const XMVECTOR vectorOne = XMLoadFloat2A(&_vectorOne.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat2A(&_vectorTwo.xmvector);
		const XMVECTOR finalVector = XMVectorLerp(vectorOne, vectorTwo, _stepFactor);
		XMStoreFloat2A(&_result.xmvector, finalVector);

	}

	inline SPROUT_VECTOR2_DX SPROUT_VECTOR2_DX::SmoothStep(const SPROUT_VECTOR2_DX& _vectorOne, const SPROUT_VECTOR2_DX& _vectorTwo, float _stepFactor) noexcept
	{
		SPROUT_VECTOR2_DX result;
		SmoothStep(_vectorOne,_vectorTwo,_stepFactor,result);
		return result;
	}

	void SPROUT_VECTOR2_DX::Reflect(const SPROUT_VECTOR2_DX& _incidentVector, const SPROUT_VECTOR2_DX& _normalVector, SPROUT_VECTOR2_DX& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR incidentVector = XMLoadFloat2A(&_incidentVector.xmvector);
		const XMVECTOR normalVector = XMLoadFloat2A(&_normalVector.xmvector);
		const XMVECTOR reflectedVector = XMVector2Reflect(incidentVector, normalVector);
		XMStoreFloat2A(&_result.xmvector, reflectedVector);
	}

	SPROUT_VECTOR2_DX SPROUT_VECTOR2_DX::Reflect(const SPROUT_VECTOR2_DX& _incidentVector, const SPROUT_VECTOR2_DX& _normalVector) noexcept
	{
		SPROUT_VECTOR2_DX result;
		Reflect(_incidentVector,_normalVector,result);
		return result;
	}

	void SPROUT_VECTOR2_DX::Refract(const SPROUT_VECTOR2_DX& _incidentVector, const SPROUT_VECTOR2_DX& _normalVector, float _refractionIndex, SPROUT_VECTOR2_DX& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR incidentVector = XMLoadFloat2A(&_incidentVector.xmvector);
		const XMVECTOR normalVector = XMLoadFloat2A(&_normalVector.xmvector);
		const XMVECTOR refractedVector = XMVector2Refract(incidentVector, normalVector, _refractionIndex);
		XMStoreFloat2A(&_result.xmvector, refractedVector);
	}

	SPROUT_VECTOR2_DX SPROUT_VECTOR2_DX::Refract(const SPROUT_VECTOR2_DX& _incidentVector, const SPROUT_VECTOR2_DX& _normalVector, float _refractionIndex) noexcept
	{
		using namespace DirectX;
		const XMVECTOR incidentVector = XMLoadFloat2A(&_incidentVector.xmvector);
		const XMVECTOR normalVector = XMLoadFloat2A(&_normalVector.xmvector);
		const XMVECTOR refractedVector = XMVector2Refract(incidentVector, normalVector, _refractionIndex);
		
		SPROUT_VECTOR2_DX result;
		XMStoreFloat2A(&result.xmvector, refractedVector);
		return result;
	}

	void SPROUT_VECTOR2_DX::Transform(const SPROUT_VECTOR2_DX& _vector, const Quaternion& _quaternion, SPROUT_VECTOR2_DX& _result) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vector = XMLoadFloat2A(&_vector.xmvector);
		const XMVECTOR quaternion = XMLoadFloat4A(&_quaternion);
		const XMVECTOR transformedVector = XMVector3Rotate(vector, quaternion);
		XMStoreFloat2A(&_result.xmvector, transformedVector);
	}

	SPROUT_VECTOR2_DX SPROUT_VECTOR2_DX::Transform(const SPROUT_VECTOR2_DX& _vector, const Quaternion& _quaternion) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vector = XMLoadFloat2A(&_vector.xmvector);
		const XMVECTOR quaternion = XMLoadFloat4A(&_quaternion);
		const XMVECTOR transformedVector = XMVector3Rotate(vector, quaternion);

		SPROUT_VECTOR2_DX result;
		XMStoreFloat2A(&result.xmvector, transformedVector);
		return result;
	}


	// Cannot Inline this for some weird reason
	

	SPROUT_VECTOR2_DX operator+(const SPROUT_VECTOR2_DX& _firstVector, const SPROUT_VECTOR2_DX& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat2A(&_firstVector.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat2A(&_secondVector.xmvector);
		const XMVECTOR addedVector = XMVectorAdd(vectorOne, vectorTwo);
		SPROUT_VECTOR2_DX finalVector;
		XMStoreFloat2A(&finalVector.xmvector, addedVector);
		return finalVector;
	}

	// Cannot Inline this for some weird reason
	SPROUT_VECTOR2_DX operator-(const SPROUT_VECTOR2_DX& _firstVector, const SPROUT_VECTOR2_DX& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat2A(&_firstVector.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat2A(&_secondVector.xmvector);
		const XMVECTOR subtractedVector = XMVectorSubtract(vectorOne, vectorTwo);
		SPROUT_VECTOR2_DX finalVector;
		XMStoreFloat2A(&finalVector.xmvector, subtractedVector);
		return finalVector;
	}

	SPROUT_VECTOR2_DX operator*(const SPROUT_VECTOR2_DX& _firstVector, const SPROUT_VECTOR2_DX& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat2A(&_firstVector.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat2A(&_secondVector.xmvector);
		const XMVECTOR multipliedVector = XMVectorMultiply(vectorOne, vectorTwo);
		SPROUT_VECTOR2_DX finalVector;
		XMStoreFloat2A(&finalVector.xmvector, multipliedVector);
		return finalVector;
	}

	SPROUT_VECTOR2_DX operator*(const SPROUT_VECTOR2_DX& _firstVector, const float _float) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat2A(&_firstVector.xmvector);
		const XMVECTOR multipliedVector = XMVectorScale(vectorOne,_float);
		
		SPROUT_VECTOR2_DX finalVector;
		XMStoreFloat2A(&finalVector.xmvector, multipliedVector);
		return finalVector;
	}

	SPROUT_VECTOR2_DX operator/(const SPROUT_VECTOR2_DX& _firstVector, const SPROUT_VECTOR2_DX& _secondVector) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat2A(&_firstVector.xmvector);
		const XMVECTOR vectorTwo = XMLoadFloat2A(&_secondVector.xmvector);
		const XMVECTOR dividedVector = XMVectorDivide(vectorOne, vectorTwo);
		SPROUT_VECTOR2_DX finalVector;
		XMStoreFloat2A(&finalVector.xmvector, dividedVector);
		return finalVector;
	}

	SPROUT_VECTOR2_DX operator/(const SPROUT_VECTOR2_DX& _firstVector, const float _float) noexcept
	{
		using namespace DirectX;
		const XMVECTOR vectorOne = XMLoadFloat2A(&_firstVector.xmvector);
		const XMVECTOR multipliedVector = XMVectorScale(vectorOne, 1.0f / _float);

		SPROUT_VECTOR2_DX finalVector;
		XMStoreFloat2A(&finalVector.xmvector, multipliedVector);
		return finalVector;
	}

	/// !End of Vector 2 Stuff
}