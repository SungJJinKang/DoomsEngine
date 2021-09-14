#pragma once
#include "Light.h"
#include <StaticContainer/StaticContainer.h>
#include "Graphics/Buffer/UniformBufferObjectUpdater.h"
namespace doom
{
	class DirectionalLight : public Light, public StaticContainer<DirectionalLight>, public graphics::UniformBufferObjectUpdater
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


		void UpdateUniformBufferObject() override;

	public:
		DirectionalLight() = default;
		~DirectionalLight(){}

	};
}
