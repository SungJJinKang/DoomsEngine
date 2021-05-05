#include "TEST.h"

#include <Doom_Core.h>
#include "../Game/AssetManager/AssetManager.h"
#include "../Graphics/Material.h"
#include <Rendering/Renderer/MeshRenderer.h>
#include <Rendering/Camera.h>
#include "UserInput_Server.h"
#include "Move_WASD.h"
#include <Rendering/Light/DirectionalLight.h>
#include "AutoRotate.h"
#include <TestComponent.h>
#include "PhysicsComponent/BoxCollider3D.h"
#include "CustomComponent/CharacterSpawner.h"

void doom::TEST::Init()
{
	auto currenScene = doom::Scene::GetCurrentWorld();


	auto lightEntity = currenScene->CreateNewEntity();
	auto dirLight = lightEntity->AddComponent<DirectionalLight>();
	dirLight->SetIntensity(5);
	lightEntity->AddComponent<AutoRotate>();

	//auto& threedasset = assetimporter::AssetManager::GetAsset<asset::eAssetType::THREE_D_MODEL>(0);
	auto threedasset = assetimporter::AssetManager::GetAsset<asset::eAssetType::THREE_D_MODEL>("cerberus.assbin");
	auto shader = assetimporter::AssetManager::GetAsset<asset::eAssetType::SHADER>("GbufferWriter_PBR.glsl");
	auto material = new graphics::Material(shader);
	material->AddTexture(graphics::eTextureBindingPoint::AlbedoTexture, assetimporter::AssetManager::GetAsset<asset::eAssetType::TEXTURE>("cerberus_A.dds"));
	material->AddTexture(graphics::eTextureBindingPoint::NormalTexture, assetimporter::AssetManager::GetAsset<asset::eAssetType::TEXTURE>("cerberus_N.dds"));
	material->AddTexture(graphics::eTextureBindingPoint::MetalnessTexture, assetimporter::AssetManager::GetAsset<asset::eAssetType::TEXTURE>("cerberus_M.dds"));
	material->AddTexture(graphics::eTextureBindingPoint::RoughnessTexture, assetimporter::AssetManager::GetAsset<asset::eAssetType::TEXTURE>("cerberus_R.dds"));

	auto planetAsset = assetimporter::AssetManager::GetAsset<asset::eAssetType::THREE_D_MODEL>("planet.assbin");

	
// 	for (int i = 0; i < 25; i++)
// 	{
// 		for (int j = 0; j < threedasset->GetMeshCount(); j++)
// 		{
// 			auto entity = currenScene->CreateNewEntity();
// 			entity->GetTransform()->SetScale(0.1f, 0.1f, 0.1f);
// 			entity->GetTransform()->SetPosition(Random::RandomFloatNumber(-20, 20), Random::RandomFloatNumber(-20, 20), Random::RandomFloatNumber(-20, 20));
// 			auto meshRenderer = entity->AddComponent<MeshRenderer>();
// 			meshRenderer->SetMesh(threedasset->GetMesh(j));
// 			meshRenderer->SetMaterial(material);
// 			entity->AddComponent<AutoRotate>();
// 			entity->AddComponent<BoxCollider3D>();
// 		}
// 	}
	int count = 330;
	for (int i = -count; i < count; i = i + 15)
	{
		for (int j = -count; j < count; j = j + 15)
		{
			for (int k = -count; k < count; k = k + 15)
			{
				auto entity = currenScene->CreateNewEntity();
				entity->GetTransform()->SetScale(1.5f, 1.5f, 1.5f);
				entity->GetTransform()->SetPosition(i, j, k);
				auto meshRenderer = entity->AddComponent<MeshRenderer>();
				meshRenderer->SetMesh(planetAsset->GetMesh(0));
				meshRenderer->SetMaterial(material);
				//entity->AddComponent<AutoRotate>();
				//entity->AddComponent<BoxCollider3D>();
			}
		}
	}

	for(int i = -50 ; i < 50;  i += 15)
	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetScale(1.5f, 1.5f, 1.5f);
		entity->GetTransform()->SetPosition(i, 0, 500);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		entity->AddComponent<AutoRotate>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);
	}

	for (int i = -50; i < 50; i += 15)
	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetScale(1.5f, 1.5f, 1.5f);
		entity->GetTransform()->SetPosition(i, 0, 700);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		entity->AddComponent<AutoRotate>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);
	}

	auto entity1 = currenScene->CreateNewEntity();
	auto entity1Camera = entity1->AddComponent<Camera>();
	entity1Camera->SetProjectionMode(doom::Camera::eProjectionType::Perspective);
	entity1->GetTransform()->SetPosition(0.0f, 0.0f, 600.0f);
	entity1->AddComponent<Move_WASD>();
	entity1->AddComponent<CharacterSpawner>();


	auto physicsEntity = currenScene->CreateNewEntity();
	entity1->AddComponent<TestComponent>();

	auto emptyEntity = currenScene->CreateNewEntity();

	
	auto entity2 = currenScene->CreateNewEntity();
	entity2->GetTransform()->SetPosition(2.0f, 1.0f, -1.0f);
	auto entity2BoxCollider3D = entity2->AddComponent<BoxCollider3D>();
	entity2BoxCollider3D->SetHalfExtent(math::Vector3(1.0f, 2.0f, 3.0f));
	entity2->AddComponent<AutoRotate>();
	
}