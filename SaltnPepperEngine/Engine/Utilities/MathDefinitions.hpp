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
	
		using Vector2 = XMFLOAT2;
		using Vector3 = XMFLOAT3;
		using Vector4 = XMFLOAT4;

		using Vector2Int = XMINT2;
		using Vector3Int = XMINT3;
		using Vector4Int = XMINT4;

		using Matrix3 = XMFLOAT3X3;
		using Matrix4 = XMFLOAT4X4;
		using Matrix3X4 = XMFLOAT3X4;
		using Matrix4X3 = XMFLOAT4X3;

		using Quaternion = XMFLOAT4;


		// Values Defines
		inline static constexpr Matrix4 IDENTITYMATRIX = Matrix4(1, 0, 0, 0,
														  0, 1, 0, 0,
														  0, 0, 1, 0,
														  0, 0, 0, 1);

		inline static constexpr float PI = XM_PI;
		inline static constexpr float HALFPI = XM_PIDIV2;
		inline static constexpr float EPSILON = FLT_EPSILON;

		inline static constexpr float DEGtoRAD = PI / 180.0f;
		inline static constexpr float DEGtoRAD_2 = PI / 360.0f;
		inline static constexpr float RADtoDEG = 1.0f / DEGtoRAD;
		inline static constexpr float RADtoDEG_2 = 1.0f / DEGtoRAD_2;

		// Genral Math Wrappers

		const inline float SquareRoot(const float value)
		{
			return std::sqrt(value);
		}


		// ================ VECTOR FUNCTION ===============================

		// ============= Length and Distances ======================

		/// <summary>
		///  Get the Squared length/Magnitude of the given vector (faster than Length())
		/// </summary>
		/// <param name="Vector2"></param>
		/// <returns> float </returns>
		const inline float LengthSquared(const Vector2& vector)
		{
			return (vector.x * vector.x + vector.y * vector.y);
		}

		/// <summary>
		///  Get the actual Length/Magnitude of the given vector (slower than LengthSquared())
		/// </summary>
		/// <param name="Vector2"></param>
		/// <returns> float </returns>
		const inline float Length(const Vector2& vector)
		{
			return std::sqrt(LengthSquared(vector));
		}

		/// <summary>
		///  Get the Squared length/Magnitude of the given vector (faster than Length())
		/// </summary>
		/// <param name="Vector3"></param>
		/// <returns> float </returns>
		const inline float LengthSquared(const Vector3& vector)
		{
			return (vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
		}

		/// <summary>
		///  Get the actual Length/Magnitude of the given vector (slower than LengthSquared())
		/// </summary>
		/// <param name="Vector4"></param>
		/// <returns> float </returns>
		const inline float Length(const Vector4& vector)
		{
			return std::sqrt(LengthSquared(vector));
		}

		/// <summary>
		///  Get the Squared length/Magnitude of the given vector (faster than Length())
		/// </summary>
		/// <param name="Vector4"></param>
		/// <returns> float </returns>
		const inline float LengthSquared(const Vector4& vector)
		{
			return (vector.x * vector.x + vector.y * vector.y + vector.z * vector.z + vector.w * vector.w);
		}

		/// <summary>
		///  Get the actual Length/Magnitude of the given vector (slower than LengthSquared())
		/// </summary>
		/// <param name="Vector3"></param>
		/// <returns> float </returns>
		const inline float Length(const Vector3& vector)
		{
			return std::sqrt(LengthSquared(vector));
		}


		/// <summary>
		///  Get the Squared Distance between the two provided Vectors (faster than Distance())
		/// </summary>
		/// <param name="XMVECTOR"></param>
		/// <param name="XMVECTOR"></param>
		/// <returns> float </returns>
		const inline float DistanceSquared(const XMVECTOR& vectorOne, const XMVECTOR& vectorTwo)
		{
			return XMVectorGetX(XMVector2LengthSq(XMVectorSubtract(vectorOne, vectorTwo)));
		}

		/// <summary>
		///  Get the actual Distance between the two provided Vectors (slower than DistanceSquared())
		/// </summary>
		/// <param name="XMVECTOR"></param>
		/// <param name="XMVECTOR"></param>
		/// <returns> float </returns>
		const inline float Distance(const XMVECTOR& vectorOne, const XMVECTOR& vectorTwo)
		{
			return XMVectorGetX(XMVector2Length(XMVectorSubtract(vectorOne, vectorTwo)));
		}

		/// <summary>
		///  Get the actual Distance between the two provided Vectors (slower than DistanceSquared())
		/// </summary>
		/// <param name="Vector2"></param>
		/// <param name="Vector2"></param>
		/// <returns> float </returns>
		const inline float Distance(const Vector2& vectorOne, const Vector2& vectorTwo)
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
		const inline float DistanceSquared(const Vector2& vectorOne, const Vector2& vectorTwo)
		{
			const XMVECTOR vecOne = XMLoadFloat2(&vectorOne); 
			const XMVECTOR vecTwo = XMLoadFloat2(&vectorTwo); 

			return DistanceSquared(vecOne, vecTwo);
		}

		/// <summary>
		///  Get the actual Distance between the two provided Vectors (slower than DistanceSquared())
		/// </summary>
		/// <param name="Vector3"></param>
		/// <param name="Vector3"></param>
		/// <returns> float </returns>
		const inline float Distance(const Vector3& vectorOne, const Vector3& vectorTwo)
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
		const inline float DistanceSquared(const Vector3& vectorOne, const Vector3& vectorTwo)
		{
			const XMVECTOR vecOne = XMLoadFloat3(&vectorOne);
			const XMVECTOR vecTwo = XMLoadFloat3(&vectorTwo);

			return DistanceSquared(vecOne, vecTwo);
		}

		//======================= Lerps and Slerps ==============================

		/// <summary>
		/// Lerps Between Two values according to the given Delta
		/// </summary>
		/// <returns> float</returns>
		constexpr float Lerp(const float valueOne, const float valueTwo, const float delta)
		{
			return valueOne + (valueTwo - valueOne) * delta;
		}

		/// <summary>
		/// Lerps Between Two values according to the given Delta
		/// </summary>
		/// <returns> XMVECTOR </returns>
		const inline XMVECTOR Lerp(XMVECTOR valueOne, XMVECTOR valueTwo, XMVECTOR delta)
		{
			return valueOne + (valueTwo - valueOne) * delta;;
		}

		/// <summary>
		/// Lerps Between Two values according to the given Delta
		/// </summary>
		/// <returns> Vector2 </returns>
		constexpr Vector2 Lerp(const Vector2& vectorOne, const Vector2& vectorTwo, const float delta)
		{
			return Vector2(Lerp(vectorOne.x, vectorTwo.x, delta), Lerp(vectorOne.y, vectorTwo.y, delta));
		}

		/// <summary>
		/// Lerps Between Two values according to the given Delta
		/// </summary>
		/// <returns> Vector3 </returns>
		constexpr Vector3 Lerp(const Vector3& vectorOne, const Vector3& vectorTwo, const float delta)
		{
			return Vector3(Lerp(vectorOne.x, vectorTwo.x, delta), Lerp(vectorOne.y, vectorTwo.y, delta), Lerp(vectorOne.z, vectorTwo.z, delta));
		}

		constexpr Vector4 Lerp(const Vector4& vectorOne, const Vector4& vectorTwo, const float delta)
		{
			return Vector4(Lerp(vectorOne.x, vectorTwo.x, delta), Lerp(vectorOne.y, vectorTwo.y, delta), Lerp(vectorOne.z, vectorTwo.z, delta), Lerp(vectorOne.w, vectorTwo.w, delta));
		}
		
		inline Quaternion Slerp(const Quaternion& rotOne, const Quaternion& rotTwo, const float delta)
		{
			XMVECTOR quatOne = XMLoadFloat4(&rotOne);
			XMVECTOR quatTwo = XMLoadFloat4(&rotTwo);
			XMVECTOR result = XMQuaternionSlerp(quatOne,quatTwo, delta);

			XMFLOAT4 retVal; 
			XMStoreFloat4(&retVal, result); 

			return retVal; 
		}

		// ===================== TRIGNOMETRY MATHS =========================

		// Sine of the angle  (angle should be in degrees)
		inline float Sin(float angle)
		{
			return std::sin(angle * DEGtoRAD);
		}
	
	}
}

#endif // !MATHDEFINITIONS_H
