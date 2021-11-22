#pragma once

#include <Macros/DllMarcos.h>
#include "../Reflection.h"

#include <vector>
#include <unordered_map>

#include "DPrimitive.h"

D_NAMESPACE(dooms)
namespace dooms
{
	class DObject;
	namespace reflection
	{
		class DAttribute;
		class DOOM_API D_CLASS DAttributeList  /*: public dooms::DObject*/ // Dont Do this
		{

		private:

			std::vector<DAttribute> mDAttributeList;

		public:

			DAttributeList(const std::vector<DAttribute>& attributes);
			DAttributeList(std::vector<DAttribute>&& attributes) noexcept;

			const DAttribute* GetAttributeWithName(const char* const attributeName) const;
		};
	}
}