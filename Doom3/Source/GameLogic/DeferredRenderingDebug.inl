#pragma once

#include "GameLogicStartPoint.h"

#include <Doom_Core.h>
#include "../Game/AssetManager/AssetManager.h"
#include "../Graphics/Material/Material.h"
#include <Rendering/Renderer/MeshRenderer.h>
#include <Rendering/Camera.h>
#include "UserInput_Server.h"
#include "Move_WASD.h"
#include <Rendering/Light/DirectionalLight.h>
#include <Rendering/Light/PointLight.h>
#include "AutoRotate.h"
#include <TestComponent.h>
#include "PhysicsComponent/BoxCollider3D.h"
#include "CustomComponent/CharacterSpawner.h"
#include "CustomComponent/ButtonRotate.h"
#include "Graphics/PictureInPicture/PIPManager.h"
#include "AutoRotateAround.h"
#include "Graphics/LightManager.h"
#include "Graphics/Graphics_Setting.h"
#include "Portfolio/RenderingAABBController.h"

void doom::GameLogicStartPoint::StartGameLogic()
{
	ISingleton<graphics::LightManager>::GetSingleton()->SetAmbientLightIntensity(0.1f);
	doom::graphics::Graphics_Setting::DefaultClearColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	auto currenScene = doom::Scene::GetCurrentWorld();


	auto lightEntity = currenScene->CreateNewEntity();
	lightEntity->GetTransform()->SetRotation(-30.0f, 0.0f, 0.0f);
	auto dirLight = lightEntity->AddComponent<DirectionalLight>();
	dirLight->SetIntensity(3.0f);
	dirLight->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	//lightEntity->AddComponent<AutoRotate>();

	//auto& threedasset = assetimporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>(0);
	auto threedasset = assetimporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>("cerberus.assbin");
	auto shader = assetimporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("GbufferWriter_PBR.glsl");
	auto material = doom::CreateDObject<graphics::Material>(shader);
	material->AddTexture(graphics::eTextureBindingPoint::AlbedoTexture, assetimporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_A.dds"));
	material->AddTexture(graphics::eTextureBindingPoint::NormalTexture, assetimporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_N.dds"));
	material->AddTexture(graphics::eTextureBindingPoint::MetalnessTexture, assetimporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_M.dds"));
	material->AddTexture(graphics::eTextureBindingPoint::RoughnessTexture, assetimporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_R.dds"));

	auto planetAsset = assetimporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>("planet.assbin");


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
	int count = 80;
	for (int i = -count; i < count; i = i + 15)
	{
		for (int j = -count; j < count; j = j + 15)
		{
			for (int k = -count; k < count; k = k + 15)
			{
				auto entity = currenScene->CreateNewEntity();
				entity->GetTransform()->SetScale(1.2f, 1.2f, 1.2f);
				entity->GetTransform()->SetPosition(i, j, k);
				auto meshRenderer = entity->AddComponent<MeshRenderer>();
				meshRenderer->SetMesh(planetAsset->GetMesh(0));
				meshRenderer->SetMaterial(material);
				//entity->AddComponent<AutoRotate>();
				//entity->AddComponent<BoxCollider3D>();
			}
		}
	}

	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetPosition(150.0f, 0.0f, 0.0f);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);
		PointLight* pointLight = entity->AddComponent<PointLight>();
		AutoRotateAround* autoRotateAround = entity->AddComponent<AutoRotateAround>();
		pointLight->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		pointLight->SetIntensity(9500.0f);
		autoRotateAround->mCenterPos = math::Vector3{ 0.0f, 0.0f, 0.0f };
		autoRotateAround->mRotateAngle = 1;
		autoRotateAround->mRotateAxis = { 0.0f, 1.0f, 0.0f };
	}

	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetPosition(0.0f, 150.0f, 0.0f);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);
		PointLight* pointLight = entity->AddComponent<PointLight>();
		AutoRotateAround* autoRotateAround = entity->AddComponent<AutoRotateAround>();
		pointLight->SetColor({ 0.0f, 1.0f, 0.0f, 1.0f });
		pointLight->SetIntensity(9500.0f);
		autoRotateAround->mCenterPos = math::Vector3{ 0.0f, 0.0f, 0.0f };
		autoRotateAround->mRotateAngle = 1;
		autoRotateAround->mRotateAxis = { 1.0f, 0.0f, 0.0f };
	}


	for (int i = -50; i < 50; i += 15)
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
	entity1->AddComponent<RenderingAABBController>();
	entity1Camera->SetProjectionMode(doom::Camera::eProjectionType::Perspective);

	doom::graphics::PIPManager::GetSingleton()->AddNewPIP({ -1.0f, -1.0f }, { -0.6f, -0.6f }, entity1Camera->mDefferedRenderingFrameBuffer.GetFrameBufferTexture(doom::graphics::GraphicsAPI::eBufferBitType::COLOR, 0));
	doom::graphics::PIPManager::GetSingleton()->AddNewPIP({ -0.6f, -1.0f }, { -0.2f, -0.6f }, entity1Camera->mDefferedRenderingFrameBuffer.GetFrameBufferTexture(doom::graphics::GraphicsAPI::eBufferBitType::COLOR, 1));
	doom::graphics::PIPManager::GetSingleton()->AddNewPIP({ -0.2f, -1.0f }, { 0.2f, -0.6f }, entity1Camera->mDefferedRenderingFrameBuffer.GetFrameBufferTexture(doom::graphics::GraphicsAPI::eBufferBitType::COLOR, 2));
	doom::graphics::PicktureInPickture* depthTexturePIP = doom::graphics::PIPManager::GetSingleton()->AddNewPIP({ 0.2f, -1.0f }, { 0.6f, -0.6f }, entity1Camera->mDefferedRenderingFrameBuffer.GetFrameBufferTexture(doom::graphics::GraphicsAPI::eBufferBitType::DEPTH, 0));
	if (depthTexturePIP != nullptr)
	{
		doom::asset::ShaderAsset* const depthTextureShader = doom::assetimporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("DepthBufferTextureShader.glsl");
		graphics::Material* const depthMaterial = doom::CreateDObject<graphics::Material>(depthTextureShader);
		//depthMaterial->SetShaderAsset(depthTextureShader);
		depthTexturePIP->SetMaterial(depthMaterial);
	}





	entity1->GetTransform()->SetPosition(0.0f, 0.0f, 600.0f);
	entity1->AddComponent<Move_WASD>();
	entity1->AddComponent<CharacterSpawner>();
	entity1->AddComponent<ButtonRotate>();


	auto physicsEntity = currenScene->CreateNewEntity();
	entity1->AddComponent<TestComponent>();

	auto emptyEntity = currenScene->CreateNewEntity();


	auto entity2 = currenScene->CreateNewEntity();
	entity2->GetTransform()->SetPosition(2.0f, 1.0f, -1.0f);
	auto entity2BoxCollider3D = entity2->AddComponent<BoxCollider3D>();
	entity2BoxCollider3D->SetHalfExtent(math::Vector3(1.0f, 2.0f, 3.0f));
	entity2->AddComponent<AutoRotate>();

	auto entity3 = currenScene->CreateNewEntity();
	//entity3->AddComponent<ViewFrustumCullingDebug>();

	if (IsValid(entity3))
	{

	}
}