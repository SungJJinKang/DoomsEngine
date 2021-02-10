#pragma once
#include "../Core/Graphics/Material.h"
#include "Core/CoreComponent.h"
#include "Iterator/RendererStaticIterator.h"

namespace doom
{
	namespace graphics
	{
		class Material;
		class Graphics_Server;
	}



	class Renderer : public CoreComponent, public ComponentStaticIterater<Renderer>
	{
		friend graphics::Graphics_Server;
	private:
		graphics::Material* mTargetMaterial;

		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;
	protected:
		
		virtual void InitComponent() override
		{

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
		virtual ~Renderer();


		virtual void Draw() = 0;

		/// <summary>
		/// Why this function is inline function.
		/// In rendering, Function Call Overhead can be critical overhead 
		/// because We should render a lot of triangles 30 times in a second
		/// 
		/// </summary>
		void BindMaterial()
		{
			if (this->mTargetMaterial != nullptr)
			{
				this->mTargetMaterial->UseProgram();
			}
		}
		void SetMaterial(graphics::Material* material);
		void SetMaterial(graphics::Material& material);
	};
}
