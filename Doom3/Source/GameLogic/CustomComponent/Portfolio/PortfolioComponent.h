#pragma once


#include <Doom_Core.h>

#include <array>

namespace doom
{
	namespace graphics
	{
		class PicktureInPickture;
	}

class PortfolioComponent : public PlainComponent
{

private:


public:

	std::array<doom::graphics::PicktureInPickture*, 4> mDeferredRenderingDebuggerPIPs;

	void InitComponent() override;
	void UpdateComponent() override;
	void OnEndOfFrame_Component() override;

};
}
