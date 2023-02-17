#pragma once
#include <clcpp/clcpp.h>

namespace dooms::reflection
{
	enum class eProperyQualifier
	{
		VALUE = clcpp::Qualifier::Operator::VALUE,
		POINTER = clcpp::Qualifier::Operator::POINTER,
		REFERENCE = clcpp::Qualifier::Operator::REFERENCE
	};
}
