#include "DFunction.h"

#include <unordered_map>

#include "Reflection/ReflectionManager.h"
#include "DClass.h"
#include "DAttributeList.h"

namespace dFunctionHelper
{
	const clcpp::Function* GetclcppFunction(const UINT32 nameHash)
	{
		D_ASSERT(dooms::reflection::ReflectionManager::GetSingleton() != nullptr);
		D_ASSERT(dooms::reflection::ReflectionManager::GetSingleton()->GetIsReflectionDatabaseLoaded() == true);

		const clcpp::Database& db = dooms::reflection::ReflectionManager::GetSingleton()->GetclcppDatabase();
		const clcpp::Function* const clcppType = db.GetFunction(nameHash);
		
		D_ASSERT(clcppType != nullptr);
		D_ASSERT(clcppType->kind == clcpp::Primitive::KIND_FUNCTION);
		return clcppType;
	}

	bool CheckIsMemberFunction(const clcpp::Function* const clFunction)
	{
		return ((clFunction->parameters.size > 0) && (std::strcmp(clFunction->parameters[0]->name.text, "this") == 0));
	}

}

dooms::reflection::DFunction::DFunction(const UINT32 nameHash)
	: DPrimitive(dFunctionHelper::GetclcppFunction(nameHash)), clFunction(static_cast<const clcpp::Function*>(clPrimitive))
{
	D_ASSERT(clPrimitive != nullptr);
	D_ASSERT(clPrimitive->kind == clcpp::Primitive::Kind::KIND_FUNCTION);
	D_ASSERT(clFunction != nullptr);

}

dooms::reflection::DFunction::DFunction(const char* const functionName)

	: DPrimitive(dooms::reflection::ReflectionManager::GetSingleton()->GetclcppDatabase().GetFunction(dooms::reflection::ReflectionManager::GetSingleton()->GetclcppNameHash(functionName))),
	clFunction(static_cast<const clcpp::Function*>(clPrimitive))
{
	D_ASSERT(clPrimitive != nullptr);
	D_ASSERT(clPrimitive->kind == clcpp::Primitive::Kind::KIND_FUNCTION);
	D_ASSERT(clFunction != nullptr);
}

dooms::reflection::DField dooms::reflection::DFunction::GetReturnValueField() const
{
	D_ASSERT(IsValid() == true);
	D_ASSERT(GetIsHasReturnValue() == true);
	return DField(clFunction->return_parameter);
}

bool dooms::reflection::DFunction::GetIsMemberFunction() const
{
	D_ASSERT(IsValid() == true);

	// TODO : Caching isMemberFunction

	return dFunctionHelper::CheckIsMemberFunction(clFunction);
}

bool dooms::reflection::DFunction::GetOwnerClassIfMemberFunction(DClass& dClass) const
{
	D_ASSERT(IsValid() == true);

	bool isSuccess = false;

	if(GetIsMemberFunction() == true)
	{
		D_ASSERT(clFunction->parameters.size > 0);

		dClass = DClass{ clFunction->parameters[0]->type };

		isSuccess = true;
	}

	return isSuccess;
}

const std::vector<dooms::reflection::DField>& dooms::reflection::DFunction::GetParameterDFieldList() const
{
	D_ASSERT(IsValid() == true);

	// key : function hash value
	// value : Functions's field list
	// value : std::vector is enough fast to find field
	static std::unordered_map<UINT32, std::vector<dooms::reflection::DField>> ParameterDFieldListCache;

	const std::vector<dooms::reflection::DField>* cachedDFieldList = nullptr;

	auto iter = ParameterDFieldListCache.find(GetPrimitiveHashValue());
	if (iter != ParameterDFieldListCache.end())
	{// if this function's paramter list is already cached
		cachedDFieldList = &(iter->second);
	}
	else
	{// not cached
		std::vector<dooms::reflection::DField> dFieldList;
		dFieldList.reserve(clFunction->parameters.size);
		
		// if function is member function, it has "this" field at first pos of clFunction->parameters
		for (UINT32 i = ( GetIsMemberFunction() == true ) ? 1 : 0 ; i < clFunction->parameters.size; i++)
		{
			dFieldList.emplace_back(clFunction->parameters[i]);
		}

		auto emplaceResult = ParameterDFieldListCache.emplace(GetPrimitiveHashValue(), std::move(dFieldList));
		cachedDFieldList = &(emplaceResult.first->second);
	}

	D_ASSERT(cachedDFieldList != nullptr);

	return *cachedDFieldList;
}

bool dooms::reflection::DFunction::GetParameterDField(const char* const parameterName, dooms::reflection::DField& dField) const
{
	D_ASSERT(IsValid() == true);

	const std::vector<dooms::reflection::DField>& parameterDFieldList = GetParameterDFieldList();

	bool isSuccess = false;

	for (size_t i = 0; i < parameterDFieldList.size(); i++)
	{
		if(std::strcmp(parameterDFieldList[i].GetFieldName(), parameterName) == 0)
		{
			dField = parameterDFieldList[i];
			isSuccess = true;
			break;
		}
	}

	return isSuccess;
}

dooms::reflection::DAttributeList dooms::reflection::DFunction::GetAttributeList() const
{
	std::vector<dooms::reflection::DAttribute> attributeList;

	D_ASSERT(clFunction != nullptr);

	attributeList.reserve(clFunction->attributes.size);
	for (UINT32 i = 0; i < clFunction->attributes.size; i++)
	{
		attributeList.emplace_back(clFunction->attributes[i]);
	}

	return std::move(attributeList);
}

