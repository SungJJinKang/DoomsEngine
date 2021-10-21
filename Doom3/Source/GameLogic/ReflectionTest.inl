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
#include "TestComponent2.h"
#include "PhysicsComponent/Rigidbody/Rigidbody.h"

void doom::GameLogicStartPoint::StartGameLogic()
{
	ISingleton<graphics::LightManager>::GetSingleton()->SetAmbientLightIntensity(0.1f);
	doom::graphics::Graphics_Setting::DefaultClearColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	auto currenScene = doom::Scene::GetCurrentWorld();


	auto lightEntity = currenScene->CreateNewEntity();
	lightEntity->GetTransform()->SetRotation(-30.0f, 0.0f, 0.0f);
	auto dirLight = lightEntity->AddComponent<DirectionalLight>();
	auto testComp1 = lightEntity->AddComponent<TestComponent>();
	auto testComp2 = lightEntity->AddComponent<TestComponent2>();
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

	auto a = Renderer::CLASS_TYPE_ID_STATIC();
	auto b = MeshRenderer::CLASS_TYPE_ID_STATIC();
	auto c = DirectionalLight::CLASS_TYPE_ID_STATIC();

	auto d = dirLight->GetClassTypeID();
	auto e = typeid(*dirLight).hash_code();

	auto b1 = IsA<DObject>(static_cast<DObject*>(dirLight));
	auto b2 = IsA<Light>(static_cast<DObject*>(dirLight));
	auto b3 = IsA<DirectionalLight>(static_cast<DObject*>(dirLight));
	auto b4 = IsA<PointLight>(static_cast<DObject*>(dirLight));
	
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
	static_assert(chain1Data[2] == PlainComponent::CLASS_TYPE_ID_STATIC());
	static_assert(chain1Data[3] == Component::CLASS_TYPE_ID_STATIC());
	static_assert(chain1Data[4] == DObject::CLASS_TYPE_ID_STATIC());

	D_ASSERT(dirLight->GetOwnerEntity()->GetComponent<DirectionalLight>() != nullptr);
	D_ASSERT(IsServerComponent(dirLight) == true);
	D_ASSERT(IsPlainComponent(dirLight) == false);


	D_ASSERT(DObject::CLASS_TYPE_ID_STATIC() != MeshRenderer::CLASS_TYPE_ID_STATIC());
	D_ASSERT(ServerComponent::CLASS_TYPE_ID_STATIC() != MeshRenderer::CLASS_TYPE_ID_STATIC());
	D_ASSERT(PlainComponent::CLASS_TYPE_ID_STATIC() != MeshRenderer::CLASS_TYPE_ID_STATIC());
	D_ASSERT(Component::CLASS_TYPE_ID_STATIC() != MeshRenderer::CLASS_TYPE_ID_STATIC());
	D_ASSERT(Component::CLASS_TYPE_ID_STATIC() != dirLight->GetClassTypeID());
	

	D_ASSERT(CastTo<DObject*>(dirLight) != nullptr);
	D_ASSERT(CastTo<MeshRenderer*>(dirLight) == nullptr);
	D_ASSERT(CastTo<PointLight*>(dirLight) == nullptr);
	D_ASSERT(CastTo<Component*>(dirLight) != nullptr);
	D_ASSERT(CastTo<ServerComponent*>(dirLight) != nullptr);
	D_ASSERT(CastTo<PlainComponent*>(dirLight) == nullptr);

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

	auto dclass = dObjectConst->GetDClass();
}
