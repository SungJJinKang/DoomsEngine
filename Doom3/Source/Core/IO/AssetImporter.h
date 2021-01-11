#pragma once


#include <filesystem>
#include <type_traits>
#include <map>
#include <string>
#include <optional>
#include <utility>

#include <thread>
#include <mutex>


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



		template <> struct AssetTypeConditional<Doom::AssetType::AUDIO> { using type = AudioAsset; };
		template <> struct AssetTypeConditional<Doom::AssetType::FONT> { using type = FontAsset; };
		template <> struct AssetTypeConditional<Doom::AssetType::TEXTURE> { using type = TextureAsset; };
		template <> struct AssetTypeConditional<Doom::AssetType::THREE_D_MODELL> { using type = ThreeDModelAsset; };

		template <AssetType assetType>
		using AssetTypeConditional_t = typename AssetTypeConditional<assetType>::type;

		template <AssetType assetType>
		static bool ReadAssetFile(std::filesystem::path path, AssetTypeConditional_t<assetType>& asset, void* importer)
		{
			static_assert(false, "Please put proper type");
			return false;
		}

		template<>
		static bool ReadAssetFile<AssetType::AUDIO>(std::filesystem::path path, AssetTypeConditional_t<AssetType::AUDIO>& asset, void* importer)
		{
			return false;
		}

		template<>
		static  bool ReadAssetFile<AssetType::FONT>(std::filesystem::path path, AssetTypeConditional_t<AssetType::FONT>& asset, void* importer)
		{
			return false;
		}

		template<>
		static bool ReadAssetFile<AssetType::TEXTURE>(std::filesystem::path path, AssetTypeConditional_t<AssetType::TEXTURE>& asset, void* importer)
		{
			return false;
		}

		// TODO : Support MultiThreading Import
		// TODO : Only Big Size File should be imported on multiThread


		//static std::array<std::pair<Assimp::Importer>>ThreeDModelAssetImporterMutex;



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


		static Assimp::Importer MainThreadAssimpImporter;
		static Assimp::Importer MultiThreadAssimpImporter[MAX_ASSETIMPORTER_THREAD_COUNT];

		//static std::optional<ThreeDModelAsset> Read3dModelFile
		/// <summary>
		/// Support MultiThreading because 3d model asset is big file size
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		template <>
		static bool ReadAssetFile<AssetType::THREE_D_MODELL>(std::filesystem::path path, AssetTypeConditional_t<AssetType::THREE_D_MODELL>& asset, void* importer)
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
			Assimp::Importer* assimpImporter = static_cast<Assimp::Importer*>(importer);
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
				MainThreadAssimpImporter.FreeScene();
				return true;
			}
			else
			{
				Debug::Log({ path.string(), " : 3D Model Asset has no scene" });
				return false;
			}

			// We're done. Everything will be cleaned up by the importer destructor
		}

		template <AssetType assetType>
		static void* GetImporter()
		{
			return nullptr;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="multiThreadIndex">If 0 Thie Import is executed on MainThread(SingleThread), else This value mean a Index of Chunks</param>
		/// <returns></returns>
		template <AssetType assetType>
		static void* GetImporter(unsigned int multiThreadIndex = 0)
		{
			return nullptr;
		}

		template <>
		static void* GetImporter<AssetType::THREE_D_MODELL>(unsigned int multiThreadIndex)
		{
			if (multiThreadIndex == 0)
			{
				return &MainThreadAssimpImporter;
			}
			else
			{
				return &MultiThreadAssimpImporter[multiThreadIndex % MAX_ASSETIMPORTER_THREAD_COUNT];
			}
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
		static bool ImportAsset(const std::filesystem::path& path, AssetTypeConditional_t<assetType>& asset, unsigned int multiThreadIndex = 0)
		{
			if (path.has_extension())
			{
				auto extension = path.extension().string();
				try
				{
					if (AssetExtension.at(extension.substr(1, extension.length() - 1)) == assetType)
					{
						if (ReadAssetFile<assetType>(path, asset, GetImporter<assetType>(multiThreadIndex)))
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

		template <AssetType assetType>
		static std::mutex AssetImporterMutex;

		/// <summary>
		/// Import Asset On MultiThread
		/// </summary>
		/// <param name="path"></param>
		/// <param name="asset"></param>
		/// <param name="extraThreadCount"></param>
		/// <param name="numOfCompletedImportingWork"></param>
		/// <returns></returns>
		template <AssetType assetType>
		static bool ImportAsset(const std::filesystem::path& path, AssetTypeConditional_t<assetType>& asset, unsigned int& extraThreadCount, unsigned int& numOfCompletedImportingWork)
		{
			AssetImporter::ImportAsset<assetType>(path, asset, true);


			std::lock_guard(AssetImporterMutex<assetType>);
			//Don't change this values execution order
			++extraThreadCount;
			++numOfCompletedImportingWork;
			return true;
		}

		// TODO : MAX_ASSETIMPORTER_THREAD_COUNT SHOULD BE READED FROM CONFIG.INI

	public:
		/// <summary>
		/// Import Assets on multithread
		/// Main Thread will be terminated until Every Importing Works is done
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

			unsigned int extraThreadCount = MAX_ASSETIMPORTER_THREAD_COUNT;

			/// <summary>
			/// if NumOfCompoletedImportingWork equal to assetSize, Every Importing Works is done, return true and exit this function
			/// </summary>
			/// <param name="paths"></param>
			/// <param name="assets"></param>
			/// <returns></returns>
			unsigned int numOfCompoletedImportingWork = 0;


			for (size_t i = 0; i < assetCount; i++)
			{
				while (extraThreadCount <= 0)
				{// wait until have thread exra
				}
					
				//Create new Thread
				--extraThreadCount;

				// TODO : ERROR LOOK THIS https://stackoverflow.com/questions/38794207/c-11-passing-member-function-to-thread-gives-no-overloaded-function-takes-2
				using Func = bool (*AssetImporter::ImportAsset<assetType>)(const std::filesystem::path&, AssetTypeConditional_t<assetType>&, unsigned int&, unsigned int&);
				/// <summary>
				/// Wh
				/// </summary>
				/// <param name="paths"></param>
				/// <returns></returns>
				std::thread newThread(static_cast<Func>(&AssetImporter::ImportAsset<assetType>), std::ref(paths[i]), std::ref(ImportedAssets[i]), std::ref(extraThreadCount), std::ref(numOfCompoletedImportingWork));
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


