#pragma once

#include <Core.h>

#include <Rendering/Culling/EveryCulling/EveryCulling.h>

#include <Vector3.h>
#include <Matrix4x4.h>

#include "RenderingCullingManager.reflection.h"
namespace dooms
{
	class Camera;
	namespace graphics
	{
		/**
		 * \brief This struct is used for deferred entity update.
		 * DoomsEngine reads back results of culling one frame later.
		 * So Updating data of entity should be deferred until previous frame's cull job is finished
		 * This struct will helps it.
		 */
		struct FEntityUpdateDataForCulling
		{
			culling::EntityBlock* TargetEntityBlock;
			UINT64 EntityBlockUniqueID;

			UINT64 EntityIndexInEntityBlock;

			enum class FEntityUpdateDataFlag
			{
				AddNewEntity,
				UpdateEntityData,
				RemoveExistingEntity
			};

			FEntityUpdateDataFlag EntityUpdateDataFlag;

			struct FUpdatedEntityData
			{
				math::Matrix4x4 ModelMatrix{ nullptr };

				struct FUpdatedEntityMeshData
				{
					const culling::Vec3* Vertice;
					UINT64 VerticeCount;
					const std::uint32_t* Indices;
					UINT64 IndiceCount;
					UINT64 VerticeStride;
				} UpdatedEntityMeshData;

				math::Vector3 AABBMinWorldPosition{ nullptr };
				math::Vector3 AABBMaxWorldPosition{ nullptr };
				math::Vector3 OriginWorldPosition{ nullptr };

				float DesiredMaxDrawDistance;

				bool bIsEntityEnabled;
			};

			FUpdatedEntityData UpdatedEntityData;

			FEntityUpdateDataForCulling() = delete;
			FEntityUpdateDataForCulling(
				culling::EntityBlock* const InTargetEntityBlock, const UINT64 InEntityIndexInEntityBlock, 
				const FEntityUpdateDataFlag InCullingDataUpdateFlag, const FUpdatedEntityData* const InUpdatedEntityData);
		};

		class D_CLASS RenderingCullingManager : public DObject
		{
			GENERATE_BODY()

		private:

			D_PROPERTY()
			UINT32 mCullingCameraCount;

			void UpdateCameraIndexInCullingSystemOfCameraComponent();

		public:

			std::unique_ptr<culling::EveryCulling> mCullingSystem;

			RenderingCullingManager();

			void Initialize();
			void PreCullJob();
			void CameraCullJob(dooms::Camera* const camera);
		};
	}
}

