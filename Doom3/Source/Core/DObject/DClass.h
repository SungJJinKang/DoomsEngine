#pragma once

#include <type_traits>

#include "DObject.h"

namespace doom
{
	class DObject;
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
		DClass
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

		//TODO : Implement DefaultObject for CreateDObject from DClass ( use CopyConstructor )
	};

	template <typename DOBJECT_TYPE>
	extern DClass CreateDClass()
	{
		static_assert(std::is_base_of_v<doom::DObject, DOBJECT_TYPE> == true);
		return DClass(
			DOBJECT_TYPE::CLASS_TYPE_ID_STATIC(), 
			DOBJECT_TYPE::BASE_CHAIN_COUNT_STATIC(), 
			DOBJECT_TYPE::BASE_CHAIN_DATA_STATIC(), 
			DOBJECT_TYPE::CLASS_NAME_STATIC(), 
			DOBJECT_TYPE::CLASS_FLAGS_STATIC()
		);
	}
}