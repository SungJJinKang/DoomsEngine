#include "imguiWithReflection.h"

#include <Core.h>

#include <unordered_map>
#include <string_view>
#include <algorithm>

#include <Reflection/ReflectionType/DClass.h>
#include <Reflection/ReflectionType/DAttributeList.h>


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
			static const float DEFULAT_DRAG_SPEED = 1.0f;
			static const float DEFULAT_SLIDER_SPEED = 1.0f;

			enum eImguiType
			{
				Color,
				Slider,
				Drag
			};

			int GetImguiFlags(const eImguiType imguiType, const reflection::DAttributeList& attributeList)
			{
				int flags = 0;

				if(attributeList.GetIsReadOnly() == true)
				{
					switch (imguiType)
					{
					case eImguiType::Color:
						flags |= ImGuiColorEditFlags_NoInputs;
						break;


					case eImguiType::Slider:
					case eImguiType::Drag:
						flags |= ImGuiSliderFlags_NoInput;
						break;

						

					default:
						D_ASSERT(false);
						break;
					}
				}

				return flags;
			}

			void DrawDObjectGUI(DObject* const dObject);

			/// <summary>
			/// check DFunction can be showing on gui
			/// </summary>
			/// <param name="dFunction"></param>
			/// <returns></returns>
			bool GetIsFunctionGUIable(const reflection::DFunction& dFunction)
			{
				return (dFunction.GetIsHasReturnValue() == false) && (dFunction.GetParameterDFieldList().empty() == true);
			}


			static std::vector<dooms::DObject*> mVisibleOnGUIDObjectList{};
			static bool isInitialized = false;


			/// <summary>
			/// return : is value changed
			/// </summary>
			using IMGUI_WITH_REFLECTION_FUNC = 
				bool (*)(void* const object, const char* const label, const reflection::DAttributeList& attributeList);

			static std::unordered_map<std::string_view, IMGUI_WITH_REFLECTION_FUNC> imguiWIthRelfectionFuncMap{};

			bool DrawImguiWithReflection(void* const object, const char* const objectTypeFullName, const char* const label, const reflection::DAttributeList& attributeList)
			{
				bool isValueChange = false;
				if(attributeList.GetIsVisibleOnGUI() == true)
				{
					auto iter = imguiWIthRelfectionFuncMap.find(std::string_view{ objectTypeFullName });
					if (iter != imguiWIthRelfectionFuncMap.end())
					{
						isValueChange = iter->second(object, label, attributeList);
					}
					else
					{
						D_DEBUG_LOG(std::string{ "imguiWithReflection : Can't resolve type " } + objectTypeFullName);
					}
				}

				return isValueChange;
			}


			////
			///
			///
			bool imguiWithReflection_bool(void* const object, const char* const label, const reflection::DAttributeList& attributeList)
			{
				//ImGui::Text("%s : %d", label, *static_cast<int*>(object));
				return ImGui::Checkbox(label, static_cast<bool*>(object));
			}


			bool imguiWithReflection_char(void* const object, const char* const label, const reflection::DAttributeList& attributeList)
			{
				//ImGui::Text("%s : %d", label, *static_cast<int*>(object));
				return ImGui::DragScalar(label, ImGuiDataType_S8, object);
			}

			bool imguiWithReflection_unsigned_char(void* const object, const char* const label, const reflection::DAttributeList& attributeList)
			{
				//ImGui::Text("%s : %u", label, *static_cast<unsigned int*>(object));
				return ImGui::DragScalar(label, ImGuiDataType_U8, object);
			}

			bool imguiWithReflection_short(void* const object, const char* const label, const reflection::DAttributeList& attributeList)
			{
				const INT16 minValue = attributeList.GetMinValue<INT16>();
				const INT16 maxValue = attributeList.GetMaxValue<INT16>();

				return ImGui::DragScalar(label, ImGuiDataType_S16, object, DEFULAT_DRAG_SPEED, &minValue, &maxValue, 0, GetImguiFlags(eImguiType::Drag, attributeList));
			}

			bool imguiWithReflection_unsigned_short(void* const object, const char* const label, const reflection::DAttributeList& attributeList)
			{
				const UINT16 minValue = attributeList.GetMinValue<UINT16>();
				const UINT16 maxValue = attributeList.GetMaxValue<UINT16>();

				return ImGui::DragScalar(label, ImGuiDataType_U16, object, DEFULAT_DRAG_SPEED, &minValue, &maxValue, 0, GetImguiFlags(eImguiType::Drag, attributeList));
			}

			bool imguiWithReflection_int(void* const object, const char* const label, const reflection::DAttributeList& attributeList)
			{
				const INT32 minValue = attributeList.GetMinValue<INT32>();
				const INT32 maxValue = attributeList.GetMaxValue<INT32>();

				return ImGui::DragScalar(label, ImGuiDataType_S32, object, DEFULAT_DRAG_SPEED, &minValue, &maxValue, 0, GetImguiFlags(eImguiType::Drag, attributeList));
			}

			bool imguiWithReflection_unsigned_int(void* const object, const char* const label, const reflection::DAttributeList& attributeList)
			{
				const UINT32 minValue = attributeList.GetMinValue<UINT32>();
				const UINT32 maxValue = attributeList.GetMaxValue<UINT32>();

				return ImGui::DragScalar(label, ImGuiDataType_U32, object, DEFULAT_DRAG_SPEED, &minValue, &maxValue, 0, GetImguiFlags(eImguiType::Drag, attributeList));
			}

			bool imguiWithReflection_long_long(void* const object, const char* const label, const reflection::DAttributeList& attributeList)
			{
				const INT64 minValue = attributeList.GetMinValue<INT64>();
				const INT64 maxValue = attributeList.GetMaxValue<INT64>();

				return ImGui::DragScalar(label, ImGuiDataType_S64, object, DEFULAT_DRAG_SPEED, &minValue, &maxValue, 0, GetImguiFlags(eImguiType::Drag, attributeList));
			}

			bool imguiWithReflection_unsigned_long_long(void* const object, const char* const label, const reflection::DAttributeList& attributeList)
			{
				const UINT64 minValue = attributeList.GetMinValue<UINT64>();
				const UINT64 maxValue = attributeList.GetMaxValue<UINT64>();

				return ImGui::DragScalar(label, ImGuiDataType_U64, object, DEFULAT_DRAG_SPEED, &minValue, &maxValue, 0, GetImguiFlags(eImguiType::Drag, attributeList));
			}

			bool imguiWithReflection_float(void* const object, const char* const label, const reflection::DAttributeList& attributeList)
			{
				const float minValue = attributeList.GetMinValue<float>();
				const float maxValue = attributeList.GetMaxValue<float>();

				return ImGui::DragScalar(label, ImGuiDataType_Float, object, DEFULAT_DRAG_SPEED, &minValue, &maxValue, 0, GetImguiFlags(eImguiType::Drag, attributeList));
			}
			
			bool imguiWithReflection_double(void* const object, const char* const label, const reflection::DAttributeList& attributeList)
			{
				//ImGui::Text("%s : %lf", label, *static_cast<double*>(object));
				const double minValue = attributeList.GetMinValue<double>();
				const double maxValue = attributeList.GetMaxValue<double>();

				return ImGui::DragScalar(label, ImGuiDataType_Double, object, DEFULAT_DRAG_SPEED, &minValue, &maxValue, 0, GetImguiFlags(eImguiType::Drag, attributeList));
			}

			bool imguiWithReflection_std_string(void* const object, const char* const label, const reflection::DAttributeList& attributeList)
			{
				//ImGui::Text("%s : %s", label, static_cast<std::string*>(object)->c_str());
				//return ImGui::DragScalar(label, ImGuiDataType_S64, static_cast<long long*>(object));
				return false;
			}

			bool imguiWithReflection_math_Vector3(void* const object, const char* const label, const reflection::DAttributeList& attributeList)
			{
				if (attributeList.GetIsHasGUIType("Color"))
				{
					return ImGui::ColorEdit3(label, static_cast<math::Vector3*>(object)->data(), GetImguiFlags(eImguiType::Color, attributeList));
				}
				else
				{
					return ImGui::DragFloat3
					(
						label, 
						static_cast<math::Vector3*>(object)->data(), 
						DEFULAT_DRAG_SPEED,
						attributeList.GetMinValue(),
						attributeList.GetMaxValue(),
						"%.3f",
						GetImguiFlags(eImguiType::Slider, attributeList)
					);
				}
				
			}

			bool imguiWithReflection_math_Vector4(void* const object, const char* const label, const reflection::DAttributeList& attributeList)
			{
				if(attributeList.GetIsHasGUIType("Color"))
				{
					return ImGui::ColorEdit4(label, static_cast<math::Vector4*>(object)->data(), GetImguiFlags(eImguiType::Color, attributeList));
				}
				else
				{
					return ImGui::DragFloat4
					(
						label,
						static_cast<math::Vector4*>(object)->data(),
						DEFULAT_DRAG_SPEED,
						attributeList.GetMinValue(),
						attributeList.GetMaxValue(),
						"%.3f",
						GetImguiFlags(eImguiType::Slider, attributeList)
					);
				}
			}

			bool imguiWithReflection_math_Quaternion(void* const object, const char* const label, const reflection::DAttributeList& attributeList)
			{
				math::Vector3 eulerAngle{ math::Quaternion::QuaternionToEulerAngle(*static_cast<math::Quaternion*>(object)) };

				const bool isValueChanged = ImGui::DragFloat3
				(
					label,
					eulerAngle.data(),
					DEFULAT_DRAG_SPEED,
					attributeList.GetMinValue(),
					attributeList.GetMaxValue(),
					"%.3f",
					GetImguiFlags(eImguiType::Slider, attributeList)
				);

				if(isValueChanged == true)
				{
					*static_cast<math::Quaternion*>(object) = eulerAngle;
				}

				return isValueChanged;
			}

			bool imguiWithReflection_TransformCoreData(void* const object, const char* const label, const reflection::DAttributeList& attributeList)
			{
				bool isValueChnaged = false;
				isValueChnaged |= imguiWithReflection_math_Vector3(&(static_cast<dooms::TransformCoreData*>(object)->mPosition), "mPosition", attributeList);
				return isValueChnaged;
			}

			bool imguiWithReflection_dooms_Entity(void* const object, const char* const label, const reflection::DAttributeList& attributeList)
			{
				dooms::Entity* const entity = static_cast<dooms::Entity*>(object);

				if(IsValid(entity) == true)
				{
					auto Transform = entity->GetTransform();
					auto& AllServerComponents = entity->GetAllPlainComponents();
					auto& AllPlainComponents = entity->GetAllPlainComponents();

					DrawDObjectGUI(Transform);
					for (auto& serverComponent : AllServerComponents)
					{
						if (serverComponent)
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
				}

				return false;
			}

			void Initialize()
			{
				if (isInitialized == false)
				{
					imguiWIthRelfectionFuncMap.emplace("math::Vector3", imguiWithReflection_math_Vector3);
					imguiWIthRelfectionFuncMap.emplace("math::Vector4", imguiWithReflection_math_Vector4);
					imguiWIthRelfectionFuncMap.emplace("math::Quaternion", imguiWithReflection_math_Quaternion);
					imguiWIthRelfectionFuncMap.emplace("bool", imguiWithReflection_bool);
					imguiWIthRelfectionFuncMap.emplace("char", imguiWithReflection_char);
					imguiWIthRelfectionFuncMap.emplace("unsigned char", imguiWithReflection_unsigned_char);
					imguiWIthRelfectionFuncMap.emplace("short", imguiWithReflection_short);
					imguiWIthRelfectionFuncMap.emplace("unsigned short", imguiWithReflection_unsigned_short);
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

			static std::vector<dooms::DObject*> DrawedDObjectList{};

			void DrawDObjectGUI(DObject* const dObject)
			{
				D_ASSERT(isInitialized == true);

				if(
					IsValid(dObject) == true &&
					// check if DObject is already drawed to prevent infinite loop
					std::find(DrawedDObjectList.begin(), DrawedDObjectList.end(), dObject) == DrawedDObjectList.end()
				)
				{
					DrawedDObjectList.push_back(dObject);

					reflection::DClass dObjectDClass = dObject->GetDClass();

					const std::unordered_map<std::string_view, dooms::reflection::DField>& dFieldList = dObjectDClass.GetDFieldList();


					if (dFieldList.empty() == false)
					{
						

						//label
						ImGui::TextColored(ImVec4{1.0f, 0.0f, 0.0f, 1.0f}, "%s", dObject->GetDObjectName().empty() == false ? dObject->GetDObjectName().c_str() : dObject->GetTypeFullName());


						bool isGUIValueChanged = false;


						for (auto& dFieldNode : dFieldList)
						{
							const dooms::reflection::DField& dField = dFieldNode.second;

							// TODO : Consider GUI Flag

							isGUIValueChanged |= dooms::ui::imguiWithReflection::DrawImguiWithReflection(
								const_cast<dooms::reflection::DField&>(dField).GetRawFieldValue(dObject),
								dField.GetFieldTypeName(),
								dField.GetFieldName(),
								dField.GetDAttributeList()
							);
						}

						//Draw Components of entity
						DrawImguiWithReflection(dObject, dObject->GetTypeFullName(), "", dObjectDClass.GetDAttributeList());

						if (isGUIValueChanged == true)
						{
							dObject->OnChangedByGUI();
						}


					}

					const std::unordered_map<std::string_view, dooms::reflection::DFunction>& dFunctionList = dObjectDClass.GetDFunctionList();
					if (dFunctionList.empty() == false)
					{
						for (auto& dFunctioNnode : dFunctionList)
						{
							const dooms::reflection::DFunction& dFunction = dFunctioNnode.second;
							
							if(GetIsFunctionGUIable(dFunction) == true)
							{
								// TODO : Check is static function or member function	
							}
						}
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
		if (
			ImGui::Begin
			(
				dObjectVisibleOnGUI->GetDObjectName().empty() == false ? dObjectVisibleOnGUI->GetDObjectName().c_str() : dObjectVisibleOnGUI->GetTypeFullName(),
				&(dooms::ui::engineGUIServer::IsEngineGUIVisible)
			)
			)
		{
			DrawDObjectGUI(dObjectVisibleOnGUI);
		}

		
		

		ImGui::End();

		DrawedDObjectList.clear();
	}	
}


