#include "BoxAdder.h"

#include <Rendering/Renderer/MeshRenderer.h>
#include <PhysicsComponent/BoxCollider3D.h>
#include <Asset/ThreeDModelAsset.h>

void doom::BoxAdder::InitComponent()
{
}

void doom::BoxAdder::UpdateComponent()
{
	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F4))
	{
		auto currenScene = doom::Scene::GetCurrentWorld();
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetScale(1.5f, 1.5f, 1.5f);
		entity->GetTransform()->SetPosition(doom::random::Random::RandomFloatNumber(-500.0f, 500.0f), doom::random::Random::RandomFloatNumber(-500.0f, 500.0f), doom::random::Random::RandomFloatNumber(-500.0f, 500.0f));
		auto meshRenderer = entity->AddComponent<MeshRenderer>();

		auto planetAsset = assetimporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>("planet.assbin");

		meshRenderer->SetMesh(planetAsset->GetMesh(0));

		auto threedasset = assetimporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>("cerberus.assbin");
		auto shader = assetimporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("GbufferWriter_PBR.glsl");
		auto material = new graphics::Material(shader);
		material->AddTexture(graphics::eTextureBindingPoint::AlbedoTexture, assetimporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_A.dds"));
		material->AddTexture(graphics::eTextureBindingPoint::NormalTexture, assetimporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_N.dds"));
		material->AddTexture(graphics::eTextureBindingPoint::MetalnessTexture, assetimporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_M.dds"));
		material->AddTexture(graphics::eTextureBindingPoint::RoughnessTexture, assetimporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_R.dds"));

		meshRenderer->SetMaterial(material);
		BoxCollider3D* box3D = entity->AddComponent<BoxCollider3D>();
		box3D->SetFromAABB3D(planetAsset->GetMesh(0)->GetBoundingBox());
	}
	
}

void doom::BoxAdder::OnEndOfFrame_Component()
{
}
