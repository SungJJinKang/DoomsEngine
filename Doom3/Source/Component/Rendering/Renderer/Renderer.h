#pragma once

#include "Core/Component.h"

#include <vector>

#include <Graphics/Graphics_Core.h>

#include "RendererStaticIterator.h"

#include <UserInput_Server.h>

#include "Physics/Collider/AABB.h"
#include "utility/BVH/BVH_Node_Object.h"
#include "utility/ColliderUpdater.h"

#include <Vector4.h>


#include "Graphics/Acceleration/LinearData_ViewFrustumCulling/DataType/EntityBlockViewer.h"


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

	class DOOM_API D_CLASS Renderer : public Component, public BVH_AABB3D_Node_Object//, public BVH_AABB3D_Node_Object // public graphics::CullDistanceRenderer
	{
		GENERATE_BODY()
		

		friend graphics::Graphics_Server;
		
	private:

		//For Sorting Renderers front to back
		std::vector<FLOAT32> mDistancesToCamera;

		Entity::eEntityMobility mOriginalEntityMobility;
		
		void MergeBVHBitFlag();
		void ClearRenderingBitFlag();

		void InitializeCullingEntityBlockViewer();


		D_PROPERTY(MIN = 0.0)
		float mDesiredMaxDrawDistance = DEFAULT_DESIRED_MAX_DRAW_DISTANCE;

	protected:

		DirtyReceiver bmIsModelMatrixDirty{ true };

		D_PROPERTY()
		const graphics::Material* mTargetMaterial;

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
		FORCE_INLINE virtual void Draw() const = 0;

		/// <summary>
		/// Why this function is inline function.
		/// In rendering, Function Call Overhead can be critical overhead 
		/// because We should render a lot of triangles 30 times in a second
		/// 
		/// </summary>
		FORCE_INLINE void BindMaterial() const noexcept
		{
			if (mTargetMaterial != nullptr)
			{
				mTargetMaterial->UseProgram();
			}
		}

		void SetMaterial(const graphics::Material* material) noexcept;
		void SetMaterial(const graphics::Material& material) noexcept;
		FORCE_INLINE const dooms::graphics::Material* GetMaterial()
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
		void CacheDistanceToCamera(const size_t cameraIndex, const math::Vector3& cameraPos);
		/// <summary>
		/// This function doesn't ensure that distance is up to date 
		/// </summary>
		/// <param name="cameraIndex"></param>
		/// <returns></returns>
		FORCE_INLINE FLOAT32 GetDistanceToCamera(const size_t cameraIndex) const
		{
			D_ASSERT(cameraIndex >= 0 && cameraIndex < mDistancesToCamera.size());

			return mDistancesToCamera[cameraIndex];
		}


		void SetDesiredMaxDrawDistance(const FLOAT32 desiredMaxDrawDistance);
		FLOAT32 GetDesiredMaxDrawDistance() const;
	};
}
