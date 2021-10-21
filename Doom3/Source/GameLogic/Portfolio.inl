#pragma once

#include "GameLogicStartPoint.h"

#include <Doom_Core.h>
#include "../Game/AssetManager/AssetManager.h"
#include "../Graphics/Material/Material.h"
#include <Rendering/Renderer/MeshRenderer.h>
#include <Rendering/Camera.h>
#include "Move_WASD.h"
#include <Rendering/Light/DirectionalLight.h>
#include <Rendering/Light/PointLight.h>
#include "AutoRotate.h"
#include "PhysicsComponent/BoxCollider3D.h"
#include "CustomComponent/Portfolio/ViewFrustumCullingDebug.h"
#include "AutoRotateAround.h"
#include "TestComponent.h"
#include "Graphics/LightManager.h"
#include "Graphics/Graphics_Setting.h"
#include "Graphics/GraphicsAPIManager.h"
#include "Portfolio/DeferredRenderingDebuggerController.h"
#include "Portfolio/OverDrawVisualizationDebugger.h"
#include "Portfolio/PhysicsDebuggerController.h"
#include <Asset/ThreeDModelAsset.h>
#include <UI/PrintText.h>

#include "BulletComponent.h"
#include "ExportTextureTester.h"
#include "FireBulletComponent.h"
#include "PhysicsComponent/Rigidbody/Rigidbody.h"

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

	//auto& threedasset = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>(0);
	auto threedasset = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>("cerberus.assbin");
	auto shader = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("GbufferWriter_PBR.glsl");
	auto material = doom::CreateDObject<graphics::Material>(shader);
	material->AddTexture(graphics::eTextureBindingPoint::AlbedoTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_A.dds"));
	material->AddTexture(graphics::eTextureBindingPoint::NormalTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_N.dds"));
	material->AddTexture(graphics::eTextureBindingPoint::MetalnessTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_M.dds"));
	material->AddTexture(graphics::eTextureBindingPoint::RoughnessTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_R.dds"));

	auto planetAsset = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>("planet.assbin");


	for (INT32 i = 0; i < 25; i++)
	{
	 	for (INT32 j = 0; j < threedasset->GetMeshCount(); j++)
	 	{
	 		auto entity = currenScene->CreateNewEntity();
	 		entity->GetTransform()->SetScale(0.1f, 0.1f, 0.1f);
	 		entity->GetTransform()->SetPosition(Random::RandomFloatNumber(-20, 20), Random::RandomFloatNumber(-20, 20), Random::RandomFloatNumber(-20, 20));
	 		auto meshRenderer = entity->AddComponent<MeshRenderer>();
	 		meshRenderer->SetMesh(threedasset->GetMesh(j));
	 		meshRenderer->SetMaterial(material);
	 		entity->AddComponent<AutoRotate>();
	 		entity->AddComponent<BoxCollider3D>();
	 	}
	}

	INT32 entityCount = 0;
	
	INT32 count = 150;
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

				BoxCollider3D* box3D = entity->AddComponent<BoxCollider3D>();
				box3D->SetFromAABB3D(planetAsset->GetMesh(0)->GetBoundingBox());
				//entity->AddComponent<AutoRotate>();
				//entity->AddComponent<BoxCollider3D>();
			}
		}
	}
	
	for (INT32 i = -200; i < 200; i += 60)
	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetScale(10.0f, 10.0f, 10.0f);
		entity->GetTransform()->SetPosition(i, 0, 500);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		entity->AddComponent<AutoRotate>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);

		BoxCollider3D* box3D = entity->AddComponent<BoxCollider3D>();
		box3D->SetFromAABB3D(planetAsset->GetMesh(0)->GetBoundingBox());
	}

	for (INT32 i = -50; i < 50; i += 30)
	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetScale(1.5f, 1.5f, 1.5f);
		entity->GetTransform()->SetPosition(i, 0, 700);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		entity->AddComponent<AutoRotate>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);


		BoxCollider3D* box3D = entity->AddComponent<BoxCollider3D>();
		box3D->SetFromAABB3D(planetAsset->GetMesh(0)->GetBoundingBox());
	}

	{
		auto entity1 = currenScene->CreateNewEntity();

		auto entity1Camera = entity1->AddComponent<Camera>();
		entity1->GetTransform()->SetPosition(0, 0, 1000);
		entity1Camera->SetProjectionMode(doom::Camera::eProjectionType::Perspective);
		entity1->AddComponent<ViewFrustumCullingDebug>();
		entity1->AddComponent<Move_WASD>();
		entity1->AddComponent<ExportTextureTester>();
		entity1->AddComponent<DeferredRenderingDebuggerController>();
		entity1->AddComponent<OverDrawVisualizationDebugger>();
		FireBulletComponent* fireComponent = entity1->AddComponent<FireBulletComponent>();
		auto physicsDebuggerController = entity1->AddComponent<PhysicsDebuggerController>();
		entity1->AddComponent<TestComponent>();

		{
			auto entity = currenScene->CreateNewEntity();
			entity->GetTransform()->SetScale(1.5f, 1.5f, 1.5f);
			entity->GetTransform()->SetPosition(0, 0, 0);
			auto meshRenderer = entity->AddComponent<MeshRenderer>();
			entity->AddComponent<Rigidbody>();
			BulletComponent* bullet = entity->AddComponent<BulletComponent>();
			meshRenderer->SetMesh(planetAsset->GetMesh(0));
			meshRenderer->SetMaterial(material);
			BoxCollider3D* box3D = entity->AddComponent<BoxCollider3D>();
			box3D->SetFromAABB3D(planetAsset->GetMesh(0)->GetBoundingBox());
			fireComponent->mBullet = bullet;
			bullet->mSpeed = 500;
		}

	
	}


	
	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetPosition(200.0f, 0.0f, 0.0f);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);
		PointLight* pointLight = entity->AddComponent<PointLight>();
		AutoRotateAround* autoRotateAround = entity->AddComponent<AutoRotateAround>();
		pointLight->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		pointLight->SetIntensity(12000.0f);
		autoRotateAround->mCenterPos = math::Vector3{ 0.0f, 0.0f, 0.0f };
		autoRotateAround->mRotateAngle = 1;
		autoRotateAround->mRotateAxis = { 0.0f, 1.0f, 0.0f };
		BoxCollider3D* box3D = entity->AddComponent<BoxCollider3D>();
		box3D->SetFromAABB3D(planetAsset->GetMesh(0)->GetBoundingBox());
	}

	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetPosition(0.0f, 200.0f, 0.0f);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);
		PointLight* pointLight = entity->AddComponent<PointLight>();
		AutoRotateAround* autoRotateAround = entity->AddComponent<AutoRotateAround>();
		pointLight->SetColor({ 0.0f, 1.0f, 0.0f, 1.0f });
		pointLight->SetIntensity(12000.0f);
		autoRotateAround->mCenterPos = math::Vector3{ 0.0f, 0.0f, 0.0f };
		autoRotateAround->mRotateAngle = 1;
		autoRotateAround->mRotateAxis = { 1.0f, 0.0f, 0.0f };
		BoxCollider3D* box3D = entity->AddComponent<BoxCollider3D>();
		box3D->SetFromAABB3D(planetAsset->GetMesh(0)->GetBoundingBox());
	}

	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetPosition(0.0f, 0.0f, 200.0f);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);
		PointLight* pointLight = entity->AddComponent<PointLight>();
		AutoRotateAround* autoRotateAround = entity->AddComponent<AutoRotateAround>();
		pointLight->SetColor({ 0.0f, 0.0f, 1.0f, 1.0f });
		pointLight->SetIntensity(12000.0f);
		autoRotateAround->mCenterPos = math::Vector3{ 0.0f, 0.0f, 0.0f };
		autoRotateAround->mRotateAngle = 1;
		autoRotateAround->mRotateAxis = { 0.0f, 1.0f, 0.0f };
		BoxCollider3D* box3D = entity->AddComponent<BoxCollider3D>();
		box3D->SetFromAABB3D(planetAsset->GetMesh(0)->GetBoundingBox());
	}

	
	doom::graphics::GraphicsAPIManager::SetWindowTitle(
		u8"F3 : 디퍼드렌더링 디버거 ON/OFF | F4 : 멀티스레드 뷰프러스텀 컬링 ON/OFF | F5 : 오브젝트 FRONT TO BACK ON / OFF | F6 : 오버드로우 디버거 ON / OFF | F7 : 충돌 처리 디버깅 ON / OFF"
	);

	doom::ui::PrintText(
		"F3 : 디퍼드렌더링 디버거 ON/OFF | F4 : 멀티스레드 뷰프러스텀 컬링 ON/OFF | F5 : 오브젝트 FRONT TO BACK ON / OFF | F6 : 오버드로우 디버거 ON / OFF | F7 : 충돌 처리 디버깅 ON / OFF"
	);

	
}
