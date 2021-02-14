#pragma once
#include "Core/PlainComponent.h"
#include "../Core/Math/LightMath_Cpp/Matrix4x4.h"
#include "../Core/Graphics/Buffer/UniformBufferObjectTempBufferUpdater.h"


namespace doom
{
	class Camera : public PlainComponent, public graphics::UniformBufferObjectTempBufferUpdater
	{
	public:
		enum class eProjectionType
		{
			Perspective,
			Orthographic
		};
	private:

	
		Camera(const Camera&) = delete;
		Camera(Camera&&) noexcept = delete;
		Camera& operator=(const Camera&) = delete;
		Camera& operator=(Camera&&) noexcept = delete;

		eProjectionType mProjectionMode{ eProjectionType::Perspective };

		///
		float mFieldOfView = 60;

		float mClippingPlaneNear = 0.3f;
		float mClippingPlaneFar = 1000.0f;

		/// <summary>
		/// opengl -1 ~ 1
		/// </summary>
		float mViewportRectX = -1.0f;
		/// <summary>
		/// opengl -1 ~ 1
		/// </summary>
		float mViewportRectY = -1.0f;

		/// <summary>
		/// opengl -1 ~ 1
		/// </summary>
		float mViewportRectWidth = 2.0f;
		/// <summary>
		/// opengl -1 ~ 1
		/// </summary>
		float mViewportRectHeight = 2.0f;

		virtual void InitComponent() final;
		virtual void UpdateComponent() final;
		virtual void OnEndOfFrame_Component() final;

		void UpdateUniformBufferObjectTempBuffer(graphics::UniformBufferObjectManager& uboManager) final;

	public:

		Camera() = default;

		void SetProjectionMode(eProjectionType value);
		void SetFieldOfView(float value);
		void SetClippingPlaneNear(float value);
		void SetClippingPlaneFar(float value);
		void SetViewportRectX(float value);
		void SetViewportRectY(float value);
		void SetViewportRectWidth(float value);
		void SetViewportRectHeight(float value);

		eProjectionType GetProjectionMode() const;
		float GetFieldOfView() const;
		float GetClippingPlaneNear() const;
		float GetClippingPlaneFar() const;
		float GetViewportRectX() const;
		float GetViewportRectY() const;
		float GetViewportRectWidth() const;
		float GetViewportRectHeight() const;
	
		

		math::Matrix4x4 mProjectionMatrixCache{};
		/// <summary>
		/// this function will be called at every frame
		/// </summary>
		/// <returns></returns>
		math::Matrix4x4 GetProjectionMatrix();
		/// <summary>
		/// this function will be called at every frame
		/// </summary>
		/// <returns></returns>
		math::Matrix4x4 GetViewMatrix();

		math::Vector3 ScreenToViewportPoint(math::Vector3 position);
		math::Vector3 ViewportToScreenPoint(math::Vector3 position);

		math::Vector3 WorldToViewportPoint(math::Vector3 position);
		math::Vector3 ViewportToWorldPoint(math::Vector3 position);

		math::Vector3 WorldToScreenPoint(math::Vector3 position);
		math::Vector3 ScreenToWorldPoint(math::Vector3 position);
	};
}
