#pragma once
#include "Light.h"
#include <StaticContainer/StaticContainer.h>
#include "Graphics/Buffer/UniformBufferObjectTempBufferUpdater.h"
namespace doom
{
	class DirectionalLight : public Light, public StaticContainer<DirectionalLight>, public graphics::UniformBufferObjectTempBufferUpdater
	{

	private:

		DirectionalLight(const DirectionalLight&) = delete;
		DirectionalLight(DirectionalLight&&) noexcept = delete;
		DirectionalLight& operator=(const DirectionalLight&) = delete;
		DirectionalLight& operator=(DirectionalLight&&) noexcept = delete;


		void InitComponent() final;
		void UpdateComponent() final;
		void OnEndOfFrame_Component() final;

	protected:


		void UpdateUniformBufferObjectTempBuffer(graphics::UniformBufferObjectManager& uboManager) override;

	public:
		DirectionalLight() = default;
		~DirectionalLight(){}

	};
}
