#pragma once
#include <array>
#include <type_traits>
#include <map>
#include <utility>
#include <optional>
#include <filesystem>

#include "../Core.h"
#include "../Asset/Asset.h"
namespace Doom
{
	template <Doom::AssetType assetType>
	class AssetContainer
	{
	private:
		using type = Doom::AssetTypeConditional_t< assetType>;
		static_assert(std::is_base_of_v<Doom::Asset, type>);
		std::map<UUID, type> Assets;

	public:

		constexpr AssetContainer() : Assets{}
		{

		}

		void AddAsset(type&& asset)
		{
			this->Assets.insert(std::move(asset));
		}
		std::optional<const type&> GetAsset(const UUID& uuid)
		{
			try
			{
				return Assets.at(uuid);
			}
			catch (const std::out_of_range& e)
			{
				DEBUG_LOG("Can't find asset");
				return {};
			}
			catch (...)
			{
				DEBUG_LOG("Unknown Error", LogType::D_ERROR);
				return {};
			}
		}
	};
	
	const inline std::filesystem::path AssetFolderPath{ ASSET_FOLDER_DIRECTORY };

	class AssetManager
	{
	public:
		static void ImportEntireAsset();



	};
}


