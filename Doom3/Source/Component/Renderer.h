#pragma once

#include "Core/ServerComponent.h"
#include "Iterator/RendererStaticIterator.h"

namespace doom
{
	namespace graphics
	{
		class Material;
		class Graphics_Server;
	}



	class Renderer : public ServerComponent, public RendererComponentStaticIterator
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

		virtual void InitComponent() override
		{
			RendererComponentStaticIterator::AddRendererToStaticContainer();
		}
		virtual void UpdateComponent() override
		{
			this->Draw();
		}

		virtual void OnEndOfFrame_Component() override
		{
			
		}
		void OnEntityLayerChanged(Renderer* renderer)
		{

		}

	public:
		Renderer();
		virtual ~Renderer() {}


		virtual void Draw() noexcept = 0;

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
