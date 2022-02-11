#pragma once

#include "GameLogicStartPoint.h"

#include <DoomsGameLogicCore.h>
#include "../Game/AssetManager/AssetManager.h"
#include "../Graphics/Material/Material.h"
#include <Rendering/Renderer/MeshRenderer.h>
#include <Rendering/Camera.h>
#include <Rendering/Light/DirectionalLight.h>
#include <Rendering/Light/PointLight.h>
#include "AutoRotate.h"
#include <TestComponent.h>
#include "CustomComponent/Portfolio/ViewFrustumCullingDebug.h"
#include "Graphics/LightManager.h"
#include "Graphics/Graphics_Setting.h"
#include <PerformanceTestController.h>

#include "Asset/ThreeDModelAsset.h"

void dooms::GameLogicStartPoint::StartGameLogic()
{
	ISingleton<graphics::LightManager>::GetSingleton()->SetAmbientLightIntensity(0.1f);
	dooms::graphics::Graphics_Setting::DefaultClearColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	auto currenScene = dooms::Scene::GetCurrentWorld();


	auto lightEntity = currenScene->CreateNewEntity();
	lightEntity->GetTransform()->SetRotation(-30.0f, 0.0f, 0.0f);
	auto dirLight = lightEntity->AddComponent<DirectionalLight>();
	dirLight->SetIntensity(3.0f);
	dirLight->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	//lightEntity->AddComponent<AutoRotate>();

	//auto& threedasset = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>(0);
	auto threedasset = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>("cerberus.assbin");
	auto shader = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("GbufferWriter_PBR.glsl");
	auto material = dooms::CreateDObject<graphics::Material>(shader);
	material->AddTexture(graphics::eTextureBindingPoint::AlbedoTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_A.dds"));
	material->AddTexture(graphics::eTextureBindingPoint::NormalTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_N.dds"));
	material->AddTexture(graphics::eTextureBindingPoint::MetalnessTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_M.dds"));
	material->AddTexture(graphics::eTextureBindingPoint::RoughnessTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_R.dds"));

	auto planetAsset = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>("planet.assbin");


	// 	for (INT32 i = 0; i < 25; i++)
	// 	{
	// 		for (INT32 j = 0; j < threedasset->GetMeshCount(); j++)
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

	INT32 entityCount = 0;

	INT32 count = 50;
	for (INT32 i = -count; i < count; i = i + 15)
	{
		for (INT32 j = -count; j < count; j = j + 15)
		{
			for (INT32 k = -count; k < count; k = k + 15)
			{
				auto entity = currenScene->CreateNewEntity();
				entity->GetTransform()->SetScale(1.5f, 1.5f, 1.5f);
				entity->GetTransform()->SetPosition(i, j, k);
				auto meshRenderer = entity->AddComponent<MeshRenderer>();
				meshRenderer->SetMesh(planetAsset->GetMesh(0));
				meshRenderer->SetMaterial(material);
				entityCount++;
				//entity->AddComponent<AutoRotate>();
				//entity->AddComponent<BoxCollider3D>();
			}
		}
	}



	for (INT32 i = -200; i < 200; i += 70)
	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetScale(10.0f, 10.0f, 10.0f);
		entity->GetTransform()->SetPosition(i, 0, 500);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		entity->AddComponent<AutoRotate>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);
	}

	for (INT32 i = -50; i < 50; i += 15)
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
	entity1Camera->SetProjectionMode(dooms::Camera::eProjectionType::Perspective);
	entity1->AddComponent<ViewFrustumCullingDebug>();
	entity1->AddComponent<PerformanceTestController>();



	entity1->GetTransform()->SetPosition(0.0f, 0.0f, 800.0f);
	//entity1->AddComponent<Move_WASD>();
	//entity1->AddComponent<CharacterSpawner>();
	//entity1->AddComponent<ButtonRotate>();
	dooms::graphics::Graphics_Setting::IsSortObjectFrontToBack = false;

	auto physicsEntity = currenScene->CreateNewEntity();
	entity1->AddComponent<TestComponent>();

	auto emptyEntity = currenScene->CreateNewEntity();


	auto entity3 = currenScene->CreateNewEntity();
	//entity3->AddComponent<ViewFrustumCullingDebug>();

	

}
