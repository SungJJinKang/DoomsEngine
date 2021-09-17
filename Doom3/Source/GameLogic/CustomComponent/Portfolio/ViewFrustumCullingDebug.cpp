#include "ViewFrustumCullingDebug.h"

#include <Graphics/Graphics_Server.h>
#include <Rendering/Camera.h>
#include "UI/PrintText.h"
#include <Graphics/Graphics_Setting.h>

void doom::ViewFrustumCullingDebug::InitComponent()
{
	auto currenScene = doom::Scene::GetCurrentWorld();

	/*
	auto entity1 = currenScene->CreateNewEntity();
	auto entity1Camera = entity1->AddComponent<Camera>();
	entity1Camera->SetCameraFlag(eCameraFlag::IS_CULLED ,false);
	entity1Camera->SetProjectionMode(doom::Camera::eProjectionType::Perspective);
	entity1->GetTransform()->SetPosition(0.0f, 200.0f, 0.0f);
	entity1->GetTransform()->SetRotation(math::Vector3(90.0f, 0.0f, 0.0f));
	*/


}

void doom::ViewFrustumCullingDebug::UpdateComponent()
{
	if (UserInput_Server::GetKeyUp(eKEY_CODE::KEY_SPACE))
	{
		const bool currentFlag = Camera::GetMainCamera()->GetCameraFlag(doom::eCameraFlag::PAUSE_CULL_JOB);

		Camera::GetMainCamera()->SetCameraFlag(doom::eCameraFlag::PAUSE_CULL_JOB, !currentFlag);
	



		if ( (!currentFlag) == true)
		{
			doom::ui::PrintText("%s", "Multi Thread ViewFrustumCulling 중단");
		}
		else
		{
			doom::ui::PrintText("%s", "Multi Thread ViewFrustumCulling 시작");
		}
	}
}

void doom::ViewFrustumCullingDebug::OnEndOfFrame_Component()
{
}
