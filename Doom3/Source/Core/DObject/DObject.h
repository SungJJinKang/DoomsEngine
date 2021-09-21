#pragma once



#define INVALID_DOBJECT_ID 0x0000000000000000

namespace doom
{
	class DObjectManager;
	class DObject
	{
		friend class DObjectManager;

	private:

		size_t mDObjectID;

		void InitializeDObject();

	protected:

		DObject();



		DObject(const DObject& dObject);
		DObject(DObject&& dObject) noexcept;
		DObject& operator=(const DObject& dObject);
		DObject& operator=(DObject&& dObject) noexcept;

		virtual ~DObject();

	public:

		inline size_t GetDObjectID() const
		{
			return mDObjectID;
		}
	};

}

