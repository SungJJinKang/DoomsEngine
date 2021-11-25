#pragma once


#include <vector>

#include <Macros/TypeDef.h>
#include <Macros/DllMarcos.h>
#include "Macros/Assert.h"

#include "../Reflection.h"

#include "DPrimitive.h"
#include "DField.h"

extern "C"
{
	void call_func(unsigned __int64*, unsigned __int64*);
}

namespace dooms
{
	class DObject;

	namespace reflection
	{
		class DClass;
		class DAttributeList;
		class DOOM_API D_CLASS DFunction : public DPrimitive /*: public dooms::DObject*/ // Dont Do this
		{
		protected:

			const clcpp::Function* clFunction;

		public:


			FORCE_INLINE DFunction()
				: DPrimitive(), clFunction(nullptr)
			{

			}

			DFunction(const UINT32 nameHash);
			DFunction(const char* const functionName);
			FORCE_INLINE DFunction(const clcpp::Function* const _clFunction)
				: DPrimitive(_clFunction), clFunction(_clFunction)
			{
				D_ASSERT(clFunction != nullptr);
			}

			FORCE_INLINE bool IsValid() const
			{
				return clFunction != nullptr;
			}

			FORCE_INLINE const char* GetFunctionFullName() const
			{
				D_ASSERT(IsValid() == true);
				return clFunction->name.text;
			}

			FORCE_INLINE const char* GetFunctionName() const
			{
				D_ASSERT(IsValid() == true);
				return dPrimitiveHelper::GetShortNamePointer(clFunction->name.text);
			}

			FORCE_INLINE UINT_PTR* GetFunctionAddress() const
			{
				D_ASSERT(IsValid() == true);
				D_ASSERT(clFunction->address != NULL);
				return (UINT_PTR*)(clFunction->address);
			}
			FORCE_INLINE bool GetIsHasFunctionAddress() const
			{
				return GetFunctionAddress() != 0;
			}
			

			DField GetReturnValueField() const;
			bool GetIsHasReturnValue() const
			{
				return clFunction->return_parameter != nullptr;
			}

			/// <summary>
			/// return true, if this function is member function of class or struct ( not static, not global function )
			/// </summary>
			/// <returns></returns>
			bool GetIsMemberFunction() const;

			bool GetOwnerClassIfMemberFunction(DClass& dClass) const;

			/// <summary>
			/// return function's Paramter DField List.
			///	returned list doesn't contain "this" field even if it's member function
			/// </summary>
			/// <returns></returns>
			const std::vector<dooms::reflection::DField>& GetParameterDFieldList() const;
			bool GetParameterDField(const char* const parameterName, dooms::reflection::DField& dField) const;

			

			/// <summary>
			/// unsed for calling static function or global function
			/// </summary>
			/// <typeparam name="RETURN_TYPE"></typeparam>
			/// <typeparam name="...ARGS"></typeparam>
			/// <param name="returnPtr"></param>
			/// <param name="...args"></param>
			/// <returns></returns>
			template <typename RETURN_TYPE, typename... ARGS>
			bool CallFunction(RETURN_TYPE* returnPtr, ARGS&&... args)
			{
				D_ASSERT_LOG(false, "CURRENTLY NOT SUPPORTED");
				//TODO : Argument type check

				bool isSuccess = false;

				D_ASSERT(GetIsHasReturnValue() == true);
				D_ASSERT(GetIsMemberFunction() == false);
				D_ASSERT(GetParameterDFieldList().size() == (sizeof...(args)) );
				D_ASSERT(GetReturnValueField().GetFieldTypeHashValue() == clcpp::GetTypeNameHash<RETURN_TYPE>());
				D_ASSERT(GetReturnValueField().GetFieldTypeSize() == sizeof(RETURN_TYPE));
				
				typedef RETURN_TYPE (*CallFunc)(ARGS...);

				CallFunc functionAddress = reinterpret_cast<CallFunc>(GetFunctionAddress());
				D_ASSERT(functionAddress != 0);
				if (functionAddress != nullptr)
				{
					// TODO :
					*returnPtr = functionAddress(std::forward<ARGS>(args)...);
					isSuccess = true;
				}

				return isSuccess;
			}

			template <typename... ARGS>
			bool CallFunctionNoReturn(ARGS&&... args)
			{
				D_ASSERT_LOG(false, "CURRENTLY NOT SUPPORTED");
				//TODO : Argument type check

				bool isSuccess = false;
				
				D_ASSERT(GetIsHasReturnValue() == false);
				D_ASSERT(GetIsMemberFunction() == false);
				D_ASSERT(GetParameterDFieldList().size() == (sizeof...(args)) ); // why minus 1S? : member function has this field at first pos of Paramter List

				typedef void (*CallFunc)(ARGS...);

				CallFunc functionAddress = reinterpret_cast<CallFunc>(GetFunctionAddress());
				D_ASSERT(functionAddress != 0);
				if (functionAddress != nullptr)
				{
					functionAddress(std::forward<ARGS>(args)...);
					isSuccess = true;
				}

				return isSuccess;
			}

			

			/*/// <summary>
			/// unsed for calling member function
			/// </summary>
			/// <typeparam name="RETURN_TYPE"></typeparam>
			/// <typeparam name="...ARGS"></typeparam>
			/// <param name="classObject"></param>
			/// <param name="returnPtr"></param>
			/// <param name="...args"></param>
			/// <returns></returns>
			template <typename RETURN_TYPE, typename... ARGS>
			bool CallMemberFunction(void* const classObject, RETURN_TYPE* returnPtr, ARGS&&... args)
			{// classObject doesn't need to be DOBject type

				//TODO : Argument type check

				D_ASSERT(classObject != nullptr);

				bool isSuccess = false;

				D_ASSERT(GetIsHasReturnValue() == true);
				D_ASSERT(GetIsMemberFunction() == true);
				D_ASSERT(GetParameterDFieldList().size() == (sizeof...(args)) );
				D_ASSERT(GetReturnValueField().GetFieldTypeHashValue() == clcpp::GetTypeNameHash<RETURN_TYPE>());
				D_ASSERT(GetReturnValueField().GetFieldTypeSize() == sizeof(RETURN_TYPE));

				typedef RETURN_TYPE (FakeStruct::*CallFunc)(ARGS...);

				CallFunc functionAddress = reinterpret_cast<CallFunc>(GetFunctionAddress());
				D_ASSERT(functionAddress != 0);
				if (functionAddress != nullptr)
				{
					// TODO :
					*returnPtr = functionAddress(std::forward<ARGS>(args)...);
					isSuccess = true;
				}

				return isSuccess;
			}*/
			
			bool CallMemberFunctionNoReturnNoParameter(void* const classObject)
			{// classObject doesn't need to be DOBject type


				//TODO : Argument type check
				D_ASSERT(classObject != nullptr);

				bool isSuccess = false;

				D_ASSERT(GetIsHasReturnValue() == false);
				D_ASSERT(GetParameterDFieldList().empty() == true);
				D_ASSERT(GetIsMemberFunction() == true);
				
				UINT_PTR* const functionAddress = GetFunctionAddress();
				if (functionAddress != nullptr)
				{
					call_func(reinterpret_cast<unsigned __int64* >(classObject), functionAddress);
				}
				/*
				void(FakeStruct::*funcionPointer)() = (void(FakeStruct::*)())(GetFunctionAddress());
				
				if (funcionPointer != nullptr)
				{
					// TODO :
					reinterpret_cast<FakeStruct*>(classObject)->*funcionPointer();
					isSuccess = true;
				}
				*/

				return isSuccess;
			}

			FORCE_INLINE bool operator==(const DFunction& dFunction) const
			{
				return clFunction == dFunction.clFunction;
			}

			FORCE_INLINE bool operator!=(const DFunction& dFunction) const
			{
				return clFunction != dFunction.clFunction;
			}

			DAttributeList GetDAttributeList() const;
		};
	}
}
