#pragma once

#include <Core.h>
#include "Buffer/UniformBufferObject/UniformBufferObjectUpdater.h"

#include <../Helper/Simple_SingleTon/Singleton.h>

#define LIGHT_DATA_CONSTANT_BUFFER_NAME "Global"

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
			virtual void UpdateUniformBufferObject(const bool force = false) override;

			FLOAT32 GetAmbientLightIntensity() const;
			void SetAmbientLightIntensity(const FLOAT32 intensity);
		};
	}
}
