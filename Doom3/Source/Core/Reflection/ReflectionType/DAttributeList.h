#pragma once

#include <Macros/DllMarcos.h>
#include "../Reflection.h"

#include <vector>
#include <unordered_map>

#include "DPrimitive.h"
#include "DAttribute.h"

struct ImVec4;

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

			/// <summary>
			/// seacrching attribute with name is case-in(!)intensive
			/// </summary>
			/// <param name="attributeName"></param>
			/// <returns></returns>
			const DAttribute* GetAttributeWithName(const char* const attributeName) const;
			
			/// <summary>
			/// return Text Color
			/// </summary>
			/// <returns></returns>
			ImVec4 GetTextColor() const;
			bool GetIsVisibleOnGUI() const;
			bool GetIsHasGUIType(const char* const typeName) const;
			bool GetIsReadOnly() const;
			/// <summary>
			/// this is only applied to field gui
			/// </summary>
			/// <returns></returns>
			bool GetIsNoLabel() const;
			/// <summary>
			/// if has drawOnSameLine attribute, return space value ( at least 0.0f ).
			///	Or return -1.0f
			/// </summary>
			/// <returns></returns>
			float GetIsDrawOnSameLine() const;

			/// <summary>
			/// if there isn't tooltip, return nullptr
			///
			///	only one tooltip is supported
			/// </summary>
			/// <returns></returns>
			const char* GetTooltip() const;
			const char* GetDirtyCallbackFunctionName() const;

			float GetMinValue() const;
			template <typename T>
			T GetMinValue() const
			{
				return static_cast<T>(GetMinValue());
			}

			float GetMaxValue() const;
			template <typename T>
			T GetMaxValue() const
			{
				return static_cast<T>(GetMaxValue());
			}

		};
	}
}