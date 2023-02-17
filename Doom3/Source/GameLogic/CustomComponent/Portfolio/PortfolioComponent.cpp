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

	if(field_of_changed_field.CompareWithFieldName("AllRocksDesiredDrawDistance"))
	{
		for(auto renderer : RockRenderers)
		{
			renderer->SetDesiredMaxDrawDistance(AllRocksDesiredDrawDistance);
		}
	}

	if (field_of_changed_field.CompareWithFieldName("AllAirPlanesMaxDrawDistance"))
	{
		for (auto renderer : PlanesRenderers)
		{
			renderer->SetDesiredMaxDrawDistance(AllAirPlanesMaxDrawDistance);
		}
	}
}

void dooms::PortfolioComponent::UpdateGUI()
{
	dooms::graphics::graphicsSetting::IsDrawMaskedOcclusionCullingBinTriangleStageDebugger = See_MaskedSWOcclusionCulling_Occluder;
	dooms::graphics::graphicsSetting::IsDrawMaskedOcclusionCullingTileCoverageMaskDebugger = Is_Enabled_MaskedSWOcclusionCullingTileCoverageMaskDebugging;
	dooms::graphics::graphicsSetting::IsDrawMaskedOcclusionCullingTileL0MaxDepthValueDebugger = See_MaskedSWOcclusionCulling_DepthBuffer;
	dooms::graphics::graphicsSetting::IsDrawMaskedOcclusionCullingOcculderBoundingBoxDebugger = See_MaskedSWOcclusionCulling_OccluderBoudingBox;
	
	graphics::DefaultGraphcisPipeLine* defaultGraphicsPipeLine = CastTo<graphics::DefaultGraphcisPipeLine*>(dooms::graphics::GraphicsPipeLine::GetSingleton());
	D_ASSERT(IsValid(defaultGraphicsPipeLine));
	if(IsValid(defaultGraphicsPipeLine))
	{
		defaultGraphicsPipeLine->mRenderingCullingManager.mCullingSystem->SetEnabledCullingModule(culling::EveryCulling::CullingModuleType::_ViewFrustumCulling, Enable_Multithread_SW_ViewFrustumCulling);
		defaultGraphicsPipeLine->mRenderingCullingManager.mCullingSystem->SetEnabledCullingModule(culling::EveryCulling::CullingModuleType::_MaskedSWOcclusionCulling, Enable_MaskedSWOccslusionCulling);
		defaultGraphicsPipeLine->mRenderingCullingManager.mCullingSystem->SetEnabledCullingModule(culling::EveryCulling::CullingModuleType::_DistanceCulling, Enable_DistanceCulling);
		defaultGraphicsPipeLine->mRenderingCullingManager.mCullingSystem->SetEnabledCullingModule(culling::EveryCulling::CullingModuleType::_PreCulling, true);
	}
}

void dooms::PortfolioComponent::InitComponent()
{

	Base::InitComponent();
	
	dooms::graphics::graphicsSetting::IsSortObjectFrontToBack = true;
	dooms::graphics::graphicsSetting::IsDrawMaskedOcclusionCullingBinTriangleStageDebugger = See_MaskedSWOcclusionCulling_Occluder;
	dooms::graphics::graphicsSetting::IsDrawMaskedOcclusionCullingTileCoverageMaskDebugger = Is_Enabled_MaskedSWOcclusionCullingTileCoverageMaskDebugging;
	dooms::graphics::graphicsSetting::IsDrawMaskedOcclusionCullingTileL0MaxDepthValueDebugger = See_MaskedSWOcclusionCulling_DepthBuffer;
	dooms::graphics::graphicsSetting::IsDrawMaskedOcclusionCullingOcculderBoundingBoxDebugger = See_MaskedSWOcclusionCulling_OccluderBoudingBox;

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
