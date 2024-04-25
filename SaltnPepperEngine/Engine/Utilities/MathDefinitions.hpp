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

		

	}
}

#endif // !MATHDEFINITIONS_H
