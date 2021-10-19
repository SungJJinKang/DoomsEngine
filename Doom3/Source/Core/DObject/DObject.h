#pragma once

#include <string>

#include <Macros/TypeDef.h>
#include <Macros/DllMarcos.h>

#include "DObjectMacros.h"

#define INVALID_DOBJECT_ID 0x0000000000000000

namespace doom
{
	class DObjectManager;
	class DObject;

	struct DOOM_API DObjectContructorParams
	{
		UINT32 DObjectFlag = 0;
		std::string mDObjectName;

		DObjectContructorParams() = default;
		DObjectContructorParams(const DObjectContructorParams&) = default;
		DObjectContructorParams(DObjectContructorParams&&) noexcept = default;
		DObjectContructorParams& operator=(const DObjectContructorParams&) = default;
		DObjectContructorParams& operator=(DObjectContructorParams&&) noexcept = default;
		~DObjectContructorParams() = default;
	};



	enum eDObjectFlag : UINT32
	{
		NewAllocated = 1 << 0
	};

	
	class DOOM_API DObject
	{
		DOBJECT_ABSTRACT_CLASS_BODY(DObject);

	protected:
		static void BASE_CHAIN_HILLCLIMB(doom::DOBJECT_BASE_CHAIN& base_chain)
		{
			base_chain.BASE_CHAIN_COUNT++;
			base_chain.BASE_CHAIN_TYPE_ID_LIST.push_back(TYPE_ID_STATIC());
		}
	public:
		inline static const DOBJECT_BASE_CHAIN BASE_CHAIN_STATIC{};
		virtual const DOBJECT_BASE_CHAIN& GET_BASE_CHAIN() const { return BASE_CHAIN_STATIC; }

		bool IsChildOf(const SIZE_T baseTypeID) const
		{
			bool isChild = (baseTypeID == TYPE_ID());

			if(isChild == false)
			{
				for (SIZE_T this_object_base_type : GET_BASE_CHAIN().BASE_CHAIN_TYPE_ID_LIST)
				{
					if (baseTypeID == this_object_base_type)
					{
						isChild = true;
						break;
					}
				}
			}
			
			return isChild;
		}

		template <typename BASE_TYPE>
		bool IsChildOf() const
		{
			static_assert(IS_DOBJECT_TYPE(BASE_TYPE));
			return IsChildOf(BASE_TYPE::TYPE_ID_STATIC());
		}

		friend class DObjectManager;

		struct DObjectProperties
		{
			UINT32 mDObjectFlag = 0;
			//Used For Debugging
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

		UINT64 mDObjectID;
		DObjectProperties mDObjectProperties;

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

		void InitProperties(const DObjectContructorParams& params);

		inline SIZE_T GetDObjectID() const
		{
			return mDObjectID;
		}

		inline UINT32 GetDObjectFlag() const
		{
			return mDObjectProperties.mDObjectFlag;
		}

		inline bool GetDObjectFlag(const eDObjectFlag flag) const
		{
			return (mDObjectProperties.mDObjectFlag & flag) != 0;
		}

		void ChangeDObjectName(const std::string& dObjectName);
		void SetOwnerDObject(const DObject* const ownerDObject);
	};
}

