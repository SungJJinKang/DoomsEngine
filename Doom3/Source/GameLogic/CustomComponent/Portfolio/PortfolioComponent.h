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
	bool Is_Enabled_DeferredRenderingDebugger = false;
	
	D_PROPERTY()
	bool Is_Enabled_MultiThread_SortingFrontToBack = false;

	D_PROPERTY()
	bool Is_Enabled_OverdrawDebugger = false;

	D_PROPERTY()
	bool Is_Enabled_CollisionDebugging = false;

	D_PROPERTY()
	bool Is_Enabled_MaskedSWOcclusionCullingBinsStageDebugging = false;

	D_PROPERTY()
	bool Is_Enabled_MaskedSWOcclusionCullingTileCoverageMaskDebugging = false;
	
	D_PROPERTY()
	bool Is_Enabled_MaskedSWOcclusionCullingTileL0MaxDepthValueDebugging = false;


	D_PROPERTY()
	bool _EnableViewFrustumCulling = true;

	D_PROPERTY()
	bool _EnableMaskedSWOcclusionCulling = true;

	void OnChangedByGUI(const dooms::reflection::DField& dFieldOfChangedField) override;

	void UpdateGUI();

public:
	
	void InitComponent() override;
	void LateInitComponent() override;
	void UpdateComponent() override;
	void OnEndOfFrame_Component() override;

};
}
