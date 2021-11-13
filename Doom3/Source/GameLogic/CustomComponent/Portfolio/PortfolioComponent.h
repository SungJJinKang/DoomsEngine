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

class DOOM_API D_CLASS PortfolioComponent : public PlainComponent
{
	GENERATE_BODY()
	
	

private:


public:

	bool a, b, c, d, e;

	std::array<dooms::graphics::PicktureInPickture*, 4> mDeferredRenderingDebuggerPIPs;

	void InitComponent() override;
	void UpdateComponent() override;
	void OnEndOfFrame_Component() override;

};
}
