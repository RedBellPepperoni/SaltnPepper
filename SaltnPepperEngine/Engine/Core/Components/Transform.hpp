#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "Utilities/MathDefinitions.hpp"

namespace SaltnPepperEngine
{
	namespace Components
	{
		struct Transform
		{
			enum FLAGS : uint8_t
			{
				NONE = 0,
				DIRTY = 1 << 0
			};


			// =============== SERIALIZED VARILABLES =================

			uint32_t flags = DIRTY;

			// the Local Position of the Transform
			Vector3 localPosition = Vector3{ 0.0f,0.0f,0.0f };

			// the Local Scale of the Transform
			Vector3 localScale = Vector3{1.0f,1.0f,1.0f};

			// the Local Rotation of the Transform
			Quaternion localRotation = Quaternion{ 0.0f,0.0f,0.0f,1.0f };
			

			// ================= NON SERIALIZED VARIBALES ==============

			// The world transformation matrix used to get the final tranformations on the given Object
			Matrix4 worldMatrix = IDENTITYMATRIX;


			constexpr inline void SetDirty(bool value = true)
			{
				value ? flags |= DIRTY : flags &= ~DIRTY;
			}

			constexpr inline bool IsDirty() const 
			{
				return flags & DIRTY; 
			}


			// ================ GETTERS ======================

			// World postion rotation sand scale getters
			const Vector3 GetPosition() const;
			const Vector3 GetScale() const;
			const Quaternion GetRotation() const;

			// Editor utilities
			const XMVECTOR GetPositionXM() const;
			const XMVECTOR GetScaleXM() const;
			const XMVECTOR GetRotationXM() const;
			


		};
	}
}


#endif // !TRANSFORM_H
