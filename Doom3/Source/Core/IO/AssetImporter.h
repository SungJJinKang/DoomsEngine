#pragma once


#include <filesystem>
#include <type_traits>
#include <map>
#include <string>
#include <optional>
#include <utility>
#include <functional>
#include <queue>

#include <thread>
#include <mutex>
#include <future>

#include "../Core.h"

#include "../Asset/Asset.h"
#include "../Asset/AudioAsset.h"
#include "../Asset/FontAsset.h"
#include "../Asset/TextureAsset.h"
#include "../Asset/ThreeDModelAsset.h"

#include "../API/ASSIMP.h"
#include "../API/STB_IMAGE.h"

#include "../../Helper/ThreadPool_Cpp/ThreadPool.h"


#define  MAX_ASSETIMPORTER_THREAD_COUNT 5

namespace Doom
{
	class DummyApiImporter
	{
	};
	extern const DummyApiImporter dummyApiImporter;
	extern const std::map<std::string, Doom::AssetType> AssetExtension;

	

	template <AssetType assetType>
	struct AssetTypeConditional;
	template <> struct AssetTypeConditional<AssetType::AUDIO> { using type = AudioAsset; };
	template <> struct AssetTypeConditional<AssetType::FONT> { using type = FontAsset; };
	template <> struct AssetTypeConditional<AssetType::TEXTURE> { using type = TextureAsset; };
	template <> struct AssetTypeConditional<AssetType::THREE_D_MODELL> { using type = ThreeDModelAsset; };
	template <AssetType assetType>
	using AssetTypeConditional_t = typename AssetTypeConditional<assetType>::type;

	

	template <AssetType assetType>
	struct ApiImporterTypeConditional;
	template <> struct ApiImporterTypeConditional<AssetType::AUDIO> { using type = DummyApiImporter; };
	template <> struct ApiImporterTypeConditional<AssetType::FONT> { using type = DummyApiImporter; };
	template <> struct ApiImporterTypeConditional<AssetType::TEXTURE> { using type = DummyApiImporter; };
	template <> struct ApiImporterTypeConditional<AssetType::THREE_D_MODELL> { using type = Assimp::Importer; };
	template <AssetType assetType>
	using ApiImporterTypeConditional_t = typename ApiImporterTypeConditional<assetType>::type;



	template <AssetType assetType, size_t ThreadSize>
	class AssetImporter
	{
		//AssetImporter<assetType, ThreadSize>
	private:
		class ApiImporter;

		template<AssetType aType>
		std::optional<AssetTypeConditional_t<aType>> ReadAssetFile(std::filesystem::path path, AssetImporter<aType, ThreadSize>& assetImporter)
		{
			static_assert(false, "Please put proper type");
			return {};
		}
		
		template<>
		std::optional <AssetTypeConditional_t<AssetType::AUDIO>> ReadAssetFile<AssetType::AUDIO>(std::filesystem::path path, AssetImporter<AssetType::AUDIO, ThreadSize>& assetImporter)
		{
			return {};
		}

		template<>
		std::optional <AssetTypeConditional_t<AssetType::FONT>> ReadAssetFile<AssetType::FONT>(std::filesystem::path path, AssetImporter<AssetType::FONT, ThreadSize>& assetImporter)
		{
			return {};
		}

		template<>
		std::optional <AssetTypeConditional_t<AssetType::TEXTURE>> ReadAssetFile<AssetType::TEXTURE>(std::filesystem::path path, AssetImporter<AssetType::TEXTURE, ThreadSize>& assetImporter)
		{
			return {};
		}




		/// <summary>
		/// Create Nodes Recursively
		/// </summary>
		/// <param name="currentNode"></param>
		/// <param name="currentAssimpNode"></param>
		/// <param name="parentNode"></param>
		/// <param name="modelAsset"></param>
		/// <param name="assimpScene"></param>
		/// <returns></returns>
		void SetThreeDModelNodesData(ThreeDModelNode* currentNode, aiNode* currentAssimpNode, ThreeDModelNode* parentNode, ThreeDModelAsset& modelAsset, const aiScene* assimpScene)
		{
			currentNode->ThreeDModelNodeParent = parentNode;
			currentNode->ThreeDModelAsset = &modelAsset;
			currentNode->Name = currentAssimpNode->mName.C_Str();
			currentNode->NumOfThreeDModelMeshes = currentAssimpNode->mNumMeshes;

			currentNode->ThreeDModelMeshes = new ThreeDModelMesh * [currentAssimpNode->mNumMeshes];
			for (unsigned int meshIndex = 0; meshIndex < currentAssimpNode->mNumMeshes; meshIndex++)
			{
				currentNode->ThreeDModelMeshes[meshIndex] = modelAsset.ModelMeshes[currentAssimpNode->mMeshes[meshIndex]];
			}

			currentNode->NumOfThreeDModelNodeChildrens = currentAssimpNode->mNumChildren;
			currentNode->ThreeDModelNodeChildrens = new ThreeDModelNode * [currentAssimpNode->mNumChildren];
			for (unsigned int childrenIndex = 0; childrenIndex < currentAssimpNode->mNumChildren; childrenIndex++)
			{
				currentNode->ThreeDModelNodeChildrens[childrenIndex] = new ThreeDModelNode();
				SetThreeDModelNodesData(currentNode->ThreeDModelNodeChildrens[childrenIndex], currentAssimpNode->mChildren[childrenIndex], currentNode, modelAsset, assimpScene);
			}
		}

#ifdef DEBUG_VERSION
		class AssimpLogStream : public Assimp::LogStream {
		public:
			// Write womethink using your own functionality
			inline void write(const char* message)
			{
				Doom::Debug::Log({ "Assimp Debugger : ", message });
			}
		};
#endif


		//static std::optional<ThreeDModelAsset> Read3dModelFile
		/// <summary>
		/// Support MultiThreading because 3d model asset is big file size
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		template<>
		std::optional <AssetTypeConditional_t<AssetType::THREE_D_MODELL>> ReadAssetFile<AssetType::THREE_D_MODELL>(std::filesystem::path path, AssetImporter<AssetType::THREE_D_MODELL, ThreadSize>& assetImporter)
		{
#ifdef DEBUG_VERSION
			static bool IsAssimpDebuggerInitialized;

			if (IsAssimpDebuggerInitialized == false)
			{
				Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
				// Select the kinds of messages you want to receive on this log stream
				const unsigned int severity = Assimp::Logger::Err | Assimp::Logger::Warn;

				// Attaching it to the default logger
				Assimp::DefaultLogger::get()->attachStream(new AssimpLogStream, severity);

				IsAssimpDebuggerInitialized = true;
			}
#endif
			ApiImporter apiImporter = assetImporter.GetMultithreadApiImporter();
			apiImporter->SetPropertyInteger("AI_CONFIG_PP_RVC_FLAGS",
				aiComponent_COLORS |
				aiComponent_BONEWEIGHTS |
				aiComponent_ANIMATIONS |
				aiComponent_LIGHTS |
				aiComponent_CAMERAS |
				aiComponent_MATERIALS |
				aiComponent_TEXTURES
			);// set removed components flags

			// And have it read the given file with some example postprocessing
			// Usually - if speed is not the most important aspect for you - you'll
			// probably to request more postprocessing than we do in this example.
			const aiScene* scene = apiImporter->ReadFile(path.string(),
				aiProcess_RemoveComponent |
				aiProcess_SplitLargeMeshes |
				aiProcess_Triangulate |
				aiProcess_JoinIdenticalVertices |
				aiProcess_GenSmoothNormals |
				aiProcess_CalcTangentSpace |
				aiProcess_TransformUVCoords |
				aiProcess_SortByPType |
				aiProcess_ImproveCacheLocality
			);

			AssetTypeConditional_t<AssetType::THREE_D_MODELL> asset{};

			//scene->mMeshes[0]->
			// If the import failed, report it
			if (scene != nullptr && scene->mRootNode != nullptr)
			{


				//Copy Asset meshes
				asset.NumOfModelMeshed = scene->mNumMeshes;
				asset.ModelMeshes = new ThreeDModelMesh * [asset.NumOfModelMeshed];
				for (unsigned int meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++)
				{
					auto mesh = scene->mMeshes[meshIndex];
					asset.ModelMeshes[meshIndex] = new ThreeDModelMesh();
					asset.ModelMeshes[meshIndex]->Name = mesh->mName.C_Str();

					asset.ModelMeshes[meshIndex]->NumOfVertices = mesh->mNumVertices;
					asset.ModelMeshes[meshIndex]->Vertices = new glm::vec3 * [mesh->mNumVertices];

					for (unsigned int verticeIndex = 0; verticeIndex < scene->mMeshes[meshIndex]->mNumVertices; verticeIndex++)
					{
						auto vertice = mesh->mVertices[verticeIndex];
						asset.ModelMeshes[meshIndex]->Vertices[verticeIndex] = new glm::vec3(vertice.x, vertice.y, vertice.z);

						asset.ModelMeshes[meshIndex]->NumOfTexCoords = 0;
						asset.ModelMeshes[meshIndex]->TexCoords = nullptr;
						if (mesh->HasTextureCoords(0))
						{//if has texCoord sets
							for (unsigned int texCoordIndex = 0; texCoordIndex < AI_MAX_NUMBER_OF_TEXTURECOORDS; texCoordIndex++)
							{
								if (mesh->mTextureCoords[texCoordIndex] == NULL)
								{
									asset.ModelMeshes[meshIndex]->NumOfTexCoords = texCoordIndex;
									break;
								}
							}

							asset.ModelMeshes[meshIndex]->TexCoords = new glm::vec3 * [asset.ModelMeshes[meshIndex]->NumOfTexCoords];
							for (unsigned int texCoordIndex = 0; texCoordIndex < asset.ModelMeshes[meshIndex]->NumOfTexCoords; texCoordIndex++)
							{
								auto& texCoord = mesh->mTextureCoords[texCoordIndex][verticeIndex];
								asset.ModelMeshes[meshIndex]->TexCoords[texCoordIndex] = new glm::vec3(texCoord.x, texCoord.y, texCoord.z);
							}
						}
					}

					asset.ModelMeshes[meshIndex]->Tangents = mesh->HasTangentsAndBitangents() ? new glm::vec3(mesh->mTangents->x, mesh->mTangents->y, mesh->mTangents->z) : nullptr;
					asset.ModelMeshes[meshIndex]->BiTangents = mesh->HasTangentsAndBitangents() ? new glm::vec3(mesh->mBitangents->x, mesh->mBitangents->y, mesh->mBitangents->z) : nullptr;
					asset.ModelMeshes[meshIndex]->Normals = mesh->HasNormals() ? new glm::vec3(mesh->mNormals->x, mesh->mNormals->y, mesh->mNormals->z) : nullptr;
				}

				//scene->mRootNode
				asset.rootNode.ThreeDModelNodeParent = nullptr;
				SetThreeDModelNodesData(&(asset.rootNode), scene->mRootNode, nullptr, asset, scene);
				apiImporter->FreeScene();
				return asset;
			}
			else
			{
				Debug::Log({ path.string(), " : 3D Model Asset has no scene" });
				return {};
			}

			// We're done. Everything will be cleaned up by the importer destructor
		}



	private:

		ThreadPool<ThreadSize> threadPool;

		using ApiImporterType = typename ApiImporterTypeConditional_t<assetType>;

		std::array<ApiImporterType, ThreadSize> apiImporters;

		
		public:
		AssetImporter() : threadPool{}, apiImporters{}, apiImporterMutex{}, ImporterQueue{}
		{
			
		}

		private:
		std::mutex apiImporterMutex;
		std::queue<ApiImporterType*> ImporterQueue;

		class ApiImporter;
		ApiImporter GetMultithreadApiImporter()
		{
			if constexpr (!std::is_same_v<ApiImporterTypeConditional_t<assetType>, DummyApiImporter>)
			{
				auto lck = std::scoped_lock(apiImporterMutex);

				ApiImporterType* importer{};
				if (this->ImporterQueue.empty())
				{
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
				return {this, &dummyApiImporter};
			}
		}

		void ReleaseMultithreadApiImporter(ApiImporterType* apiImporterType)
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

		/// <summary>
		/// RAII
		/// </summary>
		class ApiImporter
		{
		private:
			AssetImporter<assetType, ThreadSize>* assetImporter;
			ApiImporterType* importer;

		public:
			ApiImporter(AssetImporter<assetType, ThreadSize>* assetImporter, ApiImporterType* importer)
				: assetImporter{ assetImporter }, importer{ importer }
			{
			}

			ApiImporterType* operator->() const {
				return importer;
			}

			~ApiImporter()
			{
				if constexpr (!std::is_same_v<ApiImporterTypeConditional_t<assetType>, DummyApiImporter>)
				{
					assetImporter->ReleaseMultithreadApiImporter(this);
				}
				
			}
		};
		


		
	public:

		/// <summary>
		/// 
		/// </summary>
		/// <param name="path"></param>
		/// <param name="asset"></param>
		/// <param name="multiThreadIndex">If 0 Thie Import is executed on MainThread(SingleThread), else on MultiThread</param>
		/// <returns></returns>
		std::optional<std::future<std::optional<AssetTypeConditional_t<assetType>>>> ImportAsset(const std::filesystem::path& path)
		{
			if (path.has_extension())
			{
				auto extension = path.extension().string();
				try
				{
					if (AssetExtension.at(extension.substr(1, extension.length() - 1)) == assetType)
					{
						return this->threadPool.AddTask(&ReadAssetFile<assetType>, this, path, *this);
					}
				}
				catch (std::out_of_range& e)
				{
					Doom::Debug::Log({ "Can't Find proper extension : ", extension });
				}
				catch (...)
				{
					Doom::Debug::Log("Can't import asset");
				}
			}
			
			return {};
		}

	
		/// <summary>
		/// Import Assets on multithread
		/// Main Thread wait until Every Importing Works is done
		/// Should Call This Function when you need So many Assets at time like Scene Loading
		/// </summary>
		/// <param name="path"></param>
		/// <param name="assets"></param>
		/// <returns></returns>
		std::vector<std::future<std::optional<AssetTypeConditional_t<assetType>>>> ImportAssetChunk(const std::vector<std::filesystem::path>& paths)
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
							Tasks.push_back(std::bind(&ReadAssetFile<assetType>, this, path, *this));
							break;
						}
					}
					catch (std::out_of_range& e)
					{
						Doom::Debug::Log({ "Can't Find proper extension : ", extension });
					}
				}
				Doom::Debug::Log("Fail To Find File Format");
				Tasks.push_back({});
				
			}
			
			/// <summary>
			/// maybe will be copied
			/// </summary>
			/// <param name="paths"></param>
			/// <returns></returns>
			return this->threadPool.AddTaskChunk(Tasks);
		}
		
	};

	
}


