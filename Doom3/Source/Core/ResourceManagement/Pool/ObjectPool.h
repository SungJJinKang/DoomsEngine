#pragma once

#include <vector>
#include <type_traits>
#include <utility>

#include "Core.h"
#include "Simple_SingleTon/Singleton.h"

namespace doom
{
	namespace resource
	{
		template <typename T, size_t PoolCountInBlock>
		struct ObjectPoolBlock
		{
			/// <summary>
			/// 
			/// If user destroy entity, that element will be invalidated
			/// We can't know element is destroyed..
			/// </summary>
			char ObjectPool[PoolCountInBlock * sizeof(T)];
			unsigned int mAllocatedObjectPoolCount;
		};

		template <typename T, size_t PoolCountInBlock = 4000 / sizeof(T)>
		class ObjectPool : ISingleton<T>
		{
			static_assert(std::is_pointer_v<T> == false);

			using type = typename ObjectPool<T, PoolCountInBlock>;
			using object_pool_block_type = typename ObjectPoolBlock<T, PoolCountInBlock>;
			
		private:

			inline static std::vector<object_pool_block_type*> mObjectPoolBlocks{};

			FORCE_INLINE static void AllocateNewPoolBlock()
			{
				//we don't intialize objects.
				type::mObjectPoolBlocks.push_back(new object_pool_block_type());
				type::mObjectPoolBlocks[type::mObjectPoolBlocks.size() - 1].mAllocatedObjectPoolCount = 0;
			}
			
			FORCE_INLINE static T* _GetNewObjectFromPool()
			{
				if (type::mObjectPoolBlocks.size() == 0)
				{
					type::AllocateNewPoolBlock();
				}

				if (type::mObjectPoolBlocks[type::mObjectPoolBlocks.size() - 1].mAllocatedObjectPoolCount >= PoolCountInBlock)
				{
					type::AllocateNewPoolBlock();
				}

				unsigned int objectIndex = (type::mObjectPoolBlocks[type::mObjectPoolBlocks.size() - 1].mAllocatedObjectPoolCount)++;
				return reinterpret_cast<T*>(type::mObjectPoolBlocks[type::mObjectPoolBlocks.size() - 1].ObjectPool) + objectIndex;
			}

		public:

			template <typename... Args>
			FORCE_INLINE static T* GetNewObjectFromPool(Args&&... args)
			{
				T* NewObject = type::_GetNewObjectFromPool();
				std::allocator<T>::construct(NewObject, std::forward<Args>(args)...);
				return NewObject;
			}

		};
		
	

	}
}