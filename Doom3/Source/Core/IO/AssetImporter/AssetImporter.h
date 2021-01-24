#pragma once
#include <optional>
#include <map>
#include <string>
#include <functional>

#include "../../Core.h"

#include "../../Asset/Asset.h"

#include "AssetApiImporter.h"
#include "AssetImporterWorker.h"

namespace Doom
{
	namespace AssetImporter
	{
		const inline std::map<std::string, Doom::Asset::AssetType> AssetExtension
		{
			//3D Model Asset Formats
			{"dae", Doom::Asset::AssetType::THREE_D_MODEL},
			{"blend", Doom::Asset::AssetType::THREE_D_MODEL},
			{"bvh", Doom::Asset::AssetType::THREE_D_MODEL},
			{"3ds", Doom::Asset::AssetType::THREE_D_MODEL},
			{"ase", Doom::Asset::AssetType::THREE_D_MODEL},
			{"obj", Doom::Asset::AssetType::THREE_D_MODEL},
			{"glFT", Doom::Asset::AssetType::THREE_D_MODEL},
			{"ply", Doom::Asset::AssetType::THREE_D_MODEL},
			{"dxf", Doom::Asset::AssetType::THREE_D_MODEL},
			{"ifc", Doom::Asset::AssetType::THREE_D_MODEL},
			{"nff", Doom::Asset::AssetType::THREE_D_MODEL},
			{"smd", Doom::Asset::AssetType::THREE_D_MODEL},
			{"vta", Doom::Asset::AssetType::THREE_D_MODEL},
			{"mdl", Doom::Asset::AssetType::THREE_D_MODEL},
			{"mdl2", Doom::Asset::AssetType::THREE_D_MODEL},
			{"mdl3", Doom::Asset::AssetType::THREE_D_MODEL},
			{"pk3", Doom::Asset::AssetType::THREE_D_MODEL},
			{"mdmdcl2", Doom::Asset::AssetType::THREE_D_MODEL},
			{"md5mesh", Doom::Asset::AssetType::THREE_D_MODEL},
			{"md5anim", Doom::Asset::AssetType::THREE_D_MODEL},
			{"md5camera ", Doom::Asset::AssetType::THREE_D_MODEL},
			{"q3o", Doom::Asset::AssetType::THREE_D_MODEL},
			{"q3s", Doom::Asset::AssetType::THREE_D_MODEL},
			{"raw", Doom::Asset::AssetType::THREE_D_MODEL},
			{"ac", Doom::Asset::AssetType::THREE_D_MODEL},
			{"stl", Doom::Asset::AssetType::THREE_D_MODEL},
			{"dxf", Doom::Asset::AssetType::THREE_D_MODEL},
			{"irrmesh", Doom::Asset::AssetType::THREE_D_MODEL},
			{"irr", Doom::Asset::AssetType::THREE_D_MODEL},
			{"off", Doom::Asset::AssetType::THREE_D_MODEL},
			{"dterxf", Doom::Asset::AssetType::THREE_D_MODEL},
			{"mdl", Doom::Asset::AssetType::THREE_D_MODEL},
			{"hmp", Doom::Asset::AssetType::THREE_D_MODEL},
			{"mesh", Doom::Asset::AssetType::THREE_D_MODEL},
			{"skeleton", Doom::Asset::AssetType::THREE_D_MODEL},
			{"material", Doom::Asset::AssetType::THREE_D_MODEL},
			{"ms3d", Doom::Asset::AssetType::THREE_D_MODEL},
			{"lwo", Doom::Asset::AssetType::THREE_D_MODEL},
			{"lws", Doom::Asset::AssetType::THREE_D_MODEL},
			{"lxo", Doom::Asset::AssetType::THREE_D_MODEL},
			{"csm", Doom::Asset::AssetType::THREE_D_MODEL},
			{"ply", Doom::Asset::AssetType::THREE_D_MODEL},
			{"cob", Doom::Asset::AssetType::THREE_D_MODEL},
			{"scn", Doom::Asset::AssetType::THREE_D_MODEL},
			{"fbx", Doom::Asset::AssetType::THREE_D_MODEL},
			//////////////////////////////////////////////////////////////////////////

			{"txt", Doom::Asset::AssetType::TEXT},
			{"ini", Doom::Asset::AssetType::TEXT},

			/////////////////////////////////////////////////////

			{"glsl", Doom::Asset::AssetType::SHADER},

			/////////////////////////////////////////////////////////

			{"jpg", Doom::Asset::AssetType::TEXTURE},
			{"jpeg", Doom::Asset::AssetType::TEXTURE},
			{"png", Doom::Asset::AssetType::TEXTURE},
			{"bmp", Doom::Asset::AssetType::TEXTURE},
			{"psd", Doom::Asset::AssetType::TEXTURE},
			{"tga", Doom::Asset::AssetType::TEXTURE},
			{"hdr", Doom::Asset::AssetType::TEXTURE},
			{"pic", Doom::Asset::AssetType::TEXTURE},
			{"pnm", Doom::Asset::AssetType::TEXTURE},
		};

		

		
		template <Asset::AssetType assetType>
		using imported_asset_future_t = typename std::future<std::optional<Asset::asset_type_t<assetType>>>;

		class Assetimporter
		{
		private:
			static inline std::unique_ptr<::ThreadPool> threadPool{};

			static void InitializeThreadPool(size_t poolSize);
		public:

			Assetimporter(size_t poolSize);
			~Assetimporter();
			static const std::unique_ptr<::ThreadPool>& GetThreadPool();
			static bool IsThreadPoolInitialized();


			/// <summary>
			/// Import A Asset Asyncly
			/// You Should check path extension using GetAssetType function
			/// </summary>
			/// <param name="path"></param>
			/// <returns></returns>
			template <Asset::AssetType assetType>
			[[nodiscard]] static imported_asset_future_t<assetType> ImportAsset(const std::filesystem::path& path)
			{
				D_ASSERT(static_cast<bool>(threadPool) != false, "Create Assetimporter instance before call ImportAsset");

				std::function<std::optional<Asset::asset_type_t<assetType>>()> newTask = std::bind(ReadAssetFile<assetType>, path);

				DEBUG_LOG("Add new task to threadpool");
				return threadPool->AddTask(std::move(newTask));
			}



			/// <summary>
			/// Import A Asset Asyncly
			/// If you need import multiple assets, use this function
			/// You Should check path extension using GetAssetType function
			/// </summary>
			/// <param name="path"></param>
			/// <param name="assets"></param>
			/// <returns></returns>
			template <Asset::AssetType assetType>
			[[nodiscard]] static std::vector<imported_asset_future_t<assetType>> ImportAsset(const std::vector<std::filesystem::path>& paths)
			{
				D_ASSERT(static_cast<bool>(threadPool) != false, "Create Assetimporter instance before call ImportAsset");

				std::vector<std::function<std::optional<Asset::asset_type_t<assetType>>()>> Tasks{};
				Tasks.reserve(paths.size());
				for (auto& path : paths)
				{
					Tasks.push_back(std::bind(ReadAssetFile<assetType>, path));
				}

				DEBUG_LOG("Add new task to threadpool");
				/// <summary>
				/// maybe will be copied
				/// </summary>
				/// <param name="paths"></param>
				/// <returns></returns>
				return threadPool->AddTaskChunk(std::move(Tasks));
			}

			///////////////////

			
		};

		std::optional<Doom::Asset::AssetType> GetAssetType(const std::filesystem::path& path);
	}
}
