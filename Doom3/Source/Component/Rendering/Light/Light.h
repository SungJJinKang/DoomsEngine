#pragma once
#include "Core/ServerComponent.h"
#include "Vector4.h"
#include "EasyDirtyChecker/DirtyReceiver.h"

namespace doom
{
	class DOOM_API Light : public ServerComponent
	{

		DOBJECT_ABSTRACT_CLASS_BODY(Light)
		DOBJECT_CLASS_BASE_CHAIN(ServerComponent)

	private:

		

	protected:

		FLOAT32 mIntensity{ 1 };
		FLOAT32 mIndirectMultiplier{ 1 };
		math::Vector4 mColor{ 1 };

		DirtyReceiver bmIsLightUboDirty{ true };


		Light(const Light&) = default;
		Light(Light&&) noexcept = delete;
		Light& operator=(const Light&) = delete;
		Light& operator=(Light&&) noexcept = delete;


		virtual void InitComponent() override;
		virtual void UpdateComponent() override;
		virtual void OnEndOfFrame_Component() override;
		
	public:
		Light() = default;
		virtual ~Light();

		void SetIntensity(FLOAT32 intensity);
		void SetIndirectMultiplier(FLOAT32 indirectMultiplier);
		void SetColor(const math::Vector4& color);
		FLOAT32 GetIntensity();
		FLOAT32 GetIndirectMultiplier();
		math::Vector4 GetColor();
		const math::Vector4& GetColor() const;
		math::Vector4 GetRadiance();
	};
}


