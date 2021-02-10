#pragma once

#include <array>
#include <utility>

#include "ComponentStaticIterater.h"
#include "../Core/Scene/Layer.h"





namespace doom
{
	namespace graphics
	{
		class SceneGraphics;
	}
	class Renderer;

	/// <summary>
	/// Why I made ComponentIterater
	/// 
	/// Think if you wanna Iterate over specific component of spawned entity
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// 
	template <>
	class ComponentStaticIterater<Renderer>
	{
		friend class graphics::SceneGraphics;

		using this_type = typename ComponentStaticIterater<Renderer>;
		using layer_container_type = typename std::vector<Renderer*>;
		using container_type = typename std::array<layer_container_type, MAX_LAYER_COUNT>;
		
	private:

		Renderer* renderer_ptr;

		static inline container_type mComponentsInLayer{};
		int mCurrentEntityLayerIndex;

	protected:

		void AddRendererToStaticContainer();

		void RemoveRendererToStaticContainer();

		/// <summary>
		/// Component constructor should be called before StaticIterator constructor
		/// </summary>
		ComponentStaticIterater();
		~ComponentStaticIterater();

		void OnEntityLayerChanged(Entity& entity);

	public:
		[[nodiscard]] static std::pair<typename layer_container_type::iterator, typename layer_container_type::iterator> GetIterWithLayerIndex(unsigned int layerIndex);

	};

	
	

}