#pragma once

#include <string>

#define INVALID_DOBJECT_ID 0x0000000000000000

namespace doom
{
	class DObjectManager;
	class DObject;

	struct DObjectContructorParams
	{
		unsigned int DObjectFlag = 0;
		std::string mDObjectName;

		DObjectContructorParams() = default;
		DObjectContructorParams(const DObjectContructorParams&) = default;
		DObjectContructorParams(DObjectContructorParams&&) noexcept = default;
		DObjectContructorParams& operator=(const DObjectContructorParams&) = default;
		DObjectContructorParams& operator=(DObjectContructorParams&&) noexcept = default;
		~DObjectContructorParams() = default;
	};



	enum eDObjectFlag : unsigned int
	{
		NewAllocated = 1 << 0
	};

	
	class DObject;
	class DObject
	{
		friend class DObjectManager;

		struct DObjectProperties
		{
			unsigned int mDObjectFlag = 0;
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

		unsigned long long mDObjectID;
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

		inline size_t GetDObjectID() const
		{
			return mDObjectID;
		}

		inline unsigned int GetDObjectFlag() const
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

