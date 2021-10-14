#pragma once

#include <vector>
#include <type_traits>
#include <atomic>

#include "Core.h"

namespace doom
{
	namespace resource
	{
		struct MemoryPoolBlock
		{
			inline static constexpr UINT32 PoolSize{ 4096 - sizeof(SIZE_T) };
			/// <summary>
			/// 
			/// If user destroy entity, that element will be invalidated
			/// We can't know element is destroyed..
			/// </summary>
			char mDatas[PoolSize];
			SIZE_T mUnusedCapacityInByte{ PoolSize };
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
			inline static SIZE_T mCurrentObjectPoolBlockIndex{ 0 };

			FORCE_INLINE static void _AllocateNewMemoryPoolBlock()
			{
				//we don't intialize objects.
				MemoryPool::mObjectPoolBlocks.push_back(new MemoryPoolBlock());
			}

			FORCE_INLINE static void _AllocateNewMemoryPoolBlock(SIZE_T count)
			{
				//we don't intialize objects.
				for (SIZE_T i = 0; i < count; i++)
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
			FORCE_INLINE static constexpr SIZE_T _GetAlignedSize(SIZE_T typeSize)
			{
				return typeSize + (typeSize % sizeof(SIZE_T) == 0 ? 0 : sizeof(SIZE_T) - typeSize % sizeof(SIZE_T));
			}
			*/

			template <typename T>
			FORCE_INLINE static T* _AllocateFromPool()
			{
				if (MemoryPool::mObjectPoolBlocks.size() == 0)
				{
					MemoryPool::_AllocateNewMemoryPoolBlock();
				}

				//SIZE_T typeSize = MemoryPool::_GetAlignedSize(sizeof(T));
				SIZE_T typeSize = sizeof(T);

				if (MemoryPool::mObjectPoolBlocks[MemoryPool::mObjectPoolBlocks.size() - 1]->mUnusedCapacityInByte < typeSize)
				{
					MemoryPool::_AllocateNewMemoryPoolBlock();
				}

				SIZE_T targetIndex = MemoryPoolBlock::PoolSize - MemoryPool::mObjectPoolBlocks[MemoryPool::mObjectPoolBlocks.size() - 1]->mUnusedCapacityInByte;
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

			FORCE_INLINE static void PreAllocateMemoryPoolBlock(SIZE_T blockCount)
			{
				MemoryPool::_AllocateNewMemoryPoolBlock(blockCount);
			}
		};

	}
}

