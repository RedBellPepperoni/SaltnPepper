#include "Transform.hpp"

namespace SaltnPepperEngine
{
	namespace Components
	{
		const Vector3 Transform::GetPosition() const
		{
			return *((Vector3*)&worldMatrix._41);
		}

		const Vector3 Transform::GetScale() const
		{
			Vector3 scale{1.0f,1.0f,1.0f};
			XMStoreFloat3(&scale, GetScaleRaw());
			return scale;

		}

		const Quaternion Transform::GetRotation() const
		{
			Quaternion rot{ 0.0f,0.0f,0.0f,1.0f };
			XMStoreFloat4(&rot, GetRotationRaw());
			return rot;
		}

		const XMVECTOR Transform::GetPositionRaw() const
		{
			return XMLoadFloat3((Vector3*)&worldMatrix._41);
		}

		const XMVECTOR Transform::GetScaleRaw() const
		{
			XMVECTOR Scale;
			XMVECTOR Rotation;
			XMVECTOR Translation;

			XMMatrixDecompose(&Scale, &Rotation, &Translation, XMLoadFloat4x4(&worldMatrix));
			return Scale;
		}

		const XMVECTOR Transform::GetRotationRaw() const
		{
			XMVECTOR Scale;
			XMVECTOR Rotation;
			XMVECTOR Translation;

			XMMatrixDecompose(&Scale, &Rotation, &Translation, XMLoadFloat4x4(&worldMatrix));
			return Rotation;
		}

		inline const Vector3 Transform::GetForward() const
		{
			return Math::GetForward(worldMatrix);
		}

		inline const Vector3 Transform::GetRight() const
		{
			return Math::GetRight(worldMatrix);
		}

		inline const Vector3 Transform::GetUp() const
		{
			return Math::GetUp(worldMatrix);
		}

		const XMVECTOR Transform::GetForwardRaw() const
		{
			Vector3 forward = GetForward();
			return XMLoadFloat3(&forward);
		}

		const XMVECTOR Transform::GetRightRaw() const
		{
			Vector3 right = GetRight();
			return XMLoadFloat3(&right);
		}

		const XMVECTOR Transform::GetUpRaw() const
		{
			Vector3 up = GetUp();
			return XMLoadFloat3(&up);
		}

		const Matrix4 Transform::GetlocalMatrix() const
		{
			Matrix4 matrix;
			XMStoreFloat4x4(&matrix, GetlocalMatrixRaw());
			return matrix;
		}

		const XMMATRIX Transform::GetlocalMatrixRaw() const
		{
			XMVECTOR LocalScale = XMLoadFloat3(&localScale);
			XMVECTOR LocalRotation = XMLoadFloat4(&localRotation);
			XMVECTOR LocalTranslation = XMLoadFloat3(&localPosition);

			return XMMatrixScalingFromVector(LocalScale) * XMMatrixRotationQuaternion(LocalRotation) * XMMatrixTranslationFromVector(LocalTranslation);
		}

		void Transform::Translate(const Vector3& translation)
		{
		}

		void Transform::Translate(const XMVECTOR& translation)
		{
		}

		void Transform::Rotate(const Quaternion& rotation)
		{
		}

		void Transform::Rotate(const XMVECTOR& rotation)
		{
		}

		void Transform::Scale(const Vector3& scale)
		{
		}

		void Transform::Scale(const XMVECTOR& scale)
		{
		}

		void Transform::ClearTransform()
		{
			SetDirty();
			localPosition = Vector3{ 0.0f, 0.0f, 0.0f };
			localScale = Vector3{ 1.0f ,1.0f, 1.0f};
			localRotation = Quaternion{ 0.0f, 0.0f, 0.0f,1.0f };
		}

		void Transform::UpdateTransform()
		{
			if (!IsDirty()) return;

			SetDirty(false);
			XMStoreFloat4x4(&worldMatrix, GetlocalMatrixRaw());

		}

		void Transform::UpdateParentTransform(const Transform& parent)
		{
			// local matrix * parent's world matrix 
			XMMATRIX World = GetlocalMatrixRaw() * XMLoadFloat4x4(&parent.worldMatrix);
			XMStoreFloat4x4(&worldMatrix, World);
		}

		void Transform::ApplyTransform()
		{
			SetDirty();

			XMVECTOR Scale;
			XMVECTOR Rotation;
			XMVECTOR Translation;

			XMMatrixDecompose(&Scale, &Rotation, &Translation, XMLoadFloat4x4(&worldMatrix));

			XMStoreFloat3(&localScale, Scale);
			XMStoreFloat4(&localRotation, Rotation);
			XMStoreFloat3(&localPosition, Translation);

		}
	}
}