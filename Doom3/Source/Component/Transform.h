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
// 			SetPosition(mPosition);
// 			SetRotation(mRotation);
// 			SetScale(mScale);
		}
		virtual ~Transform() = default;
		std::string ToString();

		inline void SetPosition(const math::Vector3& position)
		{
			mTranslationMatrix = math::translate(position);
			mPosition = position;

			SetDirtyTrueAtThisFrame();
			bmIsDirtyModelMatrix = true;
		}
		FORCE_INLINE void SetPosition(float x, float y, float z)
		{
			SetPosition({x, y, z});
		}

		inline void SetRotation(const math::Quaternion& rotation)
		{
			mRotationMatrix = static_cast<math::Matrix4x4>(rotation);
			mRotation = rotation;
			SetDirtyTrueAtThisFrame();

			bmIsDirtyModelMatrix = true;
		}
		FORCE_INLINE void SetRotation(const math::Vector3& eulerAngle)
		{
			SetRotation(math::Quaternion(eulerAngle));
		}
		FORCE_INLINE void SetRotation(const float eulerAngleX, const float eulerAngleY, const float eulerAngleZ)
		{
			SetRotation({eulerAngleX, eulerAngleY, eulerAngleZ});
		}

		inline void SetScale(const math::Vector3& scale)
		{
			mScaleMatrix = math::scale(scale);
			mScale = scale;
			SetDirtyTrueAtThisFrame();
			bmIsDirtyModelMatrix = true;
		}
		FORCE_INLINE void SetScale(const float x, const float y, const float z)
		{
			SetScale({ x,y,z });
		}

		FORCE_INLINE math::Vector3 GetPosition()
		{
			return mPosition;
		}
		FORCE_INLINE const math::Vector3& GetPosition() const
		{
			return mPosition;
		}

		FORCE_INLINE math::Quaternion GetRotation()
		{
			return mRotation;
		}
		FORCE_INLINE const math::Quaternion& GetRotation() const
		{
			return mRotation;
		}

		FORCE_INLINE math::Vector3 GetScale()
		{
			return mScale;
		}
		FORCE_INLINE const math::Vector3& GetScale() const
		{
			return mScale;
		}

		

		FORCE_INLINE const math::Matrix4x4& GetModelMatrix() 
		{
			if (bmIsDirtyModelMatrix.GetIsDirty(true))
			{
				mModelMatrixCache = mTranslationMatrix * mRotationMatrix * mScaleMatrix;
			}
			return mModelMatrixCache;
		}


		FORCE_INLINE math::Vector3 forward() const
		{
			return mRotation * math::Vector3::forward;
		}
		FORCE_INLINE math::Vector3 right() const
		{
			return mRotation * math::Vector3::right;
		}
		FORCE_INLINE math::Vector3 up() const
		{
			return mRotation * math::Vector3::up;
		}

		FORCE_INLINE void LookAt(const Transform& target, const math::Vector3& up)
		{
			SetRotation(static_cast<math::Quaternion>(math::lookAt(mPosition, target.mPosition, up)));
		}

		FORCE_INLINE void Rotate(const math::Quaternion& quat, const eSpace& relativeTo)
		{
			if (relativeTo == eSpace::Self)
			{
				SetRotation(mRotation * quat);
			}
			else if (relativeTo == eSpace::World)
			{
				SetRotation(quat * mRotation);
			}
			
		}
		FORCE_INLINE void Rotate(const math::Vector3& eulerAngles, const eSpace& relativeTo)
		{
			if (relativeTo == eSpace::Self)
			{
				SetRotation(mRotation * math::Quaternion(eulerAngles));
			}
			else if (relativeTo == eSpace::World)
			{
				SetRotation(math::Quaternion(eulerAngles) * mRotation);
			}
		}
		void RotateAround(const math::Vector3& point, const math::Vector3& axis, float angle)
		{

		}

		FORCE_INLINE math::Vector3 TransformDirection(math::Vector3& direction) const
		{
			return mRotation * direction.normalized();
		}
		FORCE_INLINE math::Vector3 TransformPoint(const math::Vector3& point) const
		{
			return mRotation * point;
		}
		FORCE_INLINE math::Vector3 TransformVector(const math::Vector3& vector) const
		{
			return mRotation * vector;
		}
		FORCE_INLINE void Translate(const math::Vector3& translation, const eSpace& relativeTo = eSpace::World)
		{
			if (relativeTo == eSpace::World)
			{
				SetPosition(mPosition + translation);
			}
			else if (relativeTo == eSpace::Self)
			{
				SetPosition(mPosition + TransformVector(translation));
			}
		}


	};

}