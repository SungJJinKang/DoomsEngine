#pragma once
#include "../DirtyReceiver.h"

/*
template <typename ValueType>
class DirtyContainer : public DirtyReceiver
{
private:
	ValueType mValue;
public:
	DirtyContainer();
	DirtyContainer(bool initialDirty);
	DirtyContainer(const DirtyContainer& dirtyContainer);
	DirtyContainer(DirtyContainer&& dirtyContainer) noexcept;
	DirtyContainer& operator=(const DirtyContainer& dirtyContainer);
	DirtyContainer& operator=(DirtyContainer&& dirtyContainer) noexcept;
	~DirtyContainer();

	ValueType GetValue();
	const ValueType& GetValue() const;
};

*/