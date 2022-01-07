#pragma once


#include <Doom_Core.h>

#include <array>

#include <Rendering/Renderer/Renderer.h>

#include "PortfolioComponent.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class PicktureInPickture;
	}

class DOOM_API D_CLASS PortfolioComponent : public Component
{
	GENERATE_BODY()
	
	

private:

	D_PROPERTY(TOOLTIP="Enable DeferredRendering Debugger")
	bool Enabled_DeferredRenderingDebugger = false;
	
	D_PROPERTY(TOOLTIP="Enable MultiThread Sorting Front to Back")
	bool Enabled_MultiThread_SortingFrontToBack = false;

	D_PROPERTY(TOOLTIP="Enable Overdraw Debugger")
	bool OverdrawDebugger = false;

	D_PROPERTY(INVISIBLE)
	bool Is_Enabled_CollisionDebugging = false;

	D_PROPERTY(TOOLTIP="See Selected Occluders of Masked SW Occlusion Culling")
	bool See_MaskedSWOcclusionCulling_Occluder = false;

	D_PROPERTY(INVISIBLE)
	bool Is_Enabled_MaskedSWOcclusionCullingTileCoverageMaskDebugging = false;
	
	D_PROPERTY(TOOLTIP="See DepthBuffer of Masked SW Occlusion Culling")
	bool See_MaskedSWOcclusionCulling_DepthBuffer = false;


	D_PROPERTY(TOOLTIP = "Enable Multithreaded CPU View Frustum Culling")
	bool Enable_Multithread_SW_ViewFrustumCulling = true;

	D_PROPERTY(TOOLTIP="Enable Masked SW(CPU) Occlusion Culling")
	bool Enable_MaskedSWOccslusionCulling = true;

	D_PROPERTY(TOOLTIP = "Enable Distance Culling")
	bool Enable_DistanceCulling = true;

	D_PROPERTY(MIN=0.0, TOOLTIP ="Set DesiredMaxDrawDistance to All Rocks's Renderer ( Test )")
	float AllRocksDesiredMaxDrawDistance = 3000.0f;
	D_PROPERTY(MIN=0.0, TOOLTIP = "Set DesiredMaxDrawDistance to All Planes's Renderer ( Test )")
	float AllPlanesDesiredMaxDrawDistance = 3000.0f;

	void OnChangedByGUI(const dooms::reflection::DField& dFieldOfChangedField) override;

	void UpdateGUI();

public:

	std::vector<dooms::Renderer*> RockRenderers;
	std::vector<dooms::Renderer*> PlanesRenderers;

	void InitComponent() override;
	void LateInitComponent() override;
	void UpdateComponent() override;
	void OnEndOfFrame_Component() override;

};
}
