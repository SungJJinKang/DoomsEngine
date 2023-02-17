#pragma once
#include "Core/Component.h"
#include <Quaternion.h>
#include <Vector3.h>
#include <Matrix4x4.h>
#include <Matrix_utility.h>
#include "EasyDirtyChecker/DirtyReceiver.h"
#include <Graphics/GraphicsAPI/graphicsAPIHelper.h>

#include "Transform.reflection.h"
namespace dooms
{
	enum class D_ENUM eSpace
	{
		World,
		Self
	};

	class DOOM_API D_CLASS Transform : public Component
	{
		GENERATE_BODY()
		

	private:

		D_PROPERTY(CALLBACK = "SetPosition")
		math::Vector3 mPosition alignas(64) { 0.0f };
		
		/// <summary>
		/// why don't use FrameDirtyChecker::IsDirty -> FrameDirtyChecker is changed when pass frame
		/// but this modelMatrix is calculated when this is needed ( not every frame )
		/// </summary>
		D_PROPERTY()
		mutable math::Matrix4x4 mModelMatrixCache alignas(64){ 1.0f };
		D_PROPERTY()
		math::Matrix4x4 mLocalToWorldMatrix alignas(64) { 1.0f };
		D_PROPERTY()
		math::Matrix4x4 mWorldToLocalMatrix alignas(64) { 1.0f };
		D_PROPERTY()
		math::Matrix4x4 mTranslationMatrix alignas(64) { 1.0f };
		D_PROPERTY()
		math::Matrix4x4 mRotationMatrix alignas(64) { 1.0f };
		D_PROPERTY()
		math::Matrix4x4 mScaleMatrix alignas(64) { 1.0f };

		D_PROPERTY(CALLBACK = "SetScale")
		math::Vector3 mScale{ 1.0f };
		D_PROPERTY(CALLBACK = "SetRotation", TOOLTIP="Euler Angle")
		math::Quaternion mRotation{ 0.0f, 0.0f, 0.0f, 1.0f };
		D_PROPERTY(INVISIBLE)
		math::Vector3 mLastFramePosition{nullptr};


		D_PROPERTY()
		DirtyReceiver bmIsDirtyModelMatrix {true};
		//Matrix4X4 and Vector4 is aligned to 32, 16 byte
		//So To save memory, it is declared next to next

	

		D_FUNCTION(INVISIBLE)
		void SetPosition();

		D_FUNCTION(INVISIBLE)
		void SetRotation();

		D_FUNCTION(INVISIBLE)
		void SetScale();

		virtual void InitComponent() final;
		virtual void UpdateComponent() final;
		virtual void OnEndOfFrame_Component() final;
		virtual void OnDestroy() final;
		
		virtual void OnChangedByGUI(const dooms::reflection::DField& dFieldOfChangedField);

		bool IsEntityMovable() const;

	public:

		Transform();
		virtual ~Transform() = default;

		Transform(const Transform&) = default;
		Transform(Transform&&) noexcept = delete;
		Transform& operator=(const Transform&) = default;
		Transform& operator=(Transform&&) noexcept = delete;

		std::string ToString();
		
		FORCE_INLINE void SetPosition(const math::Vector3& position)
		{
			D_ASSERT(IsEntityMovable());

			if (IsEntityMovable())
			{
				mTranslationMatrix = math::translate(position);
				mPosition = position;

				SetDirtyTrueAtThisFrame();
				bmIsDirtyModelMatrix = true;
			}			
		}
		
		FORCE_INLINE void SetPosition(FLOAT32 x, FLOAT32 y, FLOAT32 z)
		{
			D_ASSERT(IsEntityMovable());

			if (IsEntityMovable())
			{
				SetPosition({ x, y, z });
			}
		}
		
		FORCE_INLINE void SetRotation(const math::Quaternion& rotation)
		{
			D_ASSERT(IsEntityMovable());

			if (IsEntityMovable())
			{
				mRotationMatrix = static_cast<math::Matrix4x4>(rotation);
				mRotation = rotation;
				SetDirtyTrueAtThisFrame();

				bmIsDirtyModelMatrix = true;
			}
		}
		
		FORCE_INLINE void SetRotation(const math::Vector3& eulerAngle)
		{
			D_ASSERT(IsEntityMovable());

			if (IsEntityMovable())
			{
				SetRotation(math::Quaternion(eulerAngle));
			}
		}
		
		FORCE_INLINE void SetRotation(const FLOAT32 eulerAngleX, const FLOAT32 eulerAngleY, const FLOAT32 eulerAngleZ)
		{
			D_ASSERT(IsEntityMovable());

			if (IsEntityMovable())
			{
				SetRotation({ eulerAngleX, eulerAngleY, eulerAngleZ });
			}
		}
		
		FORCE_INLINE void SetScale(const math::Vector3& scale)
		{
			D_ASSERT(IsEntityMovable());

			if (IsEntityMovable())
			{
				mScaleMatrix = math::scale(scale);
				mScale = scale;
				SetDirtyTrueAtThisFrame();
				bmIsDirtyModelMatrix = true;
			}
		}
		
		FORCE_INLINE void SetScale(const FLOAT32 x, const FLOAT32 y, const FLOAT32 z)
		{
			D_ASSERT(IsEntityMovable());

			if (IsEntityMovable())
			{
				SetScale({ x,y,z });
			}
		}
		
		FORCE_INLINE const math::Vector3& GetPosition() const
		{
			return mPosition;
		}
		
		FORCE_INLINE const math::Quaternion& GetRotation() const
		{
			return mRotation;
		}
		
		FORCE_INLINE const math::Vector3& GetScale() const
		{
			return mScale;
		}
		
		FORCE_INLINE const math::Matrix4x4& GetModelMatrix() const
		{
			if (bmIsDirtyModelMatrix.GetIsDirty(true))
			{
				mModelMatrixCache = mTranslationMatrix * mRotationMatrix * mScaleMatrix;
			}
			return mModelMatrixCache;
		}
		
		FORCE_INLINE const math::Matrix4x4& GetRotationMatrix() const
		{
			return mRotationMatrix;
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
		
		void LookAt(const Transform& target, const math::Vector3& up);
		void LookAt(const math::Vector3& targetPoint, const math::Vector3& up);
		void Rotate(const math::Quaternion& quat, const eSpace& relativeTo);
		void Rotate(const math::Vector3& eulerAngles, const eSpace& relativeTo);
		void RotateAround(const math::Vector3& centerPoint, const math::Vector3& axis, const FLOAT32 angle);

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
			D_ASSERT(IsEntityMovable());

			if (IsEntityMovable())
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
		}


	};

}
