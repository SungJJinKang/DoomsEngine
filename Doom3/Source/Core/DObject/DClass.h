#pragma once

#include <type_traits>

namespace doom
{
	struct DClass /*: public doom::DObject*/ // Dont Do this
	{
		const char* const CLASS_TYPE_ID;
		const SIZE_T BASE_CHAIN_COUNT;
		const char* const* const BASE_CHAIN_DATA;
		const char* const CLASS_NAME;
		const UINT32 CLASS_FLAGS;

		/*
		DOBJECT_CLASS_BODY(DClass) // Dont Do this
		DOBJECT_CLASS_BASE_CHAIN(DObject) // Dont Do this
		*/
		constexpr DClass
		(
			const char* const _CLASS_TYPE_ID,
			const SIZE_T BASE_CHAIN_COUNT,
			const char* const* const BASE_CHAIN_DATA,
			const char* const _CLASS_NAME,
			const UINT32 _CLASS_FLAGS
		)
		:
		CLASS_TYPE_ID(_CLASS_TYPE_ID),
		BASE_CHAIN_COUNT(BASE_CHAIN_COUNT),
		BASE_CHAIN_DATA(BASE_CHAIN_DATA),
		CLASS_NAME(_CLASS_NAME),
		CLASS_FLAGS(_CLASS_FLAGS)
		{}

		template <typename BASE_TYPE>
		FORCE_INLINE bool IsChildOf() const
		{
			static_assert(IS_DOBJECT_TYPE(BASE_TYPE));

			const bool isChild = (BASE_CHAIN_COUNT >= BASE_TYPE::BASE_CHAIN_COUNT_STATIC()) && (BASE_CHAIN_DATA[BASE_CHAIN_COUNT - BASE_TYPE::BASE_CHAIN_COUNT_STATIC()] == BASE_TYPE::CLASS_TYPE_ID_STATIC());

			return isChild;
		}

		//TODO : Implement DefaultObject for CreateDObject from DClass ( use CopyConstructor )
	};



}