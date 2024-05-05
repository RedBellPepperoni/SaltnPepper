#ifndef MATHDEFINITIONS_H
#define MATHDEFINITIONS_H


#if __has_include("DirectXMath.h")
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>
#else

#include "Utility/DirectXMath.h"
#include "Utility/DirectXPackedVector.h"
#include "Utility/DirectXCollision.h"
#endif

#include <cmath>
#include <algorithm>
#include <limits>


using namespace DirectX;
using namespace DirectX::PackedVector;

namespace SaltnPepperEngine
{
	namespace Math
	{
		// Defines for wrapping over Direct X floating point vectors
		using Vector2 = XMFLOAT2;
		using Vector3 = XMFLOAT3;
		using Vector4 = XMFLOAT4;

		// Defines for wrapping over Direct X integer vectors
		using Vector2Int = XMINT2;
		using Vector3Int = XMINT3;
		using Vector4Int = XMINT4;

		// Defines for wrapping over Direct X matrices
		using Matrix3 = XMFLOAT3X3;
		using Matrix4 = XMFLOAT4X4;
		using Matrix3X4 = XMFLOAT3X4;
		using Matrix4X3 = XMFLOAT4X3;

		// Defines for wrapping over Direct X vector
		using Quaternion = XMFLOAT4;


		// Identity Matrix
		inline static constexpr Matrix4 IDENTITYMATRIX = Matrix4(1, 0, 0, 0,
																 0, 1, 0, 0,
																 0, 0, 1, 0,
																 0, 0, 0, 1);

		inline static constexpr float PI = XM_PI;
		inline static constexpr float TWOPI = XM_2PI;
		inline static constexpr float HALFPI = XM_PIDIV2;
		inline static constexpr float EPSILON = FLT_EPSILON;


		// General Math Wrappers

		/// <summary>
		/// Returns the Square root of a value
		/// </summary>

		template <typename T>
		static inline T SquareRoot(T value)
		{
			return std::sqrt(value);
		}


		// ================ VECTOR FUNCTION ===============================

		// ============= LENGTH and DISTANCE ======================

		/// <summary>
		///  Get the Squared length/Magnitude of the given vector (faster than Length())
		/// </summary>
		/// <param name="Vector2"></param>
		/// <returns> float </returns>
		static constexpr float LengthSquared(const Vector2& vector)
		{
			return (vector.x * vector.x + vector.y * vector.y);
		}

		/// <summary>
		///  Get the Squared length/Magnitude of the given vector (faster than Length())
		/// </summary>
		/// <param name="Vector4"></param>
		/// <returns> float </returns>
		static constexpr float LengthSquared(const Vector4& vector)
		{
			return (vector.x * vector.x + vector.y * vector.y + vector.z * vector.z + vector.w * vector.w);
		}


		/// <summary>
		///  Get the actual Length/Magnitude of the given vector (slower than LengthSquared())
		/// </summary>
		/// <param name="Vector2"></param>
		/// <returns> float </returns>
		static inline float Length(const Vector2& vector)
		{
			return std::sqrt(LengthSquared(vector));
		}


		/// <summary>
		///  Get the Squared length/Magnitude of the given vector (faster than Length())
		/// </summary>
		/// <param name="Vector3"></param>
		/// <returns> float </returns>
		static constexpr float LengthSquared(const Vector3& vector)
		{
			return (vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
		}

		/// <summary>
		///  Get the actual Length/Magnitude of the given vector (slower than LengthSquared())
		/// </summary>
		/// <param name="Vector4"></param>
		/// <returns> float </returns>
		static inline float Length(const Vector4& vector)
		{
			return std::sqrt(LengthSquared(vector));
		}

		

		/// <summary>
		///  Get the actual Length/Magnitude of the given vector (slower than LengthSquared())
		/// </summary>
		/// <param name="Vector3"></param>
		/// <returns> float </returns>
		static inline float Length(const Vector3& vector)
		{
			return std::sqrt(LengthSquared(vector));
		}


		/// <summary>
		///  Get the Squared Distance between the two provided Vectors (faster than Distance())
		/// </summary>
		/// <param name="XMVECTOR"></param>
		/// <param name="XMVECTOR"></param>
		/// <returns> float </returns>
		static const float DistanceSquared(const XMVECTOR& vectorOne, const XMVECTOR& vectorTwo)
		{
			return XMVectorGetX(XMVector2LengthSq(XMVectorSubtract(vectorOne, vectorTwo)));
		}

		/// <summary>
		///  Get the actual Distance between the two provided Vectors (slower than DistanceSquared())
		/// </summary>
		/// <param name="XMVECTOR"></param>
		/// <param name="XMVECTOR"></param>
		/// <returns> float </returns>
		static const float Distance(const XMVECTOR& vectorOne, const XMVECTOR& vectorTwo)
		{
			return XMVectorGetX(XMVector2Length(XMVectorSubtract(vectorOne, vectorTwo)));
		}

		/// <summary>
		///  Get the estimated distance between two Vectors (faster but less accurate than Distance())
		/// </summary>
		/// <param name="XMVECTOR"></param>
		/// <param name="XMVECTOR"></param>
		/// <returns> float </returns>
		static const float DistanceEstimated(const XMVECTOR& vectorOne, const XMVECTOR& vectorTwo)
		{
			return XMVectorGetX(XMVector3LengthEst(XMVectorSubtract(vectorOne, vectorTwo)));
		}

		/// <summary>
		///  Get the actual Distance between the two provided Vectors (slower than DistanceSquared())
		/// </summary>
		/// <param name="Vector2"></param>
		/// <param name="Vector2"></param>
		/// <returns> float </returns>
		static const float Distance(const Vector2& vectorOne, const Vector2& vectorTwo)
		{
			const XMVECTOR vecOne = XMLoadFloat2(&vectorOne);
			const XMVECTOR vecTwo = XMLoadFloat2(&vectorTwo);

			return Distance(vecOne, vecTwo);
		}

		

		/// <summary>
		///  Get the Squared Distance between the two provided Vectors (faster than Distance())
		/// </summary>
		/// <param name="Vector2"></param>
		/// <param name="Vector2"></param>
		/// <returns> float </returns>
		static const float DistanceSquared(const Vector2& vectorOne, const Vector2& vectorTwo)
		{
			const XMVECTOR vecOne = XMLoadFloat2(&vectorOne); 
			const XMVECTOR vecTwo = XMLoadFloat2(&vectorTwo); 

			return DistanceSquared(vecOne, vecTwo);
		}

		/// <summary>
		///  Get the estimated distance between two Vectors (faster but less accurate than Distance())
		/// </summary>
		/// <param name="Vector2"></param>
		/// <param name="Vector2"></param>
		/// <returns> float </returns>
		static const float DistanceEstimated(const Vector2& vectorOne, const Vector2& vectorTwo)
		{
			XMVECTOR vecOne = XMLoadFloat2(&vectorOne);
			XMVECTOR vecTwo = XMLoadFloat2(&vectorTwo);
		
			return XMVectorGetX(XMVector2LengthEst(vecTwo - vecOne));
		}

		/// <summary>
		///  Get the actual Distance between the two provided Vectors (slower than DistanceSquared())
		/// </summary>
		/// <param name="Vector3"></param>
		/// <param name="Vector3"></param>
		/// <returns> float </returns>
		static const float Distance(const Vector3& vectorOne, const Vector3& vectorTwo)
		{
			const XMVECTOR vecOne = XMLoadFloat3(&vectorOne);
			const XMVECTOR vecTwo = XMLoadFloat3(&vectorTwo);

			return Distance(vectorOne, vectorTwo);
		}


		/// <summary>
		///  Get the Squared Distance between the two provided Vectors (faster than Distance())
		/// </summary>
		/// <param name="Vector3"></param>
		/// <param name="Vector3"></param>
		/// <returns> float </returns>
		static const float DistanceSquared(const Vector3& vectorOne, const Vector3& vectorTwo)
		{
			const XMVECTOR vecOne = XMLoadFloat3(&vectorOne);
			const XMVECTOR vecTwo = XMLoadFloat3(&vectorTwo);

			return DistanceSquared(vecOne, vecTwo);
		}

		/// <summary>
		///  Get the estimated distance between two Vectors (faster but less accurate than Distance())
		/// </summary>
		/// <param name="Vector3"></param>
		/// <param name="Vector3"></param>
		/// <returns> float </returns>
		static const float DistanceEstimated(const Vector3& vectorOne, const Vector3& vectorTwo)
		{
			XMVECTOR vecOne = XMLoadFloat3(&vectorOne);
			XMVECTOR vecTwo = XMLoadFloat3(&vectorTwo);

			return DistanceEstimated(vecOne, vecTwo);
		}

		// ========================== TRANSFORM VECTORS =============

		/// <summary>
		/// Returns the Forward vector for a given Transform matrix
		/// </summary>
		/// <returns> Vector3 </returns>
		inline static constexpr Vector3 GetForward(const Matrix4& matrix)
		{
			return Vector3{ matrix.m[2][0],matrix.m[2][1], matrix.m[2][2] };
		}

		/// <summary>
		/// Returns the Up vector for a given Transform matrix
		/// </summary>
		/// <returns> Vector3 </returns>
		inline static constexpr Vector3 GetUp(const Matrix4& matrix)
		{
			return Vector3{ matrix.m[1][0],matrix.m[1][1], matrix.m[1][2] };
		}

		/// <summary>
		/// Returns the Right vector for a given Transform matrix
		/// </summary>
		/// <returns> Vector3 </returns>
		inline static constexpr Vector3 GetRight(const Matrix4& matrix)
		{
			return Vector3{ matrix.m[0][0],matrix.m[0][1], matrix.m[0][2] };
		}


		// =========================== DOT and CROSS =========================================


		/// <summary>
		/// Get the Dot Product of the given vectors
		/// </summary>
		/// <param name="Vector2"></param>
		/// <param name="Vector2"></param>
		/// <returns> float </returns>
		static const float Dot(const Vector2& vectorOne, const Vector2& vectorTwo)
		{
			/*XMVECTOR vecOne = XMLoadFloat2(&vectorOne);
			XMVECTOR vecTwo = XMLoadFloat2(&vectorTwo);
			return XMVectorGetX(XMVector2Dot( vecOne, vecTwo));*/

			return vectorOne.x * vectorTwo.x + vectorOne.y * vectorTwo.y;

		}

		/// <summary>
		/// Get the Dot Product of the given vectors
		/// </summary>
		/// <param name="Vector3"></param>
		/// <param name="Vector3"></param>
		/// <returns> float </returns>
		static const float Dot(const Vector3& vectorOne, const Vector3& vectorTwo)
		{
			/*XMVECTOR vecOne = XMLoadFloat3(&vectorOne);
			XMVECTOR vecTwo = XMLoadFloat3(&vectorTwo);
			return XMVectorGetX(XMVector3Dot(vecOne, vecTwo));*/

			return vectorOne.x * vectorTwo.x + vectorOne.y * vectorTwo.y + vectorOne.z * vectorTwo.z;
		}

		/// <summary>
		/// Get the Dot Product of the given vectors
		/// </summary>
		/// <param name="Vector4"></param>
		/// <param name="Vector4"></param>
		/// <returns> float </returns>
		static const float Dot(const Vector4& vectorOne, const Vector4& vectorTwo)
		{
		/*	XMVECTOR vecOne = XMLoadFloat4(&vectorOne);
			XMVECTOR vecTwo = XMLoadFloat4(&vectorTwo);
			return XMVectorGetX(XMVector4Dot(vecOne,vecTwo));*/

			return vectorOne.x * vectorTwo.x + vectorOne.y * vectorTwo.y + vectorOne.z * vectorTwo.z + vectorOne.w * vectorTwo.w;
		}

		/// <summary>
		///  Returns teh Cross Product of two Vectors
		/// </summary>
		/// <returns> Vector2 </returns>
		static const Vector2 Cross(const Vector2& vectorOne, const Vector2& vectorTwo)
		{
			XMVECTOR vecOne = XMLoadFloat2(&vectorOne);
			XMVECTOR vecTwo = XMLoadFloat2(&vectorTwo);
			
			Vector2 result;
			XMStoreFloat2( &result , XMVector2Cross(vecOne, vecTwo));	

			return result;
		}

		/// <summary>
		///  Returns teh Cross Product of two Vectors
		/// </summary>
		/// <returns> Vector3 </returns>
		static const Vector3 Cross(const Vector3& vectorOne, const Vector3& vectorTwo)
		{
			XMVECTOR vecOne = XMLoadFloat3(&vectorOne);
			XMVECTOR vecTwo = XMLoadFloat3(&vectorTwo);

			Vector3 result;
			XMStoreFloat3(&result, XMVector2Cross(vecOne, vecTwo));

			return result;
		}


		/// <summary>
		///  Returns teh Cross Product of two Vectors
		/// </summary>
		/// <returns> Vector3 </returns>
		static const Vector4 Cross(const Vector4& vectorOne, const Vector4& vectorTwo)
		{
			XMVECTOR vecOne = XMLoadFloat4(&vectorOne);
			XMVECTOR vecTwo = XMLoadFloat4(&vectorTwo);

			Vector4 result;
			XMStoreFloat4(&result, XMVector2Cross(vecOne, vecTwo));

			return result;
		}

		/// <summary>
		///  Warpper for the Max fucntion for Vector2
		/// </summary>
		/// <returns> Vector2 </returns>
		static constexpr Vector2 Max(const Vector2& vectorOne, const Vector2& vectorTwo)
		{
			return Vector2 { Max(vectorOne.x,vectorTwo.x), Max(vectorOne.y, vectorTwo.y)};
		}

		/// <summary>
		///  Warpper for the Max fucntion for Vector3
		/// </summary>
		/// <returns> Vector2 </returns>
		static constexpr Vector3 Max(const Vector3& vectorOne, const Vector3& vectorTwo)
		{
			return Vector3{ Max(vectorOne.x,vectorTwo.x), Max(vectorOne.y, vectorTwo.y) , Max(vectorOne.z,vectorTwo.z)};
		}

		/// <summary>
		///  Warpper for the Max fucntion for Vector4
		/// </summary>
		/// <returns> Vector2 </returns>
		static constexpr Vector4 Max(const Vector4& vectorOne, const Vector4& vectorTwo)
		{
			return Vector4{ Max(vectorOne.x,vectorTwo.x), Max(vectorOne.y, vectorTwo.y) ,  Max(vectorOne.z,vectorTwo.z), Max(vectorOne.w,vectorTwo.w) };
		}

		/// <summary>
		///  Returns angle (in Radians) between the two Vector2s
		/// </summary>
		/// <returns> float </returns>
		static const float GetAngle(const Vector2& vectorOne, const Vector2& vectorTwo)
		{
			
			float dot = Dot(vectorOne, vectorTwo);  
			float determinant = vectorOne.x * vectorTwo.x - vectorOne.y * vectorTwo.y;		
			float angle = atan2f(determinant, dot);	

			if (angle < 0)
			{
				angle += PI;
			}

			return angle;
		}

		/// <summary>
		///  Returns angle (in Radians) between the two XMVECTORS
		/// </summary>
		/// <returns> float </returns>
		static const float GetAngle(XMVECTOR vectorOne, XMVECTOR vectorTwo, XMVECTOR axis, float max) 
		{
			float angle = XMVectorGetX(XMVector3AngleBetweenVectors(vectorOne, vectorTwo));

			angle = Min(angle, max);

			if (XMVectorGetX(XMVector3Dot(XMVector3Cross(vectorOne, vectorTwo), axis)) < 0)
			{
				angle = TWOPI - angle;
			}

			return angle;
		}

		/// <summary>
		///  Returns angle (in Radians) between the two Vector3s
		/// </summary>
		/// <returns> float </returns>
		static const float GetAngle(const Vector3& vectorOne, const Vector3& vectorTwo, const Vector3& axis, float max)
		{
			XMVECTOR vecOne = XMLoadFloat3(&vectorOne);
			XMVECTOR vecTwo = XMLoadFloat3(&vectorTwo);
			XMVECTOR Axis = XMLoadFloat3(&axis);
			return GetAngle(vecOne, vecTwo, Axis, max);
		}

		//======================= LERPS and SLERPS ==============================

		/// <summary>
		/// Lerps Between Two values according to the given Delta
		/// </summary>
		/// <returns> float</returns>
		constexpr float Lerp(const float valueOne, const float valueTwo, float delta)
		{
			return valueOne + (valueTwo - valueOne) * delta;
		}

		/// <summary>
		/// Lerps Between Two values according to the given Delta
		/// </summary>
		/// <returns> XMVECTOR </returns>
		static const XMVECTOR Lerp(XMVECTOR valueOne, XMVECTOR valueTwo, XMVECTOR delta)
		{
			return valueOne + (valueTwo - valueOne) * delta;;
		}

		/// <summary>
		/// Lerps Between Two values according to the given Delta
		/// </summary>
		/// <returns> Vector2 </returns>
		static const Vector2 Lerp(const Vector2& vectorOne, const Vector2& vectorTwo, float delta)
		{
			return Vector2(Lerp(vectorOne.x, vectorTwo.x, delta), Lerp(vectorOne.y, vectorTwo.y, delta));
		}

		/// <summary>
		/// Lerps Between Two values according to the given Delta
		/// </summary>
		/// <returns> Vector3 </returns>
		static const Vector3 Lerp(const Vector3& vectorOne, const Vector3& vectorTwo, float delta)
		{
			return Vector3(Lerp(vectorOne.x, vectorTwo.x, delta), Lerp(vectorOne.y, vectorTwo.y, delta), Lerp(vectorOne.z, vectorTwo.z, delta));
		}

		/// <summary>
		/// Lerps Between Two values according to the given Delta
		/// </summary>
		/// <returns> Vector2 </returns>
		static const Vector4 Lerp(const Vector4& vectorOne, const Vector4& vectorTwo, float delta)
		{
			return Vector4(Lerp(vectorOne.x, vectorTwo.x, delta), Lerp(vectorOne.y, vectorTwo.y, delta), Lerp(vectorOne.z, vectorTwo.z, delta), Lerp(vectorOne.w, vectorTwo.w, delta));
		}
		
		/// <summary>
		/// Lerps Between Two values according to the given Delta
		/// </summary>
		/// <returns> Quaternion </returns>
		static const Quaternion Slerp(const Quaternion& rotOne, const Quaternion& rotTwo, float delta)
		{
			// Load the Registers
			XMVECTOR quatOne = XMLoadFloat4(&rotOne);
			XMVECTOR quatTwo = XMLoadFloat4(&rotTwo);

			// Get the Slerp data
			XMVECTOR slerpedQuat = XMQuaternionSlerp(quatOne,quatTwo, delta);

			XMFLOAT4 returnVal = XMFLOAT4{};

			// Convert register data into a Quaternion (in out case a Float4)
			XMStoreFloat4(&returnVal, slerpedQuat);

			return returnVal; 
		}

		// ==================== MIN / MAX and CLAMP =========================

		/// <summary>
		/// Returns the Minimum values out of the two given values
		/// </summary>
		template <typename Type>
		static constexpr Type Min(Type valueOne, Type valueTwo)
		{
			return std::min(valueOne, valueTwo);
		}
		
		/// <summary>
		/// Returns the Maximum value out of the two given values
		/// </summary>
		template <typename Type>
		static constexpr float Max(Type valueOne, Type valueTwo)
		{
			return std::max(valueOne, valueTwo);
		}

		/// <summary>
		/// Returns the Clamped value between the provided min and Max values
		/// </summary>
		/// <returns>float</returns>
		static constexpr float Clamp(float value, float min, float max)
		{
			return Min(max, Max(min, value));
		}

		/// <summary>
		/// Returns the Clamped value between the provided min and Max values
		/// </summary>
		/// <returns>Vector2</returns>
		static constexpr Vector2 Clamp(Vector2 value, Vector2 min, Vector2 max)
		{
			Vector2 result = value;
			result.x = Clamp(result.x, min.x, max.x);
			result.y = Clamp(result.y, min.y, max.y);

			return result;
		}

		/// <summary>
		/// Returns the Clamped value between the provided min and Max values
		/// </summary>
		/// <returns>Vector3</returns>
		static constexpr Vector3 Clamp(Vector3 value, Vector3 min, Vector3 max)
		{
			Vector3 result = value;
			result.x = Clamp(result.x, min.x, max.x);
			result.y = Clamp(result.y, min.y, max.y);
			result.z = Clamp(result.z, min.z, max.z);

			return result;
		}


		/// <summary>
		/// Returns the Clamped value between the provided min and Max values
		/// </summary>
		/// <returns>Vector4</returns>
		static constexpr Vector4 Clamp(Vector4 value, Vector4 min, Vector4 max)
		{
			Vector4 result = value;
			result.x = Clamp(result.x, min.x, max.x);
			result.y = Clamp(result.y, min.y, max.y);
			result.z = Clamp(result.z, min.z, max.z);

			return result;
		}

		// ===================== RADIANS and DEGREES ===============

		/// <summary>
		///  Converts degress into Radians
		/// </summary>
		
		template <typename T>
		static constexpr T ToRadians(T degrees)
		{
			return degrees / 180.0f * PI;
		}

		/// <summary>
		///  Converts Radians into Degrees
		/// </summary>
		template <typename T>
		static constexpr T ToDegrees(T radians)
		{
			return radians / PI * 180.0f;
		}




		// ===================== TRIGNOMETRY MATHS =========================

		/// <summary>
		///  Gets the Sine of the given angle in degrees (angle should be in degrees)
		/// </summary>
		/// <returns> float </returns>
		static constexpr float Sin(float angle)
		{
			return ToDegrees(std::sin(angle));
		}


		/// <summary>
		///  Gets the CoSine of the given angle in degrees (angle should be in degrees)
		/// </summary>
		template <typename T>
		static constexpr T Cos(T angle)
		{
			return ToDegrees(std::cos(angle));
		}


		/// <summary>
		///  Gets the Tangent of the given angle in degrees (angle should be in degrees)
		/// </summary>
		
		template <typename T>
		static constexpr T Tan(T angle)
		{
			return ToDegrees(std::tan(angle));
		}



		/// <summary>
		///  Gets the Arc Sine of the given angle in degrees (angle should be in degrees)
		/// </summary>
		/// <returns> float </returns>
		template <typename T>
		static constexpr T ASin(T angle)
		{
			return ToDegrees(std::asin(Clamp(angle,T(-1.0f),T(1.0f)))); 
		}


		/// <summary>
		///  Gets the Arc CoSine of the given angle in degrees (angle should be in degrees)
		/// </summary>
		template <typename T>
		static constexpr T ACos(T angle)
		{
			return ToDegrees(std::acos(Clamp(angle, T(-1.0f),T(1.0f)))); 
			
		}


		/// <summary>
		///  Gets the Arc Tangent of the given angle in degrees (angle should be in degrees)
		/// </summary>
		template <typename T>
		static constexpr T ATan(T angle)
		{
			return ToDegrees(std::atan(Clamp(angle, T( - 1.0f), T(1.0f))));
		}

		/// <summary>
		///  Gets the Arc Tangent of the given angle in y/x degrees (angle should be in degrees)
		/// </summary>
		template <typename T>
		static constexpr T ATan(T angle)
		{
			return ToDegrees(std::atan(Clamp(angle, T(-1.0f), T(1.0f))));
		}

		// ====================== ROOTS and LOGS =====================
	
		/// <summary>
		/// Return the type initialized with Root Two
		/// </summary>
		/// <typeparam name="Type"></typeparam>
		/// <returns> Type </returns>
		template <typename T>
		inline static constexpr T RootTwo()
		{
			return T{ 1.41421356237309504880168872420969808 };
		}

		/// <summary>
		/// Return the type initialized with Root Three
		/// </summary>
		/// <typeparam name="Type"></typeparam>
		/// <returns> Type </returns>
		template <typename T>
		inline static constexpr T RootThree()
		{
			return T{ 1.73205080756887729352744634150587236 };
		}

		/// <summary>
		/// Return the type initialized with Root Five
		/// </summary>
		/// <typeparam name="Type"></typeparam>
		/// <returns> Type </returns>
		template <typename T>
		inline static constexpr T RootFive()
		{
			return T{ 2.23606797749978969640917366873127623 };
		}
		/// <summary>
		/// Return the type initialized with Log of Two
		/// </summary>
		/// <typeparam name="Type"></typeparam>
		/// <returns> Type </returns>
		template <typename Type>
		inline static constexpr Type LogTwo()
		{
			return Type{ 0.693147180559945309417232121458176568 };
		}

		/// <summary>
		/// Return the type initialized with Log of Ten
		/// </summary>
		/// <typeparam name="Type"></typeparam>
		/// <returns> Type </returns>
		template <typename T>
		inline static constexpr T LogTen()
		{
			return T{ 2.30258509299404568401799145468436421 };
		}

		/// <summary>
		/// Return the type initialized with Golden Ratio
		/// </summary>
		/// <typeparam name="Type"></typeparam>
		/// <returns> Type </returns>
		template <typename T>
		inline static constexpr T GoldenRatio()
		{
			return T{ 1.61803398874989484820458683436563811 };
		}

	}

	using namespace Math;
}

#endif // !MATHDEFINITIONS_H
