#pragma once

#include <string>
#include <cassert>
#include <type_traits>

#include <Macros/TypeDef.h>
#include <Macros/DllMarcos.h>

#include "DObjectMacros.h"
#include "DObject_Constant.h"

#include "Reflection/Reflection.h"
#include <GarbageCollector/GarbageCollectee.h>
#include "EngineGUI/EngineGUIAccessor.h"
#include "Reflection/ReflectionType/DField.h"

#include "DObject.reflection.h"
D_NAMESPACE(dooms)
namespace dooms
{
	namespace gc
	{
		class GarbageCollectee;
	}

	namespace reflection
	{
		class DClass;
	}

	class DObjectManager;
	class DObject;

#define IS_DOBJECT_TYPE(TYPE) std::is_base_of<dooms::DObject, TYPE>::value

	struct DOOM_API D_STRUCT DObjectContructorParams
	{
		GENERATE_BODY_DObjectContructorParams()

		D_PROPERTY()
		UINT32 DObjectFlag = 0;

		D_PROPERTY()
		std::string mDObjectName;

		DObjectContructorParams() = default;
		DObjectContructorParams(const DObjectContructorParams&) = default;
		DObjectContructorParams(DObjectContructorParams&&) noexcept = default;
		DObjectContructorParams& operator=(const DObjectContructorParams&) = default;
		DObjectContructorParams& operator=(DObjectContructorParams&&) noexcept = default;
		~DObjectContructorParams() = default;
	};



	enum D_ENUM eDObjectFlag : UINT32
	{
		NewAllocated = 1 << 0
	};

	
	class DOOM_API D_CLASS DObject
	{
		GENERATE_BODY()

	public:

		template <typename BASE_TYPE>
		FORCE_INLINE bool IsChildOf() const noexcept
		{
			static_assert(IS_DOBJECT_TYPE(BASE_TYPE));

			const UINT32 baseChainListLength = GetBaseChainListLength();
			const bool isChild = (baseChainListLength >= BASE_TYPE::BASE_CHAIN_LIST_LENGTH) && (GetBaseChainList()[baseChainListLength - BASE_TYPE::BASE_CHAIN_LIST_LENGTH] == BASE_TYPE::TYPE_FULL_NAME_HASH_VALUE);

			// TODO : if progragmmer deosn't write GENERATE_BODY macros, this function make big bug!!
			//        Make detect code that

			return isChild;
		}
		
		template <>
		FORCE_INLINE bool IsChildOf<dooms::DObject>() const noexcept
		{
			return true;
		}

		friend class DObjectManager;


		struct DOOM_API D_STRUCT DObjectProperties
		{
			GENERATE_BODY_DObjectProperties()

			D_PROPERTY()
			UINT32 mDObjectFlag = 0;

			D_PROPERTY()
			std::string mDObjectName;
			
			const DObject* mOwnerDObject = nullptr;

			DObjectProperties() = default;
			DObjectProperties(const DObjectProperties&) = default;
			DObjectProperties(DObjectProperties&&) noexcept = default;
			DObjectProperties& operator=(const DObjectProperties&) = default;
			DObjectProperties& operator=(DObjectProperties&&) noexcept = default;
			~DObjectProperties() = default;
		};

	private:

		D_PROPERTY(INVISIBLE)
		UINT64 mDObjectID;

		D_PROPERTY()
		DObjectProperties mDObjectProperties;

		gc::GarbageCollectee mGarbageCollectee;

		void Construct_Internal();
		

	protected:

		DObject();
		DObject(const std::string& dObjectName);
		DObject(const DObject* const ownerDObject, const std::string& dObjectName);

		DObject(const DObjectContructorParams& params);
		DObject(const DObject& dObject);
		DObject(DObject&& dObject) noexcept;
		DObject& operator=(const DObject& dObject);
		DObject& operator=(DObject&& dObject) noexcept;
		virtual ~DObject();



	public:

		dooms::ui::EngineGUIAccessor mEngineGUIAccessor;
		virtual void OnChangedByGUI(const dooms::reflection::DField& dFieldOfChangedField) {}
		virtual void OnUpdateGUI() {}

		void InitProperties(const DObjectContructorParams& params);


		D_FUNCTION()
		inline size_t GetDObjectID() const
		{
			return mDObjectID;
		}

		D_FUNCTION()
		inline UINT32 GetDObjectFlag() const
		{
			return mDObjectProperties.mDObjectFlag;
		}

		D_FUNCTION()
		inline bool GetDObjectFlag(const eDObjectFlag flag) const
		{
			return (mDObjectProperties.mDObjectFlag & flag) != 0;
		}

		D_FUNCTION()
		const std::string& GetDObjectName() const;

		D_FUNCTION()
		void ChangeDObjectName(const std::string& dObjectName);
		
		D_FUNCTION()
		void ChangeDObjectName(const char* const dObjectName);

		D_FUNCTION()
		void SetOwnerDObject(const DObject* const ownerDObject);

		reflection::DClass GetDClass() const;
	};
}

