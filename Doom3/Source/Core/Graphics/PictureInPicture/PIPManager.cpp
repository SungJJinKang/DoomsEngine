#include "PIPManager.h"

#include "PicktureInPickture.h"

#include <vector_erase_move_lastelement/vector_swap_popback.h>

dooms::graphics::PIPManager::PIPManager()
	: mPicktureInPicktures()
{
	AddToRootObjectList();
}

void dooms::graphics::PIPManager::DrawPIPs()
{
	if (GetPIPCount() > 0)
	{
		D_START_PROFILING(DrawPIPs, dooms::profiler::eProfileLayers::Rendering);
		for (PicktureInPickture* pip : mPicktureInPicktures)
		{
			//D_ASSERT(IsValid(pip));
			pip->DrawPictureInPicture();
		}
		D_END_PROFILING(DrawPIPs);
	}	
}

dooms::graphics::PicktureInPickture* dooms::graphics::PIPManager::AddNewPIP(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, TextureView* const _drawedTexture)
{
	dooms::graphics::PicktureInPickture* pip = nullptr;

	if(_drawedTexture != nullptr)
	{
		pip = mPicktureInPicktures.emplace_back(dooms::CreateDObject<dooms::graphics::PicktureInPickture>(leftBottomNDCPoint, rightTopNDCPoint, _drawedTexture));
		D_ASSERT(IsValid(pip));
	}

	D_ASSERT(pip != nullptr);
	return pip;
}

void dooms::graphics::PIPManager::RemovePIP(const PicktureInPickture* const removedPIP)
{
	swap_popback::vector_find_if_swap_popback(mPicktureInPicktures, [removedPIP](const PicktureInPickture* pip) -> bool
		{
			return pip == removedPIP;
		});
}

size_t dooms::graphics::PIPManager::GetPIPCount() const
{
	return mPicktureInPicktures.size();
}
