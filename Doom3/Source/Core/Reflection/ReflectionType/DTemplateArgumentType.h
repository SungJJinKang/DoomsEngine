#pragma once

#include <Macros/Assert.h>
#include <Macros/DllMarcos.h>

#include "../Reflection.h"


#include "DType.h"


D_NAMESPACE(dooms)
namespace dooms
{
	class DObject;
	namespace reflection
	{
		class DOOM_API D_CLASS DTemplateArgumentType : public DType /*: public dooms::DObject*/ // Dont Do this
		{

		private:
			
			const bool mIsPointer;

		public:

			DTemplateArgumentType();
			DTemplateArgumentType(const clcpp::Type* const clcppType, const bool isPointer);

			FORCE_INLINE bool GetIsTemplateArgumentPointerType() const
			{
				return mIsPointer;
			}

		};
	}
}
