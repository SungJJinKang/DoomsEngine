#pragma once

#include <Core.h>

#include "Array.h"

namespace dooms
{
	namespace stl
	{
		/// <summary>
		/// This library is for reducing reallocation overhead of when capacity is full
		///
		/// </summary>
		/// <typeparam name="ELEMENT_TYPE"></typeparam>
		template <typename ELEMENT_TYPE>
		class D_CLASS ChunkArray
		{

		public:

			using sizeType = size_t;
			using valueType = dooms::stl::Array<ELEMENT_TYPE>;
			using reference = dooms::stl::Array<ELEMENT_TYPE>&;
			using const_reference = const dooms::stl::Array<ELEMENT_TYPE>&;
			using pointer = dooms::stl::Array<ELEMENT_TYPE>*;
			using const_pointer = const dooms::stl::Array<ELEMENT_TYPE>*;

			//inline static constexpr sizeType CapacityCountOfChunk;

		private:

			dooms::stl::Array<dooms::stl::Array<ELEMENT_TYPE>> mArrays;

		private:

			void Destroy();
			void ResizeGrow(const sizeType size);
			void ResizeShrink(const sizeType size);
			void Expand();

		public:

			ChunkArray();
			~ChunkArray();
			ChunkArray(const ChunkArray& arr);
			ChunkArray(ChunkArray&& arr) noexcept;
			ChunkArray& operator=(const ChunkArray& arr);
			ChunkArray& operator=(ChunkArray&& arr) noexcept;
			void Reserve(const sizeType size);
			void Push_Back(const ELEMENT_TYPE& element);
			void Push_Back(ELEMENT_TYPE&& element);
			template<typename... ARGS>
			void Emplace_Back(ARGS&&... args);
			bool Empty() const;
			sizeType Count() const;
			sizeType Capacity() const;
			reference operator[](const sizeType index);
			const_reference operator[](const sizeType index) const;
			void Resize(const sizeType targetCount);
			void Clear();

		};

		template <typename ELEMENT_TYPE>
		void ChunkArray<ELEMENT_TYPE>::Destroy()
		{
			mArrays.~Array();
		}

		template <typename ELEMENT_TYPE>
		void ChunkArray<ELEMENT_TYPE>::ResizeGrow(const sizeType reAllocChunkCount)
		{
			assert(reAllocChunkCount > Count());

			ELEMENT_TYPE* const newlyAllocatedBufferBegin = reinterpret_cast<ELEMENT_TYPE*>(malloc(reAllocChunkCount * sizeof(ELEMENT_TYPE)));

			const sizeType currentElementCount = Count();

			for (sizeType elementIndex = 0; elementIndex < currentElementCount; elementIndex++)
			{
				new (newlyAllocatedBufferBegin + elementIndex) ELEMENT_TYPE(move(mBufferBegin[elementIndex]));
			}

			if (mBufferBegin != nullptr)
			{
				free(mBufferBegin);
			}

			mBufferBegin = newlyAllocatedBufferBegin;
			mBufferEnd = newlyAllocatedBufferBegin + currentElementCount;
			mBufferCapacityEnd = newlyAllocatedBufferBegin + reAllocChunkCount;
		}

		template <typename ELEMENT_TYPE>
		void ChunkArray<ELEMENT_TYPE>::ResizeShrink(const sizeType reAllocChunkCount)
		{
			assert(reAllocChunkCount < Count());

			ELEMENT_TYPE* const newlyAllocatedBufferBegin = nullptr;

			if (reAllocChunkCount > 0)
			{
				newlyAllocatedBufferBegin = reinterpret_cast<ELEMENT_TYPE*>(malloc(reAllocChunkCount * sizeof(ELEMENT_TYPE)));

				const sizeType currentElementCount = Count();

				for (sizeType elementIndex = 0; elementIndex < reAllocChunkCount; elementIndex++)
				{
					new (newlyAllocatedBufferBegin + elementIndex) ELEMENT_TYPE(move(mBufferBegin[elementIndex]));
				}
			}


			for (sizeType elementIndex = reAllocChunkCount; elementIndex < currentElementCount; elementIndex++)
			{
				(mBufferBegin + elementIndex)->~ELEMENT_TYPE();
			}

			free(mBufferBegin);

			mBufferBegin = newlyAllocatedBufferBegin;
			mBufferEnd = newlyAllocatedBufferBegin + currentElementCount;
			mBufferCapacityEnd = newlyAllocatedBufferBegin + reAllocChunkCount;
		}

		template <typename ELEMENT_TYPE>
		void ChunkArray<ELEMENT_TYPE>::Expand()
		{
			const sizeType currentCapacity = Capacity();
			ResizeGrow(currentCapacity == 0 ? (1) : (currentCapacity * 2));
		}

		template <typename ELEMENT_TYPE>
		ChunkArray<ELEMENT_TYPE>::ChunkArray()
			:
			mArrays()
		{
		}

		template <typename ELEMENT_TYPE>
		ChunkArray<ELEMENT_TYPE>::~ChunkArray()
		{
			Destroy();
		}

		template <typename ELEMENT_TYPE>
		ChunkArray<ELEMENT_TYPE>::ChunkArray(const ChunkArray& arr)
			: mArrays(arr.mArrays)
		{
		}

		template <typename ELEMENT_TYPE>
		ChunkArray<ELEMENT_TYPE>::ChunkArray(ChunkArray&& arr) noexcept
			: mArrays(std::move(arr.mArrays))
		{
		}

		template <typename ELEMENT_TYPE>
		ChunkArray<ELEMENT_TYPE>& ChunkArray<ELEMENT_TYPE>::operator=(const ChunkArray<ELEMENT_TYPE>& arr)
		{
			Destroy();

			mArrays = arr.mArrays;

			return *this;
		}

		template <typename ELEMENT_TYPE>
		ChunkArray<ELEMENT_TYPE>& ChunkArray<ELEMENT_TYPE>::operator=(ChunkArray<ELEMENT_TYPE>&& arr) noexcept
		{
			Destroy();

			mArrays = std::move(arr.mArrays);

			return *this;
		}

		template <typename ELEMENT_TYPE>
		void ChunkArray<ELEMENT_TYPE>::Reserve(const sizeType reservationCount)
		{
			if (reservationCount > Count())
			{
				ResizeGrow(reservationCount);
			}
		}



		template <typename ELEMENT_TYPE>
		void ChunkArray<ELEMENT_TYPE>::Push_Back(const ELEMENT_TYPE& element)
		{
			if (Count() == Capacity())
			{
				Expand();
			}

			*mBufferEnd = element;
			mBufferEnd++;
		}

		template <typename ELEMENT_TYPE>
		void ChunkArray<ELEMENT_TYPE>::Push_Back(ELEMENT_TYPE&& element)
		{
			if (Count() == Capacity())
			{
				Expand();
			}

			*mBufferEnd = move(element);
			++mBufferEnd;
		}

		template <typename ELEMENT_TYPE>
		template <typename... ARGS>
		void ChunkArray<ELEMENT_TYPE>::Emplace_Back(ARGS&&... args)
		{
			if (Count() == Capacity())
			{
				Expand();
			}

			new (mBufferEnd) ELEMENT_TYPE(move(args)...);
			++mBufferEnd;
		}

		template <typename ELEMENT_TYPE>
		bool ChunkArray<ELEMENT_TYPE>::Empty() const
		{
			return mArrays.Empty();
		}

		template <typename ELEMENT_TYPE>
		ChunkArray<ELEMENT_TYPE>::sizeType ChunkArray<ELEMENT_TYPE>::Count() const
		{
			return mArrays.Count();
		}

		template <typename ELEMENT_TYPE>
		ChunkArray<ELEMENT_TYPE>::sizeType ChunkArray<ELEMENT_TYPE>::Capacity() const
		{
			return mArrays.Capacity();
		}

		template <typename ELEMENT_TYPE>
		ChunkArray<ELEMENT_TYPE>::reference ChunkArray<ELEMENT_TYPE>::operator[](const sizeType index)
		{
			assert(Count() > index);
			return mArrays[index];
		}

		template <typename ELEMENT_TYPE>
		ChunkArray<ELEMENT_TYPE>::const_reference ChunkArray<ELEMENT_TYPE>::operator[](const sizeType index) const
		{
			assert(Count() > index);
			return mArrays[index];
		}

		template <typename ELEMENT_TYPE>
		void ChunkArray<ELEMENT_TYPE>::Resize(const sizeType targetCount)
		{
			const sizeType curretCount = Count();
			assert(curretCount != targetCount);
			if (targetCount > curretCount)
			{
				ResizeGrow(targetCount);
			}
			else if (targetCount < curretCount)
			{
				ResizeShrink(targetCount);
			}
		}

		template <typename ELEMENT_TYPE>
		void ChunkArray<ELEMENT_TYPE>::Clear()
		{
			mArrays.Clear();
		}
	}
}

