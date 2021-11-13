#pragma once
#include "Core/PlainComponent.h"

#include "EventSystem.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS EventSystem : public PlainComponent
	{
		GENERATE_BODY()
		

	private:

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
		virtual ~EventSystem();
		EventSystem(const EventSystem&) = default;

		//CLONE_DOBJECT(EventSystem)
		
	};
}
