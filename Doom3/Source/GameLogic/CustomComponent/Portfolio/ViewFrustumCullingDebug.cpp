#include "ViewFrustumCullingDebug.h"

#include <Rendering/Camera.h>
#include "UI/PrintText.h"

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

	}
	else
	{
		doom::ui::PrintText("%s", "Multi Thread ViewFrustumCulling 시작");

	}
}

static FLOAT32 previousTime = 0;

void doom::ViewFrustumCullingDebug::UpdateComponent()
{
	if (UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F4))
	{
		const bool currentFlag = Camera::GetMainCamera()->GetCameraFlag(doom::eCameraFlag::PAUSE_CULL_JOB);

		Camera::GetMainCamera()->SetCameraFlag(doom::eCameraFlag::PAUSE_CULL_JOB, !currentFlag);

		ShowIsViewFrustumCullingActivated();
	}


}

void doom::ViewFrustumCullingDebug::OnEndOfFrame_Component()
{
}
