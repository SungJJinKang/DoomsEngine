#include "SceneGUI.h"

#include <Scene/Scene.h>
#include <Scene/Entity.h>

#include "../../imguiHelper/imguiWithReflection.h"


void dooms::ui::SceneGUI::Init()
{
}

void dooms::ui::SceneGUI::Render()
{
	const std::vector<dooms::Entity*>& entitiesInScene = Scene::GetSingleton()->GetEntitiesInScene();

	dooms::ui::imguiWithReflection::DrawMultipleDObjects("Entities in scene", entitiesInScene, currentEntityIndex);
}