#pragma once

#include "Core.h"

#include <vector>

#include <memory>

#include "../../../Buffer/Mesh.h"
#include "../../../Material.h"

namespace doom
{
	class Renderer;
	namespace physics
	{
		class AABB3D;
	}

	namespace graphics
	{
		/// <summary>
		/// HW Occlusion Culling using Opengl Query Object and Conditional Rendering
		///
		/// HW Occlusion Culling using Opengl Query Object(https://www.khronos.org/opengl/wiki/Query_Object) and ConditionalRendering(https://www.khronos.org/opengl/wiki/Vertex_Rendering#Conditional_rendering)
		/// 
		/// This will be used for preventing to draw complex mesh what will not pass depth test
		/// because To do Occlusion Culling, we should draw Occluder(usally Bounding box of complex mesh) first at same place where complex mesh is drawn.
		/// This Occluder is very simple mesh with simple shader
		/// then if this Occluder is drawed well(pass depth test), It means Complex mesh can be drawn also.
		/// Or not Complex mesh doesn't be drawn
		/// 
		/// Never Try to Retrieve Query to memory from GPU, Performance is really bad.
		/// Sending Data between GPU and memory is really slow.
		/// 
		/// reference : 
		/// https://www.khronos.org/opengl/wiki/Query_Object
		/// https://www.khronos.org/opengl/wiki/Vertex_Rendering#Conditional_rendering
		/// https://www.khronos.org/registry/OpenGL/extensions/NV/NV_conditional_render.txt
		/// https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_occlusion_query2.txt
		/// </summary>
		class QueryOcclusionCulling
		{
			friend class Graphics_Server;
		private:

			const char* OCCLUDER_MATERIAL{ "OcclusionCullingBoundingBox.glsl" };

			unsigned int mQueryID{ 0 };
			void InitHWOcclusionCulling();

			Mesh mBakedOccluderMesh{};
			/// <summary>
			/// Really simple Material
			/// Just Draw 
			/// </summary>
			std::unique_ptr<Material> mOccluderMaterial{};

			/// <summary>
			/// draw Simple bounding volume(Occluder) after this function call
			/// TODO : Disable Pixel Shading, Texturing
			/// </summary>
			void StartQuery();
			void StopQuery();
			void DrawOccluders();

		public:

			

			/// <summary>
			/// draw complex mesh after this function call
			/// 
			/// We don't need retrieve query to memory from gpu, Just use it in GPU
			/// 
			/// Quering Occluder Data require some times. So Don't Do ConditionalRender instantly after Call Query Data 
			/// Have some wait time to query data
			/// 
			/// 
			///  For best performance, applications should attempt to insert some amount
			///  of non - dependent rendering between an occlusion query and the
			///	 conditionally - rendered primitives that depend on the query result.
			/// </summary>
			void StartConditionalRender();
			void StopConditionalRender();

			/// <summary>
			/// Bake Occluder
			/// This make Occluders's Vertex Data
			/// And Vertex Data will be stored as file
			/// Occluders should be static entity(if entity move, Baked Occluders Mesh become useless)
			/// 
			/// I recommend to bake Big mesh
			/// Small mesh can't be useful ( because small mesh usally can't hide behind objects )
			/// </summary>
			/// <param name="globalAABB3DList"></param>
			void BakeOccludersData(const std::vector<Renderer*>& occuluderList, float minimumOccluderBoxSize);
			void LoadOccludersData(const char* vertexDatas);

			/// <summary>
			/// Start Query and Draw Occluder
			/// Quering Occluder Data require some times. So Don't Do ConditionalRender instantly after Call Query Data 
			/// Have some wait time to query data
			/// </summary>
			void QueryOccluderData();
		};
	}
}
