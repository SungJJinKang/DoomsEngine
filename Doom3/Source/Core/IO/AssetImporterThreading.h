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


namespace Doom
{
	std::atomic<unsigned int> CurrentThreadCount;

	/// <summary>
	/// If Every Thread is being used, main thread wait
	/// </summary>
	/// <typeparam name="AssetType"></typeparam>
	class AssetImporterThreading
	{
		

		
		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="AssetType"></typeparam>
		/// <param name="paths"></param>
		/// <param name="IsCompleted">If Importing is completed, this should be set true ( even if Import asset fail, this value should be set true for notifying to mainthread</param>
		/// <param name=""></param>
		/// <returns></returns>
		template <typename AssetClassType>
		static void ImportAssetAsyncly(std::atomic<unsigned int>& extraThreaCount, std::atomic<unsigned int>& NumOfCompoletedImportingWork, std::filesystem::path& paths, AssetClassType& asset)
		{
			static_assert(std::is_base_of_v<Asset, AssetClassType>, "Please Pass Type of Asset class");
		
			//if import is finished, plus one to extraThreaCount, NumOfCompoletedImportingWork
		}

		template <>
		static void ImportAssetAsyncly<ThreeDModelAsset>(std::atomic<unsigned int>& extraThreaCount, std::atomic<unsigned int>& NumOfCompoletedImportingWork, std::filesystem::path& paths, ThreeDModelAsset& asset)
		{
			//if import is finished, plus one to extraThreaCount, NumOfCompoletedImportingWork




			*IsCompleted = true;
		};
		
	};

	

}