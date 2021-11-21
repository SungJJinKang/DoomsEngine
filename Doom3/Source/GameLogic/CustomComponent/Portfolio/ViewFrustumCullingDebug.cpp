#include "ViewFrustumCullingDebug.h"

#include <Rendering/Camera.h>
#include "EngineGUI/PrintText.h"

void dooms::ViewFrustumCullingDebug::InitComponent()
{
	auto currenScene = dooms::Scene::GetCurrentWorld();

	ShowIsViewFrustumCullingActivated();
}

void dooms::ViewFrustumCullingDebug::ShowIsViewFrustumCullingActivated()
{
	if(Camera::GetMainCamera() != nullptr)
	{
		if (Camera::GetMainCamera()->GetCameraFlag(dooms::eCameraFlag::PAUSE_CULL_JOB) == true)
		{
			dooms::ui::PrintText("%s", "Multi Thread ViewFrustumCulling �ߴ�");

		}
		else
		{
			dooms::ui::PrintText("%s", "Multi Thread ViewFrustumCulling ����");

		}
	}
}

static FLOAT32 previousTime = 0;

void dooms::ViewFrustumCullingDebug::UpdateComponent()
{
	if (UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F4))
	{
		const bool currentFlag = Camera::GetMainCamera()->GetCameraFlag(dooms::eCameraFlag::PAUSE_CULL_JOB);

		Camera::GetMainCamera()->SetCameraFlag(dooms::eCameraFlag::PAUSE_CULL_JOB, !currentFlag);

		ShowIsViewFrustumCullingActivated();
	}


}

void dooms::ViewFrustumCullingDebug::OnEndOfFrame_Component()
{
}
