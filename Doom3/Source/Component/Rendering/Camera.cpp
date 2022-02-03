#include "Camera.h"
#include "../Core/Scene/Scene.h"


#include "../Graphics/Graphics_Server.h"
#include "../Graphics/graphicsSetting.h"
#include "Graphics/Buffer/UniformBufferObject/UniformBlockOffsetInfo.h"
#include "Graphics/GraphicsAPI/graphicsAPISetting.h"
#include <Graphics/GraphicsAPI/Manager/GraphicsAPIManager.h>

void dooms::Camera::SetProjectionMode(eProjectionType value)
{
	mProjectionMode = value;
	SetDirtyTrueAtThisFrame();
}

void dooms::Camera::SetProjectionMode()
{
	SetProjectionMode(mProjectionMode);
}

void dooms::Camera::SetFieldOfViewInDegree(FLOAT32 degree)
{
	mFieldOfViewInDegree = degree;
	SetDirtyTrueAtThisFrame();
}

void dooms::Camera::SetFieldOfViewInRadian(FLOAT32 radian)
{
	mFieldOfViewInDegree = radian * math::RADIAN_TO_DEGREE;
	SetDirtyTrueAtThisFrame();
}

void dooms::Camera::SetClippingPlaneNear(FLOAT32 value)
{
	mClippingPlaneNear = value;
	SetDirtyTrueAtThisFrame();
}

void dooms::Camera::SetClippingPlaneFar(FLOAT32 value)
{
	mClippingPlaneFar = value;
	SetDirtyTrueAtThisFrame();
}

void dooms::Camera::SetViewportRectX(FLOAT32 value)
{
	mViewportRectX = value;
	SetDirtyTrueAtThisFrame();
}

void dooms::Camera::SetViewportRectY(FLOAT32 value)
{
	mViewportRectY = value;
	SetDirtyTrueAtThisFrame();
}

void dooms::Camera::SetViewportRectWidth(FLOAT32 value)
{
	mViewportRectWidth = value;
	SetDirtyTrueAtThisFrame();
}

void dooms::Camera::SetViewportRectHeight(FLOAT32 value)
{
	mViewportRectHeight = value;
	SetDirtyTrueAtThisFrame();
}

dooms::Camera::Camera()
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

dooms::Camera::eProjectionType dooms::Camera::GetProjectionMode() const
{
	return mProjectionMode;
}

FLOAT32 dooms::Camera::GetFieldOfViewInDegree() const
{
	return mFieldOfViewInDegree;
}


FLOAT32 dooms::Camera::GetClippingPlaneNear() const
{
	return mClippingPlaneNear;
}

FLOAT32 dooms::Camera::GetClippingPlaneFar() const
{
	return mClippingPlaneFar;
}

FLOAT32 dooms::Camera::GetViewportRectX() const
{
	return mViewportRectX;
}

FLOAT32 dooms::Camera::GetViewportRectY() const
{
	return mViewportRectY;
}

FLOAT32 dooms::Camera::GetViewportRectWidth() const
{
	return mViewportRectWidth;
}

FLOAT32 dooms::Camera::GetViewportRectHeight() const
{
	return mViewportRectHeight;
}

bool dooms::Camera::GetCameraFlag(const eCameraFlag cameraFlag) const
{
	return ( mCameraFlag & static_cast<UINT32>(cameraFlag) ) != 0;
}

bool dooms::Camera::GetIsCullJobEnabled() const
{
	return (GetCameraFlag(dooms::eCameraFlag::IS_CULLED) == true) && (GetCameraFlag(dooms::eCameraFlag::PAUSE_CULL_JOB) == false);
}


std::array<math::Vector4, 6> dooms::Camera::CalculateFrustumPlane()
{
	const math::Matrix4x4 viewProjectionMatrix = GetViewProjectionMatrix();

	std::array<math::Vector4, 6> frustumPlane{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	// Left Frustum Plane
   // Add first column of the matrix to the fourth column
	frustumPlane[0].x = viewProjectionMatrix[0][3] + viewProjectionMatrix[0][0];
	frustumPlane[0].y = viewProjectionMatrix[1][3] + viewProjectionMatrix[1][0];
	frustumPlane[0].z = viewProjectionMatrix[2][3] + viewProjectionMatrix[2][0];
	frustumPlane[0].w = viewProjectionMatrix[3][3] + viewProjectionMatrix[3][0];
	frustumPlane[0].Normalize();

	// Right Frustum Plane
	// Subtract first column of matrix from the fourth column
	frustumPlane[1].x = viewProjectionMatrix[0][3] - viewProjectionMatrix[0][0];
	frustumPlane[1].y = viewProjectionMatrix[1][3] - viewProjectionMatrix[1][0];
	frustumPlane[1].z = viewProjectionMatrix[2][3] - viewProjectionMatrix[2][0];
	frustumPlane[1].w = viewProjectionMatrix[3][3] - viewProjectionMatrix[3][0];
	frustumPlane[1].Normalize();

	// Top Frustum Plane
	// Subtract second column of matrix from the fourth column
	frustumPlane[2].x = viewProjectionMatrix[0][3] - viewProjectionMatrix[0][1];
	frustumPlane[2].y = viewProjectionMatrix[1][3] - viewProjectionMatrix[1][1];
	frustumPlane[2].z = viewProjectionMatrix[2][3] - viewProjectionMatrix[2][1];
	frustumPlane[2].w = viewProjectionMatrix[3][3] - viewProjectionMatrix[3][1];
	frustumPlane[2].Normalize();

	// Bottom Frustum Plane
	// Add second column of the matrix to the fourth column
	frustumPlane[3].x = viewProjectionMatrix[0][3] + viewProjectionMatrix[0][1];
	frustumPlane[3].y = viewProjectionMatrix[1][3] + viewProjectionMatrix[1][1];
	frustumPlane[3].z = viewProjectionMatrix[2][3] + viewProjectionMatrix[2][1];
	frustumPlane[3].w = viewProjectionMatrix[3][3] + viewProjectionMatrix[3][1];
	frustumPlane[3].Normalize();

	// Near Frustum Plane
	// We could add the third column to the fourth column to get the near plane,
	// but we don't have to do this because the third column IS the near plane
	frustumPlane[4].x = viewProjectionMatrix[0][2];
	frustumPlane[4].y = viewProjectionMatrix[1][2];
	frustumPlane[4].z = viewProjectionMatrix[2][2];
	frustumPlane[4].w = viewProjectionMatrix[3][2];
	frustumPlane[4].Normalize();

	// Far Frustum Plane
	// Subtract third column of matrix from the fourth column
	frustumPlane[5].x = viewProjectionMatrix[0][3] - viewProjectionMatrix[0][2];
	frustumPlane[5].y = viewProjectionMatrix[1][3] - viewProjectionMatrix[1][2];
	frustumPlane[5].z = viewProjectionMatrix[2][3] - viewProjectionMatrix[2][2];
	frustumPlane[5].w = viewProjectionMatrix[3][3] - viewProjectionMatrix[3][2];
	frustumPlane[5].Normalize();

	return frustumPlane;
}



void dooms::Camera::InitComponent()
{
	AddLocalDirtyToTransformDirtyReceiver(bmIsUboDirty);
	
	UpdateMainCamera();
	
}

void dooms::Camera::UpdateComponent()
{
}

void dooms::Camera::OnEndOfFrame_Component()
{

}

void dooms::Camera::UpdateMainCamera()
{
	dooms::Scene* const currentWorld = Scene::GetSingleton();
	Camera* currentMainCamera = currentWorld->GetMainCamera();
	if (currentMainCamera == nullptr)
	{
		currentWorld->SetMainCamera(this);
	}
}

void dooms::Camera::OnSetMainCamera()
{

}

void dooms::Camera::UpdateCallback()
{
	SetDirtyTrueAtThisFrame();
}


dooms::Camera* dooms::Camera::GetMainCamera()
{
	auto currentWorld = Scene::GetSingleton();
	return currentWorld->GetMainCamera();
}

/// <summary>
/// this function will be called at every frame
/// </summary>
/// <returns></returns>

math::Matrix4x4 dooms::Camera::GetProjectionMatrix()
{
	math::Matrix4x4 result{ nullptr };
	if (mProjectionMode == eProjectionType::Perspective)
	{
		result = math::perspectiveFov(mFieldOfViewInDegree * math::DEGREE_TO_RADIAN, static_cast<FLOAT32>(graphics::graphicsAPISetting::GetScreenWidth()), static_cast<FLOAT32>(graphics::graphicsAPISetting::GetScreenHeight()), mClippingPlaneNear, mClippingPlaneFar);
		//mViewFrumstum.SetCamera(mFieldOfViewInRadian, dooms::graphics::Graphics_Server::GetScreenRatio(), mClippingPlaneNear, mClippingPlaneFar);
	}
	else if (mProjectionMode == eProjectionType::Orthographic)
	{
		result = math::ortho(mViewportRectX, mViewportRectX + mViewportRectWidth, mViewportRectY, mViewportRectY + mViewportRectHeight, mClippingPlaneNear, mClippingPlaneFar);
		//mViewFrumstum.SetCamera(180.0f * math::DEGREE_TO_RADIAN, dooms::graphics::Graphics_Server::GetScreenRatio(), mClippingPlaneNear, mClippingPlaneFar);
	}
	else
	{
		NEVER_HAPPEN;
	}

	if(dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		static const math::Matrix4x4 zOffsetForD3D = math::scale(math::Vector3{ 1.0f, 1.0f, 0.5f }) * math::translate(math::Vector3{ 0, 0, 1.0f });
		result = zOffsetForD3D * result;
	}

	return result;
}

void dooms::Camera::OnDestroy()
{
	RemoveThisCameraFromMainCamera();

	graphics::UniformBufferObjectUpdater::RemoveFromUniformBufferObjectManager();
	StaticContainer<Camera>::RemoveFromStaticContainer();
}

void dooms::Camera::OnChangedByGUI(const dooms::reflection::DField& field_of_changed_field)
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


math::Vector3 dooms::Camera::NDCToScreenPoint(const math::Vector3& ndcPoint)
{
	math::Vector3 screenPoint = ndcPoint + 1.0f;
	screenPoint /= 2;
	screenPoint.x *= graphics::graphicsAPISetting::GetScreenWidth();
	screenPoint.y *= -graphics::graphicsAPISetting::GetScreenHeight(); // top of screen position has negative y value, put minus when conver to screenPoint positiSon
	return screenPoint;
}

math::Vector3 dooms::Camera::ScreenToNDCPoint(const math::Vector3& screenPoint)
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



void dooms::Camera::UpdateUniformBufferObject(const bool force)
{
	if (Scene::GetSingleton()->GetMainCamera() == this)
	{//if this camera is mainCamera
		const math::Matrix4x4 projectionMatrix = GetProjectionMatrix();

		//!!!! Opengl Use column major of matrix data layout

		dooms::graphics::UniformBufferObject* const ubo = dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_NAME);
		D_ASSERT(IsValid(ubo));

		if (IsValid(ubo))
		{
			ubo->UpdateLocalBuffer((void*)projectionMatrix.data(), dooms::graphics::eUniformBlock_Global::projection, sizeof(projectionMatrix));
			ubo->UpdateLocalBuffer((void*)&mClippingPlaneNear, graphics::eUniformBlock_Global::camNear, sizeof(FLOAT32));
			ubo->UpdateLocalBuffer((void*)&mClippingPlaneFar, graphics::eUniformBlock_Global::camFar, sizeof(FLOAT32));


			const math::Matrix4x4 viewMatrix = GetViewMatrix();
			const dooms::Transform* const transform = GetTransform();
			const math::Vector3& camPos = transform->GetPosition();
			const math::Matrix4x4 viewProjectionMatrix = GetViewProjectionMatrix();

			ubo->UpdateLocalBuffer((void*)viewMatrix.data(), graphics::eUniformBlock_Global::view, sizeof(viewMatrix));
			ubo->UpdateLocalBuffer((void*)camPos.data(), graphics::eUniformBlock_Global::camPos, sizeof(camPos));
			ubo->UpdateLocalBuffer((void*)viewProjectionMatrix.data(), graphics::eUniformBlock_Global::viewProjection, sizeof(viewProjectionMatrix));
		}
	}
}
