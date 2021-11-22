#include "imguiWithReflection.h"

#include <Core.h>

#include <unordered_map>
#include <string_view>
#include <algorithm>

#include <Reflection/ReflectionType/DClass.h>

#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Matrix2x2.h>
#include <Matrix3x3.h>
#include <Matrix4x4.h>
#include <Quaternion.h>

#include <Scene/Entity.h>

#include "imgui.h"
#include "DObject/DObject.h"

#include <vector_erase_move_lastelement/vector_swap_popback.h>

#include "../engineGUIServer.h"

namespace dooms
{
	namespace ui
	{
		namespace imguiWithReflection
		{
			void DrawDObjectGUI(DObject* const dObject);



			static std::vector<dooms::DObject*> mVisibleOnGUIDObjectList{};
			static bool isInitialized = false;


			/// <summary>
			/// return : is value changed
			/// </summary>
			using IMGUI_WITH_REFLECTION_FUNC = 
				bool (*)(void* const object, const char* const label);

			static std::unordered_map<std::string_view, IMGUI_WITH_REFLECTION_FUNC> imguiWIthRelfectionFuncMap{};

			bool DrawImguiWithReflection(const char* const objectType, void* const object, const char* const label = "")
			{
				auto iter = imguiWIthRelfectionFuncMap.find(std::string_view{ objectType });
				if (iter != imguiWIthRelfectionFuncMap.end())
				{
					return iter->second(object, label);
				}
				else
				{
					D_DEBUG_LOG(std::string{ "imguiWithReflection : Can't resolve type " } + objectType);
					return false;
				}
			}


			////
			///

			

			bool imguiWithReflection_int(void* const object, const char* const label)
			{
				ImGui::Text("%s : %d", label, *static_cast<int*>(object));
				return false;
			}

			bool imguiWithReflection_unsigned_int(void* const object, const char* const label)
			{
				ImGui::Text("%s : %u", label, *static_cast<unsigned int*>(object));
				return false;
			}

			bool imguiWithReflection_long_long(void* const object, const char* const label)
			{
				ImGui::Text("%s : %lld", label, *static_cast<long long*>(object));
				return false;
			}

			bool imguiWithReflection_unsigned_long_long(void* const object, const char* const label)
			{
				ImGui::Text("%s : %llu", label, *static_cast<unsigned long long*>(object));
				return false;
			}

			bool imguiWithReflection_float(void* const object, const char* const label)
			{
				ImGui::Text("%s : %f", label, *static_cast<float*>(object));
				return false;
			}
			
			bool imguiWithReflection_double(void* const object, const char* const label)
			{
				ImGui::Text("%s : %lf", label, *static_cast<double*>(object));
				return false;
			}

			bool imguiWithReflection_std_string(void* const object, const char* const label)
			{
				ImGui::Text("%s : %s", label, static_cast<std::string*>(object)->c_str());
				return false;
			}

			bool imguiWithReflection_math_Vector3(void* const object, const char* const label)
			{
				return ImGui::DragFloat3(label, static_cast<math::Vector3*>(object)->data());
			}

			bool imguiWithReflection_math_Vector4(void* const object, const char* const label)
			{
				return ImGui::DragFloat4(label, static_cast<math::Vector4*>(object)->data());
			}

			bool imguiWithReflection_math_Quaternion(void* const object, const char* const label)
			{
				return ImGui::DragFloat4(label, static_cast<math::Quaternion*>(object)->data());
			}

			bool imguiWithReflection_TransformCoreData(void* const object, const char* const label)
			{
				bool isValueChnaged = false;
				isValueChnaged |= imguiWithReflection_math_Vector3(&(static_cast<dooms::TransformCoreData*>(object)->mPosition), "mPosition");
				return isValueChnaged;
			}

			bool imguiWithReflection_dooms_Entity(void* const object, const char* const label)
			{
				dooms::Entity* const entity = static_cast<dooms::Entity*>(object);

				D_ASSERT(entity);

				auto Transform = entity->GetTransform();
				auto& AllServerComponents = entity->GetAllPlainComponents();
				auto& AllPlainComponents = entity->GetAllPlainComponents();

				DrawDObjectGUI(Transform);
				for(auto& serverComponent : AllServerComponents)
				{
					if(serverComponent)
					{
						DrawDObjectGUI(serverComponent.get());
					}
				}

				for (auto& plainComponent : AllPlainComponents)
				{
					if (plainComponent)
					{
						DrawDObjectGUI(plainComponent.get());
					}
				}

				return false;
			}

			void Initialize()
			{
				if (isInitialized == false)
				{
					imguiWIthRelfectionFuncMap.emplace("math::Vector3", imguiWithReflection_math_Vector3);
					imguiWIthRelfectionFuncMap.emplace("math::Vector4", imguiWithReflection_math_Vector4);
					imguiWIthRelfectionFuncMap.emplace("math::Quaternion", imguiWithReflection_math_Vector4);
					imguiWIthRelfectionFuncMap.emplace("int", imguiWithReflection_int);
					imguiWIthRelfectionFuncMap.emplace("unsigned int", imguiWithReflection_unsigned_int);
					imguiWIthRelfectionFuncMap.emplace("long long", imguiWithReflection_long_long);
					imguiWIthRelfectionFuncMap.emplace("unsigned long long", imguiWithReflection_unsigned_long_long);
					imguiWIthRelfectionFuncMap.emplace("float", imguiWithReflection_float);
					imguiWIthRelfectionFuncMap.emplace("double", imguiWithReflection_double);
					imguiWIthRelfectionFuncMap.emplace("dooms::Entity", imguiWithReflection_dooms_Entity);
					imguiWIthRelfectionFuncMap.emplace("dooms::TransformCoreData", imguiWithReflection_TransformCoreData);

					isInitialized = true;
				}
			}

			static std::vector<dooms::DObject*> drawedDObjectList{};

			void DrawDObjectGUI(DObject* const dObject)
			{
				if(
					IsValid(dObject) == true &&
					// check if DObject is already drawed to prevent infinite loop
					std::find(drawedDObjectList.begin(), drawedDObjectList.end(), dObject) == drawedDObjectList.end()
				)
				{
					drawedDObjectList.push_back(dObject);


					dooms::ui::imguiWithReflection::Initialize();

					bool isVisible = true;
					
					ImGui::BeginChild(dObject->GetDObjectName().empty() == false ? dObject->GetDObjectName().c_str() : dObject->GetTypeFullName());

					DrawImguiWithReflection(dObject->GetTypeFullName(), dObject, "");

					bool isGUIValueChanged = false;

					const std::unordered_map<std::string_view, dooms::reflection::DField>& dFieldList = dObject->GetDClass().GetDFieldList();
					for (auto& dFieldNode : dFieldList)
					{
						const dooms::reflection::DField& dField = dFieldNode.second;

						isGUIValueChanged |= dooms::ui::imguiWithReflection::DrawImguiWithReflection(
							dField.GetFieldTypeName(),
							const_cast<dooms::reflection::DField&>(dField).GetRawFieldValue(dObject),
							dField.GetFieldName()
						);
					}

					ImGui::EndChild();

					if(isGUIValueChanged == true)
					{
						dObject->OnChangedByGUI();
					}
					
				}
				
			}
		}
	}
}


void dooms::ui::imguiWithReflection::AddToVisibleOnGUIDObjectList(DObject* const dObject)
{
	dooms::ui::imguiWithReflection::mVisibleOnGUIDObjectList.push_back(dObject);
}

void dooms::ui::imguiWithReflection::RemoveFromVisibleOnGUIDObjectList(DObject* const dObject)
{
	std::vector_find_swap_popback(dooms::ui::imguiWithReflection::mVisibleOnGUIDObjectList, dObject);
}

void dooms::ui::imguiWithReflection::UpdateGUI_DObjectsVisibleOnGUI()
{
	for(dooms::DObject* const dObjectVisibleOnGUI : dooms::ui::imguiWithReflection::mVisibleOnGUIDObjectList)
	{
		ImGui::Begin
		(
			dObjectVisibleOnGUI->GetDObjectName().empty() == false ? dObjectVisibleOnGUI->GetDObjectName().c_str() : dObjectVisibleOnGUI->GetTypeFullName(),
			&(dooms::ui::engineGUIServer::IsEngineGUIVisible), 
			ImGuiWindowFlags_MenuBar
		);
		
		DrawDObjectGUI(dObjectVisibleOnGUI);

		ImGui::End();

		drawedDObjectList.clear();
	}	
}


