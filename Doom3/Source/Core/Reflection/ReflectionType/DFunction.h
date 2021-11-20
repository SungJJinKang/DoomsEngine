#pragma once


#include <vector>

#include <Macros/TypeDef.h>
#include <Macros/DllMarcos.h>
#include "Macros/Assert.h"

#include "../Reflection.h"

#include "DPrimitive.h"
#include "DField.h"

namespace dooms
{
	class DObject;

	namespace reflection
	{
		class DClass;
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

			FORCE_INLINE void* GetFunctionAddress() const
			{
				D_ASSERT(IsValid() == true);
				D_ASSERT(clFunction->address != NULL);
				return reinterpret_cast<void*>(clFunction->address);
			}
			

			DField GetReturnValueField() const;

			/// <summary>
			/// return true, if this function is member function of class or struct ( not static, not global function )
			/// </summary>
			/// <returns></returns>
			bool GetIsMemberFunction() const;

			bool GetOwnerClassIfMemberFunction(DClass& dClass) const;

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
				bool isSuccess = false;

				D_ASSERT(GetParameterDFieldList().size() == sizeof...(args));
				
				typedef void (*CallFunc)(ARGS...);

				CallFunc functionAddress = GetFunctionAddress();
				D_ASSERT(functionAddress != 0);
				if (functionAddress != nullptr)
				{
					// TODO :
				}

				return functionAddress;
			}



			/// <summary>
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
			{
				void* const functionAddress = GetFunctionAddress();

				bool isSuccess = false;

				if (functionAddress != nullptr)
				{
					// TODO :
				}

				return functionAddress;
				
			}

			FORCE_INLINE bool operator==(const DFunction& dFunction) const
			{
				return clFunction == dFunction.clFunction;
			}

			FORCE_INLINE bool operator!=(const DFunction& dFunction) const
			{
				return clFunction != dFunction.clFunction;
			}
		};
	}
}
