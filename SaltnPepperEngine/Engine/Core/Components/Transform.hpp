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

			// RAW Editor utilities
			const XMVECTOR GetPositionRaw() const;
			const XMVECTOR GetScaleRaw() const;
			const XMVECTOR GetRotationRaw() const;

		
			// Forward Right and Up Vectors
			inline const Vector3 GetForward() const;
			inline const Vector3 GetRight() const;
			inline const Vector3 GetUp() const;

			// RAW Forward Utils
			const XMVECTOR GetForwardRaw() const;
			const XMVECTOR GetRightRaw() const;
			const XMVECTOR GetUpRaw() const;
			
			// Local Matrix (Gets the loacl matric defined by the location , scale and rotation)
			const Matrix4 GetlocalMatrix() const;
			// Raw local matirx values
			const XMMATRIX GetlocalMatrixRaw() const;
		};
	}
}


#endif // !TRANSFORM_H
