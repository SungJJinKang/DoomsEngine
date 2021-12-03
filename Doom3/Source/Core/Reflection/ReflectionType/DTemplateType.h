#pragma once


#include <Macros/Assert.h>
#include <Macros/DllMarcos.h>

#include <vector>
#include <string>

#include "../Reflection.h"
#include "DType.h"


D_NAMESPACE(dooms)
namespace dooms
{
	class DObject;
	namespace reflection
	{
		class DTemplateArgumentType;

		namespace dTemplateTypeHelper
		{
			bool GetTemplateTypeNameFromTypeFullName(const char* const typeFullName, std::string& outString);
		}

		class DOOM_API D_CLASS DTemplateType : public DType /*: public dooms::DObject*/ // Dont Do this
		{
		protected:

			const clcpp::TemplateType* clTemplateType;

		public:

			DTemplateType(const clcpp::TemplateType* const _clTemplateType);
			
			size_t GetTemplateArgumentCount() const;
			reflection::DTemplateArgumentType GetTemplateArgumentType(const size_t index) const;
			const std::vector<reflection::DTemplateArgumentType> GetTemplateArgumentTypes() const;

			/// <summary>
			/// return template type name without template argument string.
			///	ex)
			///	std::unique_ptr<char*, std::allocator~~~<>> -> return std::unique_ptr
			/// std::vector<int> -> return std::vector
			/// </summary>
			/// <returns></returns>
			std::string GetTemplateTypeName() const;
		};
	}
}
