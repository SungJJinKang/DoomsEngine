#pragma once
#include "Core/PlainComponent.h"
#include "Vector4.h"
#include "EasyDirtyChecker/DirtyReceiver.h"

namespace doom
{
	class DOOM_API Light : public PlainComponent
	{
	private:

		Light(const Light&) = delete;
		Light(Light&&) noexcept = delete;
		Light& operator=(const Light&) = delete;
		Light& operator=(Light&&) noexcept = delete;

	

	protected:

		FLOAT32 mIntensity{ 1 };
		FLOAT32 mIndirectMultiplier{ 1 };
		math::Vector4 mColor{ 1 };

		DirtyReceiver bmIsLightUboDirty{ true };

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


