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

void dooms::gc::garbageCollectorSolver::StartSetUnreachableFlagStage(std::vector<UINT32>& flags)
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
	void MarkRecursively
	(
		const UINT32 keepFlags,
		void* const object,
		const dooms::reflection::DField* dField,
		const bool isRootDObject = false
	)
	{
		if( (isRootDObject == true) || ( dField->GetFieldTypePrimitiveType() == reflection::DPrimitive::ePrimitiveType::CLASS) )
		{
			if ( (isRootDObject == true) || ((dField->GetFieldQualifier() == reflection::DField::eProperyQualifier::POINTER) == false) )
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
						MarkRecursively(keepFlags, reinterpret_cast<char*>(targetDObject) + field.GetFieldOffset(), &field, false);
					}
				}
			}
			else
			{
				// if object is nullptr, DObjectManager::IsDObjectExist is suprer fast
				if (IsStrongValid(*reinterpret_cast<dooms::DObject**>(object), false) == true)
				{
					dooms::DObject* const targetDObject = (*reinterpret_cast<dooms::DObject**>(object));

					targetDObject->ClearDObjectFlag(eDObjectFlag::Unreachable);

					dooms::reflection::DClass dClass = targetDObject->GetDClass();

					// TODO : if 
					const std::vector<dooms::reflection::DField>& dFieldList = dClass.GetDFieldList();

					for (const dooms::reflection::DField& field : dFieldList)
					{
						MarkRecursively(keepFlags, reinterpret_cast<char*>(targetDObject) + field.GetFieldOffset(), &field, false);
					}

				}
				else
				{
					// TODO : add data whether class is child of DObject class to clcpp::Class
					// If DObject address in pointer is dummy address, nullify pointer
					*reinterpret_cast<dooms::DObject**>(object) = nullptr;
				}
			}
		}
		else if(dField->GetFieldTypePrimitiveType() == reflection::DPrimitive::ePrimitiveType::TEMPLATE_TYPE)
		{
			// TODO : Supprt std::vector, std::array
			
		}
	}

	void Mark(const UINT32 keepFlags, dooms::DObject* const rootDObject)
	{
		D_ASSERT(IsStrongValid(rootDObject, false) == true);
		MarkRecursively(keepFlags, rootDObject, nullptr, true);
	}

}

void dooms::gc::garbageCollectorSolver::StartMarkStage(const UINT32 keepFlags, std::vector<dooms::DObject*>& rootDObjectList)
{
	// GC if dObject is on pending kill

	// check does have NewAllocated flag

	// use multithread but doesn't delete in subthread

	// TODO : Do mark stage parallel
	for(dooms::DObject* rootDObejct : rootDObjectList)
	{
		Mark(keepFlags, rootDObejct);
	}
}


void dooms::gc::garbageCollectorSolver::StartSweepStage(std::vector<dooms::DObject*>& dObjectList, std::vector<UINT32>& flagList)
{
	std::vector<dooms::DObject*> deletedDObjectList;
	deletedDObjectList.reserve(DELETE_DOBJECT_LIST_RESERVATION_COUNT);

	const size_t flagListCount = flagList.size();
	for(size_t i = 0 ; i < flagListCount; i++ )
	{
		D_ASSERT(IsStrongValid(dObjectList[i]) == true);
		if ((flagList[i] & dooms::eDObjectFlag::NotCollectedByGC) == 0)
		{
			if ((flagList[i] & dooms::eDObjectFlag::Unreachable) != 0)
			{
				flagList[i] |= dooms::eDObjectFlag::IsPendingKill;

				deletedDObjectList.push_back(dObjectList[i]);
				D_DEBUG_LOG(eLogType::D_LOG_TYPE13, "GC DObject IsPendingKill Enabled and Sweeped ready : %s ( TypeName : %s )", dObjectList[i]->GetDObjectName().c_str(), dObjectList[i]->GetTypeFullName());
			}
		}
		else
		{
			
		}
	}

	for (dooms::DObject* deletedDbject : deletedDObjectList)
	{
		deletedDbject->DestroySelf();
	}
}


