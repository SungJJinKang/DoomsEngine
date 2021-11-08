#pragma once

#include "Core.h"

#include <vector>
#include <memory>

#include <Vector2.h>
#include "PicktureInPickture.h"

namespace dooms
{
	namespace graphics
	{
		class SingleTexture;

		class DOOM_API D_CLASS PIPManager : public DObject, public ISingleton<PIPManager>
		{

			DOBJECT_CLASS_BODY(PIPManager, dooms::eDOBJECT_ClassFlags::NonCopyable);
			DOBJECT_CLASS_BASE_CHAIN(DObject)

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


