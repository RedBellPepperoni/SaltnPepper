/************************************************************************|
|							     MathFunctions.hpp						     |
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

#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

/// <summary>
/// General purpose wrapper over Direct X math 
/// </summary>
/// 

#include <DirectXMath.h>
#include <cstdlib>
#include <cmath>
#include <limits>



using namespace DirectX;

namespace SproutEngine
{

	namespace Maths
	{
		/// Pi values
		static constexpr float PI = XM_PI;
		static constexpr float TWOPI = XM_2PI;
		static constexpr float ONE_DIV_PI = XM_1DIVPI;
		static constexpr float ONE_DIV_TWOPI = XM_1DIV2PI;
		static constexpr float PI_DIV_2 = XM_PIDIV2;
		static constexpr float PI_DIV_4 = XM_PIDIV4;
		static constexpr float DEG_TO_RAD = PI / 180.0f;
		static constexpr float RAD_TO_DEG = 180.0f / PI;

		/// Int Values
		static constexpr int MAX_INT = 0x7fffffff;
		static constexpr int MIN_INT = 0x80000000;
		static constexpr int MAX_INTUNSIGNED = 0xffffffff;
		static constexpr int MIN_INTUNSIGNED = 0x00000000;

		/// LArge and Small Values
		static constexpr float UNITEPSILON = 0.001f;
		static constexpr float EPSILON = 0.000001f;
		static constexpr float LARGEEPSILON = 0.00005f;
		static constexpr float INF = std::numeric_limits<float>::infinity();


		/// Unit Conversions : Angle
		static inline constexpr float ToRadians(const float _degrees) noexcept
		{
			return _degrees * (PI / 180.0f);
		}

		static inline constexpr float ToDegrees(const float _radians) noexcept
		{
			return _radians * (180.0f / PI);
		}

		/// Trignometry Functions : Single Precision
		static inline  float Sin   (float _value) { return XMScalarSin(_value); }
		static inline  float Cos   (float _value) { return XMScalarCos(_value); }
		static inline  float Tan   (float _value) { return std::tanf(_value); }

		static inline  float SinH  (float _value) { return std::sinhf(_value); }
		static inline  float CosH  (float _value) { return std::tanhf(_value); }
		static inline  float TanH  (float _value) { return std::coshf(_value); }

		static inline  float ASin  (float _value) { return XMScalarASin(_value); }
		static inline  float ACos  (float _value) { return	XMScalarACos(_value); }

		static inline  float ATan  (float _value) { return std::atanf(_value); }
		static inline  float ATan2 (float _valueY, float _valueX) { return std::atan2f(_valueY,_valueX); }


		/// Trignometry Functions : Double Precision
		static inline  double Sin	(double _value) { return std::sin(_value); }
		static inline  double Cos	(double _value) { return std::cos(_value); }
		static inline  double Tan	(double _value) { return std::tan(_value); }

		static inline  double SinH	(double _value) { return std::sinh(_value); }
		static inline  double CosH	(double _value) { return std::tanh(_value); }
		static inline  double TanH	(double _value) { return std::cosh(_value); }
		
		// Clamping the value 
		static inline  double ASin	(double _value) { return (_value < -1) ? (-PI / 2) : ((_value > 1) ? (PI / 2) : std::asin(_value));}
		static inline  double ACos	(double _value) { return (_value < -1) ? PI : ((_value > 1) ? 0 : std::acos(_value)); }

		static inline  double ATan	(double _value) { return std::atan(_value); }
		static inline  double ATan2 (double _valueY, double _valueX) { return std::atan2(_valueY, _valueX); }


		static inline  double SquareRoot(double _value) { return std::sqrt(_value); }
		static inline  float  SquareRoot(float _value) { return std::sqrtf(_value); }



		template <typename Type>
		static inline Type Square(Type _value)
		{
			return _value * _value;
		}

		static inline void Lerp(const float& _valueOne, const float& _valueTwo, const float& _lerpFactor, float& _result)
		{
			//_result = (_valueOne + (_valueTwo - _valueOne) * _lerpFactor);
			_result = std::lerp(_valueOne, _valueTwo, _lerpFactor);
		}

		static inline float Lerp(const float& _valueOne, const float& _valueTwo, const float& _lerpFactor)
		{
			return std::lerp(_valueOne, _valueTwo, _lerpFactor);
		}

		/// Minimum
		template <typename Type>
		static inline float Min(Type _firstValue, Type _secondValue)
		{
			//return _firstValue < _secondValue ? _firstValue : _secondValue;
			return std::min(_firstValue, _secondValue);
		}

		/*static inline double Min(double _firstValue, double _secondValue) noexcept{ return std::min(_firstValue, _secondValue);}
		static inline int Min(int _firstValue, int _secondValue) noexcept{ return std::min(_firstValue, _secondValue);}
		static inline unsigned int Min(unsigned int _firstValue, unsigned int _secondValue) noexcept{ return std::min(_firstValue, _secondValue);}*/
		

		
		/// Maximum
		template <typename Type>
		static inline float Max(Type _firstValue, Type _secondValue) noexcept
		{
			//return _firstValue > _secondValue ? _firstValue : _secondValue;
			return std::max(_firstValue, _secondValue);
		}

		/*static inline double Max(double _firstValue, double _secondValue) noexcept{ return std::max(_firstValue, _secondValue);}
		static inline int Max(int _firstValue, int _secondValue) noexcept{ return std::max(_firstValue, _secondValue);}
		static inline unsigned int Max(unsigned int _firstValue, unsigned int _secondValue) noexcept{ return std::max(_firstValue, _secondValue);}*/



		template <typename Type>
		static inline Type Abs(Type _value)
		{
			return std::abs(_value);
		}

		template <typename Type>
		static inline bool IsNan(Type _value)
		{
			return std::isnan(_value);
		}

		static inline bool IsFinite(float _value) noexcept
		{
			return std::isfinite(_value);
		}
	}
}

#endif // !MATHFUNCTIONS_H
