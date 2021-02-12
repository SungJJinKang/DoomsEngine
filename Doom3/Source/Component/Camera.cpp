#include "Camera.h"
#include "../Core/Scene/Scene.h"
#include "../Core/Math/LightMath_Cpp/Matrix_utility.h"
#include "Transform.h"
#include "../Graphics/Graphics_Server.h"

using namespace doom;

void Camera::SetProjectionMode(eProjectionType value)
{
	this->mProjectionMode = value;
	this->SetDirtyTrueAtThisFrame();
}

void Camera::SetFieldOfView(float value)
{
	this->mFieldOfView = value;
	this->SetDirtyTrueAtThisFrame();
}

void Camera::SetClippingPlaneNear(float value)
{
	this->mClippingPlaneNear = value;
	this->SetDirtyTrueAtThisFrame();
}

void Camera::SetClippingPlaneFar(float value)
{
	this->mClippingPlaneFar = value;
	this->SetDirtyTrueAtThisFrame();
}

void Camera::SetViewportRectX(float value)
{
	this->mViewportRectX = value;
	this->SetDirtyTrueAtThisFrame();
}

void Camera::SetViewportRectY(float value)
{
	this->mViewportRectY = value;
	this->SetDirtyTrueAtThisFrame();
}

void Camera::SetViewportRectWidth(float value)
{
	this->mViewportRectWidth = value;
	this->SetDirtyTrueAtThisFrame();
}

void Camera::SetViewportRectHeight(float value)
{
	this->mViewportRectHeight = value;
	this->SetDirtyTrueAtThisFrame();
}

doom::Camera::eProjectionType Camera::GetProjectionMode() const
{
	return this->mProjectionMode;
}

float Camera::GetFieldOfView() const
{
	return this->mFieldOfView;
}

float Camera::GetClippingPlaneNear() const
{
	return this->mClippingPlaneNear;
}

float Camera::GetClippingPlaneFar() const
{
	return this->mClippingPlaneFar;
}

float Camera::GetViewportRectX() const
{
	return this->mViewportRectX;
}

float Camera::GetViewportRectY() const
{
	return this->mViewportRectY;
}

float Camera::GetViewportRectWidth() const
{
	return this->mViewportRectWidth;
}

float Camera::GetViewportRectHeight() const
{
	return this->mViewportRectHeight;
}






void Camera::InitComponent()
{
	auto currentWorld = Scene::GetSingleton();
	Camera* currentMainCamera = currentWorld->GetMainCamera();
	if (currentMainCamera == nullptr)
	{
		currentWorld->SetMainCamera(this);
	}
}

void Camera::UpdateComponent()
{

}

void Camera::OnEndOfFrame_Component()
{

}

math::Matrix4x4 doom::Camera::GetProjectionMatrix()
{
	if (this->mProjectionMode == eProjectionType::Perspective)
	{
		return math::perspectiveFov( math::DEGREE_TO_RADIAN * this->mFieldOfView, static_cast<float>(doom::graphics::Graphics_Server::GetScreenWidth()), static_cast<float>(doom::graphics::Graphics_Server::GetScreenHeight()), this->mClippingPlaneNear, this->mClippingPlaneFar);
	}
	else
	{
		return math::ortho(this->mViewportRectX, this->mViewportRectX + this->mViewportRectWidth, this->mViewportRectY, this->mViewportRectY + this->mViewportRectHeight, this->mClippingPlaneNear, this->mViewportRectHeight);
	}
	
}

math::Matrix4x4 Camera::GetViewMatrix()
{
	auto transform = this->GetTransform();
	auto pos = transform->GetPosition();
	return math::lookAt(pos, pos + transform->forward(), transform->up());
}

void Camera::UpdateUniformBufferObjectTempBuffer(graphics::UniformBufferObjectManager& uboManager)
{
	if (Scene::GetSingleton()->GetMainCamera() == this)
	{//if this camera is mainCamera
		if (this->GetIsDirtyAtPreviousFrame() == true)
		{//when camera value is changed
			auto projectionMatrix = this->GetProjectionMatrix();

			//!!!! Opengl Use column major of matrix data layout
			uboManager.StoreDataAtTempBufferOfBindingPoint(GLOBAL_UNIFORM_BLOCK_BINDING_POINT, (void*)projectionMatrix.data(), sizeof(projectionMatrix), graphics::eUniformBlock_Global::projection);
		}

		auto transform = this->GetTransform();
		if (transform->GetIsDirtyAtPreviousFrame() == true)
		{//when transform value is changed
			auto viewMatrix = this->GetViewMatrix(); 
			const auto& camPos = transform->GetPosition();

			uboManager.StoreDataAtTempBufferOfBindingPoint(GLOBAL_UNIFORM_BLOCK_BINDING_POINT, (void*)viewMatrix.data(), sizeof(viewMatrix), graphics::eUniformBlock_Global::view);
			uboManager.StoreDataAtTempBufferOfBindingPoint(GLOBAL_UNIFORM_BLOCK_BINDING_POINT, (void*)camPos.data(), sizeof(camPos), graphics::eUniformBlock_Global::camPos);

		}
	}
}
