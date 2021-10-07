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
		doom::ui::PrintText("%s", "Multi Thread ViewFrustumCulling �ߴ�");

	}
	else
	{
		doom::ui::PrintText("%s", "Multi Thread ViewFrustumCulling ����");

	}
}

static float previousTime = 0;

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
