#include "ViewFrustumCullingDebug.h"

#include <Graphics/Graphics_Server.h>
#include <Rendering/Camera.h>
#include "UI/PrintText.h"
#include <Graphics/Graphics_Setting.h>
#include <Graphics/GraphicsAPIManager.h>

void doom::ViewFrustumCullingDebug::InitComponent()
{
	auto currenScene = doom::Scene::GetCurrentWorld();

	ShowIsViewFrustumCullingActivated();
}

void doom::ViewFrustumCullingDebug::ShowIsViewFrustumCullingActivated()
{
	if (Camera::GetMainCamera()->GetCameraFlag(doom::eCameraFlag::PAUSE_CULL_JOB) == true)
	{
		doom::ui::PrintText("%s", "Multi Thread ViewFrustumCulling 중단");

		doom::graphics::GraphicsAPIManager::SetWindowTitle("Space Key : Multi Thread ViewFrustumCulling On/Off ( Current Value : Off )");
	}
	else
	{
		doom::ui::PrintText("%s", "Multi Thread ViewFrustumCulling 시작");

		doom::graphics::GraphicsAPIManager::SetWindowTitle("Space Key : Multi Thread ViewFrustumCulling On/Off ( Current Value : On )");
	}
}

static float previousTime = 0;

void doom::ViewFrustumCullingDebug::UpdateComponent()
{
	if (UserInput_Server::GetKeyUp(eKEY_CODE::KEY_SPACE))
	{
		const bool currentFlag = Camera::GetMainCamera()->GetCameraFlag(doom::eCameraFlag::PAUSE_CULL_JOB);

		Camera::GetMainCamera()->SetCameraFlag(doom::eCameraFlag::PAUSE_CULL_JOB, !currentFlag);

		ShowIsViewFrustumCullingActivated();
	}

	if (UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F7))
	{
		doom::ui::PrintText("Current Frame : %f", GetTransform()->ToString().c_str());
	}

	previousTime += doom::time::MainTimer::GetDeltaTime();

	if (previousTime > 1.0f)
	{
		previousTime = 0.0f;
		doom::ui::PrintText("Current Frame : %f", 1.0f / doom::time::MainTimer::GetDeltaTime());
	}


}

void doom::ViewFrustumCullingDebug::OnEndOfFrame_Component()
{
}
