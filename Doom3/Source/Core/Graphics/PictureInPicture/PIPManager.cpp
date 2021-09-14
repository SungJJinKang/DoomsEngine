#include "PIPManager.h"

#include "PicktureInPickture.h"

#include <algorithm>
#include <vector_erase_move_lastelement/vector_swap_popback.h>

doom::graphics::PIPManager::PIPManager()
	: mPicktureInPicktures()
{
}

void doom::graphics::PIPManager::DrawPIPs()
{
	for (std::unique_ptr<PicktureInPickture>& pip : mPicktureInPicktures)
	{
		pip->DrawPictureInPicture();
	}
}

doom::graphics::PicktureInPickture* doom::graphics::PIPManager::AddNewPIP(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture)
{
	std::unique_ptr<PicktureInPickture>& newPIP = mPicktureInPicktures.emplace_back(std::make_unique< doom::graphics::PicktureInPickture>(leftBottomNDCPoint, rightTopNDCPoint, _drawedTexture));
	return newPIP.get();
}

void doom::graphics::PIPManager::RemovePIP(const PicktureInPickture* const removedPIP)
{
	std::vector_find_if_swap_popback(mPicktureInPicktures, [removedPIP](const std::unique_ptr<PicktureInPickture>& pip) -> bool
		{
			return pip.get() == removedPIP;
		});
}