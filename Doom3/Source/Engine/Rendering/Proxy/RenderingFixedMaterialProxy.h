#pragma once
#include <Core.h>

#include "RenderingProxy.h"

namespace dooms
{
	namespace graphics
	{
		class RenderingMaterialProxy;

		class RenderingFixedMaterialProxy : public RenderingProxy
		{

		public:

			static bool IsExistFixedMaterialProxy();
			static const RenderingMaterialProxy* GetFixedMaterialProxy();
			static void SetFixedMaterial(RenderingMaterialProxy* const InFixedRenderingMaterialProxy);
			static void ClearFixedMaterialProxy();

		private:

			static RenderingMaterialProxy* FixedRenderingMaterialProxy;

		};
	}
}