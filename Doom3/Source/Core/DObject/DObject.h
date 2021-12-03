#pragma once

#include <string>
#include <cassert>
#include <type_traits>

#include <Macros/TypeDef.h>
#include <CompilerMacros.h>
#include <Macros/DllMarcos.h>

#include "DObjectMacros.h"
#include "DObject_Constant.h"
#include "DObjectManager.h"
#include <GarbageCollector/RootObjectLevel.h>

#include "Reflection/Reflection.h"
#include "EngineGUI/EngineGUIAccessor.h"
#include "Reflection/ReflectionType/DField.h"

#include "DObject.reflection.h"
D_NAMESPACE(dooms)
namespace dooms
{
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
		NewAllocated = 1 << 0,
		Unreachable = 1 << 1, // When DObject is created, this value is 0. because gc do mark stage incrementally.
		IsPendingKill = 1 << 2, 
		NotCollectedByGC = 1 << 3,
		IsRootObject = 1 << 4,
		IsNotCheckedByGC = 1 << 5 // to prevent circular reference check by gc
	};

	inline extern const UINT32 NotCopyedFlagsWhenCopyMoveConstruct
		=	eDObjectFlag::NewAllocated |
			eDObjectFlag::Unreachable |
			eDObjectFlag::IsPendingKill |
			eDObjectFlag::IsRootObject |
			eDObjectFlag::IsNotCheckedByGC;

	
	class DOOM_API D_CLASS DObject
	{
		GENERATE_BODY()

		friend class DObjectManager;

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

			size_t mCurrentIndexInDObjectList;
			
			D_PROPERTY(INVISIBLE)
			std::string mDObjectName;
			
			const DObject* mOwnerDObject;

			DObjectProperties()
				: mCurrentIndexInDObjectList((size_t)-1), mDObjectName(), mOwnerDObject(nullptr)
			{
				
			}
			DObjectProperties(const DObjectProperties& dObjectProperties)
			{
				mCurrentIndexInDObjectList = (size_t)-1;
				mDObjectName = dObjectProperties.mDObjectName;
				mOwnerDObject = dObjectProperties.mOwnerDObject;
			}
			DObjectProperties(DObjectProperties&& dObjectProperties) noexcept
			{
				mCurrentIndexInDObjectList = (size_t)-1;
				mDObjectName = dObjectProperties.mDObjectName;
				mOwnerDObject = dObjectProperties.mOwnerDObject;				
			}
			DObjectProperties& operator=(const DObjectProperties& dObjectProperties)
			{
				mDObjectName = dObjectProperties.mDObjectName;
				mOwnerDObject = dObjectProperties.mOwnerDObject;
				return *this;
			}
			DObjectProperties& operator=(DObjectProperties&& dObjectProperties) noexcept
			{
				mDObjectName = dObjectProperties.mDObjectName;
				mOwnerDObject = dObjectProperties.mOwnerDObject;
				return *this;
			}
			~DObjectProperties() = default;
		};

	private:
		
		D_PROPERTY(NOLABEL)
		DObjectProperties mDObjectProperties;
				
		void Construct_Internal();

		void CopyFlagsToThisDObject(const UINT32 flags);

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

		virtual void OnSetPendingKill(){}

		bool AddToRootObjectList();
		bool GetIsRootObject() const;
		

		virtual void OnChangedByGUI(const dooms::reflection::DField& dFieldOfChangedField) {}
		virtual void OnUpdateGUI() {} // never delete this

		void InitProperties(const DObjectContructorParams& params);


		D_FUNCTION()
		inline size_t GetDObjectID() const
		{
			if(mDObjectProperties.mCurrentIndexInDObjectList != (size_t)-1)
			{
				return dooms::DObjectManager::mDObjectsContainer.mDObjectIDList[mDObjectProperties.mCurrentIndexInDObjectList];
			}
			else
			{
				return INVALID_DOBJECT_ID;
			}		
		}

		D_FUNCTION()
		FORCE_INLINE UINT32 GetDObjectFlag() const
		{
			assert(mDObjectProperties.mCurrentIndexInDObjectList != (size_t)-1);
			return dooms::DObjectManager::mDObjectsContainer.GetDObjectFlag(mDObjectProperties.mCurrentIndexInDObjectList);
		}

		D_FUNCTION()
		FORCE_INLINE bool GetDObjectFlag(const eDObjectFlag flag) const
		{
			assert(mDObjectProperties.mCurrentIndexInDObjectList != (size_t)-1);
			return (dooms::DObjectManager::mDObjectsContainer.GetDObjectFlag(mDObjectProperties.mCurrentIndexInDObjectList) & flag) != 0;
		}
		
		D_FUNCTION()
		FORCE_INLINE void SetDObjectFlag(const UINT32 flag)
		{
			assert(mDObjectProperties.mCurrentIndexInDObjectList != (size_t)-1);
			dooms::DObjectManager::mDObjectsContainer.SetDObjectFlag(mDObjectProperties.mCurrentIndexInDObjectList, flag);
		}

		D_FUNCTION()
		FORCE_INLINE void ClearDObjectFlag(const eDObjectFlag flag)
		{
			assert(mDObjectProperties.mCurrentIndexInDObjectList != (size_t)-1);
			dooms::DObjectManager::mDObjectsContainer.ClearDObjectFlag(mDObjectProperties.mCurrentIndexInDObjectList, flag);
		}

		D_FUNCTION()
		FORCE_INLINE void ResetDObjectFlag(const UINT32 flag)
		{
			assert(mDObjectProperties.mCurrentIndexInDObjectList != (size_t)-1);
			dooms::DObjectManager::mDObjectsContainer.ResetDObjectFlag(mDObjectProperties.mCurrentIndexInDObjectList, flag);
		}

		D_FUNCTION()
		const std::string& GetDObjectName() const;

		D_FUNCTION()
		void ChangeDObjectName(const std::string& dObjectName);
		
		D_FUNCTION()
		void ChangeDObjectName(const char* const dObjectName);

		D_FUNCTION()
		void SetOwnerDObject(const DObject* const ownerDObject);

		D_FUNCTION()
		reflection::DClass GetDClass() const;

		D_FUNCTION()
		FORCE_INLINE bool GetIsPendingKill() const
		{
			return GetDObjectFlag(eDObjectFlag::IsPendingKill);
		}
		D_FUNCTION()
		FORCE_INLINE void SetIsPendingKill()
		{
			if(GetIsPendingKill() == false)
			{
				OnSetPendingKill();
				SetDObjectFlag(eDObjectFlag::IsPendingKill);
			}
		}


		D_FUNCTION(INVISIBLE)
		bool DestroySelf();


		D_FUNCTION(INVISIBLE)
		bool DestroySelfInstantly();
	};
}

