#include "GarbageCollectorSolver.h"

#include <atomic>

#include <DObject/DObject.h>
#include <DObject/DObjectManager.h>
#include <ResourceManagement/JobSystem_cpp/JobSystem.h>
#include <Reflection/ReflectionType/DField.h>
#include <Reflection/ReflectionType/DClass.h>
#include <Reflection/TypeSpecialized/Helper/iteratorHelper.h>
#include <ResourceManagement/JobSystem_cpp/JobSystem.h>
#include <Macros/Log.h>
#include <Game/ConfigData.h>
#include <Math/LightMath_Cpp/Utility.h>

namespace dooms::gc::garbageCollectorSolver
{
	FORCE_INLINE void SetReachable(UINT32& flag)
	{
		flag &= ~static_cast<UINT32>(dooms::eDObjectFlag::Unreachable);
	}
}

void dooms::gc::garbageCollectorSolver::StartSetUnreachableFlagStage(const eGCMethod gcMethod, std::vector<UINT32>& flags)
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
		const dooms::reflection::DType* const dFieldType
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
		const dooms::reflection::DType* const dFieldType
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
							MarkRecursively(keepFlags, &(*beginiter), elementTypeQualifier, &elementTypeDType);

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
						MarkRecursively(keepFlags, ptr, elementTypeQualifier, &elementTypeDType);
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
		D_ASSERT(IsLowLevelValid(dObejct, false));

		if (dObejct->GetDObjectFlag(eDObjectFlag::IsNotCheckedByGC) == true)
		{
			dObejct->ClearDObjectFlag(eDObjectFlag::Unreachable | eDObjectFlag::IsNotCheckedByGC);

			dooms::reflection::DClass dClass = dObejct->GetDClass();

			const std::vector<dooms::reflection::DField>& dFieldList = dClass.GetDFieldList();

			for (const dooms::reflection::DField& field : dFieldList)
			{
				reflection::DType fieldType = field.GetDTypeOfFieldType();
				MarkRecursively(keepFlags, reinterpret_cast<char*>(dObejct) + field.GetFieldOffset(), field.GetFieldQualifier(), &fieldType);
			}
		}
	}

	void MarkRecursivelyDObjectTypeField
	(
		const UINT32 keepFlags,
		void* const object,
		const reflection::eProperyQualifier dataQualifier,
		const dooms::reflection::DType* const dFieldType
	)
	{
		if (dFieldType->GetIsDerivedFromDObject() == true)
		{
			if ((dataQualifier == reflection::eProperyQualifier::POINTER) == false)
			{
				// if object is nullptr, DObjectManager::IsDObjectExist is suprer fast
				if (IsLowLevelValid(reinterpret_cast<dooms::DObject*>(object), false) == true)
				{	// Never change this IsLowLevelValid to IsValid ( unreal engine use IsLowLevelValid )
					dooms::DObject* const targetDObject = reinterpret_cast<dooms::DObject*>(object);

					MarkRecursivelyDObjectTypeValueField(keepFlags, targetDObject, reflection::eProperyQualifier::VALUE, dFieldType);
				}
			}
			else
			{
				// if object is nullptr, DObjectManager::IsDObjectExist is suprer fast
				if (IsLowLevelValid(*reinterpret_cast<dooms::DObject**>(object), false) == true)
				{	// Never change this IsLowLevelValid to IsValid ( unreal engine use IsLowLevelValid )
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
	}

	void MarkRecursively
	(
		const UINT32 keepFlags,
		void* const object,
		const reflection::eProperyQualifier dataQualifier,
		const dooms::reflection::DType* const dFieldType
	)
	{
		if (dFieldType->GetPrimitiveType() == reflection::DPrimitive::ePrimitiveType::CLASS)
		{
			MarkRecursivelyDObjectTypeField(keepFlags, object, dataQualifier, dFieldType);
		}
		else if (dFieldType->GetPrimitiveType() == reflection::DPrimitive::ePrimitiveType::TEMPLATE_TYPE)
		{
			MarkRecursivelyTemplateTypeField(keepFlags, object, dataQualifier, dFieldType);
		}
	}

	void Mark(const UINT32 keepFlags, dooms::DObject* const rootDObject)
	{
		D_ASSERT(IsLowLevelValid(rootDObject, false) == true);

		const reflection::DClass rootObjectDClass = rootDObject->GetDClass();
		MarkRecursively(keepFlags, rootDObject, reflection::eProperyQualifier::VALUE, &rootObjectDClass);
	}

}

namespace dooms::gc::garbageCollectorSolver
{
	struct GCMultithreadCounter
	{
	    std::atomic<size_t> workingOnRootObjectCount;
	    UINT8 padding[64]; // padding for preventing false sharing
	    std::atomic<size_t> completedOnRootObjectCount;
	};
}

void dooms::gc::garbageCollectorSolver::StartMarkStage(const eGCMethod gcMethod, const UINT32 keepFlags, std::vector<dooms::DObject*>& rootDObjectList)
{
	// GC if dObject is on pending kill

	// check does have NewAllocated flag

	// use multithread but doesn't delete in subthread

	if(gcMethod == eGCMethod::SingleThreadMark)
	{
		// TODO : Do mark stage parallel
		for (dooms::DObject* rootDObejct : rootDObjectList)
		{
			if (IsLowLevelValid(rootDObejct, false) == true)
			{
				Mark(keepFlags, rootDObejct);
			}
		}
	}
	else if (gcMethod == eGCMethod::MultiThreadMark)
	{
		const size_t rootDObjectCount = rootDObjectList.size();

		GCMultithreadCounter gcMultithreadCounter;
		gcMultithreadCounter.workingOnRootObjectCount = 0;
		gcMultithreadCounter.completedOnRootObjectCount = 0;

		const int gcThreadCount = math::Min(dooms::resource::JobSystem::GetSingleton()->GetSubThreadCount(), (size_t)dooms::ConfigData::GetSingleton()->GetConfigData().GetValue<int>("SYSTEM","GC_THREAD_COUNT"));
		
		for(size_t i = 0 ; i < gcThreadCount ; i++)
		{
			std::function multiThreadJob = [&gcMultithreadCounter, &rootDObjectList, keepFlags, rootDObjectCount, threadIndex = i]()
			{
				D_DEBUG_LOG(eLogType::D_LOG_TYPE13, "Start Mark a object ( Thread Index : %d )", threadIndex);
				while (true)
				{
					const size_t rootObjectIndex = gcMultithreadCounter.workingOnRootObjectCount++;
					if (rootObjectIndex >= rootDObjectCount)
					{
						D_DEBUG_LOG(eLogType::D_LOG_TYPE13, "End Mark a object ( Thread Index : %d )", threadIndex);
						return;
					}

					Mark(keepFlags, rootDObjectList[rootObjectIndex]);

					gcMultithreadCounter.completedOnRootObjectCount++;
				}
			};

			dooms::resource::JobSystem::GetSingleton()->PushBackJobToPriorityQueueWithNoSTDFuture(multiThreadJob);
		}

		while (completedOnRootObjectCount < rootDObjectCount)
		{
			std::this_thread::yield();
		}
		
	}
}


void dooms::gc::garbageCollectorSolver::StartSweepStage(const eGCMethod gcMethod, const UINT32 keepFlags, std::unordered_set<dooms::DObject*>& dObjectList)
{
	std::vector<dooms::DObject*> deletedDObjectList;
	deletedDObjectList.reserve(DELETE_DOBJECT_LIST_RESERVATION_COUNT);

	auto beginIter = dObjectList.begin();
	const auto endIter = dObjectList.end();
	while(beginIter != endIter)
	{
		dooms::DObject* const dObject = (*beginIter);
		if ((dObject->GetDObjectFlag() & (dooms::eDObjectFlag::Unreachable | dooms::eDObjectFlag::NewAllocated)) == (dooms::eDObjectFlag::Unreachable | dooms::eDObjectFlag::NewAllocated))
		{
			/*
			// Mark unreachable dObject before sweep.
			// when there is time between Mark stage and Sweep stage, this works is required.
			const reflection::DClass dClass = dObject->GetDClass();
			MarkRecursively(keepFlags, dObject, reflection::eProperyQualifier::VALUE, &dClass);
			*/

			dObject->SetIsPendingKill();

			deletedDObjectList.push_back(dObject);
			//D_DEBUG_LOG(eLogType::D_LOG_TYPE13, "GC DObject IsPendingKill Enabled and Sweeped ready : %s ( TypeName : %s )", dObject->GetDObjectName().c_str(), dObject->GetTypeFullName());
		}
		beginIter++;
	}

	for (dooms::DObject* deletedDbject : deletedDObjectList)
	{
		deletedDbject->DestroySelfInstantly();
	}
}


