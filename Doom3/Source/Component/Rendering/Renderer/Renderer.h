#pragma once

#include "Core/ServerComponent.h"
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



	class Renderer : public ServerComponent, public RendererComponentStaticIterator, public BVH_Sphere_Node_Object, public ColliderUpdater<doom::physics::AABB3D>//, public BVH_AABB3D_Node_Object // public graphics::CullDistanceRenderer
	{
		friend graphics::Graphics_Server;
		friend class Enity;

	public:

	
	private:
		/// <summary>
		/// EntityBlockViewer never be cheanged on a entity
		/// </summary>
		culling::EntityBlockViewer mEntityBlockViewer;
							
		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

		/// <summary>
		/// Check RenderingBitFlag.h
		/// </summary>
		unsigned int mRenderingBitFlag{ 0 };
		void MergeBVHBitFlag();
		void ClearRenderingBitFlag();

	protected:
		
		graphics::Material* mTargetMaterial;

		//DirtyReceiver mIsBoundingSphereDirty{ true };
		//physics::Sphere mBoundingSphere{};

		virtual void InitComponent() override;
		virtual void UpdateComponent() override
		{
		}

		virtual void OnEndOfFrame_Component() override
		{
			
		}
		void OnEntityLayerChanged(Renderer* renderer)
		{

		}

		virtual const math::Matrix4x4& GetModelMatrix() final;


		void OnDestroy() override;

	public:
		Renderer();
		virtual ~Renderer() {}


		FORCE_INLINE virtual void Draw() = 0;

		/// <summary>
		/// Why this function is inline function.
		/// In rendering, Function Call Overhead can be critical overhead 
		/// because We should render a lot of triangles 30 times in a second
		/// 
		/// </summary>
		FORCE_INLINE void BindMaterial() noexcept
		{
			if (mTargetMaterial != nullptr)
			{
				mTargetMaterial->UseProgram();
			}
		}
		void SetMaterial(graphics::Material* material) noexcept;
		void SetMaterial(graphics::Material& material) noexcept;

		/// <summary>
		/// cameraIndex can be get from StaticContainer<Camera>
		/// </summary>
		/// <param name="cameraIndex"></param>
		/// <returns></returns>
		char GetIsVisibleWithCameraIndex(unsigned int cameraIndex);
		bool GetIsCulled(const unsigned int cameraIndex) const;

		virtual physics::AABB3D GetLocalAABBBound() const = 0;
		//const physics::Sphere& GetBoudingSphere();
	};
}
