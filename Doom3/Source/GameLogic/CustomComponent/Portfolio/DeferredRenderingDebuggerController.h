#pragma once



#include <memory>

#include <Doom_Core.h>



namespace doom
{
	namespace graphics
	{
		class PicktureInPickture;
	}


class DeferredRenderingDebuggerController : public PlainComponent
{
private:

	void InitDeferredRenderingDebuggerPIP();

public:

	std::array<doom::graphics::PicktureInPickture*, 4> mDeferredRenderingDebuggerPIPs{ nullptr, nullptr, nullptr, nullptr };

	void InitComponent() override;



	void UpdateComponent() override;
	void OnEndOfFrame_Component() override;

};
}