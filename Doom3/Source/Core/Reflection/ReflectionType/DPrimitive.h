#pragma once

#include <Macros/DllMarcos.h>
#include <Macros/Assert.h>

#include "../Reflection.h"


namespace dPrimitiveHelper
{
	// return short name
	// ex) dooms::graphics::GraphicsServer -> GraphicsServer
	// ex) dooms::graphics::eClor::Red -> Red
	const char* GetShortNamePointer(const char* const name);
}


D_NAMESPACE(dooms)
namespace dooms
{
	

	class DObject;

	namespace reflection
	{
		enum class ePrimitiveNameType
		{
			Full,
			Short
		};

		class DOOM_API D_CLASS DPrimitive /*: public dooms::DObject*/ // Dont Do this
		{
		protected:

			const clcpp::Primitive* clPrimitive;
			
		protected:

			DPrimitive();

			DPrimitive(const clcpp::Primitive* const _clPrimitive);

		public:

			FORCE_INLINE bool IsValid() const
			{
				return clPrimitive != nullptr;
			}

			FORCE_INLINE const char* GetPrimitiveFullName() const
			{
				return clPrimitive->name.text;
			}

			FORCE_INLINE const char* GetPrimitiveName() const
			{
				return dPrimitiveHelper::GetShortNamePointer(clPrimitive->name.text);
			}

			FORCE_INLINE UINT32 GetPrimitiveHashValue() const
			{
				return clPrimitive->name.hash;
			}

			FORCE_INLINE const char* GetParentFullName() const
			{
				if (clPrimitive->parent != nullptr)
				{
					return clPrimitive->parent->name.text;
				}
				else
				{
					return nullptr;
				}
			}

			


			FORCE_INLINE bool Equal(const DPrimitive& dPrimitive) const
			{
				return clPrimitive == dPrimitive.clPrimitive;
			}

			FORCE_INLINE bool operator==(const DPrimitive& dPrimitive) const
			{
				return clPrimitive == dPrimitive.clPrimitive;
			}

			FORCE_INLINE bool operator!=(const DPrimitive& dPrimitive) const
			{
				return clPrimitive != dPrimitive.clPrimitive;
			}
		};
	}
}