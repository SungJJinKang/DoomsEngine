#pragma once

#include <Entity.h>
#include <Scene.h>
#include <Camera.h>
#include <MeshRenderer.h>


namespace doom
{
	class TEST
	{
	public:

		static void Init()
		{
			auto currenScene = doom::Scene::GetCurrentWorld();
			auto entity1 = currenScene->CreateNewEntity();
			auto entity1Camera = entity1->AddComponent<Camera>();

			auto entity2 = currenScene->CreateNewEntity();
			auto meshRenderer = entity2->AddComponent<MeshRenderer>();
		}
	};
}


