#pragma once
#include "Core/PlainComponent.h"
#include "../Core/Math/LightMath_Cpp/Quaternion.h"
#include "../Core/Math/LightMath_Cpp/Vector3.h"
#include "../Core/Math/LightMath_Cpp/Matrix4x4.h"
#include "../Core/Math/LightMath_Cpp/Matrix_utility.h"

#include "Graphics/Acceleration/LinearData_ViewFrustumCulling/DataType/EntityBlockViewer.h"

namespace doom
{
	enum class eSpace
	{
		World,
		Self
	};

	class Transform : public PlainComponent
	{
		friend class Component;
		friend class Renderer;
	private:

		

		/// <summary>
		/// why don't use FrameDirtyChecker::IsDirty -> FrameDirtyChecker is changed when pass frame
		/// but this modelMatrix is calculated when this is needed ( not every frame )
		/// </summary>
		alignas(64) math::Matrix4x4 mModelMatrixCache;
		alignas(64) math::Matrix4x4 mLocalToWorldMatrix{ 1.0f };
		alignas(64) math::Matrix4x4 mWorldToLocalMatrix{ 1.0f };
		alignas(64) math::Matrix4x4 mTranslationMatrix{ 1.0f };
		alignas(64) math::Matrix4x4 mRotationMatrix{ 1.0f };
		alignas(64) math::Matrix4x4 mScaleMatrix{ 1.0f };
		
		//don't change place of this variable
		//this position is for cache hit
		alignas(64) math::Vector3 mPosition;
		math::Vector3 mLastFramePosition;
		math::Quaternion mRotation;
		math::Vector3 mScale;

		//Matrix4X4 and Vector4 is aligned to 32, 16 byte
		//So To save memory, it is declared next to next

		DirtyReceiver bmIsDirtyModelMatrix;

		Transform(const Transform&) = delete;
		Transform(Transform&&) noexcept = delete;
		Transform& operator=(const Transform&) = delete;
		Transform& operator=(Transform&&) noexcept = delete;

		virtual void InitComponent() final;
		virtual void UpdateComponent() final;
		virtual void OnEndOfFrame_Component() final;
		virtual void OnDestroy() final;

		const math::Matrix4x4 GetRotationMatrix()
		{

		}

	public:

		Transform() : mLastFramePosition{ 0.0f }, mPosition{ 0.0f }, mRotation{}, mScale{ 1.0f }, bmIsDirtyModelMatrix{ true }
		{
// 			this->SetPosition(this->mPosition);
// 			this->SetRotation(this->mRotation);
// 			this->SetScale(this->mScale);
		}
		virtual ~Transform() = default;
		std::string ToString();

		inline void SetPosition(const math::Vector3& position)
		{
			this->mTranslationMatrix = math::translate(position);
			this->mPosition = position;

			this->SetDirtyTrueAtThisFrame();
			this->bmIsDirtyModelMatrix = true;
		}
		FORCE_INLINE void SetPosition(float x, float y, float z)
		{
			this->SetPosition({x, y, z});
		}

		inline void SetRotation(const math::Quaternion& rotation)
		{
			mRotationMatrix = static_cast<math::Matrix4x4>(rotation);
			this->mRotation = rotation;
			this->SetDirtyTrueAtThisFrame();

			this->bmIsDirtyModelMatrix = true;
		}
		FORCE_INLINE void SetRotation(const math::Vector3& eulerAngle)
		{
			this->SetRotation(math::Quaternion(eulerAngle));
		}
		FORCE_INLINE void SetRotation(const float eulerAngleX, const float eulerAngleY, const float eulerAngleZ)
		{
			this->SetRotation({eulerAngleX, eulerAngleY, eulerAngleZ});
		}

		inline void SetScale(const math::Vector3& scale)
		{
			this->mScaleMatrix = math::scale(scale);
			this->mScale = scale;
			this->SetDirtyTrueAtThisFrame();
			this->bmIsDirtyModelMatrix = true;
		}
		FORCE_INLINE void SetScale(const float x, const float y, const float z)
		{
			this->SetScale({ x,y,z });
		}

		FORCE_INLINE math::Vector3 GetPosition()
		{
			return this->mPosition;
		}
		FORCE_INLINE const math::Vector3& GetPosition() const
		{
			return this->mPosition;
		}

		FORCE_INLINE math::Quaternion GetRotation()
		{
			return this->mRotation;
		}
		FORCE_INLINE const math::Quaternion& GetRotation() const
		{
			return this->mRotation;
		}

		FORCE_INLINE math::Vector3 GetScale()
		{
			return this->mScale;
		}
		FORCE_INLINE const math::Vector3& GetScale() const
		{
			return this->mScale;
		}

		

		FORCE_INLINE const math::Matrix4x4& GetModelMatrix() 
		{
			if (this->bmIsDirtyModelMatrix.GetIsDirty(true))
			{
				this->mModelMatrixCache = this->mTranslationMatrix * this->mRotationMatrix * this->mScaleMatrix;
			}
			return this->mModelMatrixCache;
		}


		FORCE_INLINE math::Vector3 forward() const
		{
			return this->mRotation * math::Vector3::forward;
		}
		FORCE_INLINE math::Vector3 right() const
		{
			return this->mRotation * math::Vector3::right;
		}
		FORCE_INLINE math::Vector3 up() const
		{
			return this->mRotation * math::Vector3::up;
		}

		FORCE_INLINE void LookAt(const Transform& target, const math::Vector3& up)
		{
			this->SetRotation(static_cast<math::Quaternion>(math::lookAt(this->mPosition, target.mPosition, up)));
		}

		FORCE_INLINE void Rotate(const math::Quaternion& quat, const eSpace& relativeTo)
		{
			if (relativeTo == eSpace::Self)
			{
				this->SetRotation(this->mRotation * quat);
			}
			else if (relativeTo == eSpace::World)
			{
				this->SetRotation(quat * this->mRotation);
			}
			
		}
		FORCE_INLINE void Rotate(const math::Vector3& eulerAngles, const eSpace& relativeTo)
		{
			if (relativeTo == eSpace::Self)
			{
				this->SetRotation(this->mRotation * math::Quaternion(eulerAngles));
			}
			else if (relativeTo == eSpace::World)
			{
				this->SetRotation(math::Quaternion(eulerAngles) * this->mRotation);
			}
		}
		void RotateAround(const math::Vector3& point, const math::Vector3& axis, float angle)
		{

		}

		FORCE_INLINE math::Vector3 TransformDirection(math::Vector3& direction) const
		{
			return this->mRotation * direction.normalized();
		}
		FORCE_INLINE math::Vector3 TransformPoint(const math::Vector3& point) const
		{
			return this->mRotation * point;
		}
		FORCE_INLINE math::Vector3 TransformVector(const math::Vector3& vector) const
		{
			return this->mRotation * vector;
		}
		FORCE_INLINE void Translate(const math::Vector3& translation, const eSpace& relativeTo = eSpace::World)
		{
			if (relativeTo == eSpace::World)
			{
				this->SetPosition(this->mPosition + translation);
			}
			else if (relativeTo == eSpace::Self)
			{
				this->SetPosition(this->mPosition + this->TransformVector(translation));
			}
		}


	};

}