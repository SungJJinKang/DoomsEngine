#include "imguiWithReflection.h"

#include <Core.h>

#include <unordered_map>
#include <string_view>
#include <algorithm>
#include <string.h>

#include "imguiFieldFunctionGetter.h"

#include <Reflection/ReflectionType/DClass.h>
#include <Reflection/ReflectionType/DAttributeList.h>

#include <Random.h>

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

#include "imgui_internal.h"
#include "../engineGUIServer.h"

#include <EngineGUI/PrintText.h>


namespace dooms
{
	namespace ui
	{
		namespace imguiWithReflectionHelper
		{
			
			
			
			static bool isInitialized = false;

			static std::vector<void*> MultipleDrawChecker{};

			

			void OnStartDrawGUI(const reflection::DAttributeList& attributeList)
			{
				if (attributeList.GetIsReadOnly() == true)
				{
					ImGui::BeginDisabled();
				}

				const float sameLineSpacingValue = attributeList.GetIsDrawOnSameLine();
				if(sameLineSpacingValue > 0.0f)
				{
					ImGui::SameLine(0, sameLineSpacingValue);
				}
			}

			void OnEndDrawGUI(const reflection::DAttributeList& attributeList)
			{
				// this is little slow. but it's acceptable
				if (attributeList.GetIsReadOnly() == true)
				{
					ImGui::EndDisabled();

				}

				if(ImGui::IsItemHovered())
				//if(ImGui::GetFocusID() == ImGui::GetID(label))
				{
					if (const char* const tooltipStr = attributeList.GetTooltip())
					{
						ImGui::SetTooltip("Tooltip : %s", tooltipStr);
					}
				}
				
			}

			/// <summary>
			/// check DFunction can be showing on gui
			/// </summary>
			/// <param name="dFunction"></param>
			/// <returns></returns>
			bool GetIsFunctionGUIable(const reflection::DFunction& dFunction)
			{
				// TODO : Check function is virtual function.
				//        virtual function can't be guiable
				return (dFunction.GetIsHasReturnValue() == false) && (dFunction.GetParameterCount() == 0);
			}
			
		
			void CallFieldDirtyCallback
			(
				const char* const dirtyCallbackFunctionName,
				const reflection::DClass* const fieldOwnerObjectTypeDClass,
				void* const fieldOwnerObejct
			)
			{
				if(dirtyCallbackFunctionName != nullptr && fieldOwnerObjectTypeDClass != nullptr && fieldOwnerObejct != nullptr)
				{
					reflection::DFunction dFunction;
					const bool isSuccess = fieldOwnerObjectTypeDClass->GetDFunctionHasNoReturnNoParameter(dirtyCallbackFunctionName, dFunction);
					if(isSuccess == true)
					{
						if (GetIsFunctionGUIable(dFunction) == true)
						{
							dFunction.CallMemberFunctionNoReturnNoParameter(fieldOwnerObejct);
						}
						
					}
				}
			}

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
			)
			{
				D_ASSERT(object != nullptr);
				D_ASSERT(label != nullptr);
				D_ASSERT(fieldDType != nullptr);

				//initialize
				//isValueChange = true;

				bool isSuccessToDrawGUI = false;
				
				if (attributeList.GetIsVisibleOnGUI() == true)
				{
					dooms::ui::imguiFieldFunctionGetter::IMGUI_WITH_REFLECTION_FUNC func =
						dooms::ui::imguiFieldFunctionGetter::GetImguiWithReflectionFunction(typeFullName, propertyQualifier, fieldDType);

					if (func != nullptr)
					{
						OnStartDrawGUI(attributeList);

						imguiWithReflection::PushImgui();

						const char* const fieldLabel = attributeList.GetIsNoLabel() == true ? "" : label;

						isValueChange = func(object, fieldLabel, typeFullName, propertyQualifier, attributeList, fieldDType);
						isSuccessToDrawGUI = true;

						OnEndDrawGUI(attributeList);

						imguiWithReflection::PopImgui();
						// TODO :Support Enum property gui.
						
					}
					else
					{
						D_DEBUG_LOG(eLogType::D_ERROR, "imguiWithReflection : Can't resolve type \" %s \"", typeFullName);
					}

				}

				return isSuccessToDrawGUI;
			}

			bool DrawImguiFieldFromDField
			(
				void* const object,
				const reflection::DField& dField, 
				bool& isValueChange,
				const reflection::DType* const fieldOwnerObjectTypeDType,
				void* const fieldOwnerObejct
			)
			{
				D_ASSERT(object != nullptr);
				D_ASSERT(fieldOwnerObjectTypeDType != nullptr);
				D_ASSERT(fieldOwnerObejct != nullptr);

				const reflection::DType fieldDType = dField.GetDTypeOfFieldType();
				const std::string fieldTypeFullName = dField.GetFieldTypeFullName();

				return DrawImguiFieldFromDField
				(
					object,
					dField.GetFieldName(),
					fieldTypeFullName.c_str(),
					dField.GetFieldQualifier(),
					&fieldDType,
					dField.GetDAttributeList(),
					isValueChange,
					fieldOwnerObjectTypeDType,
					fieldOwnerObejct
				);
			}
			
			

			

			bool DrawImguiFunctionButtonFromDFunction(void* const object, const dooms::reflection::DFunction dFunction)
			{
				bool isButtonClicked = false;
				
				if (GetIsFunctionGUIable(dFunction) == true)
				{
					const dooms::reflection::DAttributeList& attributeList = dFunction.GetDAttributeList();

					if (attributeList.GetIsVisibleOnGUI() == true)
					{
						OnStartDrawGUI(attributeList);

						imguiWithReflection::PushImgui();

						// when member function
						if (dFunction.GetIsMemberFunction() == true)
						{
							if (ImGui::Button(dFunction.GetFunctionName()))
							{
								const_cast<dooms::reflection::DFunction&>(dFunction).CallMemberFunctionNoReturnNoParameter(object);
								isButtonClicked = true;
							}
						}
						else
						{// when static function or glbal function
							if (ImGui::Button(dFunction.GetFunctionName()))
							{
								const_cast<dooms::reflection::DFunction&>(dFunction).CallFunctionNoReturn();
								isButtonClicked = true;
							}
						}

						imguiWithReflection::PopImgui();

						OnEndDrawGUI(attributeList);
					}
				}

				return isButtonClicked;
			}


			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



			/// <summary>
			/// 
			/// </summary>
			/// <param name="dClass"></param>
			/// <param name="object"></param>
			/// <param name="rawObjectName">objectType is DObject, you don't need set this. it will take name from DObject::GetDObjectName </param>
			/// <param name="objectType"></param>
			/// <returns></returns>
			bool DrawObjectGUI(const reflection::DClass& dClass, void* const object, const char* const rawObjectName)
			{
				D_ASSERT(dooms::ui::imguiWithReflection::GetIsIsInitialized() == true);

				bool isDObjectChanged = false;

				const bool isFieldOwnerObjectDerivedFromDObject = dClass.GetIsDerivedFromDObject();

				if (
					(isFieldOwnerObjectDerivedFromDObject == true ? IsValid(reinterpret_cast<dooms::DObject*>(object)) : object != nullptr)
					&&
					// check if DObject is already drawed to prevent infinite loop
					std::find(MultipleDrawChecker.begin(), MultipleDrawChecker.end(), object) == MultipleDrawChecker.end()
					)
				{
					MultipleDrawChecker.push_back(object);

					

					if (rawObjectName != nullptr && rawObjectName[0] != '\0')
					{
						ImGui::TextColored(ImVec4{ 1.0f, 0.0f, 0.0f, 1.0f }, "%s", rawObjectName);
					}
					
					const std::vector<dooms::reflection::DField>& dFieldList = dClass.GetDFieldList();
					
					if (dFieldList.empty() == false)
					{
						for (const dooms::reflection::DField& dField : dFieldList)
						{
							const reflection::DAttributeList fieldDAttributeList = dField.GetDAttributeList();

							if (fieldDAttributeList.GetIsVisibleOnGUI() == true)
							{
								bool isFieldValueChanged = false;

								void* fieldRawValue = const_cast<dooms::reflection::DField&>(dField).GetRawFieldValue(object);

								const reflection::DType fieldDType = dField.GetDTypeOfFieldType();
								const bool isFieldObjectDerivedFromDObject = fieldDType.GetIsDerivedFromDObject();

								const std::string fieldTypeFullName = dField.GetFieldTypeFullName();

								const bool isGUIDrawed = dooms::ui::imguiWithReflectionHelper::DrawImguiFieldFromDField
								(
									fieldRawValue,
									dField.GetFieldName(),
									fieldTypeFullName.c_str(),
									dField.GetFieldQualifier(),
									&fieldDType,
									fieldDAttributeList,
									isFieldValueChanged,
									&dClass,
									object
								);


								if (isGUIDrawed == false && fieldDType.GetPrimitiveType() == reflection::DPrimitive::ePrimitiveType::CLASS && dField.GetFieldQualifier() == reflection::eProperyQualifier::VALUE)
								{//fail to find special gui func. can't find proper gui function from map
									const reflection::DClass dClass = fieldDType.AsDClass();
									if ((isFieldOwnerObjectDerivedFromDObject == true) ? IsValid(reinterpret_cast<dooms::DObject*>(object)) : true)
									{// if type of field is child class of dooms::DObject
										isFieldValueChanged = DrawObjectGUI(dClass, fieldRawValue, (fieldDAttributeList.GetIsNoLabel() == false) ? dField.GetFieldName() : "");
									}
								}


								if (isFieldValueChanged == true)
								{
									if (isFieldOwnerObjectDerivedFromDObject && IsValid(reinterpret_cast<dooms::DObject*>(object)))
									{// check if object is struct or class not inheriting DObject
										reinterpret_cast<dooms::DObject*>(object)->OnChangedByGUI(dField);
										CallFieldDirtyCallback(fieldDAttributeList.GetDirtyCallbackFunctionName(), &dClass, object);
									}
								}

								isDObjectChanged |= isFieldValueChanged;
							}
						}
					}

					const std::vector<dooms::reflection::DFunction>& dFunctionList = dClass.GetDFunctionList();
					if (dFunctionList.empty() == false)
					{
						for (const dooms::reflection::DFunction& dFunction : dFunctionList)
						{
							DrawImguiFunctionButtonFromDFunction(object, dFunction);
							
						}
					}

					bool isGUIValueChanged;
					dooms::ui::imguiWithReflectionHelper::DrawImguiFieldFromDField
					(
						object,
						rawObjectName,
						dClass.GetTypeFullName(),
						reflection::eProperyQualifier::VALUE,
						&dClass,
						dClass.GetDAttributeList(),
						isGUIValueChanged,
						nullptr,
						nullptr
					);
					

				}


				return isDObjectChanged;
			}

			bool DrawDObjectGUI
			(
				const reflection::DClass& dClass, dooms::DObject* const dObject
			)
			{
				if(IsValid(dObject) == true)
				{
					return DrawObjectGUI(dClass, dObject, "");
				}
				else
				{
					return false;
				}
				
			}


			void ClearMultipleDrawChecker()
			{
				MultipleDrawChecker.clear();
			}
		}
	}
}

void dooms::ui::imguiWithReflection::Initialize()
{
	if (IsInitialized == false)
	{
		imguiFieldFunctionGetter::Initialize();

		IsInitialized = true;
	}
}

void dooms::ui::imguiWithReflection::AddToVisibleOnGUIDObjectList(DObject* const dObject)
{
	dooms::ui::imguiWithReflection::mVisibleOnGUIDObjectList.push_back(dObject);
}

void dooms::ui::imguiWithReflection::RemoveFromVisibleOnGUIDObjectList(DObject* const dObject)
{
	swap_popback::vector_find_swap_popback(dooms::ui::imguiWithReflection::mVisibleOnGUIDObjectList, dObject);
}

void dooms::ui::imguiWithReflection::UpdateGUI_DObjectsVisibleOnGUI()
{
	for (dooms::DObject* const dObjectVisibleOnGUI : dooms::ui::imguiWithReflection::mVisibleOnGUIDObjectList)
	{
		if(IsLowLevelValid(dObjectVisibleOnGUI))
		{
			if (
				ImGui::Begin
				(
					dObjectVisibleOnGUI->GetDObjectName().empty() == false ? dObjectVisibleOnGUI->GetDObjectName().c_str() : dObjectVisibleOnGUI->GetTypeFullName(),
					&(dooms::ui::engineGUIServer::IsEngineGUIVisible)
				)
				)
			{
				imguiWithReflectionHelper::DrawDObjectGUI(dObjectVisibleOnGUI->GetDClass(), dObjectVisibleOnGUI);

			}


			ImGui::End();


			imguiWithReflectionHelper::ClearMultipleDrawChecker();
		}
		
	}
}

int dooms::ui::imguiWithReflection::PushImgui()
{
	++loopId;
	ImGui::PushID(loopId);
	return loopId;
}

void dooms::ui::imguiWithReflection::PopImgui()
{
	ImGui::PopID();
	//loopId--;
}

void dooms::ui::imguiWithReflection::ClearId()
{
	loopId = INT_MIN;
}


