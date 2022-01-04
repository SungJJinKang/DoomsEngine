#pragma once


#include <Doom_Core.h>

#include <array>

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

	D_PROPERTY()
	bool Enabled_DeferredRenderingDebugger = false;
	
	D_PROPERTY()
	bool Enabled_MultiThread_SortingFrontToBack = false;

	D_PROPERTY()
	bool OverdrawDebugger = false;

	D_PROPERTY()
	bool Is_Enabled_CollisionDebugging = false;

	D_PROPERTY()
	bool See_MaskedSWOcclusionCulling_Occluder = false;

	D_PROPERTY(INVISIBLE)
	bool Is_Enabled_MaskedSWOcclusionCullingTileCoverageMaskDebugging = false;
	
	D_PROPERTY()
	bool See_MaskedSWOcclusionCulling_DepthBuffer = false;


	D_PROPERTY()
	bool Enable_Multithread_SW_ViewFrustumCulling = true;

	D_PROPERTY()
	bool Enable_MaskedSWOccslusionCulling = true;

	void OnChangedByGUI(const dooms::reflection::DField& dFieldOfChangedField) override;

	void UpdateGUI();

public:
	
	void InitComponent() override;
	void LateInitComponent() override;
	void UpdateComponent() override;
	void OnEndOfFrame_Component() override;

};
}
