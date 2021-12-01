#include "GarbageCollectee.h"

dooms::gc::GarbageCollectee::GarbageCollectee()
	: mIsPendingKill(false)
{
}

dooms::gc::GarbageCollectee::GarbageCollectee(bool isPendingKill)
	: mIsPendingKill(isPendingKill)
{
}

dooms::gc::GarbageCollectee::GarbageCollectee(const GarbageCollectee& gcee)
	: mIsPendingKill(false)
{
}

dooms::gc::GarbageCollectee::GarbageCollectee(GarbageCollectee&& gcee) noexcept
	: mIsPendingKill(false)
{
}

dooms::gc::GarbageCollectee& dooms::gc::GarbageCollectee::operator=(const GarbageCollectee& gcee)
{
	return *this;
}

dooms::gc::GarbageCollectee& dooms::gc::GarbageCollectee::operator=(GarbageCollectee&& gcee) noexcept
{
	return *this;
}

void dooms::gc::GarbageCollectee::SetIsPendingKill(const bool isPendingKill)
{
	mIsPendingKill = isPendingKill;
}
