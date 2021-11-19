#pragma once

#include <type_traits>

#include "DClass.h"
#include "../Reflection.h"

namespace dooms
{
	class DObject;

	namespace reflection
	{

		template <typename T>
		class DOOM_API D_CLASS TSubclassOf
		{
			// TODO : Implement this ( 2021/11/14 )
			static_assert(std::is_base_of_v<dooms::DObject, T> == true);

			template <typename FromType>
			friend class TSubclassOf;

		private:

			D_PROPERTY()
			dooms::reflection::DClass* mDClass;

		public:

			constexpr TSubclassOf()
				: mDClass{ nullptr }
			{

			}

			template <typename FromType>
			explicit TSubclassOf(const TSubclassOf<FromType>& from)
			{
				*this = from;
			}

			explicit constexpr TSubclassOf(dooms::reflection::DClass* const from)
			{
				*this = from;
			}

			/*
			TSubclassOf& operator=(dooms::reflection::DClass* const from)
			{
				mDClass = (from->IsChildOf<T>() == true) ? from : nullptr;
				return *this;
			}

			template <typename FromType>
			TSubclassOf& operator=(const TSubclassOf<FromType>& from)
			{
				static_assert(std::is_base_of_v<dooms::DObject, FromType> == true);

				if constexpr (std::is_base_of_v<T, FromType> == true)
				{
					mDClass = from.mDClass;
				}
				else
				{
					mDClass = nullptr;
				}


				return *this;
			}
			*/

			NO_DISCARD dooms::reflection::DClass* GetDClass() const
			{
				return mDClass;
			}

			NO_DISCARD operator DClass* () const
			{
				return GetDClass();
			}

			dooms::reflection::DClass* operator->() const
			{
				return GetDClass();
			}
		};
	}
}