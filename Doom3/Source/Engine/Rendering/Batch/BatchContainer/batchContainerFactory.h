#pragma once

#include "../eBatchRenderingType.h"

namespace dooms
{
	namespace graphics
	{
		class RendererBatchContainer;
		class Material;
		namespace batchContainerFactory
		{
			RendererBatchContainer* CreateRendererBatchContainer
			(
				Material* const targetMaterial,
				const eBatchRenderingType batchRenderingType
			);
		}
	}
}

