#pragma once
#include "Core/PlainComponent.h"
#include "Vector4.h"

namespace doom
{
	class Light : public PlainComponent
	{
	private:

		Light(const Light&) = delete;
		Light(Light&&) noexcept = delete;
		Light& operator=(const Light&) = delete;
		Light& operator=(Light&&) noexcept = delete;

		virtual void InitComponent();
		virtual void UpdateComponent();
		virtual void OnEndOfFrame_Component();

	protected:

		float mIntensity{ 1 };
		float mIndirectMultiplier{ 1 };
		math::Vector4 mColor{ 1 };

		DirtyReceiver mLightDirtyReceiver{};
		LocalDirty bmIsLightUboDirty{ true };
		
	public:
		Light() = default;
		virtual ~Light(){}

		void SetIntensity(float intensity);
		void SetIndirectMultiplier(float indirectMultiplier);
		void SetColor(const math::Vector4& color);
		float GetIntensity();
		float GetIndirectMultiplier();
		math::Vector4 GetColor();
		const math::Vector4& GetColor() const;
		math::Vector4 GetRadiance();
	};
}


