#pragma once
#include "Light.h"
#include <Misc/StaticContainer/StaticContainer.h>

#include "PointLight.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS PointLight : public Light, public StaticContainer<PointLight>
	{
		GENERATE_BODY()
		
		

	private:

		inline static UINT32 UniformBufferCounter = 0;

		void InitComponent() final;
		void UpdateComponent() final;
		void OnEndOfFrame_Component() final;

	protected:

		void OnActivated() override;
		void OnDeActivated() override;
		void UpdateUniformBufferObject(const bool force = false) override;
		virtual void OnDestroy() override;

	public:

		virtual ~PointLight();
	};
}
