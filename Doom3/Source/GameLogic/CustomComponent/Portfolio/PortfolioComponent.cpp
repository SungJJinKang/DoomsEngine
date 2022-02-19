#include "PortfolioComponent.h"

#include "DeferredRenderingDebuggerController.h"
#include "Physics_Setting.h"
#include <Graphics/graphicsSetting.h>
#include <Rendering/Culling/EveryCulling/EveryCulling.h>
#include <Rendering/Pipeline/PipeLines/DefaultGraphcisPipeLine.h>
#include <Rendering/Batch/BatchRenderingManager.h>

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
	dooms::graphics::graphicsSetting::IsSortObjectFrontToBack = Enabled_MultiThread_SortingFrontToBack;
	//dooms::graphics::graphicsSetting::IsOverDrawVisualizationEnabled = OverdrawDebugger;

	if (DeferredRenderingDebuggerController* component = GetOwnerEntity()->GetComponent<DeferredRenderingDebuggerController>())
	{
		component->SetPIPVisible(Enabled_DeferredRenderingDebugger);

	}

	dooms::physics::Physics_Setting::SetIsPhysicsOn(Is_Enabled_CollisionDebugging);
	dooms::physics::Physics_Setting::IS_RENDER_PHYSICS_RAYCASTING_DEBUGGER = Is_Enabled_CollisionDebugging;

	dooms::graphics::graphicsSetting::IsDrawMaskedOcclusionCullingBinTriangleStageDebugger = See_MaskedSWOcclusionCulling_Occluder;
	dooms::graphics::graphicsSetting::IsDrawMaskedOcclusionCullingTileCoverageMaskDebugger = Is_Enabled_MaskedSWOcclusionCullingTileCoverageMaskDebugging;
	dooms::graphics::graphicsSetting::IsDrawMaskedOcclusionCullingTileL0MaxDepthValueDebugger = See_MaskedSWOcclusionCulling_DepthBuffer;

	graphics::DefaultGraphcisPipeLine* defaultGraphicsPipeLine = CastTo<graphics::DefaultGraphcisPipeLine*>(dooms::graphics::GraphicsPipeLine::GetSingleton());
	D_ASSERT(IsValid(defaultGraphicsPipeLine));
	if(IsValid(defaultGraphicsPipeLine))
	{
		defaultGraphicsPipeLine->mRenderingCullingManager.mCullingSystem->SetEnabledCullingModule(culling::EveryCulling::CullingModuleType::_ViewFrustumCulling, Enable_Multithread_SW_ViewFrustumCulling);
		defaultGraphicsPipeLine->mRenderingCullingManager.mCullingSystem->SetEnabledCullingModule(culling::EveryCulling::CullingModuleType::_MaskedSWOcclusionCulling, Enable_MaskedSWOccslusionCulling);
		defaultGraphicsPipeLine->mRenderingCullingManager.mCullingSystem->SetEnabledCullingModule(culling::EveryCulling::CullingModuleType::_DistanceCulling, Enable_DistanceCulling);
		defaultGraphicsPipeLine->mRenderingCullingManager.mCullingSystem->SetEnabledCullingModule(culling::EveryCulling::CullingModuleType::_PreCulling, Enable_PreCulling);
	}
}

void dooms::PortfolioComponent::InitComponent()
{

	Base::InitComponent();
	
	Enabled_MultiThread_SortingFrontToBack = true;
	dooms::graphics::graphicsSetting::IsSortObjectFrontToBack = true;
	dooms::graphics::graphicsSetting::IsDrawMaskedOcclusionCullingBinTriangleStageDebugger = See_MaskedSWOcclusionCulling_Occluder;
	dooms::graphics::graphicsSetting::IsDrawMaskedOcclusionCullingTileCoverageMaskDebugger = Is_Enabled_MaskedSWOcclusionCullingTileCoverageMaskDebugging;
	dooms::graphics::graphicsSetting::IsDrawMaskedOcclusionCullingTileL0MaxDepthValueDebugger = See_MaskedSWOcclusionCulling_DepthBuffer;

	//OverdrawDebugger = false;
	//dooms::graphics::graphicsSetting::IsOverDrawVisualizationEnabled = OverdrawDebugger;

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

void dooms::PortfolioComponent::SetBoxsStatic()
{
	graphics::BatchRenderingManager::GetSingleton()->SetPauseBakeBatchMesh(true);
	for(Entity* entity : StaticMobilitySetter)
	{
		entity->SetEntityMobility(eEntityMobility::Static);
	}
	graphics::BatchRenderingManager::GetSingleton()->SetPauseBakeBatchMesh(false);
}

void dooms::PortfolioComponent::SetBoxsDynamic()
{
	graphics::BatchRenderingManager::GetSingleton()->SetPauseBakeBatchMesh(true);
	for (Entity* entity : StaticMobilitySetter)
	{
		entity->SetEntityMobility(eEntityMobility::Dynamic);
	}
	graphics::BatchRenderingManager::GetSingleton()->SetPauseBakeBatchMesh(false);
}
