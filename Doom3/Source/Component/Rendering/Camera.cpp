#include "Camera.h"
#include "../Core/Scene/Scene.h"
#include "../Core/Math/LightMath_Cpp/Matrix_utility.h"
#include "../Core/Math/LightMath_Cpp/Vector3.h"
#include "Transform.h"
#include "../Graphics/Graphics_Server.h"

using namespace doom;

void Camera::SetProjectionMode(eProjectionType value)
{
	this->mProjectionMode = value;
	this->SetDirtyTrueAtThisFrame();
	this->bmIsProjectionMatrixDirty = true;
	this->bmIsViewMatrixDirty = true;
	this->bmIsViewProjectionMatrixDirty = true;
}

void Camera::SetFieldOfView(float value)
{
	this->mFieldOfViewInDegree = value;
	this->SetDirtyTrueAtThisFrame();
	this->bmIsProjectionMatrixDirty = true;
	this->bmIsViewMatrixDirty = true;
	this->bmIsViewProjectionMatrixDirty = true;
}

void Camera::SetClippingPlaneNear(float value)
{
	this->mClippingPlaneNear = value;
	this->SetDirtyTrueAtThisFrame();
	this->bmIsProjectionMatrixDirty = true;
	this->bmIsViewMatrixDirty = true;
	this->bmIsViewProjectionMatrixDirty = true;
}

void Camera::SetClippingPlaneFar(float value)
{
	this->mClippingPlaneFar = value;
	this->SetDirtyTrueAtThisFrame();
	this->bmIsProjectionMatrixDirty = true;
	this->bmIsViewMatrixDirty = true;
	this->bmIsViewProjectionMatrixDirty = true;
}

void Camera::SetViewportRectX(float value)
{
	this->mViewportRectX = value;
	this->SetDirtyTrueAtThisFrame();
	this->bmIsProjectionMatrixDirty = true;
	this->bmIsViewMatrixDirty = true;
	this->bmIsViewProjectionMatrixDirty = true;
}

void Camera::SetViewportRectY(float value)
{
	this->mViewportRectY = value;
	this->SetDirtyTrueAtThisFrame();
	this->bmIsProjectionMatrixDirty = true;
	this->bmIsViewMatrixDirty = true;
	this->bmIsViewProjectionMatrixDirty = true;
}

void Camera::SetViewportRectWidth(float value)
{
	this->mViewportRectWidth = value;
	this->SetDirtyTrueAtThisFrame();
	this->bmIsProjectionMatrixDirty = true;
	this->bmIsViewMatrixDirty = true;
	this->bmIsViewProjectionMatrixDirty = true;
}

void Camera::SetViewportRectHeight(float value)
{
	this->mViewportRectHeight = value;
	this->SetDirtyTrueAtThisFrame();
	this->bmIsProjectionMatrixDirty = true;
	this->bmIsViewMatrixDirty = true;
	this->bmIsViewProjectionMatrixDirty = true;
}

doom::Camera::eProjectionType Camera::GetProjectionMode() const
{
	return this->mProjectionMode;
}

float Camera::GetFieldOfView() const
{
	return this->mFieldOfViewInDegree;
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






const std::array<math::Vector4, 6>& doom::Camera::CalculateFrustumPlane()
{
	auto& viewProjectionMatrix = this->GetViewProjectionMatrix();
	// Left Frustum Plane
   // Add first column of the matrix to the fourth column
	mFrustumPlane[0].x = viewProjectionMatrix[0][3] + viewProjectionMatrix[0][0];
	mFrustumPlane[0].y = viewProjectionMatrix[1][3] + viewProjectionMatrix[1][0];
	mFrustumPlane[0].z = viewProjectionMatrix[2][3] + viewProjectionMatrix[2][0];
	mFrustumPlane[0].w = viewProjectionMatrix[3][3] + viewProjectionMatrix[3][0];
	mFrustumPlane[0].Normalize();

	// Right Frustum Plane
	// Subtract first column of matrix from the fourth column
	mFrustumPlane[1].x = viewProjectionMatrix[0][3] - viewProjectionMatrix[0][0];
	mFrustumPlane[1].y = viewProjectionMatrix[1][3] - viewProjectionMatrix[1][0];
	mFrustumPlane[1].z = viewProjectionMatrix[2][3] - viewProjectionMatrix[2][0];
	mFrustumPlane[1].w = viewProjectionMatrix[3][3] - viewProjectionMatrix[3][0];
	mFrustumPlane[1].Normalize();

	// Top Frustum Plane
	// Subtract second column of matrix from the fourth column
	mFrustumPlane[2].x = viewProjectionMatrix[0][3] - viewProjectionMatrix[0][1];
	mFrustumPlane[2].y = viewProjectionMatrix[1][3] - viewProjectionMatrix[1][1];
	mFrustumPlane[2].z = viewProjectionMatrix[2][3] - viewProjectionMatrix[2][1];
	mFrustumPlane[2].w = viewProjectionMatrix[3][3] - viewProjectionMatrix[3][1];
	mFrustumPlane[2].Normalize();

	// Bottom Frustum Plane
	// Add second column of the matrix to the fourth column
	mFrustumPlane[3].x = viewProjectionMatrix[0][3] + viewProjectionMatrix[0][1];
	mFrustumPlane[3].y = viewProjectionMatrix[1][3] + viewProjectionMatrix[1][1];
	mFrustumPlane[3].z = viewProjectionMatrix[2][3] + viewProjectionMatrix[2][1];
	mFrustumPlane[3].w = viewProjectionMatrix[3][3] + viewProjectionMatrix[3][1];
	mFrustumPlane[3].Normalize();

	// Near Frustum Plane
	// We could add the third column to the fourth column to get the near plane,
	// but we don't have to do this because the third column IS the near plane
	mFrustumPlane[4].x = viewProjectionMatrix[0][2];
	mFrustumPlane[4].y = viewProjectionMatrix[1][2];
	mFrustumPlane[4].z = viewProjectionMatrix[2][2];
	mFrustumPlane[4].w = viewProjectionMatrix[3][2];
	mFrustumPlane[4].Normalize();

	// Far Frustum Plane
	// Subtract third column of matrix from the fourth column
	mFrustumPlane[5].x = viewProjectionMatrix[0][3] - viewProjectionMatrix[0][2];
	mFrustumPlane[5].y = viewProjectionMatrix[1][3] - viewProjectionMatrix[1][2];
	mFrustumPlane[5].z = viewProjectionMatrix[2][3] - viewProjectionMatrix[2][2];
	mFrustumPlane[5].w = viewProjectionMatrix[3][3] - viewProjectionMatrix[3][2];
	mFrustumPlane[5].Normalize();

	return mFrustumPlane;
}



void Camera::InitComponent()
{
	this->AddLocalDirtyToTransformDirtyReceiver(this->bmIsViewMatrixDirty);
	this->AddLocalDirtyToTransformDirtyReceiver(this->bmIsProjectionMatrixDirty);
	this->AddLocalDirtyToTransformDirtyReceiver(this->bmIsViewProjectionMatrixDirty);
	this->AddLocalDirtyToTransformDirtyReceiver(this->bmIsUboDirty);

	this->UpdateMainCamera();
	
}

void Camera::UpdateComponent()
{
}

void Camera::OnEndOfFrame_Component()
{

}

void Camera::UpdateMainCamera()
{
	auto currentWorld = Scene::GetSingleton();
	Camera* currentMainCamera = currentWorld->GetMainCamera();
	if (currentMainCamera == nullptr)
	{
		currentWorld->SetMainCamera(this);
	}
}

void Camera::OnSetMainCamera()
{

}



doom::Camera* Camera::GetMainCamera()
{
	auto currentWorld = Scene::GetSingleton();
	return currentWorld->GetMainCamera();
}

void Camera::OnDestroy()
{
	auto currentWorld = Scene::GetSingleton();
	Camera* currentMainCamera = currentWorld->GetMainCamera();
	if (currentMainCamera == this)
	{
		currentWorld->SetMainCamera(nullptr);
		auto foremostComponent = StaticContainer<Camera>::GetForemostComponentWithHint(this);
		if (foremostComponent != nullptr)
		{
			currentWorld->SetMainCamera(foremostComponent);
		}
	}
}


const math::Matrix4x4& doom::Camera::GetProjectionMatrix()
{
	if (this->bmIsProjectionMatrixDirty.GetIsDirty(true))
	{
		if (this->mProjectionMode == eProjectionType::Perspective)
		{
			this->mProjectionMatrix = math::perspectiveFov(math::DEGREE_TO_RADIAN * this->mFieldOfViewInDegree, static_cast<float>(doom::graphics::Graphics_Server::GetScreenWidth()), static_cast<float>(doom::graphics::Graphics_Server::GetScreenHeight()), this->mClippingPlaneNear, this->mClippingPlaneFar);
		}
		else
		{
			this->mProjectionMatrix = math::ortho(this->mViewportRectX, this->mViewportRectX + this->mViewportRectWidth, this->mViewportRectY, this->mViewportRectY + this->mViewportRectHeight, this->mClippingPlaneNear, this->mViewportRectHeight);
		}

	}

	return this->mProjectionMatrix;
}

const math::Matrix4x4& Camera::GetViewMatrix()
{
	if (this->bmIsViewMatrixDirty.GetIsDirty(true))
	{
		auto transform = this->GetTransform();
		auto pos = transform->GetPosition();
		this->mViewMatrix = math::lookAt(pos, pos + transform->forward(), transform->up());
	}

	return this->mViewMatrix;
}

const math::Matrix4x4& doom::Camera::GetViewProjectionMatrix()
{
	if (this->bmIsViewProjectionMatrixDirty.GetIsDirty(true))
	{
		auto& viewMatrix = this->GetViewMatrix();
		auto& projectionMatrix = this->GetProjectionMatrix();
		this->mViewProjectionMatrix = projectionMatrix * viewMatrix;
	}
	return this->mViewProjectionMatrix;
}

math::Vector3 Camera::NDCToScreenPoint(const math::Vector3& ndcPoint)
{
	math::Vector3 screenPoint = ndcPoint + 1.0f;
	screenPoint /= 2;
	screenPoint.x *= graphics::Graphics_Server::GetScreenWidth();
	screenPoint.y *= -graphics::Graphics_Server::GetScreenHeight(); // top of screen position has negative y value, put minus when conver to screenPoint positiSon
	return screenPoint;
}

math::Vector3 Camera::ScreenToNDCPoint(const math::Vector3& screenPoint)
{
	math::Vector3 ndcPoint{ screenPoint };
	ndcPoint.x /= graphics::Graphics_Server::GetScreenWidth();
	ndcPoint.y /= graphics::Graphics_Server::GetScreenHeight();// top of screen position has negative y value, put minus when conver to viewPort positiSon
	ndcPoint *= 2.0f;
	ndcPoint -= 1;
	ndcPoint.y = -ndcPoint.y;

	ndcPoint.z = 0;

	return ndcPoint;
}

math::Vector3 doom::Camera::NDCToWorldPoint(const math::Vector3& ndcPoint)
{
	math::Matrix4x4 invViewAndProjectionMatrix{ this->GetProjectionMatrix() * this->GetViewMatrix() };
	invViewAndProjectionMatrix = invViewAndProjectionMatrix.inverse();

	math::Vector4 vec4NDCPoint{ ndcPoint };
	vec4NDCPoint.w = 1;

	math::Vector4 resultPoint{ invViewAndProjectionMatrix * vec4NDCPoint };
	resultPoint /= resultPoint.w;
	//resultPoint.z = -resultPoint.z; // OpenGl basically use right hand coordinate, but NDC use left hand coordinate
	return resultPoint;
}

math::Vector3 doom::Camera::WorldToNDCPoint(const math::Vector3& worldPosition)
{
	math::Vector4 resultPoint{ worldPosition };
	resultPoint.w = 1;

	resultPoint = this->GetProjectionMatrix() * this->GetViewMatrix() * resultPoint;
	resultPoint /= resultPoint.w;

	//resultPoint.z = -resultPoint.z; // OpenGl basically use right hand coordinate, but NDC use left hand coordinate
	return resultPoint;
}

math::Vector3 doom::Camera::ScreenToWorldPoint(const math::Vector3& screenPosition)
{
	math::Vector4 ndcPoint{ ScreenToNDCPoint(screenPosition) };
	ndcPoint.w = 1;

	return NDCToWorldPoint(ndcPoint);
}

math::Vector3 doom::Camera::WorldToScreenPoint(const math::Vector3& worldPosition)
{
	return NDCToScreenPoint(WorldToNDCPoint(worldPosition));
}



void Camera::UpdateUniformBufferObjectTempBuffer(graphics::UniformBufferObjectManager& uboManager)
{
	if (Scene::GetSingleton()->GetMainCamera() == this)
	{//if this camera is mainCamera
		auto& projectionMatrix = this->GetProjectionMatrix();

		//!!!! Opengl Use column major of matrix data layout
		uboManager.StoreDataAtTempBufferOfBindingPoint(GLOBAL_UNIFORM_BLOCK_BINDING_POINT, (void*)projectionMatrix.data(), sizeof(projectionMatrix), graphics::eUniformBlock_Global::projection);

		
		if (this->bmIsUboDirty.GetIsDirty(true))
		{//when transform value is changed
			auto& viewMatrix = this->GetViewMatrix(); 
			auto transform = this->GetTransform();
			const auto& camPos = transform->GetPosition();

			uboManager.StoreDataAtTempBufferOfBindingPoint(GLOBAL_UNIFORM_BLOCK_BINDING_POINT, (void*)viewMatrix.data(), sizeof(viewMatrix), graphics::eUniformBlock_Global::view);
			uboManager.StoreDataAtTempBufferOfBindingPoint(GLOBAL_UNIFORM_BLOCK_BINDING_POINT, (void*)camPos.data(), sizeof(camPos), graphics::eUniformBlock_Global::camPos);
		}
	}
}