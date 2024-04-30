#include "Transform.hpp"

namespace SaltnPepperEngine
{
	namespace Components
	{
		const Vector3 Transform::GetPosition() const
		{
			return Vector3();
		}

		const Vector3 Transform::GetScale() const
		{
			return Vector3();
		}

		const Quaternion Transform::GetRotation() const
		{
			return Quaternion();
		}

		const XMVECTOR Transform::GetPositionXM() const
		{
			return XMVECTOR();
		}

		const XMVECTOR Transform::GetScaleXM() const
		{
			return XMVECTOR();
		}

		const XMVECTOR Transform::GetRotationXM() const
		{
			return XMVECTOR();
		}
	}
}