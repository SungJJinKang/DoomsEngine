#include "DTemplateArgumentType.h"

dooms::reflection::DTemplateArgumentType::DTemplateArgumentType()
	: DType(), mIsPointer(false)
{
}

dooms::reflection::DTemplateArgumentType::DTemplateArgumentType(const clcpp::Type* const clcppType, const bool isPointer)
	: DType(clcppType), mIsPointer(isPointer)
{

}
