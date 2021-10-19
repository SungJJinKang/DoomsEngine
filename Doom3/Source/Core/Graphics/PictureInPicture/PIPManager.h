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

		class PIPManager : public DObject, public ISingleton<PIPManager>
		{

			DOBJECT_CLASS_BODY(PIPManager, doom::eDOBJECT_ClassFlags::NonCopyable);

		private:

			std::vector<std::unique_ptr<PicktureInPickture>> mPicktureInPicktures;

		public:

			PIPManager();

			void DrawPIPs();

			PicktureInPickture* AddNewPIP(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture);
			void RemovePIP(const PicktureInPickture* const removedPIP);

			SIZE_T GetPIPCount() const;
		};
	}
}


