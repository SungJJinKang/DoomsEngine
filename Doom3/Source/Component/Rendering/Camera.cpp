#include "Camera.h"
#include "../Core/Scene/Scene.h"


#include "../Graphics/Graphics_Server.h"
#include "../Graphics/graphicsSetting.h"
#include "Graphics/Buffer/UniformBufferObject/UniformBlockOffsetInfo.h"
#include "Graphics/GraphicsAPI/graphicsAPISetting.h"

using namespace dooms;

void Camera::SetProjectionMode(eProjectionType value)
{
	mProjectionMode = value;
	SetDirtyTrueAtThisFrame();
	bmIsProjectionMatrixDirty = true;
	bmIsViewProjectionMatrixDirty = true;
	bmIsModelViewProjectionMatrixDirty = true;
	bmIsFrustumPlaneMatrixDirty = true;
}

void Camera::SetProjectionMode()
{
	SetProjectionMode(mProjectionMode);
}

void Camera::SetFieldOfViewInDegree(FLOAT32 degree)
{
	mFieldOfViewInDegree = degree;
	SetDirtyTrueAtThisFrame();
	bmIsProjectionMatrixDirty = true;
	bmIsViewProjectionMatrixDirty = true;
	bmIsModelViewProjectionMatrixDirty = true;
	bmIsFrustumPlaneMatrixDirty = true;
}

void Camera::SetFieldOfViewInRadian(FLOAT32 radian)
{
	mFieldOfViewInDegree = radian * math::RADIAN_TO_DEGREE;
	SetDirtyTrueAtThisFrame();
	bmIsProjectionMatrixDirty = true;
	bmIsViewProjectionMatrixDirty = true;
	bmIsModelViewProjectionMatrixDirty = true;
	bmIsFrustumPlaneMatrixDirty = true;
}

void Camera::SetClippingPlaneNear(FLOAT32 value)
{
	mClippingPlaneNear = value;
	SetDirtyTrueAtThisFrame();
	bmIsProjectionMatrixDirty = true;
	bmIsViewProjectionMatrixDirty = true;
	bmIsModelViewProjectionMatrixDirty = true;
	bmIsFrustumPlaneMatrixDirty = true;
}

void Camera::SetClippingPlaneFar(FLOAT32 value)
{
	mClippingPlaneFar = value;
	SetDirtyTrueAtThisFrame();
	bmIsProjectionMatrixDirty = true;
	bmIsViewProjectionMatrixDirty = true;
	bmIsModelViewProjectionMatrixDirty = true;
	bmIsFrustumPlaneMatrixDirty = true;
}

void Camera::SetViewportRectX(FLOAT32 value)
{
	mViewportRectX = value;
	SetDirtyTrueAtThisFrame();
	bmIsProjectionMatrixDirty = true;
	bmIsViewProjectionMatrixDirty = true;
	bmIsModelViewProjectionMatrixDirty = true;
	bmIsFrustumPlaneMatrixDirty = true;
}

void Camera::SetViewportRectY(FLOAT32 value)
{
	mViewportRectY = value;
	SetDirtyTrueAtThisFrame();
	bmIsProjectionMatrixDirty = true;
	bmIsViewProjectionMatrixDirty = true;
	bmIsModelViewProjectionMatrixDirty = true;
	bmIsFrustumPlaneMatrixDirty = true;
}

void Camera::SetViewportRectWidth(FLOAT32 value)
{
	mViewportRectWidth = value;
	SetDirtyTrueAtThisFrame();
	bmIsProjectionMatrixDirty = true;
	bmIsViewProjectionMatrixDirty = true;
	bmIsModelViewProjectionMatrixDirty = true;
	bmIsFrustumPlaneMatrixDirty = true;
}

void Camera::SetViewportRectHeight(FLOAT32 value)
{
	mViewportRectHeight = value;
	SetDirtyTrueAtThisFrame();
	bmIsProjectionMatrixDirty = true;
	bmIsViewProjectionMatrixDirty = true;
	bmIsModelViewProjectionMatrixDirty = true;
	bmIsFrustumPlaneMatrixDirty = true;
}

Camera::Camera()
	:UniformBufferObjectUpdater(false), mClearColor(dooms::graphics::graphicsSetting::DefaultClearColor[0], dooms::graphics::graphicsSetting::DefaultClearColor[1], dooms::graphics::graphicsSetting::DefaultClearColor[2], dooms::graphics::graphicsSetting::DefaultClearColor[3])
{

}

void dooms::Camera::SetCameraFlag(const eCameraFlag cameraFlag, const bool isSet)
{
	if (isSet == true)
	{
		mCameraFlag |= cameraFlag ;
	}
	else
	{
		mCameraFlag &= ~cameraFlag;
	}
}

dooms::Camera::eProjectionType Camera::GetProjectionMode() const
{
	return mProjectionMode;
}

FLOAT32 Camera::GetFieldOfViewInDegree() const
{
	return mFieldOfViewInDegree;
}


FLOAT32 Camera::GetClippingPlaneNear() const
{
	return mClippingPlaneNear;
}

FLOAT32 Camera::GetClippingPlaneFar() const
{
	return mClippingPlaneFar;
}

FLOAT32 Camera::GetViewportRectX() const
{
	return mViewportRectX;
}

FLOAT32 Camera::GetViewportRectY() const
{
	return mViewportRectY;
}

FLOAT32 Camera::GetViewportRectWidth() const
{
	return mViewportRectWidth;
}

FLOAT32 Camera::GetViewportRectHeight() const
{
	return mViewportRectHeight;
}

bool dooms::Camera::GetCameraFlag(const eCameraFlag cameraFlag) const
{
	return ( mCameraFlag & static_cast<UINT32>(cameraFlag) ) != 0;
}

bool Camera::GetIsCullJobEnabled() const
{
	return (GetCameraFlag(dooms::eCameraFlag::IS_CULLED) == true) && (GetCameraFlag(dooms::eCameraFlag::PAUSE_CULL_JOB) == false);
}


const std::array<math::Vector4, 6>& dooms::Camera::CalculateFrustumPlane()
{
	auto& viewProjectionMatrix = GetViewProjectionMatrix();
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
	AddLocalDirtyToTransformDirtyReceiver(bmIsViewMatrixDirty);
	AddLocalDirtyToTransformDirtyReceiver(bmIsViewProjectionMatrixDirty);
	AddLocalDirtyToTransformDirtyReceiver(bmIsUboDirty);
	AddLocalDirtyToTransformDirtyReceiver(bmIsFrustumPlaneMatrixDirty);
	AddLocalDirtyToTransformDirtyReceiver(bmIsModelViewProjectionMatrixDirty);
	
	UpdateMainCamera();
	
}

void Camera::UpdateComponent()
{
}

void Camera::OnEndOfFrame_Component()
{

}

void Camera::UpdateMainCamera()
{
	dooms::Scene* const currentWorld = Scene::GetSingleton();
	Camera* currentMainCamera = currentWorld->GetMainCamera();
	if (currentMainCamera == nullptr)
	{
		currentWorld->SetMainCamera(this);
	}
}

void Camera::OnSetMainCamera()
{

}

void Camera::UpdateCallback()
{
	SetDirtyTrueAtThisFrame();
	bmIsProjectionMatrixDirty = true;
	bmIsViewProjectionMatrixDirty = true;
	bmIsModelViewProjectionMatrixDirty = true;
	bmIsFrustumPlaneMatrixDirty = true;
}


dooms::Camera* Camera::GetMainCamera()
{
	auto currentWorld = Scene::GetSingleton();
	return currentWorld->GetMainCamera();
}

/// <summary>
/// this function will be called at every frame
/// </summary>
/// <returns></returns>

const math::Matrix4x4& dooms::Camera::GetProjectionMatrix()
{
	if (bmIsProjectionMatrixDirty.GetIsDirty(true) )
	{
		if (mProjectionMode == eProjectionType::Perspective)
		{
			mProjectionMatrix = math::perspectiveFov(mFieldOfViewInDegree * math::DEGREE_TO_RADIAN, static_cast<FLOAT32>(graphics::graphicsAPISetting::GetScreenWidth()), static_cast<FLOAT32>(graphics::graphicsAPISetting::GetScreenHeight()), mClippingPlaneNear, mClippingPlaneFar);
			//mViewFrumstum.SetCamera(mFieldOfViewInRadian, dooms::graphics::Graphics_Server::GetScreenRatio(), mClippingPlaneNear, mClippingPlaneFar);
		}
		else
		{
			mProjectionMatrix = math::ortho(mViewportRectX, mViewportRectX + mViewportRectWidth, mViewportRectY, mViewportRectY + mViewportRectHeight, mClippingPlaneNear, mClippingPlaneFar);
			//mViewFrumstum.SetCamera(180.0f * math::DEGREE_TO_RADIAN, dooms::graphics::Graphics_Server::GetScreenRatio(), mClippingPlaneNear, mClippingPlaneFar);
		}

	}

	return mProjectionMatrix;
}

void Camera::OnDestroy()
{
	RemoveThisCameraFromMainCamera();

	graphics::UniformBufferObjectUpdater::RemoveFromUniformBufferObjectManager();
	StaticContainer<Camera>::RemoveFromStaticContainer();
}

void Camera::OnChangedByGUI(const dooms::reflection::DField& field_of_changed_field)
{
	Base::OnChangedByGUI(field_of_changed_field);

	UpdateCallback();

	

}

bool dooms::Camera::IsMainCamera() const
{
	return Camera::GetMainCamera() == this;
}

void dooms::Camera::RemoveThisCameraFromMainCamera()
{
	dooms::Scene* const currentWorld = Scene::GetSingleton();
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


math::Vector3 Camera::NDCToScreenPoint(const math::Vector3& ndcPoint)
{
	math::Vector3 screenPoint = ndcPoint + 1.0f;
	screenPoint /= 2;
	screenPoint.x *= graphics::graphicsAPISetting::GetScreenWidth();
	screenPoint.y *= -graphics::graphicsAPISetting::GetScreenHeight(); // top of screen position has negative y value, put minus when conver to screenPoint positiSon
	return screenPoint;
}

math::Vector3 Camera::ScreenToNDCPoint(const math::Vector3& screenPoint)
{
	math::Vector3 ndcPoint{ screenPoint };
	ndcPoint.x /= graphics::graphicsAPISetting::GetScreenWidth();
	ndcPoint.y /= graphics::graphicsAPISetting::GetScreenHeight();// top of screen position has negative y value, put minus when conver to viewPort positiSon
	ndcPoint *= 2.0f;
	ndcPoint -= 1;
	ndcPoint.y = -ndcPoint.y;

	ndcPoint.z = 0;

	return ndcPoint;
}

math::Vector3 dooms::Camera::NDCToWorldPoint(const math::Vector3& ndcPoint)
{
	math::Matrix4x4 invViewAndProjectionMatrix{ GetProjectionMatrix() * GetViewMatrix() };
	invViewAndProjectionMatrix = invViewAndProjectionMatrix.inverse();

	math::Vector4 vec4NDCPoint{ ndcPoint };
	vec4NDCPoint.w = 1;

	math::Vector4 resultPoint{ invViewAndProjectionMatrix * vec4NDCPoint };
	//resultPoint.z = -resultPoint.z; // OpenGl basically use right hand coordinate, but NDC use left hand coordinate
	return math::Vector3{ resultPoint /= resultPoint.w };
}

math::Vector3 dooms::Camera::WorldToNDCPoint(const math::Vector3& worldPosition)
{
	math::Vector4 resultPoint{ worldPosition };
	resultPoint.w = 1;

	resultPoint = GetProjectionMatrix() * GetViewMatrix() * resultPoint;
	resultPoint /= resultPoint.w;

	//resultPoint.z = -resultPoint.z; // OpenGl basically use right hand coordinate, but NDC use left hand coordinate
	return math::Vector3{ resultPoint };
}

math::Vector3 dooms::Camera::ScreenToWorldPoint(const math::Vector3& screenPosition)
{
	math::Vector4 ndcPoint{ ScreenToNDCPoint(screenPosition) };
	ndcPoint.w = 1;

	return NDCToWorldPoint(math::Vector3{ ndcPoint });
}

math::Vector3 dooms::Camera::WorldToScreenPoint(const math::Vector3& worldPosition)
{
	return NDCToScreenPoint(WorldToNDCPoint(worldPosition));
}



void Camera::UpdateUniformBufferObject(const bool force)
{
	if (Scene::GetSingleton()->GetMainCamera() == this)
	{//if this camera is mainCamera
		const math::Matrix4x4& projectionMatrix = GetProjectionMatrix();

		//!!!! Opengl Use column major of matrix data layout
		dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_BINDING_POINT)->UpdateDataToGPU((void*)projectionMatrix.data(), sizeof(projectionMatrix), dooms::graphics::eUniformBlock_Global::projection);
		dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_BINDING_POINT)->UpdateDataToGPU((void*)&mClippingPlaneNear, sizeof(FLOAT32), graphics::eUniformBlock_Global::camNear);
		dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_BINDING_POINT)->UpdateDataToGPU((void*)&mClippingPlaneFar, sizeof(FLOAT32), graphics::eUniformBlock_Global::camFar);

		
		auto& viewMatrix = GetViewMatrix(); 
		const dooms::Transform* const transform = GetTransform();
		const math::Vector3& camPos = transform->GetPosition();
		auto& viewProjectionMatrix = GetViewProjectionMatrix();

		dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_BINDING_POINT)->UpdateDataToGPU((void*)viewMatrix.data(), sizeof(viewMatrix), graphics::eUniformBlock_Global::view);
		dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_BINDING_POINT)->UpdateDataToGPU((void*)camPos.data(), sizeof(camPos), graphics::eUniformBlock_Global::camPos);
		dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_BINDING_POINT)->UpdateDataToGPU((void*)viewProjectionMatrix.data(), sizeof(viewProjectionMatrix), graphics::eUniformBlock_Global::viewProjection);
	
	}
}
