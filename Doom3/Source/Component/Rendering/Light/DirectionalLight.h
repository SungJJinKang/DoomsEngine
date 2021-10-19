#pragma once
#include "Light.h"
#include <StaticContainer/StaticContainer.h>
#include "Graphics/Buffer/UniformBufferObjectUpdater.h"
namespace doom
{
	class DOOM_API DirectionalLight : public Light, public StaticContainer<DirectionalLight>, public graphics::UniformBufferObjectUpdater
	{

		DOBJECT_CLASS_BODY(DirectionalLight)

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
