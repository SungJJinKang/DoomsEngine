#pragma once
#include "Light.h"
#include <StaticContainer/StaticContainer.h>
#include "Graphics/Buffer/UniformBufferObjectUpdater.h"

namespace doom
{
	class DOOM_API PointLight : public Light, public StaticContainer<PointLight>, public graphics::UniformBufferObjectUpdater
	{

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
