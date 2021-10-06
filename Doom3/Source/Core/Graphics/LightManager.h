#pragma once

#include <Core.h>
#include "Buffer/UniformBufferObjectUpdater.h"

namespace doom
{
	namespace graphics
	{
		class LightManager : public DObject, public ISingleton<LightManager>, public graphics::UniformBufferObjectUpdater
		{

		private:

			bool bmIsAmbientLightIntensityDirty = true;
			float mAmbientLightIntensity = 0.1f;

		public:

			// Inherited via UniformBufferObjectUpdater
			virtual void UpdateUniformBufferObject() override;

			float GetAmbientLightIntensity() const;
			void SetAmbientLightIntensity(const float intensity);
		};
	}
}
