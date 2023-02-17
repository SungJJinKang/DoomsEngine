#pragma once

#include <vector>

#include <Core.h>

class DirtyReceiver;
class D_CLASS DirtySender
{
	friend class DirtyReceiver;
private:

	std::vector<DirtyReceiver*> mDirtyReceivers;
	//this class doens't have dirty value itself, this clacss just send dirty to Reveivers

	

public:
	
	DirtySender() = default;
	DirtySender(const DirtySender&);
	DirtySender(DirtySender&&) noexcept = delete;
	DirtySender& operator=(const DirtySender&);
	DirtySender& operator=(DirtySender&&) noexcept = delete;
	virtual ~DirtySender();

	/// <summary>
	/// Don't call this function directly
	/// Construct Receiver object with Sender parameter
	/// </summary>
	/// <param name="reciever"></param>
	void AddDirtyReceiver(DirtyReceiver* receiver);
	/// <summary>
	/// Don't call this function directly
	/// </summary>
	/// <param name="reciever"></param>
	void RemoveDirtyReceiver(DirtyReceiver* receiver);

	D_FUNCTION(INVISIBLE)
	void NotifyDirty();
};

