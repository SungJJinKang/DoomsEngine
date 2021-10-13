#include "CharacterSpawner.h"
#include "Rendering/Renderer/MeshRenderer.h"
#include "Graphics/Buffer/Mesh.h"
#include "Game/AssetManager/AssetManager.h"

#include "../IO/UserInput_Server.h"

void doom::CharacterSpawner::CreateEnemy(const math::Vector3& position)
{
	auto currenScene = doom::Scene::GetCurrentWorld();
	auto newEntity = currenScene->CreateNewEntity();
	newEntity->GetTransform()->SetPosition(position);

	D_ASSERT(mBillboardShader != nullptr);
	auto material = new graphics::Material(mBillboardShader);
	material->AddTexture(graphics::eTextureBindingPoint::AlbedoTexture, assetimporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("Enemy1.dds"));


	auto meshRenderer = newEntity->AddComponent<MeshRenderer>();
	meshRenderer->SetMesh(graphics::Mesh::GetQuadMesh().get());
	meshRenderer->SetMaterial(material);

	
}

void doom::CharacterSpawner::InitComponent()
{
	if (mBillboardShader == nullptr)
	{
		mBillboardShader = assetimporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("Billboard.glsl");
	}
}

void doom::CharacterSpawner::UpdateComponent()
{
	if (UserInput_Server::GetKeyUp(userinput::eKEY_CODE::KEY_9))
	{
		auto tr = GetTransform();

		CreateEnemy(tr->GetPosition() + tr->forward() * 2);
	}
}
