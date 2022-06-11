#pragma once

#include <type_traits>
#include <memory>
#include <unordered_map>

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
		std::is_same_v<VALUE_TYPE, FLOAT64>,		\
		"Unsupported Type"							\
	)

namespace dooms
{
	class GeneralConfigurationValue;

	struct ConfigurationValueContainer
	{
		std::unordered_map<std::string, std::unordered_map<std::string, GeneralConfigurationValue*>> Data;
	};

	class ConfigurationValueManager
	{
	public:

		inline static ConfigurationValueManager* GetConfigurationValueManager()
		{
			static std::unique_ptr<ConfigurationValueManager> StaticConfigurationValueManager = std::make_unique<ConfigurationValueManager>();
			return StaticConfigurationValueManager.get();
		}

		void AddGeneralConfigurationValueToList(GeneralConfigurationValue* const Value);
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


	private:

		ConfigurationValueContainer GeneralConfigurationValueList{};
	};

	

	class GeneralConfigurationValue
	{

	public:

		const char* GetValueCategory() const;
		const char* GetValueName() const;
		const char* GetValueDescription() const;

		virtual bool IsValueBoolean() const { D_ASSERT(false); return false; }
		virtual bool IsValueInt32() const { D_ASSERT(false); return false; }
		virtual bool IsValueInt64() const { D_ASSERT(false); return false; }
		virtual bool IsValueUInt32() const { D_ASSERT(false); return false; }
		virtual bool IsValueUInt64() const { D_ASSERT(false); return false; }
		virtual bool IsValueFloat32() const { D_ASSERT(false); return false; }
		virtual bool IsValueFloat64() const { D_ASSERT(false); return false; }

		virtual bool AsBoolean() const { D_ASSERT(false); return {}; }
		virtual INT32 AsInt32() const { D_ASSERT(false); return {}; }
		virtual INT64 AsInt64() const { D_ASSERT(false); return {}; }
		virtual UINT32 AsUInt32() const { D_ASSERT(false); return {}; }
		virtual UINT64 AsUInt64() const { D_ASSERT(false); return {}; }
		virtual FLOAT32 AsFloat32() const { D_ASSERT(false); return {}; }
		virtual FLOAT64 AsFloat64() const { D_ASSERT(false); return {}; }

	protected:

		GeneralConfigurationValue
		(
			const char* const Category,
			const char* const Name,
			const char* const Description
		);
		virtual ~GeneralConfigurationValue() = default;

	private:

		const char* const mCategory;
		const char* const mName;
		const char* const mDescription;
	};

	inline GeneralConfigurationValue::GeneralConfigurationValue
	(
		const char* const Category,
		const char* const Name, 
		const char* const Description
	)
		: mCategory(Category), mName(Name), mDescription(Description)
	{
		ConfigurationValueManager::GetConfigurationValueManager()->AddGeneralConfigurationValueToList(this);
	}

	

	template <typename ValueType>
	class TCVar : GeneralConfigurationValue
	{
		CONFIGURATION_VALUE_TYPE_CHECK(ValueType);

	public:

		TCVar
		(
			const char* const Category,
			const char* const Name,
			const char* const Description,
			const ValueType InitialValue
		);
		
		void SetValue(const ValueType Value);
		TCVar<ValueType>& operator=(const ValueType Value);
		ValueType GetValue() const;
		operator ValueType() const;

		virtual bool IsValueBoolean() const override
		{
			return std::is_same_v<ValueType, bool>;
		}
		virtual bool IsValueInt32() const override
		{
			return std::is_same_v<ValueType, INT32>;
		}
		virtual bool IsValueInt64() const override
		{
			return std::is_same_v<ValueType, INT64>;
		}
		virtual bool IsValueUInt32() const override
		{
			return std::is_same_v<ValueType, UINT32>;
		}
		virtual bool IsValueUInt64() const override
		{
			return std::is_same_v<ValueType, UINT64>;
		}
		virtual bool IsValueFloat32() const override
		{
			return std::is_same_v<ValueType, FLOAT32>;
		}
		virtual bool IsValueFloat64() const override
		{
			return std::is_same_v<ValueType, FLOAT64>;
		}

		virtual bool AsBoolean() const { D_ASSERT(IsValueBoolean()); return *reinterpret_cast<const bool*>(&mValue); }
		virtual INT32 AsInt32() const { D_ASSERT(IsValueInt32()); return *reinterpret_cast<const INT32*>(&mValue); }
		virtual INT64 AsInt64() const { D_ASSERT(IsValueInt64()); return *reinterpret_cast<const INT64*>(&mValue); }
		virtual UINT32 AsUInt32() const { D_ASSERT(IsValueUInt32()); return *reinterpret_cast<const UINT32*>(&mValue); }
		virtual UINT64 AsUInt64() const { D_ASSERT(IsValueUInt64()); return *reinterpret_cast<const UINT64*>(&mValue); }
		virtual FLOAT32 AsFloat32() const { D_ASSERT(IsValueFloat32()); return *reinterpret_cast<const FLOAT32*>(&mValue); }
		virtual FLOAT64 AsFloat64() const { D_ASSERT(IsValueFloat64()); return *reinterpret_cast<const FLOAT64*>(&mValue); }

	private:

		ValueType mValue;

	};


	template <typename ValueType>
	TCVar<ValueType>::TCVar
	(
		const char* const Category, 
		const char* const Name, 
		const char* const Description,
		const ValueType InitialValue
	)
		: GeneralConfigurationValue(Category, Name, Description), mValue(InitialValue)
	{
		
	}
	
	

	template <typename ValueType>
	void TCVar<ValueType>::SetValue(const ValueType Value)
	{
		mValue = Value;
	}

	template <typename ValueType>
	TCVar<ValueType>& TCVar<ValueType>::operator=(const ValueType Value)
	{
		mValue = Value;
		return *this;
	}

	template <typename ValueType>
	ValueType TCVar<ValueType>::GetValue() const
	{
		return mValue;
	}

	template <typename ValueType>
	TCVar<ValueType>::operator ValueType() const
	{
		return mValue;
	}
}


