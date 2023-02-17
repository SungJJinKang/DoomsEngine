#pragma once

#include <Core.h>
#include "GraphicsAPI.h"

namespace dooms
{
	namespace graphics
	{
		namespace graphicsAPIHelper
		{
			/*
			FORCE_INLINE math::eClipRange GetCurrentGraphicsAPIClipRange()
			{
				static const GraphicsAPI::eGraphicsAPIType currentAPIType = graphics::GraphicsAPI::GetCurrentAPIType();

				switch (currentAPIType)
				{
				case GraphicsAPI::eGraphicsAPIType::OpenGL: 
					return math::eClipRange::CLIP_RANGE_NEGATIVE_ONE_TO_ONE;
				case GraphicsAPI::eGraphicsAPIType::D3D11: 
					return math::eClipRange::CLIP_RANGE_NEGATIVE_ONE_TO_ONE;
				default:
					ASSUME_ZERO;
				}
			}

			FORCE_INLINE math::eCoordinateSystem GetCurrentGraphicsAPICoordinateSystem()
			{
				static const GraphicsAPI::eGraphicsAPIType currentAPIType = graphics::GraphicsAPI::GetCurrentAPIType();

				switch (currentAPIType)
				{
				case GraphicsAPI::eGraphicsAPIType::OpenGL:
					return math::eCoordinateSystem::RIGHT_HAND;
				case GraphicsAPI::eGraphicsAPIType::D3D11:
					return math::eCoordinateSystem::RIGHT_HAND;
					//return math::eCoordinateSystem::LEFT_HAND;
				default:
					ASSUME_ZERO;
				}
			}
			*/
		}
	}
}

