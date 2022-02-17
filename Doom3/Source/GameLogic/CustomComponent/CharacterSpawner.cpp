#include "CharacterSpawner.h"
#include "Rendering/Renderer/MeshRenderer.h"
#include "Rendering/Buffer/Mesh.h"
#include "Asset/AssetManager/AssetManager.h"
#include "../IO/UserInput_Server.h"
#include "Rendering/Buffer/MeshHelper.h"

void dooms::CharacterSpawner::CreateEnemy(const math::Vector3& position)
{
	auto currenScene = dooms::Scene::GetCurrentWorld();
	auto newEntity = currenScene->CreateNewEntity();
	newEntity->GetTransform()->SetPosition(position);

	D_ASSERT(mBillboardShader != nullptr);
	auto material = dooms::CreateDObject<graphics::Material>(mBillboardShader);
	material->AddTexture(graphics::eTextureBindingPoint::AlbedoTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("Enemy1.dds"));


	auto meshRenderer = newEntity->AddComponent<MeshRenderer>();
	meshRenderer->SetMesh(graphics::meshHelper::GetQuadMesh());
	meshRenderer->SetMaterial(material);

	
}

void dooms::CharacterSpawner::InitComponent()
{
	if (mBillboardShader == nullptr)
	{
		mBillboardShader = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("Billboard.glsl");
	}
}

void dooms::CharacterSpawner::UpdateComponent()
{
	if (UserInput_Server::GetKeyUp(dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_9))
	{
		auto tr = GetTransform();

		CreateEnemy(tr->GetPosition() + tr->forward() * 2);
	}
}
