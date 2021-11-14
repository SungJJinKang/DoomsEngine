#pragma once

#include <type_traits>

#include "DClass.h"
#include "../Reflection.h"

namespace dooms
{
	class DObject;
	template <typename T>
	class TSubclassOf
	{
		// TODO : Implement this ( 2021/11/14 )
		static_assert(std::is_base_of_v<dooms::DObject, T> == true);

		template <typename FromType>
		friend class TSubclassOf;

	private:

		D_PROPERTY()
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
			static_assert(std::is_base_of_v<dooms::DObject, FromType> == true);

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

		NO_DISCARD DClass* GetDClass() const
		{
			return mDClass;
		}

		NO_DISCARD operator DClass*() const
		{
			return GetDClass();
		}

		DClass* operator->() const
		{
			return GetDClass();
		}
	};
}