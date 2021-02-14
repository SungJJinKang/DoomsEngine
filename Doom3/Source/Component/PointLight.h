#pragma once
#include "Light.h"
#include "Iterator/ComponentStaticIterater.h"
#include "Graphics/Buffer/UniformBufferObjectTempBufferUpdater.h"

namespace doom
{
	class PointLight : public Light, public ComponentStaticIterater<PointLight>, public graphics::UniformBufferObjectTempBufferUpdater
	{

	private:

		void InitComponent() final;
		void UpdateComponent() final;
		void OnEndOfFrame_Component() final;

	protected:


		void UpdateUniformBufferObjectTempBuffer(graphics::UniformBufferObjectManager& uboManager) override;

	public:

		virtual ~PointLight() {}
	};
}
