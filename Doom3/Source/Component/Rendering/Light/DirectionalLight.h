#pragma once
#include "Light.h"
#include <StaticContainer/StaticContainer.h>
#include "Graphics/Buffer/UniformBufferObjectUpdater.h"
namespace dooms
{
	class DOOM_API D_CLASS DirectionalLight : public Light, public StaticContainer<DirectionalLight>, public graphics::UniformBufferObjectUpdater
	{

		DOBJECT_CLASS_BODY(DirectionalLight)
		DOBJECT_CLASS_BASE_CHAIN(Light)

	private:



		void InitComponent() final;
		void UpdateComponent() final;
		void OnEndOfFrame_Component() final;

	protected:


		void UpdateUniformBufferObject() override;

	public:
		DirectionalLight() = default;
		~DirectionalLight();
		DirectionalLight(const DirectionalLight&) = default;
		DirectionalLight(DirectionalLight&&) noexcept = delete;
		DirectionalLight& operator=(const DirectionalLight&) = delete;
		DirectionalLight& operator=(DirectionalLight&&) noexcept = delete;


	};
}
