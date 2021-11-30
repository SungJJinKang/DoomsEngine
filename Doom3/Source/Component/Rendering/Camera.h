#pragma once
#include "Core/PlainComponent.h"

#include "../Core/Math/LightMath_Cpp/Vector3.h"
#include "../Core/Math/LightMath_Cpp/Vector4.h"
#include "../Core/Math/LightMath_Cpp/Matrix4x4.h"
#include "../Core/Math/LightMath_Cpp/Matrix_utility.h"

#include <array>
#include "../Core/Graphics/Buffer/UniformBufferObjectUpdater.h"
#include <StaticContainer/StaticContainer.h>

#include <EasyDirtyChecker/DirtyReceiver.h>

#include "Transform.h"

#include "Graphics/FrameBuffer/DefferedRenderingFrameBuffer.h"

#ifndef MAX_CAMERA_COUNT
#define MAX_CAMERA_COUNT 5
#endif

#include "Camera.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class Graphics_Server;
	}

	enum D_ENUM eCameraFlag : UINT32
	{
		IS_CULLED = 1 << 0,
		PAUSE_CULL_JOB = 1 << 1,
	};

	class DOOM_API D_CLASS Camera : public PlainComponent, public graphics::UniformBufferObjectUpdater, public StaticContainer<Camera>
	{
		GENERATE_BODY()
		

		friend class Scene;
		friend class graphics::Graphics_Server;

	public:

		enum class D_ENUM eProjectionType
		{
			Perspective,
			Orthographic
		};

	private:


		D_PROPERTY(CALLBACK="SetProjectionMode")
		eProjectionType mProjectionMode{ eProjectionType::Perspective };

		D_PROPERTY(CALLBACK="UpdateCallback")
		FLOAT32 mFieldOfViewInDegree = 60;

		D_PROPERTY(CALLBACK="UpdateCallback")
		FLOAT32 mClippingPlaneNear = 0.001f;

		D_PROPERTY(CALLBACK="UpdateCallback")
		FLOAT32 mClippingPlaneFar = 1500.0f;

		/// <summary>
		/// opengl -1 ~ 1
		/// </summary>
		D_PROPERTY(CALLBACK="UpdateCallback")
		FLOAT32 mViewportRectX = -1.0f;
		/// <summary>
		/// opengl -1 ~ 1
		/// </summary>
		D_PROPERTY(CALLBACK="UpdateCallback")
		FLOAT32 mViewportRectY = -1.0f;

		/// <summary>
		/// opengl -1 ~ 1
		/// </summary>
		D_PROPERTY(CALLBACK="UpdateCallback")
		FLOAT32 mViewportRectWidth = 2.0f;

		/// <summary>
		/// opengl -1 ~ 1
		/// </summary>
		D_PROPERTY(CALLBACK="UpdateCallback")
		FLOAT32 mViewportRectHeight = 2.0f;
		
		DirtyReceiver bmIsProjectionMatrixDirty{ true };
		DirtyReceiver bmIsViewMatrixDirty{ true };
		DirtyReceiver bmIsViewProjectionMatrixDirty{ true };
		DirtyReceiver bmIsModelViewProjectionMatrixDirty{ true };
		DirtyReceiver bmIsFrustumPlaneMatrixDirty{ true };
		math::Matrix4x4 mViewMatrix{nullptr};
		math::Matrix4x4 mProjectionMatrix{ nullptr };
		math::Matrix4x4 mViewProjectionMatrix{ nullptr };
		math::Matrix4x4 mMovelViewProjectionMatrix{ nullptr };
		std::array<math::Vector4, 6> mFrustumPlane{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

		//graphics::ViewFrustum mViewFrumstum{};

		const std::array<math::Vector4, 6>& CalculateFrustumPlane();
		
		virtual void InitComponent() final;
		virtual void UpdateComponent() final;
		virtual void OnEndOfFrame_Component() final;

		DirtyReceiver bmIsUboDirty{ true };
	
		void UpdateMainCamera();
		/// <summary>
		/// This object Component is set to Scene's MainCamera
		/// </summary>
		void OnSetMainCamera();

		D_FUNCTION(INVISIBLE)
		void UpdateCallback();

	protected:


		void OnDestroy() override;

		void OnChangedByGUI(const dooms::reflection::DField& dFieldOfChangedField) override;


	public:

		D_PROPERTY(Color)
		math::Vector4 mClearColor;


		Camera(const Camera&) = default;
		Camera(Camera&&) noexcept = delete;
		Camera& operator=(const Camera&) = delete;
		Camera& operator=(Camera&&) noexcept = delete;

		graphics::DefferedRenderingFrameBuffer mDefferedRenderingFrameBuffer;

		UINT32 CameraIndexInCullingSystem;

		static constexpr UINT32 DEFAULT_CAMERA_FLAG = eCameraFlag::IS_CULLED;

		UINT32 mCameraFlag = DEFAULT_CAMERA_FLAG;

		Camera();
		virtual ~Camera() = default;

		void SetProjectionMode(eProjectionType value);
		D_FUNCTION()
		void SetProjectionMode();
		void SetFieldOfViewInDegree(FLOAT32 degree);
		void SetFieldOfViewInRadian(FLOAT32 radian);
		void SetClippingPlaneNear(FLOAT32 value);
		void SetClippingPlaneFar(FLOAT32 value);
		void SetViewportRectX(FLOAT32 value);
		void SetViewportRectY(FLOAT32 value);
		void SetViewportRectWidth(FLOAT32 value);
		void SetViewportRectHeight(FLOAT32 value);
		void SetCameraFlag(const eCameraFlag cameraFlag, const bool isSet);

		eProjectionType GetProjectionMode() const;
		FLOAT32 GetFieldOfViewInDegree() const;
		FLOAT32 GetClippingPlaneNear() const;
		FLOAT32 GetClippingPlaneFar() const;
		FLOAT32 GetViewportRectX() const;
		FLOAT32 GetViewportRectY() const;
		FLOAT32 GetViewportRectWidth() const;
		FLOAT32 GetViewportRectHeight() const;
		bool GetCameraFlag(const eCameraFlag cameraFlag) const;
		bool GetIsCullJobEnabled() const;

		static Camera* GetMainCamera();

		/// <summary>
		/// this function will be called at every frame
		/// </summary>
		/// <returns></returns>
		const math::Matrix4x4& GetProjectionMatrix();
		/// <summary>
		/// this function will be called at every frame
		/// </summary>
		/// <returns></returns>
		FORCE_INLINE const math::Matrix4x4& GetViewMatrix()
		{
			if (bmIsViewMatrixDirty.GetIsDirty(true))
			{
				auto transform = GetTransform();
				auto pos = transform->GetPosition();
				auto forward = transform->forward();
				auto up = transform->up();
				mViewMatrix = math::lookAt(pos, pos + forward, up);
				//mViewFrumstum.UpdateLookAt(pos, forward, up);

			}

			return mViewMatrix;
		}
		FORCE_INLINE const math::Matrix4x4& GetViewProjectionMatrix()
		{
			if (bmIsViewProjectionMatrixDirty.GetIsDirty(true) )
			{
				mViewProjectionMatrix = GetProjectionMatrix() * GetViewMatrix();
			}
			return mViewProjectionMatrix;
		}
		FORCE_INLINE const math::Matrix4x4& GetModelViewProjectionMatrix( )
		{
			if (bmIsModelViewProjectionMatrixDirty.GetIsDirty(true) )
			{
				mMovelViewProjectionMatrix =  GetViewProjectionMatrix() * GetTransform()->GetModelMatrix();
			}
			return mMovelViewProjectionMatrix;
		}
		FORCE_INLINE bool GetIsViewProjectionMatrixDirty() const
		{
			return static_cast<bool>(bmIsViewProjectionMatrixDirty);
		}

		NO_DISCARD math::Vector3 NDCToScreenPoint(const math::Vector3& ndcPoint);
		NO_DISCARD math::Vector3 ScreenToNDCPoint(const math::Vector3& screenPoint);
		
		NO_DISCARD math::Vector3 WorldToNDCPoint(const math::Vector3& worldPosition);
		NO_DISCARD math::Vector3 NDCToWorldPoint(const math::Vector3& ndcPoint);

		NO_DISCARD math::Vector3 WorldToScreenPoint(const math::Vector3& worldPosition);
		NO_DISCARD math::Vector3 ScreenToWorldPoint(const math::Vector3& screenPosition);

		// we don't use ViewPort
		// We use NDC. x : -1 ~ 1, y : -1 ~ 1, z : depth value * 2 - 1, relative to bottom-left corner

		/// <summary>
		/// Top of screen has negative y value
		/// 
		/// Screen coordinate is relative to top-left corner of screen
		/// </summary>
		/// <param name="screenPosition"></param>
		/// <returns></returns>
		[[deprecated]] math::Vector3 ScreenToViewportPoint(const math::Vector3& screenPosition);
		/// <summary>
		/// Top of screen has negative y value
		/// 
		/// Screen coordinate is relative to top-left corner of screen
		/// </summary>
		/// <param name="viewportPosition"></param>
		/// <returns></returns>
		[[deprecated]] math::Vector3 ViewportToScreenPoint(const math::Vector3& viewportPosition);

		bool IsMainCamera() const;
		void RemoveThisCameraFromMainCamera();

		virtual void UpdateUniformBufferObject() final;




	};
}
