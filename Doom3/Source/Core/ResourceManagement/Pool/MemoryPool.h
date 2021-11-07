#pragma once

#include <vector>
#include <type_traits>
#include <atomic>

#include "Core.h"

namespace dooms
{
	namespace resource
	{
		struct MemoryPoolBlock
		{
			inline static constexpr UINT32 PoolSize{ 4096 - sizeof(size_t) };
			/// <summary>
			/// 
			/// If user destroy entity, that element will be invalidated
			/// We can't know element is destroyed..
			/// </summary>
			char mDatas[PoolSize];
			size_t mUnusedCapacityInByte{ PoolSize };
		};

		/// <summary>
		/// size of MemoryPoolBlock should be less than 4kb
		/// </summary>
		static_assert(sizeof(MemoryPoolBlock) <= 4096);

		/// <summary>
		///
		/// Feature : 
		/// Data objects is aligned to align size
		/// 
		/// 
		/// 
		/// references : https://github.com/cacay/MemoryPool/tree/master/C-11
		class MemoryPool
		{

		private:

			inline static std::vector<MemoryPoolBlock*> mObjectPoolBlocks{};
			inline static size_t mCurrentObjectPoolBlockIndex{ 0 };

			FORCE_INLINE static void _AllocateNewMemoryPoolBlock()
			{
				//we don't intialize objects.
				MemoryPool::mObjectPoolBlocks.push_back(new MemoryPoolBlock());
			}

			FORCE_INLINE static void _AllocateNewMemoryPoolBlock(size_t count)
			{
				//we don't intialize objects.
				for (size_t i = 0; i < count; i++)
				{
					MemoryPool::_AllocateNewMemoryPoolBlock();
				}				
			}

			/*
			/// <summary>
			/// For making instances to be aligned to WORD
			/// </summary>
			/// <param name="typeSize"></param>
			/// <returns></returns>
			FORCE_INLINE static constexpr size_t _GetAlignedSize(size_t typeSize)
			{
				return typeSize + (typeSize % sizeof(size_t) == 0 ? 0 : sizeof(size_t) - typeSize % sizeof(size_t));
			}
			*/

			template <typename T>
			FORCE_INLINE static T* _AllocateFromPool()
			{
				if (MemoryPool::mObjectPoolBlocks.size() == 0)
				{
					MemoryPool::_AllocateNewMemoryPoolBlock();
				}

				//size_t typeSize = MemoryPool::_GetAlignedSize(sizeof(T));
				size_t typeSize = sizeof(T);

				if (MemoryPool::mObjectPoolBlocks[MemoryPool::mObjectPoolBlocks.size() - 1]->mUnusedCapacityInByte < typeSize)
				{
					MemoryPool::_AllocateNewMemoryPoolBlock();
				}

				size_t targetIndex = MemoryPoolBlock::PoolSize - MemoryPool::mObjectPoolBlocks[MemoryPool::mObjectPoolBlocks.size() - 1]->mUnusedCapacityInByte;
				MemoryPool::mObjectPoolBlocks[MemoryPool::mObjectPoolBlocks.size() - 1]->mUnusedCapacityInByte -= typeSize;
				return reinterpret_cast<T*>(MemoryPool::mObjectPoolBlocks[MemoryPool::mObjectPoolBlocks.size() - 1]->mDatas + targetIndex);
			}

		public:

			template <typename T, typename... Args>
			FORCE_INLINE static T* AllocateFromPool(Args&&... args)
			{
				T* NewObject = MemoryPool::_AllocateFromPool();
				new (NewObject) T(std::forward<Args>(args)...); // call constructor
				//std::allocator_traits<
				return NewObject;
			}

			FORCE_INLINE static void PreAllocateMemoryPoolBlock(size_t blockCount)
			{
				MemoryPool::_AllocateNewMemoryPoolBlock(blockCount);
			}
		};

	}
}

