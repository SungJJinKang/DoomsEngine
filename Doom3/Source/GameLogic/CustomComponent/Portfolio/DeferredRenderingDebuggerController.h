#pragma once


#include <Doom_Core.h>



namespace dooms
{
	namespace graphics
	{
		class PicktureInPickture;
	}


class DeferredRenderingDebuggerController : public PlainComponent
{
		DOBJECT_CLASS_BODY(DeferredRenderingDebuggerController)
		DOBJECT_CLASS_BASE_CHAIN(PlainComponent)

private:

	void InitDeferredRenderingDebuggerPIP();

public:

	std::array<dooms::graphics::PicktureInPickture*, 4> mDeferredRenderingDebuggerPIPs{ nullptr, nullptr, nullptr, nullptr };

	void InitComponent() override;



	void UpdateComponent() override;
	void OnEndOfFrame_Component() override;

};
}
