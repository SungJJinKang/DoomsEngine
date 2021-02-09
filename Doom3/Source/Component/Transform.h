#pragma once
#include "Core/CoreComponent.h"
#include "../Core/Math/LightMath_Cpp/Quaternion.h"
#include "../Core/Math/LightMath_Cpp/Vector3.h"
#include "../Core/Math/LightMath_Cpp/Matrix4x4.h"

namespace doom
{
	enum class eSpace
	{
		World,
		Self
	};

	class Transform : public CoreComponent 
	{
	private:
		/// <summary>
		/// why don't use FrameDirtyChecker::IsDirty -> FrameDirtyChecker is changed when pass frame
		/// but this modelMatrix is calculated when this is needed ( not every frame )
		/// </summary>
		math::Matrix4x4 mModelMatrixCache;
		bool bmIsDirtyModelMatrix;

		math::Matrix4x4 mLocalToWorldMatrix{ 1.0f };
		math::Matrix4x4 mWorldToLocalMatrix{ 1.0f };

		math::Vector3 mPosition;
		math::Quaternion mRotation;
		math::Vector3 mScale;

		Transform(const Transform&) = delete;
		Transform(Transform&&) noexcept = delete;
		Transform& operator=(const Transform&) = delete;
		Transform& operator=(Transform&&) noexcept = delete;

		virtual void InitComponent() final;
		virtual void UpdateComponent() final;
		virtual void OnEndOfFrame_Component() final;

	public:

		Transform(){}

		constexpr void SetPosition(const math::Vector3& position)
		{
			this->mPosition = position;
			this->SetDirtyTrueAtThisFrame();
			this->mModelMatrixCache = true;
		}
		constexpr void SetRotation(const math::Quaternion& rotation)
		{
			this->mRotation = rotation;
			this->SetDirtyTrueAtThisFrame();
			this->mModelMatrixCache = true;
		}

		constexpr void SetScale(const math::Vector3& scale)
		{
			this->mScale = scale;
			this->SetDirtyTrueAtThisFrame();
			this->mModelMatrixCache = true;
		}
		constexpr math::Vector3 GetPosition() const
		{
			return this->mPosition;
		}
		constexpr math::Quaternion GetRotation() const
		{
			return this->mRotation;
		}
		constexpr math::Vector3 GetScale() const
		{
			return this->mScale;
		}

		constexpr math::Matrix4x4 GetModelMatrix() 
		{
			if (this->bmIsDirtyModelMatrix == false)
			{
				return this->mModelMatrixCache;
			}
			else
			{
				this->mModelMatrixCache = math::Matrix4x4::identify;
				this->mModelMatrixCache = math::translate(this->mModelMatrixCache, this->mPosition);
				this->mModelMatrixCache = this->mModelMatrixCache * static_cast<math::Matrix4x4>(this->mRotation);
				this->mModelMatrixCache = math::scale(this->mModelMatrixCache, this->mScale);
				this->mModelMatrixCache *= this->mLocalToWorldMatrix;

				this->bmIsDirtyModelMatrix = false;

				return this->mModelMatrixCache;
			}
		}

		constexpr math::Matrix4x4 GetViewMatrix()
		{
			return math::lookAt(this->mPosition, this->forward() + this->mPosition, this->up());
		}

		constexpr math::Vector3 forward() const
		{
			return this->mRotation * math::Vector3::forward;
		}
		constexpr math::Vector3 right() const
		{
			return this->mRotation * math::Vector3::right;
		}
		constexpr math::Vector3 up() const
		{
			return this->mRotation * math::Vector3::up;
		}

		constexpr void LookAt(const Transform& target, const math::Vector3& up)
		{
			this->SetRotation(static_cast<math::Quaternion>(math::lookAt(this->mPosition, target.mPosition, up)));
		}
		constexpr void Rotate(const math::Vector3& eulerAngles, const eSpace& relativeTo)
		{
			this->SetRotation(this->mRotation *= math::Quaternion(eulerAngles));
		}
		constexpr void RotateAround(const math::Vector3& point, const math::Vector3& axis, float angle)
		{

		}

		constexpr math::Vector3 TransformDirection(const math::Vector3& direction) const
		{
			return this->mRotation * direction;
		}
		constexpr math::Vector3 TransformPoint(const math::Vector3& point) const
		{
			return this->mRotation * point;
		}
		constexpr math::Vector3 TransformVector(const math::Vector3& vector) const
		{
			return this->mRotation * vector;
		}
		constexpr void Translate(const math::Vector3& translation, const eSpace& relativeTo) 
		{

		}

	};

}