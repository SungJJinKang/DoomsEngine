#pragma once


#include "DirtySender.h"

class DirtySender;
class D_CLASS DirtyReceiver
{
	friend class DirtySender;
private:

	DirtySender* mDirtySender{ nullptr };
	mutable bool bmIsDirty;

public:

	DirtyReceiver();
	DirtyReceiver(bool initialDirty);
	DirtyReceiver(const DirtyReceiver & dirtyReceiver);
	DirtyReceiver(DirtyReceiver && dirtyReceiver) noexcept ;
	DirtyReceiver& operator=(const DirtyReceiver& dirtyReceiver);
	DirtyReceiver& operator=(DirtyReceiver&& dirtyReceiver) noexcept;
	virtual ~DirtyReceiver();

	operator bool() const
	{
		return this->bmIsDirty;
	}

	DirtyReceiver& operator=(bool isDirty)
	{
		this->bmIsDirty = isDirty;
		return *this;
	}

	D_FUNCTION(INVISIBLE)
	void SetDirty(bool isDirty = true)
	{
		this->bmIsDirty = isDirty;
	}

	D_FUNCTION(INVISIBLE)
	bool HasDirtySender() const;

	D_FUNCTION(INVISIBLE)
	void ClearDirtySender()
	{
		if (this->mDirtySender != nullptr)
		{
			this->mDirtySender->RemoveDirtyReceiver(this);
		}
	}

	/// <summary>
	/// Get IsDirty
	/// </summary>
	/// <param name="clearDirty">Do Clear Dirty Variable???</param>
	/// <returns></returns>
	D_FUNCTION(INVISIBLE)
	inline bool GetIsDirty(bool clearDirty) const noexcept // don't put default value to clearDirty argument
	{
		if (clearDirty == true)
		{
			bool currentDirtyVariable = this->bmIsDirty;
			this->bmIsDirty = false;
			return currentDirtyVariable;
		}
		else
		{
			return this->bmIsDirty;
		}
	}

};

