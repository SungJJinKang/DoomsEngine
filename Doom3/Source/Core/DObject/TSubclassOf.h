#pragma once

#include <type_traits>

#include "DClass.h"

namespace doom
{
	class DObject;
	template <typename T>
	class TSubclassOf
	{
		static_assert(std::is_base_of_v<doom::DObject, T> == true);

		template <typename FromType>
		friend class TSubclassOf;

	private:

		DClass* mDClass;

	public:

		constexpr TSubclassOf()
			: mDClass { nullptr }
		{
			
		}

		template <typename FromType>
		explicit TSubclassOf(const TSubclassOf<FromType>& from)
		{
			*this = from;
		}

		explicit constexpr TSubclassOf(DClass* const from)
		{
			*this = from;
		}

		TSubclassOf& operator=(DClass* const from)
		{
			mDClass = ( from->IsChildOf<T>() == true ) ? from : nullptr;
			return *this;
		}

		template <typename FromType>
		TSubclassOf& operator=(const TSubclassOf<FromType>& from)
		{
			static_assert(std::is_base_of_v<doom::DObject, FromType> == true);

			if constexpr(std::is_base_of_v<T, FromType> == true)
			{
				mDClass = from.mDClass;
			}
			else
			{
				mDClass = nullptr;
			}


			return *this;
		}

		[[nodiscard]] DClass* GetDClass() const
		{
			return mDClass;
		}

		[[nodiscard]] operator DClass*() const
		{
			return GetDClass();
		}

		DClass* operator->() const
		{
			return GetDClass();
		}
	};
}