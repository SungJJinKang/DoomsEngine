#pragma once

#include <type_traits>
#include <memory>
#include <unordered_map>
#include <string>

#include <CompilerMacros.h>
#include <TypeDef.h>
#include <Macros/Assert.h>

#define CONFIGURATION_VALUE_TYPE_CHECK(VALUE_TYPE)  \
	static_assert									\
	(												\
		std::is_same_v<VALUE_TYPE, bool> ||			\
		std::is_same_v<VALUE_TYPE, INT32> ||		\
		std::is_same_v<VALUE_TYPE, INT64> ||		\
		std::is_same_v<VALUE_TYPE, UINT32> ||		\
		std::is_same_v<VALUE_TYPE, UINT64> ||		\
		std::is_same_v<VALUE_TYPE, FLOAT32> ||		\
		std::is_same_v<VALUE_TYPE, FLOAT64> ||		\
		std::is_same_v<VALUE_TYPE, std::string>, 	\
		"Unsupported Type"							\
	)

namespace dooms
{
	class GeneralConfigurationValue;

	template <typename ValueType>
	class TCvar;

	class GeneralConfigurationValue
	{

	public:

		GeneralConfigurationValue
		(
			const std::string& Category,
			const std::string& Name,
			const std::string& Description
		);
		virtual ~GeneralConfigurationValue() = default;

		const std::string& GetValueCategory() const;
		const std::string& GetValueName() const;
		const std::string& GetValueDescription() const;

		virtual bool IsValueBoolean() const = 0;
		virtual bool IsValueInt32() const = 0;
		virtual bool IsValueInt64() const = 0;
		virtual bool IsValueUInt32() const = 0;
		virtual bool IsValueUInt64() const = 0;
		virtual bool IsValueFloat32() const = 0;
		virtual bool IsValueFloat64() const = 0;
		virtual bool IsValueString() const = 0;

		template <typename ValueType>
		inline bool IsValueType() const
		{
			D_ASSERT_LOG(false, "Unsupported Type");
			return false;
		}

		template <>
		inline bool IsValueType<bool>() const
		{
			return IsValueBoolean();
		}

		template <>
		inline bool IsValueType<INT32>() const
		{
			return IsValueInt32();
		}

		template <>
		inline bool IsValueType<INT64>() const
		{
			return IsValueInt64();
		}

		template <>
		inline bool IsValueType<UINT32>() const
		{
			return IsValueUInt32();
		}

		template <>
		inline bool IsValueType<UINT64>() const
		{
			return IsValueUInt64();
		}

		template <>
		inline bool IsValueType<FLOAT32>() const
		{
			return IsValueFloat32();
		}

		template <>
		inline bool IsValueType<FLOAT64>() const
		{
			return IsValueFloat64();
		}

		template <>
		inline bool IsValueType<std::string>() const
		{
			return IsValueString();
		}

		virtual bool AsBoolean() const = 0;
		virtual INT32 AsInt32() const = 0;
		virtual INT64 AsInt64() const = 0;
		virtual UINT32 AsUInt32() const = 0;
		virtual UINT64 AsUInt64() const = 0;
		virtual FLOAT32 AsFloat32() const = 0;
		virtual FLOAT64 AsFloat64() const = 0;
		virtual std::string AsString() const = 0;
		

	private:

		const std::string mCategory;
		const std::string mName;
		const std::string mDescription;
	};
	
	template <typename ValueType>
	class TCvar : GeneralConfigurationValue
	{
		CONFIGURATION_VALUE_TYPE_CHECK(ValueType);

	public:

		TCvar
		(
			const std::string& Category,
			const std::string& Name,
			const std::string& Description,
			const ValueType InitialValue
		);
		
		inline void SetValue(const ValueType& InValue);
		inline ValueType GetValue() const;
		inline ValueType& GetReference();
		inline const ValueType& GetReference() const;
		inline ValueType& operator*();
		inline const ValueType& operator*() const;
		inline ValueType* operator->();
		inline const ValueType* operator->() const;

		virtual bool IsValueBoolean() const override final
		{
			return std::is_same_v<ValueType, bool>;
		}
		virtual bool IsValueInt32() const override final
		{
			return std::is_same_v<ValueType, INT32>;
		}
		virtual bool IsValueInt64() const override final
		{
			return std::is_same_v<ValueType, INT64>;
		}
		virtual bool IsValueUInt32() const override final
		{
			return std::is_same_v<ValueType, UINT32>;
		}
		virtual bool IsValueUInt64() const override final
		{
			return std::is_same_v<ValueType, UINT64>;
		}
		virtual bool IsValueFloat32() const override final
		{
			return std::is_same_v<ValueType, FLOAT32>;
		}
		virtual bool IsValueFloat64() const override final
		{
			return std::is_same_v<ValueType, FLOAT64>;
		}
		virtual bool IsValueString() const override final
		{
			return std::is_same_v<ValueType, std::string>;
		}

		virtual bool AsBoolean() const final { D_ASSERT(IsValueBoolean()); return *reinterpret_cast<const bool*>(&Value); }
		virtual INT32 AsInt32() const final { D_ASSERT(IsValueInt32()); return *reinterpret_cast<const INT32*>(&Value); }
		virtual INT64 AsInt64() const final { D_ASSERT(IsValueInt64()); return *reinterpret_cast<const INT64*>(&Value); }
		virtual UINT32 AsUInt32() const final { D_ASSERT(IsValueUInt32()); return *reinterpret_cast<const UINT32*>(&Value); }
		virtual UINT64 AsUInt64() const final { D_ASSERT(IsValueUInt64()); return *reinterpret_cast<const UINT64*>(&Value); }
		virtual FLOAT32 AsFloat32() const final { D_ASSERT(IsValueFloat32()); return *reinterpret_cast<const FLOAT32*>(&Value); }
		virtual FLOAT64 AsFloat64() const final { D_ASSERT(IsValueFloat64()); return *reinterpret_cast<const FLOAT64*>(&Value); }
		virtual std::string AsString() const final { D_ASSERT(IsValueString()); return *reinterpret_cast<const std::string*>(&Value); }

	private:

		ValueType Value;

	};

	struct ConfigurationValueContainer
	{
		std::unordered_map<std::string, std::unordered_map<std::string, GeneralConfigurationValue*>> Data;
	};

	class ConfigurationValueManager
	{
	public:

		static ConfigurationValueManager* GetConfigurationValueManager();

		void RegisterConsoleVariable(GeneralConfigurationValue* const Value);
		ConfigurationValueContainer& GetGeneralConfigurationValueList();
		const ConfigurationValueContainer& GetGeneralConfigurationValueList() const;

		GeneralConfigurationValue* GetGeneralConfigurationValue
		(
			const char* const Category,
			const char* const Name
		);
		const GeneralConfigurationValue* GetGeneralConfigurationValue
		(
			const char* const Category,
			const char* const Name
		) const;

		template <typename ValueType>
		TCvar<ValueType>* GetTCvar
		(
			const char* const Category,
			const char* const Name
		)
		{
			return const_cast<dooms::TCvar<ValueType>*>(static_cast<const dooms::ConfigurationValueManager*>(this)->GetTCvar<ValueType>(Category, Name));
		}

		template <typename ValueType>
		TCvar<ValueType>* GetTCvar
		(
			const char* const Category,
			const char* const Name
		) const
		{
			const GeneralConfigurationValue* const Cvar = GetGeneralConfigurationValue(Category, Name);
			return Cvar->IsValueType<ValueType>() ? reinterpret_cast<TCvar<ValueType>*>(const_cast<GeneralConfigurationValue*>(Cvar)) : nullptr;
		}


	private:

		ConfigurationValueContainer GeneralConfigurationValueList{};
	};
	
	template <typename ValueType>
	inline TCvar<ValueType>::TCvar
	(
		const std::string& Category,
		const std::string& Name,
		const std::string& Description,
		const ValueType InitialValue
	)
		: GeneralConfigurationValue(Category, Name, Description), Value(InitialValue)
	{
	}

	template <typename ValueType>
	inline void TCvar<ValueType>::SetValue(const ValueType& InValue)
	{
		Value = InValue;
	}

	template <typename ValueType>
	inline ValueType TCvar<ValueType>::GetValue() const
	{
		return Value;
	}

	template <typename ValueType>
	inline ValueType& TCvar<ValueType>::GetReference()
	{
		return Value;
	}

	template <typename ValueType>
	inline const ValueType& TCvar<ValueType>::GetReference() const
	{
		return Value;
	}

	template <typename ValueType>
	inline ValueType& TCvar<ValueType>::operator*()
	{
		return Value;
	}

	template <typename ValueType>
	inline const ValueType& TCvar<ValueType>::operator*() const
	{
		return Value;
	}

	template <typename ValueType>
	inline ValueType* TCvar<ValueType>::operator->()
	{
		return &Value;
	}

	template <typename ValueType>
	inline const ValueType* TCvar<ValueType>::operator->() const
	{
		return &Value;
	}
}


