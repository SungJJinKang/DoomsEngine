#define STB_IMAGE_IMPLEMENTATION
#include "AssetImporterBase.h"

#include <map>
#include <string>

#include "../../Core.h"

using namespace Doom;

template <AssetType assetType>
ApiImporter<assetType>::~ApiImporter()
{
	if constexpr (!std::is_same_v<ApiImporterTypeConditional_t<assetType>, DummyApiImporter>)
	{
		assetImporter->ReleaseMultithreadApiImporter(importer);
	}

}

//template <Doom::AssetType assetType>
//std::function<bool(const std::filesystem::path&, Doom::AssetImporter::AssetTypeConditional_t<assetType>&, unsigned int&, unsigned int&)> ThreadImport = std::bind(&Doom::AssetImporter::ImportAsset<assetType>, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
const DummyApiImporter dummyApiImporter{};

const std::map<std::string, AssetType> AssetExtension
{
	//3D Model Asset Formats
	{"dae", Doom::AssetType::THREE_D_MODELL},
	{"blend", Doom::AssetType::THREE_D_MODELL},
	{"bvh", Doom::AssetType::THREE_D_MODELL},
	{"3ds", Doom::AssetType::THREE_D_MODELL},
	{"ase", Doom::AssetType::THREE_D_MODELL},
	{"obj", Doom::AssetType::THREE_D_MODELL},
	{"glFT", Doom::AssetType::THREE_D_MODELL},
	{"ply", Doom::AssetType::THREE_D_MODELL},
	{"dxf", Doom::AssetType::THREE_D_MODELL},
	{"ifc", Doom::AssetType::THREE_D_MODELL},
	{"nff", Doom::AssetType::THREE_D_MODELL},
	{"smd", Doom::AssetType::THREE_D_MODELL},
	{"vta", Doom::AssetType::THREE_D_MODELL},
	{"mdl", Doom::AssetType::THREE_D_MODELL},
	{"mdl2", Doom::AssetType::THREE_D_MODELL},
	{"mdl3", Doom::AssetType::THREE_D_MODELL},
	{"pk3", Doom::AssetType::THREE_D_MODELL},
	{"mdmdcl2", Doom::AssetType::THREE_D_MODELL},
	{"md5mesh", Doom::AssetType::THREE_D_MODELL},
	{"md5anim", Doom::AssetType::THREE_D_MODELL},
	{"md5camera ", Doom::AssetType::THREE_D_MODELL},
	{"q3o", Doom::AssetType::THREE_D_MODELL},
	{"q3s", Doom::AssetType::THREE_D_MODELL},
	{"raw", Doom::AssetType::THREE_D_MODELL},
	{"ac", Doom::AssetType::THREE_D_MODELL},
	{"stl", Doom::AssetType::THREE_D_MODELL},
	{"dxf", Doom::AssetType::THREE_D_MODELL},
	{"irrmesh", Doom::AssetType::THREE_D_MODELL},
	{"irr", Doom::AssetType::THREE_D_MODELL},
	{"off", Doom::AssetType::THREE_D_MODELL},
	{"dterxf", Doom::AssetType::THREE_D_MODELL},
	{"mdl", Doom::AssetType::THREE_D_MODELL},
	{"hmp", Doom::AssetType::THREE_D_MODELL},
	{"mesh", Doom::AssetType::THREE_D_MODELL},
	{"skeleton", Doom::AssetType::THREE_D_MODELL},
	{"material", Doom::AssetType::THREE_D_MODELL},
	{"ms3d", Doom::AssetType::THREE_D_MODELL},
	{"lwo", Doom::AssetType::THREE_D_MODELL},
	{"lws", Doom::AssetType::THREE_D_MODELL},
	{"lxo", Doom::AssetType::THREE_D_MODELL},
	{"csm", Doom::AssetType::THREE_D_MODELL},
	{"ply", Doom::AssetType::THREE_D_MODELL},
	{"cob", Doom::AssetType::THREE_D_MODELL},
	{"scn", Doom::AssetType::THREE_D_MODELL},

	//////////////////////////////////////////////////////////////////////////

	{"txt", Doom::AssetType::TEXT},
	{"glsl", Doom::AssetType::TEXT},
	{"ini", Doom::AssetType::TEXT},

};

template <AssetType assetType>
AssetImporter<assetType>::AssetImporter(size_t threadPoolSize) : threadPool{ threadPoolSize }, ApiImporters{}, apiImporterMutex{}, ImporterQueue{}
{
	ApiImporters = new ApiImporterType[threadPoolSize];
	for (size_t i = 0; i < threadPool.PoolSize; i++)
	{
		this->InitApiImporter(ApiImporters[i]);

		ImporterQueue.push(&ApiImporters[i]);
	}

}

template <AssetType assetType>
AssetImporter<assetType>::~AssetImporter()
{
	this->threadPool.TerminateThreadPool();
}

template <AssetType assetType>
ApiImporter<assetType> AssetImporter<assetType>::GetMultithreadApiImporter()
{
	if constexpr (!std::is_same_v<ApiImporterTypeConditional_t<assetType>, DummyApiImporter>)
	{
		auto lck = std::scoped_lock(apiImporterMutex);

		ApiImporterType* importer{};
		if (this->ImporterQueue.empty())
		{
			DEBUG_LOG("Create New ApiImporter");
			importer = new ApiImporterTypeConditional_t<assetType>();
		}
		else
		{
			importer = this->ImporterQueue.front();
			ImporterQueue.pop();
		}

		return { this, importer };
	}
	else
	{
		return { this, &dummyApiImporter };
	}
}

template <AssetType assetType>
void AssetImporter<assetType>::ReleaseMultithreadApiImporter(ApiImporterType* apiImporterType)
{
	if constexpr (!std::is_same_v<ApiImporterTypeConditional_t<assetType>, DummyApiImporter>)
	{
		auto lck = std::scoped_lock(apiImporterMutex);
		this->ImporterQueue.push(apiImporterType);
	}
	else
	{
		return;
	}
}

template <AssetType assetType>
std::optional<AssetTypeConditional_t<assetType>> AssetImporter<assetType>::ImportAsset(const std::filesystem::path& path)
{
	if (path.has_extension())
	{
		auto extension = path.extension().string();
		try
		{
			if (AssetExtension.at(extension.substr(1, extension.length() - 1)) == assetType)
			{
				return AssetImporter<assetType>::ReadAssetFile(path, this);
			}
		}
		catch (std::out_of_range& e)
		{
			DEBUG_LOG({ "Can't Find proper extension : ", extension });
		}
		catch (...)
		{
			DEBUG_LOG("Can't import asset");
		}
	}

	return {};

}

template <AssetType assetType>
std::optional<std::future<std::optional<AssetTypeConditional_t<assetType>>>> AssetImporter<assetType>::ImportAssetAsync(const std::filesystem::path& path)
{
	if (path.has_extension())
	{
		auto extension = path.extension().string();
		try
		{
			if (AssetExtension.at(extension.substr(1, extension.length() - 1)) == assetType)
			{
				std::function<std::optional<AssetTypeConditional_t<assetType>>()> newTask = std::bind(&AssetImporter<assetType>::ReadAssetFile, this, path, this);
				return this->threadPool.AddTask(std::move(newTask));
			}
		}
		catch (const std::out_of_range& e)
		{
			DEBUG_LOG({ "Can't Find proper extension : ", extension });
		}
		catch (...)
		{
			DEBUG_LOG("Can't import asset");
		}
	}

	return {};
}

template <AssetType assetType>
std::vector<std::optional<AssetTypeConditional_t<assetType>>> AssetImporter<assetType>::ImportAsset(const std::vector<std::filesystem::path>& paths)
{

	std::vector<std::optional<AssetTypeConditional_t<assetType>>> Assets{};

	for (auto& path : paths)
	{
		if (path.has_extension())
		{
			auto extension = path.extension().string();
			try
			{
				if (AssetExtension.at(extension.substr(1, extension.length() - 1)) == assetType)
				{
					Assets.push_back(AssetImporter<assetType>::ReadAssetFile(path, this));
					continue;
				}
			}
			catch (std::out_of_range& e)
			{
				DEBUG_LOG({ "Can't Find proper extension : ", extension });
			}
			catch (...)
			{
				DEBUG_LOG({ "Undefined Error : ", extension });
			}
		}
		else
		{
			DEBUG_LOG({ path.string(), " : Doesn't have file extension" });
		}
		DEBUG_LOG({ "Fail To ImportAsset", path.string() });
		Assets.push_back({});

	}


	return Assets;
}

template <AssetType assetType>
std::vector<std::future<std::optional<AssetTypeConditional_t<assetType>>>> AssetImporter<assetType>::ImportAssetAsync(const std::vector<std::filesystem::path>& paths)
{

	std::vector<std::function<std::optional<AssetTypeConditional_t<assetType>>()>> Tasks{};

	for (auto& path : paths)
	{
		if (path.has_extension())
		{
			auto extension = path.extension().string();
			try
			{
				if (AssetExtension.at(extension.substr(1, extension.length() - 1)) == assetType)
				{
					Tasks.push_back(std::bind(&AssetImporter<assetType>::ReadAssetFile, this, path, this));
					continue;
				}
			}
			catch (std::out_of_range& e)
			{
				DEBUG_LOG({ "Can't Find proper extension : ", extension });
			}
			catch (...)
			{
				DEBUG_LOG({ "Undefined Error : ", extension });
			}
		}
		else
		{
			DEBUG_LOG({ path.string(), " : Doesn't have file extension" });
		}
		DEBUG_LOG({ "Fail To ImportAsset", path.string() });
		Tasks.push_back(std::bind(&AssetImporter<assetType>::Dummy, this));

	}

	/// <summary>
	/// maybe will be copied
	/// </summary>
	/// <param name="paths"></param>
	/// <returns></returns>
	return this->threadPool.AddTaskChunk(Tasks);
}

AssetType Doom::GetAssetType(const std::filesystem::path& path)
{
	if (path.has_extension())
	{
		auto extension = path.extension().string();
		try
		{
			return AssetExtension.at(extension.substr(1, extension.length() - 1));

		}
		catch (...)
		{
			return AssetType::NONE;
		}
	}

	return AssetType::NONE;
}