#include "PortfolioComponent.h"

#include "DeferredRenderingDebuggerController.h"
#include "Physics_Setting.h"



void dooms::PortfolioComponent::OnChangedByGUI(const dooms::reflection::DField& field_of_changed_field)
{
	Component::OnChangedByGUI(field_of_changed_field);

	UpdateGUI();

	if(field_of_changed_field.CompareWithFieldName("AllRocksDesiredMaxDrawDistance"))
	{
		for(auto renderer : RockRenderers)
		{
			renderer->SetDesiredMaxDrawDistance(AllRocksDesiredMaxDrawDistance);
		}
	}

	if (field_of_changed_field.CompareWithFieldName("AllPlanesDesiredMaxDrawDistance"))
	{
		for (auto renderer : PlanesRenderers)
		{
			renderer->SetDesiredMaxDrawDistance(AllPlanesDesiredMaxDrawDistance);
		}
	}
}

void dooms::PortfolioComponent::UpdateGUI()
{
	dooms::graphics::Graphics_Setting::IsSortObjectFrontToBack = Enabled_MultiThread_SortingFrontToBack;
	dooms::graphics::Graphics_Setting::IsOverDrawVisualizationEnabled = OverdrawDebugger;

	if (DeferredRenderingDebuggerController* component = GetOwnerEntity()->GetComponent<DeferredRenderingDebuggerController>())
	{
		component->SetPIPVisible(Enabled_DeferredRenderingDebugger);

	}

	dooms::physics::Physics_Setting::SetIsPhysicsOn(Is_Enabled_CollisionDebugging);
	dooms::physics::Physics_Setting::IS_RENDER_PHYSICS_RAYCASTING_DEBUGGER = Is_Enabled_CollisionDebugging;

	dooms::graphics::Graphics_Setting::IsDrawMaskedOcclusionCullingBinTriangleStageDebugger = See_MaskedSWOcclusionCulling_Occluder;
	dooms::graphics::Graphics_Setting::IsDrawMaskedOcclusionCullingTileCoverageMaskDebugger = Is_Enabled_MaskedSWOcclusionCullingTileCoverageMaskDebugging;
	dooms::graphics::Graphics_Setting::IsDrawMaskedOcclusionCullingTileL0MaxDepthValueDebugger = See_MaskedSWOcclusionCulling_DepthBuffer;


	dooms::graphics::Graphics_Server::GetSingleton()->mCullingSystem->SetEnabledCullingModule(culling::EveryCulling::CullingModuleType::_ViewFrustumCulling, Enable_Multithread_SW_ViewFrustumCulling);
	dooms::graphics::Graphics_Server::GetSingleton()->mCullingSystem->SetEnabledCullingModule(culling::EveryCulling::CullingModuleType::_MaskedSWOcclusionCulling, Enable_MaskedSWOccslusionCulling);
	dooms::graphics::Graphics_Server::GetSingleton()->mCullingSystem->SetEnabledCullingModule(culling::EveryCulling::CullingModuleType::_DistanceCulling, Enable_DistanceCulling);
}

void dooms::PortfolioComponent::InitComponent()
{

	Base::InitComponent();
	
	Enabled_MultiThread_SortingFrontToBack = true;
	dooms::graphics::Graphics_Setting::IsSortObjectFrontToBack = true;
	dooms::graphics::Graphics_Setting::IsDrawMaskedOcclusionCullingBinTriangleStageDebugger = See_MaskedSWOcclusionCulling_Occluder;
	dooms::graphics::Graphics_Setting::IsDrawMaskedOcclusionCullingTileCoverageMaskDebugger = Is_Enabled_MaskedSWOcclusionCullingTileCoverageMaskDebugging;
	dooms::graphics::Graphics_Setting::IsDrawMaskedOcclusionCullingTileL0MaxDepthValueDebugger = See_MaskedSWOcclusionCulling_DepthBuffer;

	OverdrawDebugger = false;
	dooms::graphics::Graphics_Setting::IsOverDrawVisualizationEnabled = OverdrawDebugger;

	Enabled_DeferredRenderingDebugger = false;
	if (DeferredRenderingDebuggerController* component = GetOwnerEntity()->GetComponent<DeferredRenderingDebuggerController>())
	{
		component->SetPIPVisible(Enabled_DeferredRenderingDebugger);

	}

	Is_Enabled_CollisionDebugging = false;
	dooms::physics::Physics_Setting::SetIsPhysicsOn(Is_Enabled_CollisionDebugging);
	dooms::physics::Physics_Setting::IS_RENDER_PHYSICS_RAYCASTING_DEBUGGER = Is_Enabled_CollisionDebugging;

	UpdateGUI();
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
