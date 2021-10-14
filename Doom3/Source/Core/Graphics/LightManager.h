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
			FLOAT32 mAmbientLightIntensity = 0.1f;

		public:

			// Inherited via UniformBufferObjectUpdater
			virtual void UpdateUniformBufferObject() override;

			FLOAT32 GetAmbientLightIntensity() const;
			void SetAmbientLightIntensity(const FLOAT32 intensity);
		};
	}
}
