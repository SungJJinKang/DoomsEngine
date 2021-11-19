#include "DFunction.h"

#include <unordered_map>

#include "Reflection/ReflectionManager.h"

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

		for (UINT32 i = 0; i < clFunction->parameters.size; i++)
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

