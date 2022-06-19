#pragma once

#include "Core.h"

#include <vector>
#include <memory>

#include <Vector2.h>
#include "PicktureInPickture.h"
#include <Simple_SingleTon/Singleton.h>

#include "PIPManager.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class DOOM_API D_CLASS PIPManager : public plugin::EnginePlugin, public ISingleton<PIPManager>
		{
			GENERATE_BODY()
			
			

		private:

			D_PROPERTY()
			std::vector<PicktureInPickture*> mPicktureInPicktures;

		public:

			PIPManager();
			PIPManager(const PIPManager&) = delete;
			PIPManager& operator=(const PIPManager&) = delete;

			void DrawPIPs();

			PicktureInPickture* AddNewPIP(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, RenderingTextureViewProxy* const _drawedTexture);
			void RemovePIP(const PicktureInPickture* const removedPIP);

			size_t GetPIPCount() const;
		};
	}
}


