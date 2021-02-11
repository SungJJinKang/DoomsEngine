#include "TEST.h"

#include <Entity.h>
#include <Scene.h>
#include <Camera.h>
#include <MeshRenderer.h>
#include "../Game/AssetManager.h"

void doom::TEST::Init()
{
	auto currenScene = doom::Scene::GetCurrentWorld();



	//TODO : Asset 가져오는 것만 해도 존나 복잡하다 이거 해결하다
	auto& threedasset = assetimporter::AssetManager::GetAsset<eAssetType::THREE_D_MODEL>(0).value().get();
	auto& shader = assetimporter::AssetManager::GetAsset<eAssetType::SHADER>(0).value().get();
	auto material = new graphics::Material(shader);
	for (int i = 0; i < threedasset.GetMeshCount(); i++)
	{
		auto entity = currenScene->CreateNewEntity();
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(threedasset.GetMesh(i));
		meshRenderer->SetMaterial(material);
	}





	auto entity1 = currenScene->CreateNewEntity();
	auto entity1Camera = entity1->AddComponent<Camera>();
	entity1->GetTransform()->SetPosition(0.0f, 0.0f, 1.0f);
	//meshRenderer->
}