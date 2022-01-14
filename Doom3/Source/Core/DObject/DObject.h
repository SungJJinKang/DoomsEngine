#pragma once

#include <string>
#include <cassert>
#include <type_traits>
#include <atomic>

#include <Macros/TypeDef.h>
#include <CompilerMacros.h>
#include <Macros/DllMarcos.h>

#include "DObjectMacros.h"
#include "DObject_Constant.h"
#include "DObjectManager.h"

#include "Reflection/Reflection.h"
#include "EngineGUI/EngineGUIAccessor.h"
#include "Reflection/ReflectionType/DField.h"


#define DAFAULT_DOBJECT_FLAGS 0

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
		IsRootObject = 1 << 3,
		IsNotCheckedByGC = 1 << 4 // to prevent circular reference check by gc
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

			D_PROPERTY(INVISIBLE)
			INT64 mCurrentIndexInDObjectList;

			D_PROPERTY(INVISIBLE)
			std::atomic<UINT64> mDObjectFlag;

			D_PROPERTY(READONLY)
			INT64 mDObjectID;
			
			D_PROPERTY(INVISIBLE)
			std::string mDObjectName;
			
			const DObject* mOwnerDObject;

			DObjectProperties()
				:
			mCurrentIndexInDObjectList(INVALID_CURRENT_INDEX_IN_DOBJECT_LIST),
			mDObjectID(INVALID_DOBJECT_ID),
			mDObjectName(),
			mOwnerDObject(nullptr),
			mDObjectFlag(DAFAULT_DOBJECT_FLAGS)
			{
				
			}
			DObjectProperties(const DObjectProperties& dObjectProperties)
			{
				mCurrentIndexInDObjectList = INVALID_CURRENT_INDEX_IN_DOBJECT_LIST;
				mDObjectID = INVALID_DOBJECT_ID;
				mDObjectName = dObjectProperties.mDObjectName;
				mOwnerDObject = dObjectProperties.mOwnerDObject;
			}
			DObjectProperties(DObjectProperties&& dObjectProperties) noexcept
			{
				mCurrentIndexInDObjectList = INVALID_CURRENT_INDEX_IN_DOBJECT_LIST;
				mDObjectID = INVALID_DOBJECT_ID;
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
		void OnSetPendingKill_Internal();

		/// <summary>
		/// If you want that this object is not collected by gc, call this fucntion
		/// </summary>
		/// <returns></returns>
		bool AddToRootObjectList();
		bool GetIsRootObject() const;
		

		virtual void OnChangedByGUI(const dooms::reflection::DField& dFieldOfChangedField) {}
		virtual void OnUpdateGUI() {} // never delete this

		void InitProperties(const DObjectContructorParams& params);


		D_FUNCTION()
		inline UINT64 GetDObjectID() const
		{
			return mDObjectProperties.mDObjectID;
		}

		D_FUNCTION()
		FORCE_INLINE UINT64 GetDObjectFlag(const std::memory_order memoryOrder = std::memory_order_seq_cst) const
		{
			return mDObjectProperties.mDObjectFlag.load(memoryOrder);
		}

		D_FUNCTION()
		FORCE_INLINE bool GetDObjectFlag(const UINT64 flag, const std::memory_order memoryOrder = std::memory_order_seq_cst) const
		{
			return (GetDObjectFlag(memoryOrder) & flag) != 0;
		}
		
		D_FUNCTION()
		FORCE_INLINE void SetDObjectFlag(const UINT64 flag, const std::memory_order memoryOrder = std::memory_order_seq_cst)
		{
			mDObjectProperties.mDObjectFlag |= flag;
		}

		D_FUNCTION()
		FORCE_INLINE void ClearDObjectFlag(const UINT64 flag, const std::memory_order memoryOrder = std::memory_order_seq_cst)
		{
			mDObjectProperties.mDObjectFlag &= (~flag);
		}

		D_FUNCTION()
		FORCE_INLINE void ResetDObjectFlag(const UINT64 flag, const std::memory_order memoryOrder = std::memory_order_seq_cst)
		{
			mDObjectProperties.mDObjectFlag.store(flag, memoryOrder);
		}

		D_FUNCTION()
		FORCE_INLINE bool HasDObjectFlag(const UINT64 flag, const std::memory_order memoryOrder = std::memory_order_seq_cst)
		{
			return (GetDObjectFlag() & flag) == flag;
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
		FORCE_INLINE bool GetIsPendingKill(const std::memory_order memoryOrder = std::memory_order_seq_cst) const
		{
			return GetDObjectFlag(eDObjectFlag::IsPendingKill, memoryOrder);
		}

		D_FUNCTION()
		FORCE_INLINE bool GetIsNewAllocated(const std::memory_order memoryOrder = std::memory_order_seq_cst) const
		{
			return GetDObjectFlag(eDObjectFlag::NewAllocated, memoryOrder);
		}

		D_FUNCTION()
		FORCE_INLINE bool SetIsPendingKill(const std::memory_order memoryOrder = std::memory_order_seq_cst)
		{
			bool isSuccess = false;
			if(GetIsPendingKill() == false/* && GetIsNewAllocated() == true*/)
			{
				OnSetPendingKill_Internal();
				OnSetPendingKill();
				SetDObjectFlag(eDObjectFlag::IsPendingKill, memoryOrder);

				isSuccess = true;
			}
			return isSuccess;
		}


		D_FUNCTION(INVISIBLE)
		bool DestroySelf();

		/// <summary>
		/// This is really dangerous. it can makes problem when you call IsValid function
		/// </summary>
		D_FUNCTION(INVISIBLE)
		bool DestroySelfInstantly();
	};
}

