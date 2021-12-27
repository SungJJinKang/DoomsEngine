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
	dooms::graphics::Graphics_Setting::IsSortObjectFrontToBack = Is_Enabled_MultiThread_SortingFrontToBack;
	dooms::graphics::Graphics_Setting::IsOverDrawVisualizationEnabled = Is_Enabled_OverdrawDebugger;

	if (DeferredRenderingDebuggerController* component = GetOwnerEntity()->GetComponent<DeferredRenderingDebuggerController>())
	{
		component->SetPIPVisible(Is_Enabled_DeferredRenderingDebugger);

	}

	dooms::physics::Physics_Setting::SetIsPhysicsOn(Is_Enabled_CollisionDebugging);
	dooms::physics::Physics_Setting::IS_RENDER_PHYSICS_RAYCASTING_DEBUGGER = Is_Enabled_CollisionDebugging;

	dooms::graphics::Graphics_Setting::IsDrawMaskedOcclusionCullingBinTriangleStageDebugger = Is_Enabled_MaskedSWOcclusionCullingBinsStageDebugging;
	dooms::graphics::Graphics_Setting::IsDrawMaskedOcclusionCullingTileCoverageMaskDebugger = Is_Enabled_MaskedSWOcclusionCullingTileCoverageMaskDebugging;
	dooms::graphics::Graphics_Setting::IsDrawMaskedOcclusionCullingTileL0MaxDepthValueDebugger = Is_Enabled_MaskedSWOcclusionCullingTileL0MaxDepthValueDebugging;


	dooms::graphics::Graphics_Server::GetSingleton()->mCullingSystem->SetEnabledCullingModule(culling::EveryCulling::CullingModuleType::_ViewFrustumCulling, _EnableViewFrustumCulling);
	dooms::graphics::Graphics_Server::GetSingleton()->mCullingSystem->SetEnabledCullingModule(culling::EveryCulling::CullingModuleType::_MaskedSWOcclusionCulling, _EnableMaskedSWOcclusionCulling);
}

void dooms::PortfolioComponent::InitComponent()
{

	Base::InitComponent();
	
	Is_Enabled_MultiThread_SortingFrontToBack = true;
	dooms::graphics::Graphics_Setting::IsSortObjectFrontToBack = true;
	dooms::graphics::Graphics_Setting::IsDrawMaskedOcclusionCullingBinTriangleStageDebugger = Is_Enabled_MaskedSWOcclusionCullingBinsStageDebugging;
	dooms::graphics::Graphics_Setting::IsDrawMaskedOcclusionCullingTileCoverageMaskDebugger = Is_Enabled_MaskedSWOcclusionCullingTileCoverageMaskDebugging;
	dooms::graphics::Graphics_Setting::IsDrawMaskedOcclusionCullingTileL0MaxDepthValueDebugger = Is_Enabled_MaskedSWOcclusionCullingTileL0MaxDepthValueDebugging;

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
