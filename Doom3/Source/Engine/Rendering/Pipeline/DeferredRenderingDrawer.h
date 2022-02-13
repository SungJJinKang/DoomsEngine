#pragma once

#include <memory>

#include <Graphics/Material/Material.h>
#include <Graphics/Buffer/Mesh.h>

#include "DeferredRenderingDrawer.reflection.h"
namespace dooms
{
	namespace graphics
	{
		

		class DOOM_API D_CLASS DeferredRenderingDrawer : public DObject
		{
			GENERATE_BODY()
			

		private:

			/// <summary>
			/// Gbuffer drawer material.
			/// this will be used in Quad Mesh
			/// </summary>
			D_PROPERTY()
			Material mGbufferDrawerMaterial;

			D_PROPERTY()
			Mesh* mQuadMesh;

			void SetShaderToGBufferMaterial();

		public:

			DeferredRenderingDrawer();
			~DeferredRenderingDrawer();

			void Initialize();

			void DrawDeferredRenderingQuadDrawer();
			
		};
		
	}
}