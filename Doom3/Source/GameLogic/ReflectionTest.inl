#pragma once

#include "GameLogicStartPoint.h"

#include <DoomsGameLogicCore.h>
#include "../Asset/AssetManager/AssetManager.h"
#include <Rendering/Material/Material.h>
#include <Rendering/Renderer/MeshRenderer.h>
#include <Rendering/Camera.h>
#include "Move_WASD.h"
#include <Rendering/Light/DirectionalLight.h>
#include <Rendering/Light/PointLight.h>
#include "AutoRotate.h"
#include "PhysicsComponent/BoxCollider3D.h"
#include "CustomComponent/Portfolio/ViewFrustumCullingDebug.h"
#include "CustomComponent/Portfolio/PortfolioComponent.h"
#include "AutoRotateAround.h"
#include "TestComponent.h"
#include "Rendering/Light/LightManager.h"
#include "Graphics/graphicsSetting.h"
#include "Graphics/GraphicsAPI/graphicsAPISetting.h"
#include "Portfolio/DeferredRenderingDebuggerController.h"
#include "Portfolio/OverDrawVisualizationDebugger.h"
#include "Portfolio/PhysicsDebuggerController.h"
#include <Asset/ThreeDModelAsset.h>
#include "ReflectionTestComponent.h"
#include <EngineGUI/PrintText.h>

#include "BulletComponent.h"
#include "ExportTextureTester.h"
#include "FireBulletComponent.h"
#include "TestComponent2.h"
#include "PhysicsComponent/Rigidbody/Rigidbody.h"
#include <Rendering/Buffer/Mesh.h>
#include <Scene/Entity.h>
#include <Rendering/Buffer/MeshHelper.h>
#include "WanderComponent.h"

void dooms::GameLogicStartPoint::StartGameLogic()
{
	ISingleton<graphics::LightManager>::GetSingleton()->SetAmbientLightIntensity(0.1f);

	auto currenScene = dooms::Scene::GetCurrentWorld();

	FireBulletComponent* fireComponent;
	PortfolioComponent* portfolioComponent;
	{
		auto entity1 = currenScene->CreateNewEntity();

		entity1->SetEntityName("Camera");

		auto entity1Camera = entity1->AddComponent<Camera>();
		entity1->GetTransform()->SetPosition(14.0f, -14.0f, 1140.0f);
		entity1->GetTransform()->SetRotation(0.0f, 0.0f, 0.0f);
		entity1Camera->SetProjectionMode(dooms::Camera::eProjectionType::Perspective);
		entity1Camera->SetClippingPlaneNear(1.0f);
		entity1Camera->SetClippingPlaneFar(6500.0f);
		entity1->AddComponent<Move_WASD>();

		//entity1->AddComponent<ExportTextureTester>();
		entity1->AddComponent<DeferredRenderingDebuggerController>();
		fireComponent = entity1->AddComponent<FireBulletComponent>();

		portfolioComponent = entity1->AddComponent<PortfolioComponent>();
		portfolioComponent->RockRenderers.reserve(5000);
		portfolioComponent->PlanesRenderers.reserve(5000);

	}

	
	
	
	auto lightEntity = currenScene->CreateNewEntity();
	lightEntity->GetTransform()->SetPosition(-30.0f, 0.0f, 0.0f);
	lightEntity->GetTransform()->SetRotation(30.0f, 0.0f, 0.0f);
	lightEntity->GetTransform()->SetScale(2.0f, 2.0f, 2.0f);
	lightEntity->ChangeDObjectName("DirectionalLight");
	auto dirLight = lightEntity->AddComponent<DirectionalLight>();
	dirLight->SetIntensity(2.0f);
	dirLight->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });

	/*
	 *{
		auto entity = currenScene->CreateNewEntity();
		entity->ChangeDObjectName("PointLight");
		entity->GetTransform()->SetPosition(200.0f, 0.0f, 0.0f);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);
		PointLight* pointLight = entity->AddComponent<PointLight>();
		AutoRotateAround* autoRotateAround = entity->AddComponent<AutoRotateAround>();
		pointLight->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		pointLight->SetIntensity(300.0f);
		autoRotateAround->mCenterPos = math::Vector3{ 0.0f, 0.0f, 0.0f };
		autoRotateAround->mRotateAngle = 1;
		autoRotateAround->mRotateAxis = { 0.0f, 1.0f, 0.0f };
		BoxCollider3D* box3D = entity->AddComponent<BoxCollider3D>();
		box3D->SetFromAABB3D(planetAsset->GetMesh(0)->GetBoundingBox());
	}

	{
		auto entity = currenScene->CreateNewEntity();
		entity->ChangeDObjectName("PointLight");
		entity->GetTransform()->SetPosition(0.0f, 200.0f, 0.0f);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);
		PointLight* pointLight = entity->AddComponent<PointLight>();
		AutoRotateAround* autoRotateAround = entity->AddComponent<AutoRotateAround>();
		pointLight->SetColor({ 0.0f, 1.0f, 0.0f, 1.0f });
		pointLight->SetIntensity(300.0f);
		autoRotateAround->mCenterPos = math::Vector3{ 0.0f, 0.0f, 0.0f };
		autoRotateAround->mRotateAngle = 1;
		autoRotateAround->mRotateAxis = { 1.0f, 0.0f, 0.0f };
		BoxCollider3D* box3D = entity->AddComponent<BoxCollider3D>();
		box3D->SetFromAABB3D(planetAsset->GetMesh(0)->GetBoundingBox());
	}

	{
		auto entity = currenScene->CreateNewEntity();
		entity->ChangeDObjectName("PointLight");
		entity->GetTransform()->SetPosition(0.0f, 0.0f, 200.0f);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);
		PointLight* pointLight = entity->AddComponent<PointLight>();
		AutoRotateAround* autoRotateAround = entity->AddComponent<AutoRotateAround>();
		pointLight->SetColor({ 0.0f, 0.0f, 1.0f, 1.0f });
		pointLight->SetIntensity(300.0f);
		autoRotateAround->mCenterPos = math::Vector3{ 0.0f, 0.0f, 0.0f };
		autoRotateAround->mRotateAngle = 1;
		autoRotateAround->mRotateAxis = { 0.0f, 1.0f, 0.0f };
		BoxCollider3D* box3D = entity->AddComponent<BoxCollider3D>();
		box3D->SetFromAABB3D(planetAsset->GetMesh(0)->GetBoundingBox());
	}


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

	

	INT32 entityCount = 0;
	
	
	INT32 count = 300;
	for (INT32 i = -count; i < count; i = i + 40)
	{
		for (INT32 j = -count; j < count; j = j + 40)
		{
			for (INT32 k = -count; k < count; k = k + 40)
			{
				auto entity = currenScene->CreateNewEntity();
				entity->GetTransform()->SetScale(3.0f, 3.0f, 3.0f);
				entity->GetTransform()->SetPosition(i, j, k);
				auto meshRenderer = entity->AddComponent<MeshRenderer>();
				entity->AddComponent<TestComponent>();
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

	
	count = 100;
	for (INT32 i = -count; i < count; i = i + 40)
	{
		for (INT32 j = -count; j < count; j = j + 40)
		{
			for (INT32 k = -count; k < count; k = k + 40)
			{
				auto entity = currenScene->CreateNewEntity();
				entity->GetTransform()->SetScale(3.0f, 3.0f, 3.0f);
				entity->GetTransform()->SetPosition(i, j, k + 700);
				auto meshRenderer = entity->AddComponent<MeshRenderer>();
				entity->AddComponent<TestComponent>();
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
	

	
	
	for (INT32 i = -150; i < 150; i += 60)
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
		entity->GetTransform()->SetScale(2.0f, 2.0f, 2.0f);
		entity->GetTransform()->SetPosition(i, 0, 700);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		entity->AddComponent<AutoRotate>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);


		BoxCollider3D* box3D = entity->AddComponent<BoxCollider3D>();
		box3D->SetFromAABB3D(planetAsset->GetMesh(0)->GetBoundingBox());
	}
	

	for (INT32 i = -200; i < 200; i += 30)
	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetScale(2.0f, 2.0f, 2.0f);
		entity->GetTransform()->SetPosition(0, 0, 1300 + i + 200);
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
		entity->GetTransform()->SetScale(2.0f, 2.0f, 2.0f);
		entity->GetTransform()->SetPosition(i, 0, 800);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		entity->AddComponent<AutoRotate>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);


		BoxCollider3D* box3D = entity->AddComponent<BoxCollider3D>();
		box3D->SetFromAABB3D(planetAsset->GetMesh(0)->GetBoundingBox());
	}
	

	
	
	
	

	

	
	
	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetScale(2.0f, 2.0f, 2.0f);
		entity->GetTransform()->SetPosition(0, 0, 800);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		entity->AddComponent<AutoRotate>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);


		BoxCollider3D* box3D = entity->AddComponent<BoxCollider3D>();
		box3D->SetFromAABB3D(planetAsset->GetMesh(0)->GetBoundingBox());
	}
	
	
	
	
	
	
	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetScale(60.0f, 60.0f, 60.0f);
		entity->GetTransform()->SetPosition(0, 0, 1000);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(dooms::graphics::meshHelper::GetQuadMesh());
		meshRenderer->SetMaterial(material);

	}

	
	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetScale(1.0f, 1.0f, 400.0f);
		entity->GetTransform()->SetPosition(0, 0, -1000);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(dooms::graphics::meshHelper::GetQuadMesh());
		meshRenderer->SetMaterial(material);

	}

	
	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetScale(60.0f, 60.0f, 60.0f);
		entity->GetTransform()->SetPosition(-300, 0, 1000);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(dooms::graphics::meshHelper::GetQuadMesh());
		meshRenderer->SetMaterial(material);

	}
	
	
	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetScale(60.0f, 60.0f, 60.0f);
		entity->GetTransform()->SetPosition(300, 0, 1000);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(dooms::graphics::meshHelper::GetQuadMesh());
		meshRenderer->SetMaterial(material);

	}
	
	
	
	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetScale(60.0f, 60.0f, 60.0f);
		entity->GetTransform()->SetPosition(700, 0, 0);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		entity->AddComponent<AutoRotate>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);
	}

	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetScale(60.0f, 60.0f, 60.0f);
		entity->GetTransform()->SetPosition(-700, 0, 0);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		entity->AddComponent<AutoRotate>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);
	}

	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetScale(60.0f, 60.0f, 60.0f);
		entity->GetTransform()->SetPosition(0, 0, -700);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		entity->AddComponent<AutoRotate>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);
	}


	/*
	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetScale(50.0f, 50.0f, 50.0f);
		entity->GetTransform()->SetPosition(0, 500, 0);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		entity->AddComponent<AutoRotate>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);
		AutoRotateAround* autoRotateAround = entity->AddComponent<AutoRotateAround>();
		autoRotateAround->mRotateAngle = 1.0f;
		autoRotateAround->mRotateAxis.x = -1;
	}
	
	{
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetScale(50.0f, 50.0f, 50.0f);
		entity->GetTransform()->SetPosition(0, 0, -700);
		auto meshRenderer = entity->AddComponent<MeshRenderer>();
		entity->AddComponent<AutoRotate>();
		meshRenderer->SetMesh(planetAsset->GetMesh(0));
		meshRenderer->SetMaterial(material);
		AutoRotateAround* autoRotateAround = entity->AddComponent<AutoRotateAround>();
		autoRotateAround->mRotateAngle = 1.0f;
		autoRotateAround->mRotateAxis.y = 1;
	}

	#1#

	
	{
		auto modelAsset = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>("StarSparrow09.assbin");
		auto shader1 = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("GbufferWriter_PBR.glsl");
		auto material1 = dooms::CreateDObject<graphics::Material>(shader1);
		material1->AddTexture(graphics::eTextureBindingPoint::AlbedoTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("StarSparrow_Red.dds"));
		material1->AddTexture(graphics::eTextureBindingPoint::NormalTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("StarSparrow_Normal.dds"));
		material1->AddTexture(graphics::eTextureBindingPoint::MetalnessTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("StarSparrow_Metallic.dds"));
		//material1->AddTexture(graphics::eTextureBindingPoint::SpecularTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("ufo_spec.dds"));

		for(size_t meshIndex = 0 ; meshIndex < modelAsset->GetMeshCount() ; meshIndex++)
		{
			graphics::Mesh* mesh = modelAsset->GetMesh(meshIndex);
			if (mesh->GetTargetThreeDModelMesh()->mIsValidMesh == true)
			{
				auto entity = currenScene->CreateNewEntity();
				entity->GetTransform()->SetScale(100.0f, 100.0f, 100.0f);
				entity->GetTransform()->SetPosition(0, 0, 700);
				auto meshRenderer = entity->AddComponent<MeshRenderer>();
				meshRenderer->SetMesh(mesh);
				meshRenderer->SetMaterial(material1);
			}
			
		}
		
		
	}*/


	/*
	{
		const std::vector<std::string> modelAssetNameList =
		{
			"StarSparrow01.assbin",
			"StarSparrow02.assbin",
			"StarSparrow03.assbin",
			"StarSparrow04.assbin",
			"StarSparrow05.assbin",
			"StarSparrow06.assbin",
			"StarSparrow07.assbin",
			"StarSparrow08.assbin",
			"StarSparrow09.assbin",
			"StarSparrow10.assbin",
			"StarSparrow11.assbin",
			"StarSparrow12.assbin",
			"StarSparrow13.assbin"
		};

		const std::vector<std::string> albedoTextureAssetNameList =
		{
			"StarSparrow_Yellow.dds",
			"StarSparrow_Red.dds",
			"StarSparrow_Purple.dds",
			"StarSparrow_Orange.dds",
			"StarSparrow_Green.dds",
			"StarSparrow_Cyan.dds",
			"StarSparrow_Blue.dds",
			"StarSparrow_Black.dds"
		};

		{
			std::vector<graphics::Material*> materialList;
			materialList.reserve(albedoTextureAssetNameList.size());
			for (auto& texture : albedoTextureAssetNameList)
			{
				auto shader1 = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("GbufferWriter_PBR.glsl");
				auto material1 = dooms::CreateDObject<graphics::Material>(shader1);
				material1->AddTexture(graphics::eTextureBindingPoint::AlbedoTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>(texture));
				material1->AddTexture(graphics::eTextureBindingPoint::NormalTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("StarSparrow_Normal.dds"));
				material1->AddTexture(graphics::eTextureBindingPoint::MetalnessTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("StarSparrow_Metallic.dds"));

				materialList.push_back(material1);
			}

			for (size_t i = 0; i < 700; i++)
			{
				auto modelAsset = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>(modelAssetNameList[Random::RandomUIntNumber(0, modelAssetNameList.size() - 1)]);

				//material1->AddTexture(graphics::eTextureBindingPoint::SpecularTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("ufo_spec.dds"));

				for (size_t meshIndex = 0; meshIndex < modelAsset->GetMeshCount(); meshIndex++)
				{
					graphics::Mesh* mesh = modelAsset->GetMesh(meshIndex);
					if (mesh->GetTargetThreeDModelMesh()->mIsValidMesh == true)
					{
						auto entity = currenScene->CreateNewEntity();
						entity->GetTransform()->SetScale(10.0f, 10.0f, 10.0f);
						auto y = Random::RandomFloatNumber(-1500.0f, 1500.0f);
						entity->GetTransform()->SetPosition(Random::RandomFloatNumber(-500.0f, 500.0f), y, Random::RandomFloatNumber(-500.0f, 500.0f));
						auto meshRenderer = entity->AddComponent<MeshRenderer>();
						meshRenderer->SetMesh(mesh);
						meshRenderer->SetMaterial(materialList[Random::RandomUIntNumber(0, materialList.size() - 1)]);
						portfolioComponent->PlanesRenderers.push_back(meshRenderer);

						WanderComponent* wanderComp = entity->AddComponent<WanderComponent>();
						wanderComp->mPoint1 = { Random::RandomFloatNumber(-1500.0f, 1500.0f) , y , Random::RandomFloatNumber(-1500.0f, 1500.0f) };
						wanderComp->mPoint2 = { Random::RandomFloatNumber(-1500.0f, 1500.0f) , y , Random::RandomFloatNumber(-1500.0f, 1500.0f) };
						wanderComp->mLookAtDestination = true;
						wanderComp->mSpeed = 130.0f;
						wanderComp->mRotationEulerOffset = { 0.0f, 180.0f, 0.0f };
					}

				}


			}
		}
	}
	
	

	{
		auto modelAsset = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>("PlanetsOBJ.assbin");
		auto shader1 = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("GbufferWriter_PBR.glsl");
		auto material1 = dooms::CreateDObject<graphics::Material>(shader1);
		material1->AddTexture(graphics::eTextureBindingPoint::AlbedoTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_earth_daymap.dds"));
		material1->AddTexture(graphics::eTextureBindingPoint::NormalTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_earth_normal_map.dds"));
		material1->AddTexture(graphics::eTextureBindingPoint::MetalnessTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_earth_normal_map.dds"));
		//material1->AddTexture(graphics::eTextureBindingPoint::SpecularTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_earth_specular_map.dds"));

		graphics::Mesh* mesh = modelAsset->GetMesh(0);
		if (mesh->GetTargetThreeDModelMesh()->mIsValidMesh == true)
		{
			auto entity = currenScene->CreateNewEntity();
			entity->GetTransform()->SetScale(280.0f, 280.0f, 280.0f);
			entity->GetTransform()->SetPosition(Random::RandomFloatNumber(-2000.0f, 2000.0f), Random::RandomFloatNumber(-2000.0f, 2000.0f), Random::RandomFloatNumber(-2000.0f, 2000.0f));
			auto meshRenderer = entity->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(mesh);
			meshRenderer->SetMaterial(material1);
		}
	}

	{
		auto modelAsset = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>("PlanetsOBJ.assbin");
		auto shader1 = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("GbufferWriter_PBR.glsl");
		auto material1 = dooms::CreateDObject<graphics::Material>(shader1);
		material1->AddTexture(graphics::eTextureBindingPoint::AlbedoTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_jupiter.dds"));
		material1->AddTexture(graphics::eTextureBindingPoint::NormalTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_earth_normal_map.dds"));
		material1->AddTexture(graphics::eTextureBindingPoint::MetalnessTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_earth_normal_map.dds"));
		//material1->AddTexture(graphics::eTextureBindingPoint::SpecularTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_earth_specular_map.dds"));

		graphics::Mesh* mesh = modelAsset->GetMesh(0);
		if (mesh->GetTargetThreeDModelMesh()->mIsValidMesh == true)
		{
			auto entity = currenScene->CreateNewEntity();
			entity->GetTransform()->SetScale(200.0f, 200.0f, 200.0f);
			entity->GetTransform()->SetPosition(Random::RandomFloatNumber(-2000.0f, 2000.0f), Random::RandomFloatNumber(-2000.0f, 2000.0f), Random::RandomFloatNumber(-2000.0f, 2000.0f));
			auto meshRenderer = entity->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(mesh);
			meshRenderer->SetMaterial(material1);
		}
	}

	{
		auto modelAsset = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>("PlanetsOBJ.assbin");
		auto shader1 = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("GbufferWriter_PBR.glsl");
		auto material1 = dooms::CreateDObject<graphics::Material>(shader1);
		material1->AddTexture(graphics::eTextureBindingPoint::AlbedoTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_mars.dds"));
		material1->AddTexture(graphics::eTextureBindingPoint::NormalTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_earth_normal_map.dds"));
		material1->AddTexture(graphics::eTextureBindingPoint::MetalnessTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_earth_normal_map.dds"));
		//material1->AddTexture(graphics::eTextureBindingPoint::SpecularTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_earth_specular_map.dds"));

		graphics::Mesh* mesh = modelAsset->GetMesh(0);
		if (mesh->GetTargetThreeDModelMesh()->mIsValidMesh == true)
		{
			auto entity = currenScene->CreateNewEntity();
			entity->GetTransform()->SetScale(300.0f, 300.0f, 300.0f);
			entity->GetTransform()->SetPosition(Random::RandomFloatNumber(-2000.0f, 2000.0f), Random::RandomFloatNumber(-2000.0f, 2000.0f), Random::RandomFloatNumber(-2000.0f, 2000.0f));
			auto meshRenderer = entity->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(mesh);
			meshRenderer->SetMaterial(material1);
		}
	}

	{
		auto modelAsset = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>("PlanetsOBJ.assbin");
		auto shader1 = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("GbufferWriter_PBR.glsl");
		auto material1 = dooms::CreateDObject<graphics::Material>(shader1);
		material1->AddTexture(graphics::eTextureBindingPoint::AlbedoTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_mercury.dds"));
		material1->AddTexture(graphics::eTextureBindingPoint::NormalTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_earth_normal_map.dds"));
		material1->AddTexture(graphics::eTextureBindingPoint::MetalnessTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_earth_normal_map.dds"));
		//material1->AddTexture(graphics::eTextureBindingPoint::SpecularTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_earth_specular_map.dds"));

		graphics::Mesh* mesh = modelAsset->GetMesh(0);
		if (mesh->GetTargetThreeDModelMesh()->mIsValidMesh == true)
		{
			auto entity = currenScene->CreateNewEntity();
			entity->GetTransform()->SetScale(150.0f, 150.0f, 150.0f);
			entity->GetTransform()->SetPosition(Random::RandomFloatNumber(-2000.0f, 2000.0f), Random::RandomFloatNumber(-2000.0f, 2000.0f), Random::RandomFloatNumber(-2000.0f, 2000.0f));
			auto meshRenderer = entity->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(mesh);
			meshRenderer->SetMaterial(material1);
		}
	}

	{
		auto modelAsset = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>("PlanetsOBJ.assbin");
		auto shader1 = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("GbufferWriter_PBR.glsl");
		auto material1 = dooms::CreateDObject<graphics::Material>(shader1);
		material1->AddTexture(graphics::eTextureBindingPoint::AlbedoTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_moon.dds"));
		material1->AddTexture(graphics::eTextureBindingPoint::NormalTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_earth_normal_map.dds"));
		material1->AddTexture(graphics::eTextureBindingPoint::MetalnessTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_earth_normal_map.dds"));
		//material1->AddTexture(graphics::eTextureBindingPoint::SpecularTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_earth_specular_map.dds"));

		graphics::Mesh* mesh = modelAsset->GetMesh(0);
		if (mesh->GetTargetThreeDModelMesh()->mIsValidMesh == true)
		{
			auto entity = currenScene->CreateNewEntity();
			entity->GetTransform()->SetScale(300.0f, 300.0f, 300.0f);
			entity->GetTransform()->SetPosition(Random::RandomFloatNumber(-2000.0f, 2000.0f), Random::RandomFloatNumber(-2000.0f, 2000.0f), Random::RandomFloatNumber(-2000.0f, 2000.0f));
			auto meshRenderer = entity->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(mesh);
			meshRenderer->SetMaterial(material1);
		}
	}

	
	{
		auto modelAsset = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>("PlanetsOBJ.assbin");
		auto shader1 = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("GbufferWriter_PBR.glsl");
		auto material1 = dooms::CreateDObject<graphics::Material>(shader1);
		material1->AddTexture(graphics::eTextureBindingPoint::AlbedoTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_uranus.dds"));
		material1->AddTexture(graphics::eTextureBindingPoint::NormalTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_earth_normal_map.dds"));
		material1->AddTexture(graphics::eTextureBindingPoint::MetalnessTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_earth_normal_map.dds"));
		//material1->AddTexture(graphics::eTextureBindingPoint::SpecularTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("2k_earth_specular_map.dds"));

		graphics::Mesh* mesh = modelAsset->GetMesh(0);
		if (mesh->GetTargetThreeDModelMesh()->mIsValidMesh == true)
		{
			auto entity = currenScene->CreateNewEntity();
			entity->GetTransform()->SetScale(180.0f, 180.0f, 180.0f);
			entity->GetTransform()->SetPosition(Random::RandomFloatNumber(-2000.0f, 2000.0f), Random::RandomFloatNumber(-2000.0f, 2000.0f), Random::RandomFloatNumber(-2000.0f, 2000.0f));
			auto meshRenderer = entity->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(mesh);
			meshRenderer->SetMaterial(material1);
		}
	}

	{
		auto modelAsset = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>("Rock.assbin");
		auto shader1 = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("GbufferWriter_PBR.glsl");
		auto material1 = dooms::CreateDObject<graphics::Material>(shader1);
		material1->AddTexture(graphics::eTextureBindingPoint::AlbedoTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("Rock_albedo.dds"));
		material1->AddTexture(graphics::eTextureBindingPoint::NormalTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("Rock_normal.dds"));
		material1->AddTexture(graphics::eTextureBindingPoint::MetalnessTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("Rock_metallic.dds"));

		for (size_t i = 0; i < 6000; i++)
		{
			for (size_t meshIndex = 0; meshIndex < modelAsset->GetMeshCount(); meshIndex++)
			{
				graphics::Mesh* mesh = modelAsset->GetMesh(meshIndex);
				if (mesh->GetTargetThreeDModelMesh()->mIsValidMesh == true)
				{
					auto entity = currenScene->CreateNewEntity();
					const float scale = Random::RandomFloatNumber(0.5f, 2.0f);
					entity->GetTransform()->SetScale(scale, scale, scale);
					entity->GetTransform()->SetRotation(Random::RandomFloatNumber(0.0f, 90.0f), Random::RandomFloatNumber(0.0f, 90.0f), Random::RandomFloatNumber(0.0f, 90.0f));
					entity->GetTransform()->SetPosition(Random::RandomFloatNumber(-3500.0f, 3500.0f), Random::RandomFloatNumber(-3500.0f, 3500.0f), Random::RandomFloatNumber(-3500.0f, 3500.0f));
					auto meshRenderer = entity->AddComponent<MeshRenderer>();
					meshRenderer->SetMesh(mesh);
					meshRenderer->SetMaterial(material1);
					portfolioComponent->RockRenderers.push_back(meshRenderer);

					WanderComponent* wanderComp = entity->AddComponent<WanderComponent>();
					wanderComp->mPoint1 = { Random::RandomFloatNumber(-3500.0f, 3500.0f) , Random::RandomFloatNumber(-3500.0f, 3500.0f) , Random::RandomFloatNumber(-3500.0f, 3500.0f) };
					wanderComp->mPoint2 = { Random::RandomFloatNumber(-3500.0f, 3500.0f) , Random::RandomFloatNumber(-3500.0f, 3500.0f) , Random::RandomFloatNumber(-3500.0f, 3500.0f) };
					wanderComp->mLookAtDestination = false;
					wanderComp->mSpeed = 3.0f;
				}

			}
		}

		for (size_t i = 0; i < 10000; i++)
		{
			for (size_t meshIndex = 0; meshIndex < modelAsset->GetMeshCount(); meshIndex++)
			{
				graphics::Mesh* mesh = modelAsset->GetMesh(meshIndex);
				if (mesh->GetTargetThreeDModelMesh()->mIsValidMesh == true)
				{
					auto entity = currenScene->CreateNewEntity();
					const float scale = Random::RandomFloatNumber(0.1f, 0.4f);
					entity->GetTransform()->SetScale(scale, scale, scale);
					entity->GetTransform()->SetRotation(Random::RandomFloatNumber(0.0f, 90.0f), Random::RandomFloatNumber(0.0f, 90.0f), Random::RandomFloatNumber(0.0f, 90.0f));
					entity->GetTransform()->SetPosition(Random::RandomFloatNumber(-3500.0f, 3500.0f), Random::RandomFloatNumber(-3500.0f, 3500.0f), Random::RandomFloatNumber(-3500.0f, 3500.0f));
					auto meshRenderer = entity->AddComponent<MeshRenderer>();
					meshRenderer->SetMesh(mesh);
					meshRenderer->SetMaterial(material1);
					portfolioComponent->RockRenderers.push_back(meshRenderer);

					WanderComponent* wanderComp = entity->AddComponent<WanderComponent>();
					wanderComp->mPoint1 = { Random::RandomFloatNumber(-3500.0f, 3500.0f) , Random::RandomFloatNumber(-3500.0f, 3500.0f) , Random::RandomFloatNumber(-3500.0f, 3500.0f) };
					wanderComp->mPoint2 = { Random::RandomFloatNumber(-3500.0f, 3500.0f) , Random::RandomFloatNumber(-3500.0f, 3500.0f) , Random::RandomFloatNumber(-3500.0f, 3500.0f) };
					wanderComp->mLookAtDestination = false;
					wanderComp->mSpeed = 3.0f;
				}

			}
		}
		

		
		

	}
	*/
	{
		auto modelAsset = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>("wooden crate.assbin");
		auto shader1 = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("GbufferWriter_PBR.glsl");
		auto material1 = dooms::CreateDObject<graphics::Material>(shader1);
		material1->AddTexture(graphics::eTextureBindingPoint::AlbedoTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("crate_BaseColor.dds"));
		material1->AddTexture(graphics::eTextureBindingPoint::NormalTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("crate_Normal.dds"));
		material1->AddTexture(graphics::eTextureBindingPoint::MetalnessTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("crate_Metallic.dds"));

		for (size_t i = 0; i < 600; i++)
		{
			graphics::Mesh* mesh = modelAsset->GetMesh(0);
			if (mesh->GetTargetThreeDModelMesh()->mIsValidMesh == true)
			{
				auto entity = currenScene->CreateNewEntity();
				const float scale = Random::RandomFloatNumber(10.0f, 40.0f);
				entity->GetTransform()->SetScale(scale, scale, scale);
				entity->GetTransform()->SetRotation(Random::RandomFloatNumber(0.0f, 90.0f), Random::RandomFloatNumber(0.0f, 90.0f), Random::RandomFloatNumber(0.0f, 90.0f));
				entity->GetTransform()->SetPosition(Random::RandomFloatNumber(-2000.0f, 2000.0f), Random::RandomFloatNumber(-2000.0f, 2000.0f), Random::RandomFloatNumber(-2000.0f, 2000.0f));
				//entity->SetEntityMobility(eEntityMobility::Static);
				auto meshRenderer = entity->AddComponent<MeshRenderer>();
				meshRenderer->SetMesh(mesh);
				meshRenderer->SetMaterial(material1);

				portfolioComponent->StaticMobilitySetter.push_back(entity);
			}
		}
		}


	/*

	auto a = Renderer::CLASS_TYPE_ID_STATIC();
	auto b = MeshRenderer::CLASS_TYPE_ID_STATIC();
	auto c = DirectionalLight::CLASS_TYPE_ID_STATIC();
	

	auto b1 = IsChildOf<DObject>(static_cast<DObject*>(dirLight));
	auto b2 = IsChildOf<Light>(static_cast<DObject*>(dirLight));
	auto b3 = IsChildOf<DirectionalLight>(static_cast<DObject*>(dirLight));
	auto b4 = IsChildOf<PointLight>(static_cast<DObject*>(dirLight));
	
	auto c2 = CastTo<DirectionalLight*>(dirLight);
	auto c3 = CastTo<PointLight*>(dirLight);
	auto c4= CastTo<MeshRenderer*>(dirLight);

	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	//START TO TEST FROM HERE

	//Test Compile Time Resolvation

	
	 
	constexpr auto c5= DirectionalLight::CLASS_FLAGS_STATIC();
	constexpr const char* c6= DirectionalLight::CLASS_NAME_STATIC();
	D_ASSERT(std::strcmp(c6, "DirectionalLight") == 0);
	constexpr auto c7= DirectionalLight::CLASS_TYPE_ID_STATIC();


	constexpr auto chainCount = DirectionalLight::BASE_CHAIN_COUNT_STATIC();
	constexpr auto chainData = DirectionalLight::BASE_CHAIN_DATA_STATIC();
	static_assert(chainData[0] == DirectionalLight::CLASS_TYPE_ID_STATIC());
	static_assert(chainData[1] == Light::CLASS_TYPE_ID_STATIC());
	static_assert(chainData[2] == ServerComponent::CLASS_TYPE_ID_STATIC());
	static_assert(chainData[3] == Component::CLASS_TYPE_ID_STATIC());
	static_assert(chainData[4] == DObject::CLASS_TYPE_ID_STATIC());


	constexpr auto chain1Count = TestComponent2::BASE_CHAIN_COUNT_STATIC();
	constexpr auto chain1Data = TestComponent2::BASE_CHAIN_DATA_STATIC();
	static_assert(chain1Data[0] == TestComponent2::CLASS_TYPE_ID_STATIC());
	static_assert(chain1Data[1] == TestComponent::CLASS_TYPE_ID_STATIC());
	static_assert(chain1Data[2] == Component::CLASS_TYPE_ID_STATIC());
	static_assert(chain1Data[3] == Component::CLASS_TYPE_ID_STATIC());
	static_assert(chain1Data[4] == DObject::CLASS_TYPE_ID_STATIC());

	D_ASSERT(dirLight->GetOwnerEntity()->GetComponent<DirectionalLight>() != nullptr);
	D_ASSERT(IsServerComponent(dirLight) == true);
	D_ASSERT(IsComponent(dirLight) == false);


	D_ASSERT(DObject::CLASS_TYPE_ID_STATIC() != MeshRenderer::CLASS_TYPE_ID_STATIC());
	D_ASSERT(ServerComponent::CLASS_TYPE_ID_STATIC() != MeshRenderer::CLASS_TYPE_ID_STATIC());
	D_ASSERT(Component::CLASS_TYPE_ID_STATIC() != MeshRenderer::CLASS_TYPE_ID_STATIC());
	D_ASSERT(Component::CLASS_TYPE_ID_STATIC() != MeshRenderer::CLASS_TYPE_ID_STATIC());
	D_ASSERT(Component::CLASS_TYPE_ID_STATIC() != dirLight->GetClassTypeID());
	

	D_ASSERT(CastTo<DObject*>(dirLight) != nullptr);
	D_ASSERT(CastTo<MeshRenderer*>(dirLight) == nullptr);
	D_ASSERT(CastTo<PointLight*>(dirLight) == nullptr);
	D_ASSERT(CastTo<Component*>(dirLight) != nullptr);
	D_ASSERT(CastTo<ServerComponent*>(dirLight) != nullptr);
	D_ASSERT(CastTo<Component*>(dirLight) == nullptr);

	DObject* dObject = CastTo<DObject*>(dirLight);
	D_ASSERT(CastTo<const DirectionalLight*>(dObject) != nullptr);
	D_ASSERT(CastTo<MeshRenderer*>(dObject) == nullptr);
	D_ASSERT(CastTo<PointLight*>(dObject) == nullptr);

	const DObject* dObjectConst = CastTo<DObject*>(dirLight);
	D_ASSERT(CastTo<const DirectionalLight*>(dObjectConst) != nullptr);
	D_ASSERT(CastTo<const MeshRenderer*>(dObjectConst) == nullptr);
	D_ASSERT(CastTo<const PointLight*>(dObjectConst) == nullptr);

	auto str = DirectionalLight::CLASS_NAME_STATIC();
	
	D_ASSERT(std::strcmp(DirectionalLight::CLASS_NAME_STATIC(), "DirectionalLight") == 0);
	D_ASSERT(std::strcmp(dObjectConst->GetClassName(), "DirectionalLight") == 0);
	D_ASSERT(std::strcmp(dObjectConst->GetClassName(), "PointLight") != 0);
	D_ASSERT(std::strcmp(dObjectConst->GetClassName(), "Component") != 0);


	D_ASSERT(CastTo<TestComponent*>(testComp2) != nullptr);
	D_ASSERT(CastTo<TestComponent2*>(testComp1) == nullptr);

	dooms::DClass* dclass2 = testComp2->GetDClass();
	D_ASSERT(dclass2->IsChildOf<TestComponent>() == true);
	D_ASSERT(std::strcmp(dclass2->CLASS_NAME, "TestComponent2") == 0);
	
	dooms::DClass* dclass1 = testComp1->GetDClass();
	D_ASSERT(dclass1->IsChildOf<TestComponent2>() == false);
	D_ASSERT(std::strcmp(dclass1->CLASS_NAME, "TestComponent2") != 0);

	TSubclassOf<dooms::TestComponent> testComp1SubClassOf{ dclass1 };
	TSubclassOf<dooms::TestComponent> testComp2SubClassOf{ dclass2 };
	TSubclassOf<dooms::TestComponent2> testComp3SubClassOf{ dclass2 };
	TSubclassOf<dooms::TestComponent2> testComp13SubClassOf{ testComp2SubClassOf };
	D_ASSERT(testComp1SubClassOf != nullptr);
	D_ASSERT(testComp2SubClassOf != nullptr);
	D_ASSERT(testComp3SubClassOf != nullptr);
	D_ASSERT(testComp13SubClassOf == nullptr);

	
	TSubclassOf<dooms::TestComponent2> testComp12SubClassOf{ dclass1 };
	D_ASSERT(testComp12SubClassOf == nullptr);

	DClass* meshDClass = dooms::graphics::Mesh::StaticClass();
	dooms::graphics::Mesh* newMesh = CastTo<dooms::graphics::Mesh*>(meshDClass->CreateDObject());

	TSubclassOf<dooms::DObject> DObjectSubClassOf{ Renderer::StaticClass() };

	*/
}
