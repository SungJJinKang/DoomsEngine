#pragma once

#include <Core.h>

#include <string>
#include <functional>

namespace dooms
{
	struct D_UUID
	{
		std::string Value{};

		D_UUID()
			: Value()
		{

		}
		D_UUID(const std::string& InValue)
			: Value(InValue)
		{

		}
		D_UUID(const D_UUID&) = default;
		D_UUID(D_UUID&&) noexcept = default;
		~D_UUID() = default;

		D_UUID& operator=(const D_UUID& InUUID) = default;
		D_UUID& operator=(D_UUID&& InUUID) noexcept = default;

		bool operator==(const D_UUID& ComparedStr) const
		{
			return Value == ComparedStr.Value;
		}
		bool operator!=(const D_UUID& ComparedStr) const
		{
			return Value != ComparedStr.Value;
		}

		bool operator==(const std::string& ComparedStr) const
		{
			return Value == ComparedStr;
		}
		bool operator!=(const std::string& ComparedStr) const
		{
			return Value != ComparedStr;
		}
	};
	
	extern D_UUID GenerateUUID();
}


template<>
struct std::hash<dooms::D_UUID>
{
	std::size_t operator()(const dooms::D_UUID& UUID) const noexcept
	{
		return std::hash<std::string>{}(UUID.Value);
	}
};

extern bool operator==(const dooms::D_UUID& Lhs, const dooms::D_UUID& Rhs);