#pragma once
#include <type_traits>
#include <thread>
#include <array>
#include <queue>
#include <future>
#include <filesystem>
#include <atomic>

#include "../Core.h"
#include "../Asset/Asset.h"
#include "../Asset/AudioAsset.h"
#include "../Asset/FontAsset.h"
#include "../Asset/TextureAsset.h"
#include "../Asset/ThreeDModelAsset.h"

#include "../API/ASSIMP.h"

#define MAX_IMPORTER_THREAD_COUNT 5

namespace Doom
{
	std::atomic<unsigned int> CurrentThreadCount;

	/// <summary>
	/// If Every Thread is being used, main thread wait
	/// </summary>
	/// <typeparam name="AssetType"></typeparam>
	template <typename AssetType, int MaxThreadCount>
	class AssetImporterThreading
	{
		static_assert(std::is_base_of_v<Asset, AssetType>, "Please Pass Type of Asset class");

		
		/*
		static AssetType ImportAssetAsyncly(std::function<AssetType(std::filesystem::path)> importer)
		{
			/// <summary>
			/// Wait Until CurrentThreadCount become less than MaxThreadCount
			/// </summary>
			/// <param name="importer"></param>
			/// <returns></returns>
			while (CurrentThreadCount < MaxThreadCount);

			//

		}

		static std::future<AssetType> WaitAsset(std::function < AssetType(std::filesystem::path))
		{

		}
		*/
	};

	template <int MaxThreadCount>
	class AssetImporterThreading<ThreeDModelAsset, MaxThreadCount>
	{


	};

}