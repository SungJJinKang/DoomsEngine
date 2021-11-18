#pragma once

#include <Macros/DllMarcos.h>
#include "../Reflection.h"

#include <vector>
#include <unordered_map>

#include "DType.h"
#include "DField.h"

D_NAMESPACE(dooms)
namespace dooms
{
	class DObject;
	class DOOM_API D_STRUCT DClass : public DType /*: public dooms::DObject*/ // Dont Do this
	{
	private:

		static std::unordered_map<UINT32, std::vector<dooms::DField>> PropertyCacheHashMap;

	protected:

		const clcpp::Class* clClass;

	public:

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

			// TODO : 
			const bool isChild = false;// (BASE_CHAIN_COUNT >= BASE_TYPE::BASE_CHAIN_COUNT_STATIC()) && (BASE_CHAIN_DATA[BASE_CHAIN_COUNT - BASE_TYPE::BASE_CHAIN_COUNT_STATIC()] == BASE_TYPE::CLASS_TYPE_ID_STATIC());

			return isChild;
		}

		/*dooms::DObject* CreateDObject() const
		{
			/*
			D_ASSERT(CREATE_DOBJECT_FUNCTION_PTR != nullptr);

			dooms::DObject* CreatedDObject = nullptr;

			if(CREATE_DOBJECT_FUNCTION_PTR != nullptr)
			{
				CreatedDObject = (*CREATE_DOBJECT_FUNCTION_PTR)();
			}
			
			return CreatedDObject;
			#1#

			return nullptr;
		}*/

		//TODO : Implement DefaultObject for CreateDObject from DClass ( use CopyConstructor )

		//dooms:DClass* CreateDClass

		const std::vector<dooms::DField>& GetFieldList() const;
		bool GetField(const char* const fieldName, dooms::DField& dProperty) const;
	};


	template <typename DOBJECT_TYPE>
	extern dooms::DClass CreateDClass()
	{
		return dooms::DClass(DOBJECT_TYPE::TYPE_FULL_NAME_HASH_VALUE);
	}
}