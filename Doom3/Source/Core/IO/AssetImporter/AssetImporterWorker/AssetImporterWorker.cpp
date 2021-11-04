#include "AssetImporterWorker.h"

std::atomic<bool> doom::assetImporter::AssetImporterWorker::IsInitializedStatic = false;

doom::assetImporter::AssetImporterWorker::AssetImporterWorker() = default;
doom::assetImporter::AssetImporterWorker::AssetImporterWorker(const AssetImporterWorker&) = default;
doom::assetImporter::AssetImporterWorker::AssetImporterWorker(AssetImporterWorker&&) noexcept = default;
doom::assetImporter::AssetImporterWorker& doom::assetImporter::AssetImporterWorker::operator=(const AssetImporterWorker&) = default;
doom::assetImporter::AssetImporterWorker& doom::assetImporter::AssetImporterWorker::operator=(AssetImporterWorker&&) noexcept = default;
doom::assetImporter::AssetImporterWorker::~AssetImporterWorker() = default;