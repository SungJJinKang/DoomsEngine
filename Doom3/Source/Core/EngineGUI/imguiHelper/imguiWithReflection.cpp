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
				isValueChange = true;

				bool isSuccessToDrawGUI = false;
				
				if (attributeList.GetIsVisibleOnGUI() == true)
				{
					dooms::ui::imguiFieldFunctionGetter::IMGUI_WITH_REFLECTION_FUNC func =
						dooms::ui::imguiFieldFunctionGetter::GetImguiWithReflectionFunction(typeFullName, fieldDType);

					if (func != nullptr)
					{
						OnStartDrawGUI(attributeList);

						imguiWithReflection::PushImgui();

						const char* const fieldLabel = attributeList.GetIsNoLabel() == true ? "" : label;

						isValueChange = func(object, fieldLabel, typeFullName, attributeList, fieldDType);
						isSuccessToDrawGUI = true;

						OnEndDrawGUI(attributeList);

						imguiWithReflection::PopImgui();

						if (isValueChange == true)
						{
							if (fieldOwnerObjectTypeDType != nullptr && fieldOwnerObejct != nullptr && fieldOwnerObjectTypeDType->GetPrimitiveType() == reflection::DPrimitive::ePrimitiveType::CLASS)
							{
								reflection::DClass dClass = fieldOwnerObjectTypeDType->AsDClass();
								CallFieldDirtyCallback(attributeList.GetDirtyCallbackFunctionName(), &dClass, fieldOwnerObejct);
							}
						}
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
				std::string fieldTypeFullName = dField.GetFieldTypeFullName();
				if (dField.GetFieldQualifier() == reflection::DField::eProperyQualifier::POINTER)
				{
					fieldTypeFullName += '*';
				}
				else if (dField.GetFieldQualifier() == reflection::DField::eProperyQualifier::REFERENCE)
				{
					fieldTypeFullName += '&';
				}

				return DrawImguiFieldFromDField
				(
					object, 
					dField.GetFieldName(), 
					fieldTypeFullName.c_str(),
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
			bool DrawObjectGUI(const reflection::DClass& dClass, void* const object, const char* const rawObjectName, const eObjectType objectType)
			{
				D_ASSERT(dooms::ui::imguiWithReflection::GetIsIsInitialized() == true);

				bool isDObjectChanged = false;

				if (
					objectType == eObjectType::DObject ? IsValid(reinterpret_cast<dooms::DObject*>(object)) == true : true &&
					// check if DObject is already drawed to prevent infinite loop
					std::find(MultipleDrawChecker.begin(), MultipleDrawChecker.end(), object) == MultipleDrawChecker.end()
					)
				{
					MultipleDrawChecker.push_back(object);



					/*
					//label
					const char* objectName;
					if(rawObjectName == nullptr || rawObjectName[0] == '\0')
					{
						if(objectType == eObjectType::DObject)
						{
							objectName = reinterpret_cast<dooms::DObject*>(object)->GetDObjectName().c_str();
						}
						else
						{// if rawObjectName is empty and object type is rawobject, objectname will be type full name
							objectName = dClass.GetTypeFullName();
						}
					}
					else
					{
						objectName = rawObjectName;
					}
					*/


					if (rawObjectName != nullptr && rawObjectName[0] != '\0')
					{
						ImGui::TextColored(ImVec4{ 1.0f, 0.0f, 0.0f, 1.0f }, "%s", rawObjectName);
					}
					
					const std::vector<dooms::reflection::DField>& dFieldList = dClass.GetDFieldList();
					
					if (dFieldList.empty() == false)
					{
						for (const dooms::reflection::DField& dField : dFieldList)
						{
							bool isFieldValueChanged = false;

							void* fieldRawValue = const_cast<dooms::reflection::DField&>(dField).GetRawFieldValue(object);

							const bool isGUIDrawed = dooms::ui::imguiWithReflectionHelper::DrawImguiFieldFromDField
													(
														fieldRawValue,
														dField,
														isFieldValueChanged,
														&dClass,
														object
													);

						
							if(isGUIDrawed == false)
							{//fail to find special gui func. can't find proper gui function from map
								if (dField.GetFieldTypePrimitiveType() == reflection::DPrimitive::ePrimitiveType::CLASS)
								{
									const reflection::DType fieldType = dField.GetDTypeOfFieldType();

									if(fieldType.GetPrimitiveType() == reflection::DPrimitive::ePrimitiveType::CLASS)
									{
										const reflection::DClass fieldTypeDClass = fieldType.AsDClass();
										if (IsValid(reinterpret_cast<dooms::DObject*>(fieldRawValue)) == true)
										{// if type of field is child class of dooms::DObject
											isFieldValueChanged = DrawObjectGUI(fieldTypeDClass, fieldRawValue, (dField.GetDAttributeList().GetIsNoLabel() == false) ? dField.GetFieldName() : "", eObjectType::DObject);
										}
										else
										{
											if (dField.GetFieldQualifier() == reflection::DField::eProperyQualifier::VALUE)
											{
												isFieldValueChanged = DrawObjectGUI(fieldTypeDClass, fieldRawValue, (dField.GetDAttributeList().GetIsNoLabel() == false) ? dField.GetFieldName() : "", eObjectType::RawObject);
											}
										}
									}
								}
							}


							if (objectType == eObjectType::DObject && isFieldValueChanged == true)
							{
								reinterpret_cast<dooms::DObject*>(object)->OnChangedByGUI(dField);
							}

							isDObjectChanged |= isFieldValueChanged;
							
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
					return DrawObjectGUI(dClass, dObject, "", eObjectType::DObject);
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


