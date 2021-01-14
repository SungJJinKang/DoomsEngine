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



#define  MAX_ASSETIMPORTER_THREAD_COUNT 5

namespace Doom
{
	class AssetImporter
	{
	private:
		static const std::map<std::string, Doom::AssetType> AssetExtension;

		template <AssetType assetType>
		struct AssetTypeConditional;
		template <> struct AssetTypeConditional<AssetType::AUDIO> { using type = AudioAsset; };
		template <> struct AssetTypeConditional<AssetType::FONT> { using type = FontAsset; };
		template <> struct AssetTypeConditional<AssetType::TEXTURE> { using type = TextureAsset; };
		template <> struct AssetTypeConditional<AssetType::THREE_D_MODELL> { using type = ThreeDModelAsset; };
		template <AssetType assetType>
		using AssetTypeConditional_t = typename AssetTypeConditional<assetType>::type;

		class DummyApiImporter
		{

		};

		template <AssetType assetType>
		struct ApiImporterTypeConditional;
		template <> struct ApiImporterTypeConditional<AssetType::AUDIO> { using type = DummyApiImporter; };
		template <> struct ApiImporterTypeConditional<AssetType::FONT> { using type = DummyApiImporter; };
		template <> struct ApiImporterTypeConditional<AssetType::TEXTURE> { using type = DummyApiImporter; };
		template <> struct ApiImporterTypeConditional<AssetType::THREE_D_MODELL> { using type = Assimp::Importer; };
		template <AssetType assetType>
		using ApiImporterTypeConditional_t = typename ApiImporterTypeConditional<assetType>::type;
		
		template <AssetType assetType>
		class ApiImporter
		{
		public:
			using ApiImporterTypePointer = typename ApiImporterTypeConditional_t<assetType>*;
		private:
			static inline ApiImporterTypePointer MainThreadImporter{};
			static inline std::mutex ApiImporterMutex{};

			//
			static inline std::queue<ApiImporterTypePointer> ImporterQueue{};
			ApiImporterTypePointer Importer;

			bool isSingleThread;
		public:

			ApiImporter(bool IsSingleThread) : Importer{}
			{
				this->isSingleThread = IsSingleThread;

				if (IsSingleThread == true)
				{
					if (this->MainThreadImporter == nullptr)
					{
						this->MainThreadImporter = new ApiImporterTypeConditional_t<assetType>();
					}
					this->Importer = this->MainThreadImporter;
				}
				else
				{
					if constexpr (!std::is_same_v<ApiImporterTypeConditional_t<assetType>, DummyApiImporter>)
					{
						auto lck = std::lock_guard(ApiImporterMutex);
						if (ImporterQueue.empty())
						{
							this->Importer = new ApiImporterTypeConditional_t<assetType>();
						}
						else
						{
							this->Importer = ImporterQueue.front();
							ImporterQueue.pop();
						}
					}
				}
				
			}

			ApiImporterTypeConditional_t<assetType>* operator->() const {
				return Importer;
			}

			~ApiImporter()
			{
				if (this->isSingleThread == true)
				{

				}
				else
				{
					auto lck = std::lock_guard(ApiImporterMutex);
					if (Importer != nullptr)
					{
						ImporterQueue.push(Importer);
						Debug::Log({ "Now Importer Queue Size is : ", std::to_string(ImporterQueue.size()) });
					}
				}
			}

			

		};
		


		template <AssetType assetType>
		static bool ReadAssetFile(std::filesystem::path path, AssetTypeConditional_t<assetType>& asset, bool IsMultiThreaded = false)
		{
			static_assert(false, "Please put proper type");
			return false;
		}

		template<>
		static bool ReadAssetFile<AssetType::AUDIO>(std::filesystem::path path, AssetTypeConditional_t<AssetType::AUDIO>& asset, bool IsMultiThreaded)
		{
			return false;
		}

		template<>
		static  bool ReadAssetFile<AssetType::FONT>(std::filesystem::path path, AssetTypeConditional_t<AssetType::FONT>& asset, bool IsMultiThreaded)
		{
			return false;
		}

		template<>
		static bool ReadAssetFile<AssetType::TEXTURE>(std::filesystem::path path, AssetTypeConditional_t<AssetType::TEXTURE>& asset, bool IsMultiThreaded)
		{
			return false;
		}

		// TODO : Support MultiThreading Import
		// TODO : Only Big Size File should be imported on multiThread





		/// <summary>
		/// Create Nodes Recursively
		/// </summary>
		/// <param name="currentNode"></param>
		/// <param name="currentAssimpNode"></param>
		/// <param name="parentNode"></param>
		/// <param name="modelAsset"></param>
		/// <param name="assimpScene"></param>
		/// <returns></returns>
		static void SetThreeDModelNodesData(ThreeDModelNode* currentNode, aiNode* currentAssimpNode, ThreeDModelNode* parentNode, ThreeDModelAsset& modelAsset, const aiScene* assimpScene)
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
			void write(const char* message);
		};
#endif
		

		//static std::optional<ThreeDModelAsset> Read3dModelFile
		/// <summary>
		/// Support MultiThreading because 3d model asset is big file size
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		template <>
		static bool ReadAssetFile<AssetType::THREE_D_MODELL>(std::filesystem::path path, AssetTypeConditional_t<AssetType::THREE_D_MODELL>& asset, bool IsMultiThreaded)
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
			ApiImporter<AssetType::THREE_D_MODELL> assimpImporter{ IsMultiThreaded };

			assimpImporter->SetPropertyInteger("AI_CONFIG_PP_RVC_FLAGS",
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
			const aiScene* scene = assimpImporter->ReadFile(path.string(),
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
				assimpImporter->FreeScene();
				return true;
			}
			else
			{
				Debug::Log({ path.string(), " : 3D Model Asset has no scene" });
				return false;
			}

			// We're done. Everything will be cleaned up by the importer destructor
		}


	public:

		/// <summary>
		/// 
		/// </summary>
		/// <param name="path"></param>
		/// <param name="asset"></param>
		/// <param name="multiThreadIndex">If 0 Thie Import is executed on MainThread(SingleThread), else on MultiThread</param>
		/// <returns></returns>
		template <AssetType assetType>
		static bool ImportAsset(const std::filesystem::path& path, AssetTypeConditional_t<assetType>& asset, bool isMultiThreaded = false)
		{
			if (path.has_extension())
			{
				auto extension = path.extension().string();
				try
				{
					if (AssetExtension.at(extension.substr(1, extension.length() - 1)) == assetType)
					{
						if (ReadAssetFile<assetType>(path, asset))
						{
							asset.SetBaseMetaData(path);
							return true;
						}
						else
						{
							Doom::Debug::Log("Fail To Find File Format");
							return false;
						}
					}
				}
				catch (std::out_of_range& e)
				{
					Doom::Debug::Log({ "Can't Find proper extension : ", extension });
				}
			}
			Doom::Debug::Log("Fail To Find File Format");
			return false;
		}

	private:

		
		/// <summary>
		/// Import Asset On MultiThread
		/// </summary>
		/// <param name="path"></param>
		/// <param name="asset"></param>
		/// <param name="extraThreadCount"></param>
		/// <param name="numOfCompletedImportingWork"></param>
		/// <param name="nowThreadIndex"></param>
		/// <returns></returns>
		template <AssetType assetType>
		static bool ImportAssetOnMultiThread(const std::filesystem::path& path, AssetTypeConditional_t<assetType>& asset, std::atomic<unsigned int>& extraThreadCount, std::atomic<unsigned int>& numOfCompletedImportingWork)
		{
			AssetImporter::ImportAsset<assetType>(path, asset, true);

			//Don't change this values execution order
			Debug::Log({ "Finish Import Asset : ", path.string() });
			++extraThreadCount;
			++numOfCompletedImportingWork;
			return true;
		}

		// TODO : MAX_ASSETIMPORTER_THREAD_COUNT SHOULD BE READED FROM CONFIG.INI
		//template <AssetType assetType>
		//static std::function<bool(const std::filesystem::path&, AssetTypeConditional_t<assetType>&, unsigned int&, unsigned int&)> ThreadImport;
	public:

		/// <summary>
		/// Inport Asset Asyncly
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		template <AssetType assetType>
		static std::future<AssetTypeConditional_t<assetType>> ImportAssetAsync(const std::filesystem::path& path)
		{
			//std::thread ~~~
			//thread.detach()
			//return future
		}

		/// <summary>
		/// Import Assets on multithread
		/// Main Thread wait until Every Importing Works is done
		/// Should Call This Function when you need So many Assets at time like Scene Loading
		/// </summary>
		/// <param name="path"></param>
		/// <param name="assets"></param>
		/// <returns></returns>
		template <AssetType assetType>
		static std::vector<AssetTypeConditional_t<assetType>> ImportAssetChunk(const std::vector<std::filesystem::path> paths)
		{
			const size_t assetCount = paths.size();


			std::vector<AssetTypeConditional_t<assetType>> ImportedAssets{ assetCount };// = new AssetTypeConditional_t<assetType>[assetSize];

			std::atomic<unsigned int> extraThreadCount = MAX_ASSETIMPORTER_THREAD_COUNT;

			/// <summary>
			/// if NumOfCompoletedImportingWork equal to assetSize, Every Importing Works is done, return true and exit this function
			/// </summary>
			/// <param name="paths"></param>
			/// <param name="assets"></param>
			/// <returns></returns>
			std::atomic<unsigned int> numOfCompoletedImportingWork = 0;

			for (size_t i = 0; i < assetCount; i++)
			{
				while (extraThreadCount <= 0)
				{// wait until have thread exra
				}

				//Create new Thread
				--extraThreadCount;

				// TODO : ERROR LOOK THIS https://stackoverflow.com/questions/38794207/c-11-passing-member-function-to-thread-gives-no-overloaded-function-takes-2
				//using Func = bool (*AssetImporter::ImportAsset<assetType>)(const std::filesystem::path&, AssetTypeConditional_t<assetType>&, unsigned int&, unsigned int&);
				/// <summary>
				/// Wh
				/// </summary>
				/// <param name="paths"></param>
				/// <returns></returns>
				/// 

				Debug::Log({"Start Importing Asset : ", paths[i].string()});
				std::thread newThread(&AssetImporter::ImportAssetOnMultiThread<assetType>, std::ref(paths[i]), std::ref(ImportedAssets[i]), std::ref(extraThreadCount), std::ref(numOfCompoletedImportingWork));
				newThread.detach(); // this make when newThread is destructed, thread continues executions
			}

			/// <summary>
			/// Put Every Importing Works to thread, Wait Until Every Thread finished their works
			/// </summary>
			/// <param name="paths"></param>
			/// <returns></returns>
			while (numOfCompoletedImportingWork != assetCount);

			/// <summary>
			/// maybe will be copied
			/// </summary>
			/// <param name="paths"></param>
			/// <returns></returns>
			return ImportedAssets;
		}
	};

	
}


