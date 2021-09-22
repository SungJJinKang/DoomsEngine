#pragma once

#include "Core.h"

#include <vector>
#include <memory>

#include <Vector2.h>
#include "PicktureInPickture.h"

namespace doom
{
	namespace graphics
	{
		class SingleTexture;

		class PIPManager : public ISingleton<PIPManager>
		{

		private:

			std::vector<std::unique_ptr<PicktureInPickture>> mPicktureInPicktures;

		public:

			PIPManager();

			void DrawPIPs();

			PicktureInPickture* AddNewPIP(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture);
			void RemovePIP(const PicktureInPickture* const removedPIP);

			size_t GetPIPCount() const;
		};
	}
}


