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

	DOBJECT_BODY(PortfolioComponent)

private:


public:

	bool a, b, c, d, e;

	std::array<doom::graphics::PicktureInPickture*, 4> mDeferredRenderingDebuggerPIPs;

	void InitComponent() override;
	void UpdateComponent() override;
	void OnEndOfFrame_Component() override;

};
}
