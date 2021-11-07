#include "AssetImporterWorker.h"

std::atomic<bool> dooms::assetImporter::AssetImporterWorker::IsInitializedStatic = false;

dooms::assetImporter::AssetImporterWorker::AssetImporterWorker() = default;
dooms::assetImporter::AssetImporterWorker::AssetImporterWorker(const AssetImporterWorker&) = default;
dooms::assetImporter::AssetImporterWorker::AssetImporterWorker(AssetImporterWorker&&) noexcept = default;
dooms::assetImporter::AssetImporterWorker& dooms::assetImporter::AssetImporterWorker::operator=(const AssetImporterWorker&) = default;
dooms::assetImporter::AssetImporterWorker& dooms::assetImporter::AssetImporterWorker::operator=(AssetImporterWorker&&) noexcept = default;
dooms::assetImporter::AssetImporterWorker::~AssetImporterWorker() = default;