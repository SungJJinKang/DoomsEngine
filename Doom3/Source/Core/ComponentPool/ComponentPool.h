#pragma once

#include <memory>
#include <vector>
#include <cstdlib>

#include <Core.h>

namespace dooms
{
	void a()
	{
		
	}

	template <typename ComponentType, typename Allocator = std::allocator<ComponentType>>
	class DOOM_API ComponentPool
	{
		using alloc = std::allocator_traits<Allocator>;
	private:

		inline static constexpr size_t DEFAULT_COMPONENT_POOL_SIZE = 20;

		inline static std::vector<ComponentType*> mFreeComponents;
		inline static Allocator alloc{};

	public:


		static void GenerateComponentPool(size_t componentCount)
		{
			//Never use new!!
			//Constructor is never called at here
			//ignore alignment

			auto* arrayPointer = std::malloc(sizeof(ComponentType) * componentCount);
			for (size_t i = 0; i < componentCount; i++)
			{
				mFreeComponents.push_back(arrayPointer + i);
			}

		}

		FORCE_INLINE static ComponentType* GetNewComponent()
		{

			//Don't mind deallocating at here
			//Deallocating will be called from

			//Call Construct at here

			//!!
			//Using delete on allocated memory with malloc is undefined behaviour
		
			//ComponentType* newComponent = ComponentPool<ComponentType>::mFreeComponents.back();
			//ComponentPool<ComponentType>::mFreeComponents.pop_back();
			//new (newComponent) ComponentType();
			return newComponent;

			//Check this : https://stackoverflow.com/questions/67852689/what-happen-if-deallocate-allocated-object-with-malloc-using-delete
		}
	};

	

}