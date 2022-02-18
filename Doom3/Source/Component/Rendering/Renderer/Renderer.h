#pragma once

#include "Core/Component.h"

#include <vector>

#include <Graphics/Graphics_Core.h>
#include <Rendering/Material/Material.h>
#include "RendererStaticIterator.h"
#include "Physics/Collider/AABB.h"
#include <Misc/AccelerationContainer//BVH/BVH_Node_Object.h>
#include <Rendering/Culling/EveryCulling/DataType/EntityBlockViewer.h>
#include <Transform.h>
#include <Scene/Entity.h>

#include "Renderer.reflection.h"
#include "Rendering/Batch/eBatchRenderingType.h"

namespace dooms
{
	namespace graphics
	{
		class Material;
		class Graphics_Server;
	}

	class Camera;

	enum D_ENUM eRenderingFlag : UINT32
	{
		STATIC_BATCH = 1 << 0,
		DYNAMIC_BATCH = 1 << 1
	};

	struct DistanceToCameraData
	{
		std::array<FLOAT32, MAX_CAMERA_COUNT> mDistancesToCamera;
	};

	class DOOM_API D_CLASS Renderer : public Component, public BVH_AABB3D_Node_Object//, public BVH_AABB3D_Node_Object // public graphics::CullDistanceRenderer
	{
		GENERATE_BODY()
		

		friend graphics::Graphics_Server;
		
	private:

		bool bmIsBatched;

		void MergeBVHBitFlag();
		void ClearRenderingBitFlag();

		void InitializeCullingEntityBlockViewer();


		D_PROPERTY(MIN = 0.0, TOOLTIP="Used in Distance Culling. If Distance between camera and this entity is greater than this value, this entity is culled")
		float mDesiredMaxDrawDistance = DEFAULT_DESIRED_MAX_DRAW_DISTANCE;

		DistanceToCameraData mDistanceToCameraData;

	protected:

		DirtyReceiver bmIsModelMatrixDirty{ true };

		D_PROPERTY()
		graphics::Material* mTargetMaterial;

		virtual void UpdateCullingEntityBlockViewer();

		Renderer(const Renderer&) = default;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

		void OnActivated() override;
		void OnDeActivated() override;

		void AddRendererToCullingSystem();
		void RemoveRendererFromCullingSystem();

		void OnChangedByGUI(const dooms::reflection::DField& dFieldOfChangedField) override;
		bool AddToBatchRendering();
		bool RemoveFromBatchRendering();
		virtual void OnRendererAddedToBatchRendering();
		virtual void OnRendererRemovedFromBatchRendering();

		void UpdateRendererBatchRendering();
		virtual graphics::eBatchRenderingType GetCapableBatchRenderingType() const = 0;
		virtual bool IsBatchable() const = 0;

	public:

		/// <summary>
		/// EntityBlockViewer never be cheanged on a entity
		/// </summary>
		culling::EntityBlockViewer mCullingEntityBlockViewer;

		/// <summary>
		/// Check RenderingBitFlag.h
		/// </summary>
		UINT32 mRenderingFlag{ 0x00000000 };


		void SetRenderingFlag(const eRenderingFlag flag, const bool isSet);
		FORCE_INLINE bool GetRenderingFlag(const eRenderingFlag flag) const
		{
			return (mRenderingFlag & static_cast<UINT32>(flag));
		}

		//DirtyReceiver mIsBoundingSphereDirty{ true };
		//physics::Sphere mBoundingSphere{};

		virtual void InitComponent() override;
		virtual void UpdateComponent() override;

		FORCE_INLINE virtual void OnEndOfFrame_Component() override
		{
			
		}

		void OnEntityLayerChanged(Renderer* renderer)
		{

		}

		virtual const math::Matrix4x4& GetModelMatrix() final;


		void OnDestroy() override;

		Renderer();
		virtual ~Renderer();

		void PreRender();
		FORCE_INLINE virtual void Draw() = 0;

		/// <summary>
		/// Why this function is inline function.
		/// In rendering, Function Call Overhead can be critical overhead 
		/// because We should render a lot of triangles 30 times in a second
		/// 
		/// </summary>
		FORCE_INLINE void BindMaterial() const noexcept
		{
			D_ASSERT(IsValid(mTargetMaterial));
			if (IsValid(mTargetMaterial))
			{
				mTargetMaterial->BindMaterial();
			}
		}

		void SetMaterial(graphics::Material* material) noexcept;
		void SetMaterial(graphics::Material& material) noexcept;
		FORCE_INLINE dooms::graphics::Material* GetMaterial()
		{
			return mTargetMaterial;
		}
		FORCE_INLINE const dooms::graphics::Material* GetMaterial() const
		{
			return mTargetMaterial;
		}
		/// <summary>
		/// cameraIndex can be get from StaticContainer<Camera>
		/// </summary>
		/// <param name="cameraIndex"></param>
		/// <returns></returns>
		char GetIsVisibleWithCameraIndex(UINT32 cameraIndex) const;
		FORCE_INLINE bool GetIsCulled(const UINT32 cameraIndex) const
		{
			return mCullingEntityBlockViewer.GetIsCulled(cameraIndex);
		}

		virtual physics::AABB3D GetLocalAABBBound() const = 0;
		//const physics::Sphere& GetBoudingSphere();

		void CacheDistanceToCamera(const size_t cameraIndex, const Camera* const camera);
		FORCE_INLINE void CacheDistanceToCamera(const size_t cameraIndex, const math::Vector3& cameraPos)
		{
			assert(cameraIndex < MAX_CAMERA_COUNT);
			if (cameraIndex < MAX_CAMERA_COUNT)
			{
				mDistanceToCameraData.mDistancesToCamera[cameraIndex] = (static_cast<const Transform*>(GetTransform())->GetPosition() - cameraPos).magnitude() - dooms::ColliderUpdater<dooms::physics::AABB3D>::GetWorldCollider()->GetDiagonarLineLength();
			}
		}

		/// <summary>
		/// This function doesn't ensure that distance is up to date 
		/// </summary>
		/// <param name="cameraIndex"></param>
		/// <returns></returns>
		FORCE_INLINE FLOAT32 GetDistanceToCamera(const size_t cameraIndex) const
		{
			D_ASSERT(cameraIndex >= 0 && cameraIndex < mDistanceToCameraData.mDistancesToCamera.size());

			return mDistanceToCameraData.mDistancesToCamera[cameraIndex];
		}


		void SetDesiredMaxDrawDistance(const FLOAT32 desiredMaxDrawDistance);
		FLOAT32 GetDesiredMaxDrawDistance() const;
		void OnEntityMobilityChanged(const eEntityMobility entityMobility) override;
		FORCE_INLINE bool GetIsBatched() const
		{
			return bmIsBatched;
		}
	};
}
