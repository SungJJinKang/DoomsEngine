#include "GarbageCollectorSolver.h"

#include <DObject/DObject.h>
#include <DObject/DObjectManager.h>
#include <ResourceManagement/JobSystem_cpp/JobSystem.h>
#include <Reflection/ReflectionType/DField.h>
#include <Reflection/ReflectionType/DClass.h>
#include <Reflection/TypeSpecialized/Helper/iteratorHelper.h>

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
		*start |= (dooms::eDObjectFlag::Unreachable | dooms::eDObjectFlag::IsNotCheckedByGC);
		start++;
	}
}

namespace dooms::gc::garbageCollectorSolver
{
	void MarkRecursively
	(
		const UINT32 keepFlags,
		void* const object,
		const reflection::eProperyQualifier dataQualifier,
		const dooms::reflection::DType* const dFieldType,
		const bool isRootDObject = false
	);
	void MarkRecursivelyTemplateTypeField
	(
		const UINT32 keepFlags,
		void* const object,
		const reflection::eProperyQualifier dataQualifier,
		const dooms::reflection::DType* const dFieldType
	);
	void MarkRecursivelyDObjectTypeField
	(
		const UINT32 keepFlags,
		dooms::DObject* const dObejct,
		const reflection::eProperyQualifier dataQualifier,
		const dooms::reflection::DType* const dFieldType,
		const bool isRootDObject
	);

	void MarkRecursivelyTemplateTypeField
	(
		const UINT32 keepFlags,
		void* const object,
		const reflection::eProperyQualifier dataQualifier,
		const dooms::reflection::DType* const dFieldType
	)
	{
		if (dataQualifier == reflection::eProperyQualifier::VALUE)
		{
			const reflection::DTemplateType dTemplateDType = dFieldType->AsDTemplateType();

			const reflection::eTemplateTypeCategory templateTypeType = dooms::reflection::helper::GetTempalteTypeCategory(dTemplateDType);

			if(templateTypeType != reflection::eTemplateTypeCategory::NotSupported)
			{
				const reflection::eProperyQualifier elementTypeQualifier = (reflection::helper::GetStdTemplateElementTypeIsPointer(dTemplateDType) == true) ? reflection::eProperyQualifier::POINTER : reflection::eProperyQualifier::VALUE;
				const reflection::DType elementTypeDType = reflection::helper::GetStdTemplateElementTypeDType(dTemplateDType);

				if (templateTypeType == reflection::eTemplateTypeCategory::RandomAccessIterator)
				{
					auto beginiter = dooms::reflection::helper::Generate_Reflection_Std_Container(object, dFieldType->GetTypeFullName(), reflection::eProperyQualifier::VALUE, dTemplateDType, reflection::helper::eIteratorIndex::Begin);
					if (beginiter == true)
					{
						auto endIter = dooms::reflection::helper::Generate_Reflection_Std_Container(object, dFieldType->GetTypeFullName(), reflection::eProperyQualifier::VALUE, dTemplateDType, reflection::helper::eIteratorIndex::End);
						while (beginiter != endIter)
						{
							MarkRecursively(keepFlags, &(*beginiter), elementTypeQualifier, &elementTypeDType, false);

							beginiter++;
						}
					}
				}
				else if (templateTypeType == reflection::eTemplateTypeCategory::SmartPointer)
				{
					void* const ptr = reflection::helper::Generate_Reflection_smartPointer(object, dataQualifier, dTemplateDType);

					// template argument of smartpoint always be pointer type. ex) std::shared_ptr<char> -> returned value of Generate_Reflection_smartPointer is pointer
					if (ptr != nullptr)
					{// when smart pointer has valid address 
						MarkRecursively(keepFlags, ptr, elementTypeQualifier, &elementTypeDType, false);
					}					
				}
			}
			else
			{
				D_DEBUG_LOG(eLogType::D_LOG_TYPE13, "GC Mark stage - Not Supported Template Type : %s", dTemplateDType.GetTemplateTypeName().c_str());
			}
			
		}
		else
		{
			D_ASSERT_LOG(false, "std::vector*, std::vector&, std::array*, std::array&, std::unique_ptr*, std::unique_ptr&, std::shared_ptr*, std::shared_ptr&");
		}
	}

	void MarkRecursivelyDObjectTypeValueField
	(
		const UINT32 keepFlags,
		dooms::DObject* const dObejct,
		const reflection::eProperyQualifier dataQualifier,
		const dooms::reflection::DType* const dFieldType
	)
	{
		D_ASSERT(IsStrongValid(dObejct) == true);

		if (dObejct->GetDObjectFlag(eDObjectFlag::IsNotCheckedByGC) == true)
		{
			dObejct->ClearDObjectFlag(eDObjectFlag::Unreachable);
			dObejct->ClearDObjectFlag(eDObjectFlag::IsNotCheckedByGC);

			dooms::reflection::DClass dClass = dObejct->GetDClass();

			const std::vector<dooms::reflection::DField>& dFieldList = dClass.GetDFieldList();

			for (const dooms::reflection::DField& field : dFieldList)
			{
				reflection::DType fieldType = field.GetDTypeOfFieldType();
				MarkRecursively(keepFlags, reinterpret_cast<char*>(dObejct) + field.GetFieldOffset(), field.GetFieldQualifier(), &fieldType, false);
			}
		}
	}

	void MarkRecursivelyDObjectTypeField
	(
		const UINT32 keepFlags,
		void* const object,
		const reflection::eProperyQualifier dataQualifier,
		const dooms::reflection::DType* const dFieldType,
		const bool isRootDObject
	)
	{
		if ((isRootDObject == true) || ((dataQualifier == reflection::eProperyQualifier::POINTER) == false))
		{
			// if object is nullptr, DObjectManager::IsDObjectExist is suprer fast
			if (IsStrongValid(reinterpret_cast<dooms::DObject*>(object), false) == true)
			{
				dooms::DObject* const targetDObject = reinterpret_cast<dooms::DObject*>(object);

				MarkRecursivelyDObjectTypeValueField(keepFlags, targetDObject, reflection::eProperyQualifier::VALUE, dFieldType);
			}
		}
		else
		{
			// if object is nullptr, DObjectManager::IsDObjectExist is suprer fast
			if (IsStrongValid(*reinterpret_cast<dooms::DObject**>(object), false) == true)
			{
				dooms::DObject* const targetDObject = (*reinterpret_cast<dooms::DObject**>(object));
				
				MarkRecursivelyDObjectTypeValueField(keepFlags, targetDObject, reflection::eProperyQualifier::VALUE, dFieldType);
			}
			else
			{
				// TODO : add data whether class is child of DObject class to clcpp::Class
				// If DObject address in pointer is dummy address, nullify pointer
				*reinterpret_cast<dooms::DObject**>(object) = nullptr;
			}
		}
	}

	void MarkRecursively
	(
		const UINT32 keepFlags,
		void* const object,
		const reflection::eProperyQualifier dataQualifier,
		const dooms::reflection::DType* const dFieldType,
		const bool isRootDObject
	)
	{
		if( (isRootDObject == true) || ( dFieldType->GetPrimitiveType() == reflection::DPrimitive::ePrimitiveType::CLASS) )
		{
			MarkRecursivelyDObjectTypeField(keepFlags, object, dataQualifier, dFieldType, isRootDObject);
		}
		else if(dFieldType->GetPrimitiveType() == reflection::DPrimitive::ePrimitiveType::TEMPLATE_TYPE)
		{
			MarkRecursivelyTemplateTypeField(keepFlags, object, dataQualifier, dFieldType);
		}
	}

	void Mark(const UINT32 keepFlags, dooms::DObject* const rootDObject)
	{
		D_ASSERT(IsStrongValid(rootDObject, false) == true);

		const reflection::DClass rootObjectDClass = rootDObject->GetDClass();
		MarkRecursively(keepFlags, rootDObject, reflection::eProperyQualifier::POINTER, &rootObjectDClass, true);
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
		if ((flagList[i] & (dooms::eDObjectFlag::NotCollectedByGC | dooms::eDObjectFlag::IsRootObject) ) == 0)
		{
			if ((flagList[i] & (dooms::eDObjectFlag::Unreachable | dooms::eDObjectFlag::NewAllocated)) == (dooms::eDObjectFlag::Unreachable | dooms::eDObjectFlag::NewAllocated))
			{
				flagList[i] |= dooms::eDObjectFlag::IsPendingKill;
				dObjectList[i]->SetIsPendingKill();

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


