#pragma once

#include <type_traits>

#include <Macros/DllMarcos.h>
#include "../Reflection.h"

#include "DType.h"

D_NAMESPACE(dooms)
namespace dooms
{
	class DObject;
	struct DOOM_API D_STRUCT DClass : public DType /*: public dooms::DObject*/ // Dont Do this
	{
		const clcpp::Class* const clClass;

		//D_PROPERTY()
		//const size_t BASE_CHAIN_COUNT;

		//D_PROPERTY()
		//const char* const* const BASE_CHAIN_DATA;
		
		//D_PROPERTY()
		//const UINT32 CLASS_FLAGS;
		
		DClass(dooms::DObject* const dObject);
		DClass(const UINT32 nameHash);
		DClass(const clcpp::Class* const clcppType);

		

		template <typename BASE_TYPE>
		FORCE_INLINE bool IsChildOf() const
		{
			static_assert(IS_DOBJECT_TYPE(BASE_TYPE));

			const bool isChild = false;// (BASE_CHAIN_COUNT >= BASE_TYPE::BASE_CHAIN_COUNT_STATIC()) && (BASE_CHAIN_DATA[BASE_CHAIN_COUNT - BASE_TYPE::BASE_CHAIN_COUNT_STATIC()] == BASE_TYPE::CLASS_TYPE_ID_STATIC());

			return isChild;
		}

		dooms::DObject* CreateDObject() const
		{
			/*
			D_ASSERT(CREATE_DOBJECT_FUNCTION_PTR != nullptr);

			dooms::DObject* CreatedDObject = nullptr;

			if(CREATE_DOBJECT_FUNCTION_PTR != nullptr)
			{
				CreatedDObject = (*CREATE_DOBJECT_FUNCTION_PTR)();
			}
			
			return CreatedDObject;
			*/

			return nullptr;
		}

		//TODO : Implement DefaultObject for CreateDObject from DClass ( use CopyConstructor )

		//dooms:DClass* CreateDClass
	};



}