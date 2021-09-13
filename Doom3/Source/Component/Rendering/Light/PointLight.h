#pragma once
#include "Light.h"
#include <StaticContainer/StaticContainer.h>
#include "Graphics/Buffer/UniformBufferObjectTempBufferUpdater.h"

namespace doom
{
	class PointLight : public Light, public StaticContainer<PointLight>, public graphics::UniformBufferObjectTempBufferUpdater
	{

	private:

		void InitComponent() final;
		void UpdateComponent() final;
		void OnEndOfFrame_Component() final;

	protected:


		void UpdateUniformBufferObjectTempBuffer() override;

	public:

		virtual ~PointLight() {}
	};
}
