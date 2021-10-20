#pragma once

#include <type_traits>

#include "DOBJECT_BASE_CHAIN.h"

#include "DObject.h"

namespace doom
{
	class DObject;
	struct DClass /*: public doom::DObject*/ // Dont Do this
	{
		const SIZE_T CLASS_TYPE_ID;
		const DOBJECT_BASE_CHAIN BASE_CHAIN;
		const std::string CLASS_NAME;
		const UINT32 CLASS_FLAGS;

		/*
		DOBJECT_CLASS_BODY(DClass) // Dont Do this
		DOBJECT_CLASS_BASE_CHAIN(DObject) // Dont Do this
		*/
		DClass
		(
			const SIZE_T _CLASS_TYPE_ID,
			const DOBJECT_BASE_CHAIN& _BASE_CHAIN,
			const std::string& _CLASS_NAME,
			const UINT32 _CLASS_FLAGS
		) : CLASS_TYPE_ID(_CLASS_TYPE_ID), BASE_CHAIN(_BASE_CHAIN), CLASS_NAME(_CLASS_NAME), CLASS_FLAGS(_CLASS_FLAGS)
		{}

		//TODO : Implement DefaultObject for CreateDObject from DClass ( use CopyConstructor )
	};

	template <typename DOBJECT_TYPE>
	extern DClass CreateDClass()
	{
		static_assert(std::is_base_of_v<doom::DObject, DOBJECT_TYPE> == true);
		return DClass(DOBJECT_TYPE::CLASS_TYPE_ID_STATIC(), DOBJECT_TYPE::BASE_CHAIN_STATIC(), DOBJECT_TYPE::CLASS_NAME_STATIC(), DOBJECT_TYPE::CLASS_FLAGS_STATIC());
	}
}