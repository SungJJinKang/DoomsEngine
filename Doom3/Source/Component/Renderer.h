#pragma once
#include "../Core/Graphics/Material.h"
#include "../Core/CoreComponent/CoreComponent.h"

namespace doom
{
	namespace graphics
	{
		class Material;
	}

	class Renderer : public CoreComponent
	{
	private:
		graphics::Material* mTargetMaterial;
	protected:
		

	public:
		Renderer();
		Renderer(graphics::Material* targetMaterial);
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
	};
}
