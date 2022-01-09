#include "BoxAdder.h"

#include <Rendering/Renderer/MeshRenderer.h>
#include <PhysicsComponent/BoxCollider3D.h>
#include <Asset/ThreeDModelAsset.h>

void dooms::BoxAdder::InitComponent()
{
}

void dooms::BoxAdder::UpdateComponent()
{
	if (dooms::userinput::UserInput_Server::GetKeyUp(dooms::graphics::GraphicsAPIInput::eKEY_CODE::KEY_F4))
	{
		auto currenScene = dooms::Scene::GetCurrentWorld();
		auto entity = currenScene->CreateNewEntity();
		entity->GetTransform()->SetScale(1.5f, 1.5f, 1.5f);
		entity->GetTransform()->SetPosition(dooms::random::Random::RandomFloatNumber(-500.0f, 500.0f), dooms::random::Random::RandomFloatNumber(-500.0f, 500.0f), dooms::random::Random::RandomFloatNumber(-500.0f, 500.0f));
		auto meshRenderer = entity->AddComponent<MeshRenderer>();

		auto planetAsset = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>("planet.assbin");

		meshRenderer->SetMesh(planetAsset->GetMesh(0));

		auto threedasset = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::THREE_D_MODEL>("cerberus.assbin");
		auto shader = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("GbufferWriter_PBR.glsl");
		auto material = new graphics::Material(shader);
		material->AddTexture(graphics::eTextureBindingPoint::AlbedoTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_A.dds"));
		material->AddTexture(graphics::eTextureBindingPoint::NormalTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_N.dds"));
		material->AddTexture(graphics::eTextureBindingPoint::MetalnessTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_M.dds"));
		material->AddTexture(graphics::eTextureBindingPoint::RoughnessTexture, assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::TEXTURE>("cerberus_R.dds"));

		meshRenderer->SetMaterial(material);
		BoxCollider3D* box3D = entity->AddComponent<BoxCollider3D>();
		box3D->SetFromAABB3D(planetAsset->GetMesh(0)->GetBoundingBox());
	}
	
}

void dooms::BoxAdder::OnEndOfFrame_Component()
{
}
