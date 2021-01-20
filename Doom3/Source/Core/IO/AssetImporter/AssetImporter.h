#pragma once

#include "AssetImporterBase.h"
#include "AssetImporter_Audio.h"
#include "AssetImporter_Font.h"
#include "AssetImporter_Text.h"
#include "AssetImporter_Texture.h"
#include "AssetImporter_Three_D_Model.h"
#include "AssetImporter_Shader.h"

extern template class Doom::AssetImporter<Asset::AssetType::AUDIO>;
extern template class Doom::AssetImporter<Asset::AssetType::FONT>;
extern template class Doom::AssetImporter<Asset::AssetType::TEXT>;
extern template class Doom::AssetImporter<Asset::AssetType::TEXTURE>;
extern template class Doom::AssetImporter<Asset::AssetType::THREE_D_MODEL>;
extern template class Doom::AssetImporter<Asset::AssetType::SHADER>;