#pragma once

#include <memory>

#include "Material/Material.h"
#include "Buffer/Mesh.h"


namespace doom
{
	namespace graphics
	{
		

		class DeferredRenderingDrawer : public DObject
		{
			DOBJECT_CLASS_BODY(DeferredRenderingDrawer, doom::eDOBJECT_ClassFlags::NonCopyable);
			DOBJECT_CLASS_BASE_CHAIN(DObject)

		private:

			/// <summary>
			/// Gbuffer drawer material.
			/// this will be used in Quad Mesh
			/// </summary>
			Material mGbufferDrawerMaterial;
			std::shared_ptr<Mesh> mQuadMesh;

			void SetShaderToGBufferMaterial();

		public:

			DeferredRenderingDrawer();
			~DeferredRenderingDrawer();

			void Initialize();

			void DrawDeferredRenderingQuadDrawer();
			
		};
		
	}
}