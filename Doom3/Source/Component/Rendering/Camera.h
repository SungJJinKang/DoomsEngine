#pragma once
#include "Core/Component.h"

#include "../Core/Math/LightMath_Cpp/Vector3.h"
#include "../Core/Math/LightMath_Cpp/Vector4.h"
#include "../Core/Math/LightMath_Cpp/Matrix4x4.h"
#include "../Core/Math/LightMath_Cpp/Matrix_utility.h"
#include <array>
#include "../Core/Graphics/Buffer/UniformBufferObject/UniformBufferObjectUpdater.h"
#include <Misc/StaticContainer/StaticContainer.h>
#include <EasyDirtyChecker/DirtyReceiver.h>
#include "Transform.h"
#include "MaxCameraCount.h"

#include "Camera.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class Graphics_Server;
		class GraphicsPipeLineCamera;
	}

	enum D_ENUM eCameraFlag : UINT32
	{
		IS_CULLED = 1 << 0,
		PAUSE_CULL_JOB = 1 << 1,
	};

	class DOOM_API D_CLASS Camera : public Component, public graphics::UniformBufferObjectUpdater, public StaticContainer<Camera>
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

		D_PROPERTY(CALLBACK="UpdateCallback", MIN = 1.0f)
		FLOAT32 mFieldOfViewInDegree = 60;

		D_PROPERTY(CALLBACK="UpdateCallback", MIN = 1.0f)
		FLOAT32 mClippingPlaneNear = 0.001f;

		D_PROPERTY(CALLBACK="UpdateCallback", MIN = 1.0f)
		FLOAT32 mClippingPlaneFar = 3000.0f;

		/// <summary>
		/// opengl -1 ~ 1
		/// </summary>
		D_PROPERTY(CALLBACK="UpdateCallback")
		FLOAT32 mViewportRectX = 0.0f;
		/// <summary>
		/// opengl -1 ~ 1
		/// </summary>
		D_PROPERTY(CALLBACK="UpdateCallback")
		FLOAT32 mViewportRectY = 0.0f;

		/// <summary>
		/// opengl -1 ~ 1
		/// </summary>
		D_PROPERTY(CALLBACK="UpdateCallback")
		FLOAT32 mViewportRectWidth = 1920.0f;

		/// <summary>
		/// opengl -1 ~ 1
		/// </summary>
		D_PROPERTY(CALLBACK="UpdateCallback")
		FLOAT32 mViewportRectHeight = 1080.0f;

		D_PROPERTY()
		graphics::GraphicsPipeLineCamera* mGraphicsPipeLineCamera;

		std::array<math::Vector4, 6> CalculateFrustumPlane();

		void InitCameraViewportRect();
		void InitGraphicsPipeLineCamera();

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

		D_PROPERTY()
		UINT32 CameraIndexInCullingSystem;

		static constexpr UINT32 DEFAULT_CAMERA_FLAG = eCameraFlag::IS_CULLED;

		D_PROPERTY()
		UINT32 mCameraFlag;

		Camera();
		virtual ~Camera() = default;

		void SetProjectionMode(eProjectionType value);
		D_FUNCTION(INVISIBLE)
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
		math::Matrix4x4 GetProjectionMatrix(const bool forceNDCNegativeOneToOne = false);
		/// <summary>
		/// this function will be called at every frame
		/// </summary>
		/// <returns></returns>
		FORCE_INLINE math::Matrix4x4 GetViewMatrix()
		{
			const dooms::Transform* const transform = GetTransform();
			const math::Vector3& pos = transform->GetPosition();
			const math::Vector3 forward = transform->forward();
			const math::Vector3 up = transform->up();
			return math::lookAt(pos, pos + forward, up);
		}
		FORCE_INLINE math::Matrix4x4 GetViewProjectionMatrix(const bool forceNDCNegativeOneToOne = false)
		{
			return GetProjectionMatrix(forceNDCNegativeOneToOne) * GetViewMatrix();
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

		virtual void UpdateUniformBufferObject(const bool force = false) final;
		void OnSetPendingKill() override;

		graphics::GraphicsPipeLineCamera* GetGraphicsPipeLineCamera() const;
	};
}
