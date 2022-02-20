#pragma once
#include <Core.h>

#include <cassert>
#include <stdlib.h>

namespace dooms
{
	namespace stl
	{
		// TODO : support std iterator

		template <typename ELEMENT_TYPE>
		class D_CLASS Array
		{
		public:

			using sizeType = size_t;
			using valueType = ELEMENT_TYPE;
			using reference = ELEMENT_TYPE&;
			using const_reference = const ELEMENT_TYPE&;
			using pointer = ELEMENT_TYPE*;
			using const_pointer = const ELEMENT_TYPE*;

		private:

			ELEMENT_TYPE* mBufferBegin;
			ELEMENT_TYPE* mBufferEnd;
			ELEMENT_TYPE* mBufferCapacityEnd;

		private:

			void Destroy();
			void NullifyBufferPtr();
			void ResizeGrow(const sizeType size);
			void ResizeShrink(const sizeType size);

			void Expand();

		public:

			Array();
			~Array();
			Array(const Array& arr);
			Array(Array&& arr) noexcept;
			Array& operator=(const Array& arr);
			Array& operator=(Array&& arr) noexcept;
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
			pointer RawPointer();
			const_pointer RawPointer() const;
			void Resize(const sizeType targetCount);
			void Clear();
			
		};

		template <typename ELEMENT_TYPE>
		void Array<ELEMENT_TYPE>::Destroy()
		{
			if(mBufferBegin != nullptr)
			{
				const sizeType elementCount = Count();
				for (sizeType elementIndex = 0; elementIndex < elementCount; elementIndex++)
				{
					mBufferBegin[elementIndex].~ELEMENT_TYPE();
				}

				free(mBufferBegin);
			}			
		}

		template <typename ELEMENT_TYPE>
		void Array<ELEMENT_TYPE>::NullifyBufferPtr()
		{
			mBufferBegin = nullptr;
			mBufferEnd = nullptr;
			mBufferCapacityEnd = nullptr;
		}

		template <typename ELEMENT_TYPE>
		void Array<ELEMENT_TYPE>::ResizeGrow(const sizeType reAllocElementCount)
		{
			assert(reAllocElementCount > Count());

			ELEMENT_TYPE* const newlyAllocatedBufferBegin = reinterpret_cast<ELEMENT_TYPE*>(malloc(reAllocElementCount * sizeof(ELEMENT_TYPE)));

			const sizeType currentElementCount = Count();

			for (sizeType elementIndex = 0; elementIndex < currentElementCount; elementIndex++)
			{
				new (newlyAllocatedBufferBegin + elementIndex) ELEMENT_TYPE(move(mBufferBegin[elementIndex]));
			}

			if(mBufferBegin != nullptr)
			{
				free(mBufferBegin);
			}

			mBufferBegin = newlyAllocatedBufferBegin;
			mBufferEnd = newlyAllocatedBufferBegin + currentElementCount;
			mBufferCapacityEnd = newlyAllocatedBufferBegin + reAllocElementCount;
		}

		template <typename ELEMENT_TYPE>
		void Array<ELEMENT_TYPE>::ResizeShrink(const sizeType reAllocElementCount)
		{
			assert(reAllocElementCount < Count());

			ELEMENT_TYPE* const newlyAllocatedBufferBegin = nullptr;

			if(reAllocElementCount > 0)
			{
				newlyAllocatedBufferBegin = reinterpret_cast<ELEMENT_TYPE*>(malloc(reAllocElementCount * sizeof(ELEMENT_TYPE)));

				const sizeType currentElementCount = Count();

				for (sizeType elementIndex = 0; elementIndex < reAllocElementCount; elementIndex++)
				{
					new (newlyAllocatedBufferBegin + elementIndex) ELEMENT_TYPE(move(mBufferBegin[elementIndex]));
				}
			}
			

			for (sizeType elementIndex = reAllocElementCount; elementIndex < currentElementCount; elementIndex++)
			{
				(mBufferBegin + elementIndex)->~ELEMENT_TYPE();
			}

			free(mBufferBegin);

			mBufferBegin = newlyAllocatedBufferBegin;
			mBufferEnd = newlyAllocatedBufferBegin + currentElementCount;
			mBufferCapacityEnd = newlyAllocatedBufferBegin + reAllocElementCount;
		}

		template <typename ELEMENT_TYPE>
		void Array<ELEMENT_TYPE>::Expand()
		{
			const sizeType currentCapacity = Capacity();
			ResizeGrow(currentCapacity == 0 ? (1) : (currentCapacity * 2));
		}

		template <typename ELEMENT_TYPE>
		Array<ELEMENT_TYPE>::Array()
			:
			mBufferBegin{ nullptr },
			mBufferEnd{ nullptr },
			mBufferCapacityEnd{ nullptr }
		{
		}

		template <typename ELEMENT_TYPE>
		Array<ELEMENT_TYPE>::~Array()
		{
			Destroy();
			NullifyBufferPtr();
		}

		template <typename ELEMENT_TYPE>
		Array<ELEMENT_TYPE>::Array(const Array& arr)
		{
			const sizeType passedArrayElementSize = arr.Count();
			if (passedArrayElementSize > 0)
			{
				mBufferBegin = reinterpret_cast<ELEMENT_TYPE*>(malloc(passedArrayElementSize * sizeof(ELEMENT_TYPE)));
				mBufferEnd = mBufferBegin + passedArrayElementSize;
				mBufferCapacityEnd = mBufferEnd;

				for (sizeType elementIndex = 0; elementIndex < passedArrayElementSize; elementIndex++)
				{
					new (mBufferBegin + elementIndex) ELEMENT_TYPE(arr.mBufferBegin[elementIndex]);
				}
			}
			else
			{
				NullifyBufferPtr();
			}
		}

		template <typename ELEMENT_TYPE>
		Array<ELEMENT_TYPE>::Array(Array&& arr) noexcept
		{
			mBufferBegin = arr.mBufferBegin;
			mBufferEnd = arr.mBufferEnd;
			mBufferCapacityEnd = arr.mBufferCapacityEnd;

			arr.NullifyBufferPtr();
		}

		template <typename ELEMENT_TYPE>
		Array<ELEMENT_TYPE>& Array<ELEMENT_TYPE>::operator=(const Array<ELEMENT_TYPE>& arr)
		{
			const sizeType currentArrayElementCount = Count();
			const sizeType passedArrayElementCount = arr.Count();
			if (currentArrayElementCount >= passedArrayElementCount)
			{
				for (sizeType elementIndex = 0; elementIndex < passedArrayElementCount; elementIndex++)
				{
					mBufferBegin[elementIndex] = arr.mBufferBegin[elementIndex];
				}

				for (sizeType elementIndex = passedArrayElementCount; elementIndex < currentArrayElementCount; elementIndex++)
				{
					mBufferBegin[elementIndex].~ELEMENT_TYPE();
				}

				mBufferEnd = mBufferBegin + passedArrayElementCount;
			}
			else
			{
				Destroy();

				mBufferBegin = reinterpret_cast<ELEMENT_TYPE*>(malloc(passedArrayElementCount * sizeof(ELEMENT_TYPE)));
				mBufferEnd = mBufferBegin + passedArrayElementCount;
				mBufferCapacityEnd = mBufferEnd;

				for (sizeType elementIndex = 0; elementIndex < passedArrayElementCount; elementIndex++)
				{
					new (mBufferBegin + elementIndex) ELEMENT_TYPE(arr.mBufferBegin[elementIndex]);
				}
			}

			return *this;
		}

		template <typename ELEMENT_TYPE>
		Array<ELEMENT_TYPE>& Array<ELEMENT_TYPE>::operator=(Array<ELEMENT_TYPE>&& arr) noexcept
		{
			Destroy();

			mBufferBegin = arr.mBufferBegin;
			mBufferEnd = arr.mBufferEnd;
			mBufferCapacityEnd = arr.mBufferCapacityEnd;

			arr.NullifyBufferPtr();

			return *this;
		}

		template <typename ELEMENT_TYPE>
		void Array<ELEMENT_TYPE>::Reserve(const sizeType reservationCount)
		{
			if (reservationCount > Count())
			{
				ResizeGrow(reservationCount);
			}
		}



		template <typename ELEMENT_TYPE>
		void Array<ELEMENT_TYPE>::Push_Back(const ELEMENT_TYPE& element)
		{
			if (Count() == Capacity())
			{
				Expand();
			}

			*mBufferEnd = element;
			mBufferEnd++;
		}

		template <typename ELEMENT_TYPE>
		void Array<ELEMENT_TYPE>::Push_Back(ELEMENT_TYPE&& element)
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
		void Array<ELEMENT_TYPE>::Emplace_Back(ARGS&&... args)
		{
			if (Count() == Capacity())
			{
				Expand();
			}

			new (mBufferEnd) ELEMENT_TYPE(move(args)...);
			++mBufferEnd;
		}

		template <typename ELEMENT_TYPE>
		bool Array<ELEMENT_TYPE>::Empty() const
		{
			return (mBufferBegin == mBufferEnd);
		}

		template <typename ELEMENT_TYPE>
		Array<ELEMENT_TYPE>::sizeType Array<ELEMENT_TYPE>::Count() const
		{
			return mBufferEnd - mBufferBegin;
		}

		template <typename ELEMENT_TYPE>
		Array<ELEMENT_TYPE>::sizeType Array<ELEMENT_TYPE>::Capacity() const
		{
			return mBufferCapacityEnd - mBufferBegin;
		}

		template <typename ELEMENT_TYPE>
		Array<ELEMENT_TYPE>::reference Array<ELEMENT_TYPE>::operator[](const sizeType index)
		{
			assert(Count() > index);
			return mBufferBegin[index];
		}

		template <typename ELEMENT_TYPE>
		Array<ELEMENT_TYPE>::const_reference Array<ELEMENT_TYPE>::operator[](const sizeType index) const
		{
			assert(Count() > index);
			return mBufferBegin[index];
		}

		template <typename ELEMENT_TYPE>
		Array<ELEMENT_TYPE>::pointer Array<ELEMENT_TYPE>::RawPointer()
		{
			return mBufferBegin;
		}

		template <typename ELEMENT_TYPE>
		Array<ELEMENT_TYPE>::const_pointer Array<ELEMENT_TYPE>::RawPointer() const
		{
			return mBufferBegin;
		}

		template <typename ELEMENT_TYPE>
		void Array<ELEMENT_TYPE>::Resize(const sizeType targetCount)
		{
			const sizeType curretCount = Count();
			assert(curretCount != targetCount);
			if(targetCount > curretCount)
			{
				ResizeGrow(targetCount);
			}
			else if(targetCount < curretCount)
			{
				ResizeShrink(targetCount);
			}
		}

		template <typename ELEMENT_TYPE>
		void Array<ELEMENT_TYPE>::Clear()
		{
			const sizeType elementCount = mBufferEnd - mBufferBegin;
			for (sizeType elementIndex = 0; elementIndex < elementCount; elementIndex++)
			{
				mBufferBegin[elementIndex].~ELEMENT_TYPE();
			}

			mBufferEnd = mBufferBegin;
		}
	}
}

