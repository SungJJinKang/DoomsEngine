#pragma once
#include "Core/PlainComponent.h"

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
		Light() {}
		virtual ~Light() {}
	};
}


