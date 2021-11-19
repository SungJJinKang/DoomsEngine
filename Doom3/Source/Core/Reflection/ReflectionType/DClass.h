#pragma once

#include <Macros/DllMarcos.h>
#include "../Reflection.h"

#include <vector>
#include <unordered_map>

#include "DType.h"
#include "DField.h"
#include "DFunction.h"

D_NAMESPACE(dooms)
namespace dooms
{
	class DObject;
	namespace reflection
	{
		class DOOM_API D_CLASS DClass : public DType /*: public dooms::DObject*/ // Dont Do this
		{
		private:

			static std::unordered_map<UINT32, std::unordered_map<std::string_view, dooms::reflection::DField>> PropertyCacheHashMap;
			static std::unordered_map<UINT32, std::unordered_map<std::string_view, dooms::reflection::DFunction>> FunctionCacheHashMap;

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



			/*
			template <typename BASE_TYPE>
			FORCE_INLINE bool IsChildOf() const
			{
				static_assert(IS_DOBJECT_TYPE(BASE_TYPE));

				// TODO : 
				const bool isChild = false;// (BASE_CHAIN_COUNT >= BASE_TYPE::BASE_CHAIN_LIST_LENGTH) && (BASE_CHAIN_DATA[BASE_CHAIN_COUNT - BASE_TYPE::BASE_CHAIN_LIST_LENGTH] == BASE_TYPE::TYPE_FULL_NAME_HASH_VALUE);

				return isChild;
			}
			*/


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

			const std::unordered_map<std::string_view, dooms::reflection::DField>& GetDFieldList() const;
			const std::unordered_map<std::string_view, dooms::reflection::DFunction>& GetDFunctionList() const;

			bool GetDField(const char* const fieldName, dooms::reflection::DField& dProperty) const;
			bool GetDFunction(const char* const functionName, dooms::reflection::DFunction& dFunction) const;



			
			/// <summary>
			/// Call Function
			///
			///	You can call only function with no return, no parameter
			/// </summary>
			/// <param name="functionName"></param>
			template <typename RETURN_TYPE, typename... ARGS>
			bool CallMemberFunction(void* const classObject, const char* const functionName, RETURN_TYPE* returnPtr, ARGS&&... args)
			{
				// TODO :

				bool isCallFunctionSuccess = false;

				dooms::reflection::DFunction dFunction;
				const bool isFindFunction = GetDFunction(functionName, dFunction);
				if(isFindFunction == true)
				{
					dFunction.CallMemberFunction(classObject, std::forward<RETURN_TYPE>(returnPtr), std::forward<ARGS>(args)...);
				}

				return isCallFunctionSuccess;
			}
		};


		template <typename DOBJECT_TYPE>
		extern dooms::reflection::DClass CreateDClass()
		{
			return dooms::reflection::DClass(DOBJECT_TYPE::TYPE_FULL_NAME_HASH_VALUE);
		}
	}
}