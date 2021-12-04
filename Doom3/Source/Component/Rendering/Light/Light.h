#pragma once
#include "Core/Component.h"
#include <Vector4.h>
#include "EasyDirtyChecker/DirtyReceiver.h"
#include "Graphics/Buffer/UniformBufferObjectUpdater.h"
#include "Rendering/Renderer/RendererStaticIterator.h"

#include "Light.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS Light : public Component, public graphics::UniformBufferObjectUpdater, public StaticContainer<Light>
	{
		GENERATE_BODY()
		
		

	private:

		

	protected:

		D_PROPERTY(CALLBACK = "UpdateLight")
		FLOAT32 mIntensity{ 1 };

		D_PROPERTY(CALLBACK = "UpdateLight")
		FLOAT32 mIndirectMultiplier{ 1 };

		D_PROPERTY(Color, CALLBACK="UpdateLight")
		math::Vector4 mColor{ 1 };

		DirtyReceiver bmIsLightUboDirty{ true };
		
	
		
	public:

		Light() = default;
		Light(const Light&) = default;
		Light(Light&&) noexcept = delete;
		Light& operator=(const Light&) = delete;
		Light& operator=(Light&&) noexcept = delete;
		virtual ~Light();

		virtual void InitComponent() override;
		virtual void UpdateComponent() override;
		virtual void OnEndOfFrame_Component() override;
		virtual void OnDestroy() override;

		void SetIntensity(FLOAT32 intensity);
		void SetIndirectMultiplier(FLOAT32 indirectMultiplier);
		void SetColor(const math::Vector4& color);
		D_FUNCTION()
		void UpdateLight();
		FLOAT32 GetIntensity();
		FLOAT32 GetIndirectMultiplier();
		math::Vector4 GetColor();
		const math::Vector4& GetColor() const;
		math::Vector4 GetRadiance();
	};
}


