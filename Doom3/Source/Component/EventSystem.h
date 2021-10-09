#pragma once
#include "Core/PlainComponent.h"

namespace doom
{
	class DOOM_API EventSystem : public PlainComponent
	{
	private:

		EventSystem(const EventSystem&) = delete;
		EventSystem(EventSystem&&) noexcept = delete;
		EventSystem& operator=(const EventSystem&) = delete;
		EventSystem& operator=(EventSystem&&) noexcept = delete;

		virtual void InitComponent() override;
		virtual void FixedUpdateComponent() override;
		virtual void UpdateComponent() override;
		virtual void OnEndOfFrame_Component() override;

	protected:



	public:
		EventSystem() = default;
		virtual ~EventSystem() {}

	};
}
