#pragma once

#include "Core/ServerComponent.h"
#include "RendererStaticIterator.h"

#include <UserInput_Server.h>

#include "Physics/Collider/AABB.h"
#include "utility/BVH/BVH_Node_Object.h"

#include "Graphics/Graphics_Server.h"

namespace doom
{
	namespace graphics
	{
		class Material;
		class Graphics_Server;
	}



	class Renderer : public ServerComponent, public RendererComponentStaticIterator, public BVH3D_Node_Object
	{
		friend graphics::Graphics_Server;
		friend class Enity;

	private:

				
		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

		

	protected:
		
		graphics::Material* mTargetMaterial;

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


		const math::Matrix4x4& GetModelMatrix() const final;

	public:
		Renderer();
		virtual ~Renderer() {}


		virtual void Draw() = 0;

		/// <summary>
		/// Why this function is inline function.
		/// In rendering, Function Call Overhead can be critical overhead 
		/// because We should render a lot of triangles 30 times in a second
		/// 
		/// </summary>
		void BindMaterial() noexcept;
		void SetMaterial(graphics::Material* material) noexcept;
		void SetMaterial(graphics::Material& material) noexcept;
	};
}
