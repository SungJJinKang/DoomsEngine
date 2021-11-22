#include "ReflectionTestComponent.h"

#include <EngineGUI/imguiHelper/imguiWithReflection.h>

void dooms::ReflectionTestComponent::UpdateComponent()
{
	PlainComponent::UpdateComponent();

	GetOwnerEntity()->GetTransform()->mEngineGUIAccessor.SetIsVisibleOnGUI(true);

}
