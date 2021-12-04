#pragma once


#include <Doom_Core.h>


#include "DeferredRenderingDebuggerController.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class PicktureInPickture;
	}


class DOOM_API D_CLASS DeferredRenderingDebuggerController : public Component
{
	GENERATE_BODY()
		

private:

	void InitDeferredRenderingDebuggerPIP();

public:

	std::array<dooms::graphics::PicktureInPickture*, 4> mDeferredRenderingDebuggerPIPs{ nullptr, nullptr, nullptr, nullptr };

	void InitComponent() override;



	void UpdateComponent() override;
	void OnEndOfFrame_Component() override;

	void SetPIPVisible(bool isVisible);

};
}
