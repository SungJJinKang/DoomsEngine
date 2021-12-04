#pragma once

#include <vector>

#include "imgui.h"

#include "DObject/DObject.h"
#include "Reflection/ReflectionType/DClass.h"


namespace dooms
{
	class DObject;

	namespace reflection
	{
		class DFunction;
		class DClass;
		class DField;
	}

	
	namespace ui
	{
		namespace imguiWithReflectionHelper
		{
			enum class eObjectType
			{
				DObject,
				RawObject
			};

			bool DrawImguiFieldFromDField
			(
				void* const object,
				const char* const label,
				const char* const typeFullName,
				const reflection::eProperyQualifier propertyQualifier,
				const reflection::DType* const fieldDType,
				const reflection::DAttributeList& attributeList,
				bool& isValueChange,
				const reflection::DType* const fieldOwnerObjectTypeDType,
				void* const fieldOwnerObejct
			);

			bool DrawObjectGUI(const reflection::DClass& dClass, void* const object, const char* const rawObjectName, const eObjectType objectType);
			bool DrawDObjectGUI(const reflection::DClass& dClass, dooms::DObject* const dObject);

			void ClearMultipleDrawChecker();
		}


		class imguiWithReflection
		{
		private:

			inline static int loopId = 0;

			inline static bool IsInitialized = false;
			inline static std::vector<dooms::DObject*> mVisibleOnGUIDObjectList{};
			
		public:

			inline static bool GetIsIsInitialized()
			{
				return IsInitialized;
			}
			static void Initialize();

			static void AddToVisibleOnGUIDObjectList(DObject* const dObject);
			static void RemoveFromVisibleOnGUIDObjectList(DObject* const dObject);

			static int PushImgui();
			static void PopImgui();
			static void ClearId();

			static void UpdateGUI_DObjectsVisibleOnGUI();

			template <typename DOBJECT_TYPE>
			static void DrawMultipleDObjects(const char* const uiLabel, const std::vector<DOBJECT_TYPE*>& dObjects, size_t& currentIndex)
			{
				static_assert(std::is_base_of_v<dooms::DObject, DOBJECT_TYPE> == true);

				if (ImGui::Begin(uiLabel))
				{
					ImGuiStyle& style = ImGui::GetStyle();
					ImGui::PushItemWidth(120);

					if (ImGui::BeginCombo("##", dObjects[currentIndex]->GetDObjectName().c_str(), ImGuiComboFlags_NoArrowButton))
					{
						for (int dObjectIndex = 0; dObjectIndex < dObjects.size(); dObjectIndex++)
						{
							PushImgui();

							bool is_selected = (currentIndex == dObjectIndex);

							if (ImGui::Selectable(dObjects[dObjectIndex]->GetDObjectName().c_str(), is_selected))
							{
								currentIndex = dObjectIndex;
							}

							if (is_selected)
							{
								ImGui::SetItemDefaultFocus();
							}

							PopImgui();
						}
						ImGui::EndCombo();
					}

					ImGui::PopItemWidth();

					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Text("----------------");
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();

					std::vector<dooms::DObject*> multipleDrawChecker;
					dooms::ui::imguiWithReflectionHelper::DrawDObjectGUI(dObjects[currentIndex]->GetDClass(), dObjects[currentIndex]);

					dooms::ui::imguiWithReflectionHelper::ClearMultipleDrawChecker();

				}

				ImGui::End();


			}


		
		};
	}
}
