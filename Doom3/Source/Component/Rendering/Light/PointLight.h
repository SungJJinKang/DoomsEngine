#pragma once
#include "Light.h"
#include <StaticContainer/StaticContainer.h>
#include "Graphics/Buffer/UniformBufferObjectUpdater.h"

#include "PointLight.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS PointLight : public Light, public StaticContainer<PointLight>, public graphics::UniformBufferObjectUpdater
	{
		GENERATE_BODY()
		
		

	private:

		void InitComponent() final;
		void UpdateComponent() final;
		void OnEndOfFrame_Component() final;

	protected:


		void UpdateUniformBufferObject() override;

	public:

		virtual ~PointLight();
	};
}
