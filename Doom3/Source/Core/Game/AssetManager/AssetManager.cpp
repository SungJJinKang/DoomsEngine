#include "AssetManager.h"

#include <iterator>

#include "../IO/AssetImporter/AssetImporter.h"
#include "../../Helper/ForLoop_Compile_Time/ForLoop_Compile.h"
#include "AssetImporter/AssetApiImporter.h"


using namespace doom::assetimporter;

bool AssetManager::CheckFileIsValidAssetFile(const std::filesystem::directory_entry& entry)
{
	return entry.is_regular_file() == true;
}

void AssetManager::GetWaitingImportFuture()
{
	for (auto& future : this->mWaitingImportFuture)
	{
		future.get();
	}
}

void doom::assetimporter::AssetManager::Init()
{

}

void doom::assetimporter::AssetManager::Update()
{

}

void doom::assetimporter::AssetManager::OnEndOfFrame()
{
}




void doom::assetimporter::AssetManager::ImportEntireAsset()
{
	CHECK_IS_EXECUTED_ON_MAIN_THREAD;

	std::filesystem::path lastEntryPath{};

	std::array<std::vector<std::filesystem::path>, ::doom::asset::ENUM_ASSETTYPE_COUNT> entireAssetPaths{};
	/// <summary>
	/// Check file extension
	/// </summary>
	for (const auto& entry : std::filesystem::recursive_directory_iterator(AssetFolderPath))
	{
		if (CheckFileIsValidAssetFile(entry)== false)
		{
			continue; // if directory if folder, continue
		}

		std::filesystem::path currentEntryPath = entry.path();
		std::optional<::doom::asset::eAssetType> optionalAssetType = Assetimporter::GetAssetType(currentEntryPath);

	
		
		if (optionalAssetType.has_value())
		{
			std::string extension = currentEntryPath.extension().string();
			::doom::asset::eAssetType assetType = optionalAssetType.value();

			// same file name with difference extension will be iterated sequentially
			// if Non-In Build Extension come first
			// push Non-In Build Extension and if next directory has same filename and it have In-Build Extension.
			// then pop_back vector before pusing In-Build Extension file
			//
			// if In Build Extension come first, next direcoty compare filename with vector's last element
			// And If file name is same, ignore Not-In Build Extension file

			auto iter = Assetimporter::AssetInBuildExtension.find(assetType);
			if (iter != Assetimporter::AssetInBuildExtension.end())
			{// if There is In-Build Extension of File's AssetType, 

				if (extension == iter->second)
				{// if current file is In-Build Extension
					while (true)
					{//iter from last to first for removing files with same file name with current file name
						if (entireAssetPaths[static_cast<unsigned int>(assetType)].size() > 0 && entireAssetPaths[static_cast<unsigned int>(assetType)].back().stem() == currentEntryPath.stem())
						{// if Already stored path's  last element file name is same with current file name
							entireAssetPaths[static_cast<unsigned int>(assetType)].pop_back();
						}
						else
						{
							break;
						}
					}
				}
				else
				{// if current file is not(!!) In-Build Extension
					if (entireAssetPaths[static_cast<unsigned int>(assetType)].size() > 0 && entireAssetPaths[static_cast<unsigned int>(assetType)].back().stem() == currentEntryPath.stem())
					{// if Already stored path's last element have same file name with current file name
						continue; // ignore current file
					}
				}
			}

			entireAssetPaths[static_cast<unsigned int>(assetType)].push_back(std::move(currentEntryPath));
		}
		
	}

	//TODO : 시간 많이 안걸리는 text타입같은거는 굳이 thread에 맞길 필요없다 오히려 더 느림, 사이즈 작은건 그냥 메인 스레드에서 처리하자.
	//->원래는 메인스레드가 get future하면서 거의 노는데 이렇게 하면 메인스레드도 열심히 일 돌릴 수 있다.


	//push stored paths to AssetManager::AssetPaths
	for (size_t i = 0; i < entireAssetPaths.size(); ++i)
	{
		AssetManager::AssetPaths[i].insert(AssetManager::AssetPaths[i].end(), entireAssetPaths[i].begin(), entireAssetPaths[i].end());
	}
	
		
	{
		ForLoop_CompileTime<::doom::asset::eAssetType>::Loop<::doom::asset::FIRST_ENUM_ASSETTYPE_VALUE, ::doom::asset::LAST_ENUM_ASSETTYPE_VALUE, eConditionType::LE, 1, ImportAssetInitSetting>();
		ForLoop_CompileTime<::doom::asset::eAssetType>::Loop<::doom::asset::FIRST_ENUM_ASSETTYPE_VALUE, ::doom::asset::LAST_ENUM_ASSETTYPE_VALUE, eConditionType::LE, 1, ImportAssetFunctor>(entireAssetPaths);
		this->GetWaitingImportFuture();

	}
	ForLoop_CompileTime<::doom::asset::eAssetType>::Loop<::doom::asset::FIRST_ENUM_ASSETTYPE_VALUE, ::doom::asset::LAST_ENUM_ASSETTYPE_VALUE, eConditionType::LE, 1, OnEndImportInMainThreadFunctor>();
	doom::assetimporter::ClearAllApiImporterQueue();
	
}



const std::array<std::vector<std::filesystem::path>, doom::asset::ENUM_ASSETTYPE_COUNT>& AssetManager::GetAllAssetPath()
{
	return this->AssetPaths;
}

