#pragma once
#include "Light.h"
#include <StaticContainer/StaticContainer.h>

#include "DirectionalLight.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS DirectionalLight : public Light
	{
		GENERATE_BODY()
		
		

	private:
		
		inline static UINT32 UniformBufferCounter = 0;

		void InitComponent() final;
		void UpdateComponent() final;
		void OnEndOfFrame_Component() final;

	protected:


		void UpdateUniformBufferObject() override;
		virtual void OnDestroy() override;

	public:
		DirectionalLight() = default;
		~DirectionalLight();
		DirectionalLight(const DirectionalLight&) = default;
		DirectionalLight(DirectionalLight&&) noexcept = delete;
		DirectionalLight& operator=(const DirectionalLight&) = delete;
		DirectionalLight& operator=(DirectionalLight&&) noexcept = delete;


	};
}
