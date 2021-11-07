#pragma once

#include <Core.h>
#include "Buffer/UniformBufferObjectUpdater.h"

namespace dooms
{
	namespace graphics
	{
		class DOOM_API LightManager : public DObject, public ISingleton<LightManager>, public graphics::UniformBufferObjectUpdater
		{

			DOBJECT_CLASS_BODY(LightManager);
			DOBJECT_CLASS_BASE_CHAIN(DObject)

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
