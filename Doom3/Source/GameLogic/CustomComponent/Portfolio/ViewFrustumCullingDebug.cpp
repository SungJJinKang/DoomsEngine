#include "ViewFrustumCullingDebug.h"

#include <Graphics/Graphics_Server.h>
#include <Rendering/Camera.h>

void doom::ViewFrustumCullingDebug::InitComponent()
{
	auto currenScene = doom::Scene::GetCurrentWorld();

	auto entity1 = currenScene->CreateNewEntity();
	auto entity1Camera = entity1->AddComponent<Camera>();
	entity1Camera->SetCameraFlag(eCameraFlag::IS_CULLED ,false);
	entity1Camera->SetProjectionMode(doom::Camera::eProjectionType::Perspective);
	entity1->GetTransform()->SetPosition(0.0f, 200.0f, 0.0f);
	entity1->GetTransform()->SetRotation(math::Vector3(90.0f, 0.0f, 0.0f));
	


}

void doom::ViewFrustumCullingDebug::UpdateComponent()
{
}

void doom::ViewFrustumCullingDebug::OnEndOfFrame_Component()
{
}
