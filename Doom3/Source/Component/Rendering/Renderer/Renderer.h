#pragma once

#include "Core/ServerComponent.h"

#include <vector>

#include <Graphics/Graphics_Core.h>

#include "RendererStaticIterator.h"

#include <UserInput_Server.h>

#include "Physics/Collider/AABB.h"
#include "utility/BVH/BVH_Node_Object.h"
#include "utility/ColliderUpdater.h"


#include "Graphics/Acceleration/LinearData_ViewFrustumCulling/DataType/EntityBlockViewer.h"


namespace doom
{
	namespace graphics
	{
		class Material;
		class Graphics_Server;
	}

	class Camera;

	enum eRenderingFlag : unsigned int
	{
		STATIC_BATCH = 1 << 0,
		DYNAMIC_BATCH = 1 << 1

	};

	class DOOM_API Renderer : public ServerComponent, public RendererComponentStaticIterator, public BVH_Sphere_Node_Object, public ColliderUpdater<doom::physics::AABB3D>//, public BVH_AABB3D_Node_Object // public graphics::CullDistanceRenderer
	{
		friend graphics::Graphics_Server;
		friend class Enity;
		
	private:

		//For Sorting Renderers front to back
		std::vector<float> mDistancesToCamera;

		/// <summary>
		/// EntityBlockViewer never be cheanged on a entity
		/// </summary>
		culling::EntityBlockViewer mEntityBlockViewer;

		
							
		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

		
		void MergeBVHBitFlag();
		void ClearRenderingBitFlag();

	protected:

		DirtyReceiver bmIsModelMatrixDirty{ true };
		const graphics::Material* mTargetMaterial;

	public:
		
		/// <summary>
		/// Check RenderingBitFlag.h
		/// </summary>
		unsigned int mRenderingFlag{ 0x00000000 };
		void SetRenderingFlag(const eRenderingFlag flag, const bool isSet);
		FORCE_INLINE bool GetRenderingFlag(const eRenderingFlag flag) const
		{
			return (mRenderingFlag & static_cast<unsigned int>(flag));
		}

		//DirtyReceiver mIsBoundingSphereDirty{ true };
		//physics::Sphere mBoundingSphere{};

		virtual void InitComponent() override;
		FORCE_INLINE virtual void UpdateComponent() override
		{
			
		}

		FORCE_INLINE virtual void OnEndOfFrame_Component() override
		{
			
		}

		void OnEntityLayerChanged(Renderer* renderer)
		{

		}

		virtual const math::Matrix4x4& GetModelMatrix() final;


		void OnDestroy() override;

		Renderer();
		virtual ~Renderer() {}


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
		FORCE_INLINE const doom::graphics::Material* GetMaterial()
		{
			return mTargetMaterial;
		}

		/// <summary>
		/// cameraIndex can be get from StaticContainer<Camera>
		/// </summary>
		/// <param name="cameraIndex"></param>
		/// <returns></returns>
		char GetIsVisibleWithCameraIndex(unsigned int cameraIndex) const;
		FORCE_INLINE bool GetIsCulled(const unsigned int cameraIndex) const
		{
			return mEntityBlockViewer.GetIsCulled(cameraIndex);
		}

		virtual physics::AABB3D GetLocalAABBBound() const = 0;
		//const physics::Sphere& GetBoudingSphere();

		void CacheDistanceToCamera(const size_t cameraIndex, const Camera* const camera);
		/// <summary>
		/// This function doesn't ensure that distance is up to date 
		/// </summary>
		/// <param name="cameraIndex"></param>
		/// <returns></returns>
		FORCE_INLINE float GetDistanceToCamera(const size_t cameraIndex) const
		{
			D_ASSERT(cameraIndex >= 0 && cameraIndex < mDistancesToCamera.size());

			return mDistancesToCamera[cameraIndex];
		}
	};
}
