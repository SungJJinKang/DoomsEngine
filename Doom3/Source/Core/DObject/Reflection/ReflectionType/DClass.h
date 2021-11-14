#pragma once

#include <type_traits>

#include <Macros/DllMarcos.h>
#include "../Reflection.h"

D_NAMESPACE(dooms)
namespace dooms
{
	class DObject;
	struct DOOM_API D_STRUCT DClass /*: public dooms::DObject*/ // Dont Do this
	{
		// TODO : Implement this ( 2021/11/14 )
		D_PROPERTY()
		const size_t CLASS_TYPE_SIZE;

		D_PROPERTY()
		const char* const CLASS_TYPE_ID;

		D_PROPERTY()
		const size_t BASE_CHAIN_COUNT;

		//D_PROPERTY()
		const char* const* const BASE_CHAIN_DATA;

		D_PROPERTY()
		const char* const CLASS_NAME;

		D_PROPERTY()
		const UINT32 CLASS_FLAGS;
		
		dooms::DObject* (*const CREATE_DOBJECT_FUNCTION_PTR) () ;

		/*
		
		
		*/
		DClass
		(
			const size_t _CLASS_TYPE_SIZE,
			const char* const _CLASS_TYPE_ID,
			const size_t BASE_CHAIN_COUNT,
			const char* const* const BASE_CHAIN_DATA,
			const char* const _CLASS_NAME,
			const UINT32 _CLASS_FLAGS,
			dooms::DObject* (* const _CREATE_DOBJECT_FUNCTION_PTR) ()
		)
		:
		CLASS_TYPE_SIZE(_CLASS_TYPE_SIZE),
		CLASS_TYPE_ID(_CLASS_TYPE_ID),
		BASE_CHAIN_COUNT(BASE_CHAIN_COUNT),
		BASE_CHAIN_DATA(BASE_CHAIN_DATA),
		CLASS_NAME(_CLASS_NAME),
		CLASS_FLAGS(_CLASS_FLAGS),
		CREATE_DOBJECT_FUNCTION_PTR(_CREATE_DOBJECT_FUNCTION_PTR)
		{}

		template <typename BASE_TYPE>
		FORCE_INLINE bool IsChildOf() const
		{
			static_assert(IS_DOBJECT_TYPE(BASE_TYPE));

			const bool isChild = (BASE_CHAIN_COUNT >= BASE_TYPE::BASE_CHAIN_COUNT_STATIC()) && (BASE_CHAIN_DATA[BASE_CHAIN_COUNT - BASE_TYPE::BASE_CHAIN_COUNT_STATIC()] == BASE_TYPE::CLASS_TYPE_ID_STATIC());

			return isChild;
		}

		dooms::DObject* CreateDObject() const
		{
			D_ASSERT(CREATE_DOBJECT_FUNCTION_PTR != nullptr);

			dooms::DObject* CreatedDObject = nullptr;

			if(CREATE_DOBJECT_FUNCTION_PTR != nullptr)
			{
				CreatedDObject = (*CREATE_DOBJECT_FUNCTION_PTR)();
			}

			return CreatedDObject;
		}

		//TODO : Implement DefaultObject for CreateDObject from DClass ( use CopyConstructor )

		//dooms:DClass* CreateDClass
	};



}