#pragma once

#include <Core.h>
#include "Buffer/UniformBufferObjectUpdater.h"

#include "LightManager.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class DOOM_API D_CLASS LightManager : public DObject, public ISingleton<LightManager>, public graphics::UniformBufferObjectUpdater
		{
			GENERATE_BODY()
			
			
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
