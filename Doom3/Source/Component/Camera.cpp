#include "Camera.h"
#include "../Core/Scene/Scene.h"
#include "../Core/Math/LightMath_Cpp/Matrix_utility.h"
#include "Transform.h"

using namespace doom;

void Camera::SetProjectionMode(eProjectionType value)
{
	this->mProjectionMode = value;
}

void Camera::SetFieldOfView(float value)
{
	this->mFieldOfView = value;
	this->bmIsDirty = true;
}

void Camera::SetClippingPlaneNear(float value)
{
	this->mClippingPlaneNear = value;
	this->bmIsDirty = true;
}

void Camera::SetClippingPlaneFar(float value)
{
	this->mClippingPlaneFar = value;
	this->bmIsDirty = true;
}

void Camera::SetViewportRectX(float value)
{
	this->mViewportRectX = value;
	this->bmIsDirty = true;
}

void Camera::SetViewportRectY(float value)
{
	this->mViewportRectY = value;
	this->bmIsDirty = true;
}

void Camera::SetViewportRectWidth(float value)
{
	this->mViewportRectWidth = value;
	this->bmIsDirty = true;
}

void Camera::SetViewportRectHeight(float value)
{
	this->mViewportRectHeight = value;
	this->bmIsDirty = true;
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





void doom::Camera::Init()
{
	auto currentWorld = Scene::GetSingleton();
	Camera* currentMainCamera = currentWorld->GetMainCamera();
	if (currentMainCamera == nullptr)
	{
		currentWorld->SetMainCamera(this);
	}
}

void doom::Camera::Update()
{

}

void doom::Camera::OnEndOfFrame()
{
}

math::Matrix4x4 doom::Camera::GetProjectionMatrix()
{
	if (this->mProjectionMode == eProjectionType::Perspective)
	{
		return math::perspective(this->mFieldOfView, this->mViewportRectWidth / this->mViewportRectHeight, this->mClippingPlaneNear, this->mClippingPlaneFar);
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
		if (this->bmIsDirty == true)
		{//when camera value is changed
			auto projectionMatrix = this->GetProjectionMatrix();

			//!!!! Opengl Use column major of matrix data layout
			uboManager.StoreDataAtTempBufferOfBindingPoint(GLOBAL_UNIFORM_BLOCK_BINDING_POINT, (void*)projectionMatrix.data(), sizeof(projectionMatrix), graphics::eUniformBlock_Global::projection);
			this->bmIsDirty = false;
		}

		if (this->GetTransform()->GetIsDirtyAtPreviousFrame() == true)
		{//when transform value is changed
			auto viewMatrix = this->GetViewMatrix();
			uboManager.StoreDataAtTempBufferOfBindingPoint(GLOBAL_UNIFORM_BLOCK_BINDING_POINT, (void*)viewMatrix.data(), sizeof(viewMatrix), graphics::eUniformBlock_Global::view);
		}
	}
}
