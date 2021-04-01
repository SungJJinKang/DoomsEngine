/*
* 
#pragma once

#include <vector>
#include <type_traits>
#include <utility>

#include "Core.h"

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

		/// <summary>
		/// Object Pool For specific class or struct
		/// Instances is stored configously.
		/// Maybe it will help cache hitting when iterate over instances
		/// </summary>
		/// <typeparam name="T"></typeparam>
		template <typename T>
		class ObjectPool
		{
			static_assert(std::is_pointer_v<T> == false);

			inline static constexpr size_t PoolCountInBlock = 4000 / sizeof(T);

			using type = typename ObjectPool<T>;
			using object_pool_block_type = typename ObjectPoolBlock<T, PoolCountInBlock>;
			
		private:

			inline static std::vector<object_pool_block_type*> mObjectPoolBlocks{};
			inline static size_t mCurrentPoolIndex{ 0 };

			FORCE_INLINE static void _AllocateNewMemoryPoolBlock()
			{
				//we don't intialize objects.
				type::mObjectPoolBlocks.push_back(new object_pool_block_type());
				type::mObjectPoolBlocks[type::mObjectPoolBlocks.size() - 1]->mAllocatedObjectPoolCount = 0;
			}
			
			FORCE_INLINE static T* _AllocateFromPool()
			{


				if (type::mObjectPoolBlocks.size() == 0 || type::mObjectPoolBlocks.size() < mCurrentPoolIndex)
				{
					type::_AllocateNewMemoryPoolBlock();
				}

				if (type::mObjectPoolBlocks[mCurrentPoolIndex]->mAllocatedObjectPoolCount >= PoolCountInBlock)
				{
					type::_AllocateNewMemoryPoolBlock();
					mCurrentPoolIndex++;
				}

				unsigned int objectIndex = (type::mObjectPoolBlocks[mCurrentPoolIndex]->mAllocatedObjectPoolCount)++;
				return reinterpret_cast<T*>(type::mObjectPoolBlocks[mCurrentPoolIndex]->ObjectPool) + objectIndex;
			}

		public:

			template <typename... Args>
			FORCE_INLINE static T* AllocateFromPool(Args&&... args)
			{
				T* NewObject = type::_AllocateFromPool();
				new (NewObject) T(std::forward<Args>(args)...); // call constructor
				//std::allocator_traits<
				return NewObject;
			}

		};
		
	

	}
}

*/