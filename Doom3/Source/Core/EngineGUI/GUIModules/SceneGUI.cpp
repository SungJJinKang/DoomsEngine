#include "SceneGUI.h"

#include <Scene/Scene.h>
#include <Scene/Entity.h>

#include "../imguiHelper/imguiWithReflection.h"

namespace dooms
{
	namespace ui
	{
		namespace sceneGUI
		{
			static size_t currentEntityIndex;
		}
	}
}

void dooms::ui::sceneGUI::Render()
{
	const std::vector<dooms::Entity*>& entitiesInScene = Scene::GetSingleton()->GetEntitiesInScene();

	dooms::ui::imguiWithReflection::DrawMultipleDObjects("Entities in scene", entitiesInScene, currentEntityIndex);
}
