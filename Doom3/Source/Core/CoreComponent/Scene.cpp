#include "Scene.h"

doom::Entity& doom::Scene::AddEntity()
{
	return this->mSpawnedEntities.emplace_back();
}
