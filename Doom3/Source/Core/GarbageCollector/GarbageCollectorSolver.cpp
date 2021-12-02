#include "GarbageCollectorSolver.h"

#include <DObject/DObject.h>
#include <DObject/DObjectManager.h>
#include <ResourceManagement/JobSystem_cpp/JobSystem.h>
#include <Reflection/ReflectionType/DField.h>
#include <Reflection/ReflectionType/DClass.h>

namespace dooms::gc::garbageCollectorSolver
{
	FORCE_INLINE void SetReachable(UINT32& flag)
	{
		flag &= ~static_cast<UINT32>(dooms::eDObjectFlag::Unreachable);
	}
}

void dooms::gc::garbageCollectorSolver::SetUnreachableFlag(std::vector<UINT32>& flags)
{
	UINT32* start = flags.data();
	const UINT32* const end = flags.data() + flags.size();
	while(start != end)
	{
		// compiler is good at vectorizing this
		*start |= static_cast<UINT32>(dooms::eDObjectFlag::Unreachable);
		start++;
	}
}

namespace dooms::gc::garbageCollectorSolver
{
	void SolveGCRecursive
	(
		const UINT32 keepFlags,
		void* const object,
		const dooms::reflection::DField& dField
	)
	{
		if(dField.GetFieldTypePrimitiveType() == reflection::DPrimitive::ePrimitiveType::CLASS)
		{
			if (dField.GetFieldQualifier() == reflection::DField::eProperyQualifier::POINTER)
			{
				// if object is nullptr, DObjectManager::IsDObjectExist is suprer fast
				if(IsStrongValid(*reinterpret_cast<dooms::DObject**>(object), false) == true)
				{
					dooms::DObject* const targetDObject = (*reinterpret_cast<dooms::DObject**>(object));

					targetDObject->ClearDObjectFlag(eDObjectFlag::Unreachable);

					dooms::reflection::DClass dClass = targetDObject->GetDClass();

					const std::vector<dooms::reflection::DField>& dFieldList = dClass.GetDFieldList();

					for(const dooms::reflection::DField& field : dFieldList)
					{
						SolveGCRecursive(keepFlags, reinterpret_cast<char*>(targetDObject) + field.GetFieldOffset(), field);
					}

				}
				else
				{
					// TODO : add data whether class is child of DObject class to clcpp::Class
					// If DObject address in pointer is dummy address, nullify pointer
					*reinterpret_cast<dooms::DObject**>(object) = nullptr;
				}
			}
			else
			{
				// if object is nullptr, DObjectManager::IsDObjectExist is suprer fast
				if (IsStrongValid(reinterpret_cast<dooms::DObject*>(object), false) == true)
				{
					dooms::DObject* const targetDObject = reinterpret_cast<dooms::DObject*>(object);

					targetDObject->ClearDObjectFlag(eDObjectFlag::Unreachable);

					dooms::reflection::DClass dClass = targetDObject->GetDClass();

					const std::vector<dooms::reflection::DField>& dFieldList = dClass.GetDFieldList();

					for (const dooms::reflection::DField& field : dFieldList)
					{
						SolveGCRecursive(keepFlags, reinterpret_cast<char*>(targetDObject) + field.GetFieldOffset(), field);
					}

				}
			}
		}
	}
}

void dooms::gc::garbageCollectorSolver::Mark(const UINT32 keepFlags, std::vector<dooms::DObject*>& rootDObjectList)
{
	// GC if dObject is on pending kill

	// check does have NewAllocated flag

	// use multithread but doesn't delete in subthread

	for(dooms::DObject* rootDObejct : rootDObjectList)
	{
		D_ASSERT(IsStrongValid(rootDObejct, false) == true);
		Mark(keepFlags, rootDObejct);
	}
}

void dooms::gc::garbageCollectorSolver::Mark(const UINT32 keepFlags, dooms::DObject* const rootObject)
{
	// First clear rootObject's Unreachable flags
	rootObject->ClearDObjectFlag(dooms::eDObjectFlag::Unreachable);


}

void dooms::gc::garbageCollectorSolver::Sweep(std::vector<dooms::DObject*>& dObjectList)
{
}
