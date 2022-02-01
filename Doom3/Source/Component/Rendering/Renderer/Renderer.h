#pragma once

#include "Core/Component.h"

#include <vector>

#include <Graphics/Graphics_Core.h>
#include <Graphics/Material/Material.h>
#include "RendererStaticIterator.h"
#include "Physics/Collider/AABB.h"
#include "utility/BVH/BVH_Node_Object.h"
#include "Graphics/Acceleration/LinearData_ViewFrustumCulling/DataType/EntityBlockViewer.h"
#include <Transform.h>
#include <Scene/Entity.h>

#include "Renderer.reflection.h"
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
		UINT8 padding1[56];
		std::array<FLOAT32, MAX_CAMERA_COUNT> mDistancesToCamera;
	};

	class DOOM_API D_CLASS Renderer : public Component, public BVH_AABB3D_Node_Object//, public BVH_AABB3D_Node_Object // public graphics::CullDistanceRenderer
	{
		GENERATE_BODY()
		

		friend graphics::Graphics_Server;
		
	private:

		//For Sorting Renderers front to back
		Entity::eEntityMobility mOriginalEntityMobility;
		
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

	private :
		std::array<unsigned long, MAX_CAMERA_COUNT> mFrontToBackSortingOrder;

	public:

		FORCE_INLINE UINT32 GetFrontToBackSortingOrder(const size_t cameraIndex) const
		{
			D_ASSERT(cameraIndex < MAX_CAMERA_COUNT);
			return mFrontToBackSortingOrder[cameraIndex];
		}
		FORCE_INLINE void SetFrontToBackSortingOrder(const size_t cameraIndex, const UINT32 frontToBackSortingOrder)
		{
			D_ASSERT(cameraIndex < MAX_CAMERA_COUNT);
			mFrontToBackSortingOrder[cameraIndex] = frontToBackSortingOrder;
		}
	};
}
