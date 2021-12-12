#include "PortfolioComponent.h"

#include "DeferredRenderingDebuggerController.h"
#include "Physics_Setting.h"



void dooms::PortfolioComponent::OnChangedByGUI(const dooms::reflection::DField& field_of_changed_field)
{
	Component::OnChangedByGUI(field_of_changed_field);

	UpdateGUI();
}

void dooms::PortfolioComponent::UpdateGUI()
{
	Camera::GetMainCamera()->SetCameraFlag(dooms::eCameraFlag::PAUSE_CULL_JOB, Is_Pause_Multithread_ViewfrustumCulling);
	
	dooms::graphics::Graphics_Setting::IsSortObjectFrontToBack = Is_Enabled_MultiThread_SortingFrontToBack;
	dooms::graphics::Graphics_Setting::IsOverDrawVisualizationEnabled = Is_Enabled_OverdrawDebugger;

	if(DeferredRenderingDebuggerController* component = GetOwnerEntity()->GetComponent<DeferredRenderingDebuggerController>())
	{
		component->SetPIPVisible(Is_Enabled_DeferredRenderingDebugger);

	}
	
	dooms::physics::Physics_Setting::SetIsPhysicsOn(Is_Enabled_CollisionDebugging);
	dooms::physics::Physics_Setting::IS_RENDER_PHYSICS_RAYCASTING_DEBUGGER = Is_Enabled_CollisionDebugging;
}

void dooms::PortfolioComponent::InitComponent()
{

	Base::InitComponent();

	Is_Pause_Multithread_ViewfrustumCulling = false;
	Camera::GetMainCamera()->SetCameraFlag(dooms::eCameraFlag::PAUSE_CULL_JOB, Is_Pause_Multithread_ViewfrustumCulling);

	Is_Enabled_MultiThread_SortingFrontToBack = true;
	dooms::graphics::Graphics_Setting::IsSortObjectFrontToBack = true;

	Is_Enabled_OverdrawDebugger = false;
	dooms::graphics::Graphics_Setting::IsOverDrawVisualizationEnabled = Is_Enabled_OverdrawDebugger;

	Is_Enabled_DeferredRenderingDebugger = false;
	if (DeferredRenderingDebuggerController* component = GetOwnerEntity()->GetComponent<DeferredRenderingDebuggerController>())
	{
		component->SetPIPVisible(Is_Enabled_DeferredRenderingDebugger);

	}

	Is_Enabled_CollisionDebugging = false;
	dooms::physics::Physics_Setting::SetIsPhysicsOn(Is_Enabled_CollisionDebugging);
	dooms::physics::Physics_Setting::IS_RENDER_PHYSICS_RAYCASTING_DEBUGGER = Is_Enabled_CollisionDebugging;

}

void dooms::PortfolioComponent::LateInitComponent()
{
	Base::LateInitComponent();



	mEngineGUIAccessor.SetIsVisibleOnGUI(true);
}

void dooms::PortfolioComponent::UpdateComponent()
{
	
}

void dooms::PortfolioComponent::OnEndOfFrame_Component()
{

}
