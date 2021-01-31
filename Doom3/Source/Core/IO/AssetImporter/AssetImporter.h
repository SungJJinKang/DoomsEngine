#pragma once
#include <optional>
#include <map>
#include <string>
#include <functional>

#include "../../Core.h"

#include "../../Asset/Asset.h"

#include "AssetApiImporter.h"
#include "AssetImporterWorker.h"

#define THREADPOOL_DEBUG
#include "../../../Helper/ThreadPool_Cpp/ThreadPool.h"

namespace doom
{
	namespace assetimporter
	{
		const inline std::map<std::string, doom::Asset::eAssetType> AssetExtension
		{
			//3D Model Asset Formats
			{".dae", doom::Asset::eAssetType::THREE_D_MODEL},
			{".blend", doom::Asset::eAssetType::THREE_D_MODEL},
			{".bvh", doom::Asset::eAssetType::THREE_D_MODEL},
			{".3ds", doom::Asset::eAssetType::THREE_D_MODEL},
			{".ase", doom::Asset::eAssetType::THREE_D_MODEL},
			{".obj", doom::Asset::eAssetType::THREE_D_MODEL},
			{".glFT", doom::Asset::eAssetType::THREE_D_MODEL},
			{".ply", doom::Asset::eAssetType::THREE_D_MODEL},
			{".dxf", doom::Asset::eAssetType::THREE_D_MODEL},
			{".ifc", doom::Asset::eAssetType::THREE_D_MODEL},
			{".nff", doom::Asset::eAssetType::THREE_D_MODEL},
			{".smd", doom::Asset::eAssetType::THREE_D_MODEL},
			{".vta", doom::Asset::eAssetType::THREE_D_MODEL},
			{".mdl", doom::Asset::eAssetType::THREE_D_MODEL},
			{".mdl2", doom::Asset::eAssetType::THREE_D_MODEL},
			{".mdl3", doom::Asset::eAssetType::THREE_D_MODEL},
			{".pk3", doom::Asset::eAssetType::THREE_D_MODEL},
			{".mdmdcl2", doom::Asset::eAssetType::THREE_D_MODEL},
			{".md5mesh", doom::Asset::eAssetType::THREE_D_MODEL},
			{".md5anim", doom::Asset::eAssetType::THREE_D_MODEL},
			{".md5camera ", doom::Asset::eAssetType::THREE_D_MODEL},
			{".q3o", doom::Asset::eAssetType::THREE_D_MODEL},
			{".q3s", doom::Asset::eAssetType::THREE_D_MODEL},
			{".raw", doom::Asset::eAssetType::THREE_D_MODEL},
			{".ac", doom::Asset::eAssetType::THREE_D_MODEL},
			{".stl", doom::Asset::eAssetType::THREE_D_MODEL},
			{".dxf", doom::Asset::eAssetType::THREE_D_MODEL},
			{".irrmesh", doom::Asset::eAssetType::THREE_D_MODEL},
			{".irr", doom::Asset::eAssetType::THREE_D_MODEL},
			{".off", doom::Asset::eAssetType::THREE_D_MODEL},
			{".dterxf", doom::Asset::eAssetType::THREE_D_MODEL},
			{".mdl", doom::Asset::eAssetType::THREE_D_MODEL},
			{".hmp", doom::Asset::eAssetType::THREE_D_MODEL},
			{".mesh", doom::Asset::eAssetType::THREE_D_MODEL},
			{".skeleton", doom::Asset::eAssetType::THREE_D_MODEL},
			{".material", doom::Asset::eAssetType::THREE_D_MODEL},
			{".ms3d", doom::Asset::eAssetType::THREE_D_MODEL},
			{".lwo", doom::Asset::eAssetType::THREE_D_MODEL},
			{".lws", doom::Asset::eAssetType::THREE_D_MODEL},
			{".lxo", doom::Asset::eAssetType::THREE_D_MODEL},
			{".csm", doom::Asset::eAssetType::THREE_D_MODEL},
			{".ply", doom::Asset::eAssetType::THREE_D_MODEL},
			{".cob", doom::Asset::eAssetType::THREE_D_MODEL},
			{".scn", doom::Asset::eAssetType::THREE_D_MODEL},
			{".fbx", doom::Asset::eAssetType::THREE_D_MODEL},
			//////////////////////////////////////////////////////////////////////////

			{".txt", doom::Asset::eAssetType::TEXT},
			{".ini", doom::Asset::eAssetType::TEXT},

			/////////////////////////////////////////////////////

			{".glsl", doom::Asset::eAssetType::SHADER},

			/////////////////////////////////////////////////////////

			{".jpg", doom::Asset::eAssetType::TEXTURE},
			{".jpeg", doom::Asset::eAssetType::TEXTURE},
			{".png", doom::Asset::eAssetType::TEXTURE},
			{".bmp", doom::Asset::eAssetType::TEXTURE},
			{".psd", doom::Asset::eAssetType::TEXTURE},
			{".tga", doom::Asset::eAssetType::TEXTURE},
			{".hdr", doom::Asset::eAssetType::TEXTURE},
			{".pic", doom::Asset::eAssetType::TEXTURE},
			{".pnm", doom::Asset::eAssetType::TEXTURE},
		};

		

		
		template <Asset::eAssetType assetType>
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
			template <Asset::eAssetType assetType>
			[[nodiscard]] static imported_asset_future_t<assetType> ImportAsset(const std::filesystem::path& path)
			{
				D_ASSERT(static_cast<bool>(threadPool) != false);

				std::function<std::optional<Asset::asset_type_t<assetType>>()> newTask = std::bind(ReadAssetFile<assetType>, path);

				D_DEBUG_LOG("Add new task to threadpool");
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
			template <Asset::eAssetType assetType>
			[[nodiscard]] static std::vector<imported_asset_future_t<assetType>> ImportAsset(const std::vector<std::filesystem::path>& paths)
			{
				D_ASSERT(static_cast<bool>(threadPool) != false);

				std::vector<std::function<std::optional<Asset::asset_type_t<assetType>>()>> Tasks{};
				Tasks.reserve(paths.size());
				for (auto& path : paths)
				{
					Tasks.push_back(std::bind(ReadAssetFile<assetType>, path));
				}

				D_DEBUG_LOG("Add new task to threadpool");
				/// <summary>
				/// maybe will be copied
				/// </summary>
				/// <param name="paths"></param>
				/// <returns></returns>
				return threadPool->AddTaskChunk(std::move(Tasks));
			}

			///////////////////

			
		};

		std::optional<doom::Asset::eAssetType> GetAssetType(const std::filesystem::path& path);
	}
}
