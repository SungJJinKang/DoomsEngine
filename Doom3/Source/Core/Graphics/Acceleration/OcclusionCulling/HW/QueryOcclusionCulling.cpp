#include "QueryOcclusionCulling.h"

#include <API/OpenglAPI.h>
#include "Game/AssetManager/AssetManager.h"


void doom::graphics::QueryOcclusionCulling::InitHWOcclusionCulling()
{
	glGenQueries(1, &(this->mQueryID));

	auto occluderMaterial = doom::assetimporter::AssetManager::GetAsset<asset::eAssetType::SHADER>(OCCLUDER_MATERIAL);
	this->mOccluderMaterial = std::make_unique<Material>(occluderMaterial);
}

void doom::graphics::QueryOcclusionCulling::StartQuery()
{
	D_ASSERT(this->mQueryID != 0);
	glBeginQuery(GL_SAMPLES_PASSED, this->mQueryID);
	glBeginQuery(GL_ANY_SAMPLES_PASSED, this->mQueryID);
	//glBeginQuery(GL_ANY_SAMPLES_PASSED_CONSERVATIVE, this->mQueryID);
}

void doom::graphics::QueryOcclusionCulling::StopQuery()
{
	glEndQuery(this->mQueryID);
}

void doom::graphics::QueryOcclusionCulling::DrawOccluders()
{

}

void doom::graphics::QueryOcclusionCulling::StartConditionalRender()
{
	glBeginConditionalRender(this->mQueryID, GL_QUERY_WAIT); 
	// Test GL_QUERY_WAIT vs GL_QUERY_NO_WAIT
	// don't wait until query complete. if query isn't completed just draw it normally
		
}

void doom::graphics::QueryOcclusionCulling::StopConditionalRender()
{
	glEndConditionalRender();
}

void doom::graphics::QueryOcclusionCulling::BakeOccludersData(const std::vector<Renderer*>& occuluderList, float minimumOccluderBoxSize)
{

}


void doom::graphics::QueryOcclusionCulling::LoadOccludersData(const char* vertexDatas)
{

}

void doom::graphics::QueryOcclusionCulling::QueryOccluderData()
{
	this->StartQuery();
	this->DrawOccluders();
	this->StopQuery();
}

