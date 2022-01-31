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
#include <EngineGUI/PrintText.h>


void dooms::gc::garbageCollectorSolver::StartSetUnreachableFlagStage(const eGCMethod gcMethod, std::unordered_set<DObject*>& dObjects)
{
	// TODO : Optimize this function. too slow....
	for(DObject* dObject : dObjects)
	{
		dObject->SetDObjectFlag(dooms::eDObjectFlag::Unreachable | dooms::eDObjectFlag::IsNotCheckedByGC, std::memory_order_relaxed);
	}
}

namespace dooms::gc::garbageCollectorSolver
{
	FORCE_INLINE void MarkRecursively
	(
		const UINT32 keepFlags,
		void* const object,
		const reflection::eProperyQualifier dataQualifier,
		const dooms::reflection::DType* const dFieldType
	);
	FORCE_INLINE void MarkRecursivelyTemplateTypeField
	(
		const UINT32 keepFlags,
		void* const object,
		const reflection::eProperyQualifier dataQualifier,
		const dooms::reflection::DType* const dFieldType
	);
	FORCE_INLINE void MarkRecursivelyDObjectTypeField
	(
		const UINT32 keepFlags,
		dooms::DObject* const dObejct,
		const reflection::eProperyQualifier dataQualifier,
		const dooms::reflection::DType* const dFieldType
	);

	FORCE_INLINE void MarkRecursivelyTemplateTypeField
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

	FORCE_INLINE void MarkRecursivelyDObjectTypeValueField
	(
		const UINT32 keepFlags,
		dooms::DObject* const dObejct,
		const reflection::eProperyQualifier dataQualifier,
		const dooms::reflection::DType* const dFieldType
	)
	{
		D_ASSERT(IsLowLevelValid(dObejct, false));

		if (dObejct->GetDObjectFlag(eDObjectFlag::IsNotCheckedByGC, std::memory_order_seq_cst) == true)
		{
			// TODO : Data race may be caused in multithreaded mark stage?
			// DObjectFlag isn't std::atomic
			dObejct->ClearDObjectFlag(eDObjectFlag::Unreachable | eDObjectFlag::IsNotCheckedByGC, std::memory_order_seq_cst);

			dooms::reflection::DClass dClass = dObejct->GetDClass();

			const std::vector<dooms::reflection::DField>& dFieldList = dClass.GetDFieldList();

			for (const dooms::reflection::DField& field : dFieldList)
			{
				reflection::DType fieldType = field.GetDTypeOfFieldType();
				MarkRecursively(keepFlags, reinterpret_cast<char*>(dObejct) + field.GetFieldOffset(), field.GetFieldQualifier(), &fieldType);
			}
		}
	}

	FORCE_INLINE void MarkRecursivelyDObjectTypeField
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

	FORCE_INLINE void MarkRecursively
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

	FORCE_INLINE void Mark(const UINT32 keepFlags, dooms::DObject* const rootDObject)
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
	    std::atomic<size_t> gcCompletedRootObjectCount;
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
		std::atomic_thread_fence(std::memory_order_seq_cst);

		const size_t rootDObjectCount = rootDObjectList.size();

		GCMultithreadCounter gcMultithreadCounter;
		gcMultithreadCounter.workingOnRootObjectCount = 0;
		gcMultithreadCounter.gcCompletedRootObjectCount = 0;

		std::function multiThreadJob = [&gcMultithreadCounter, &rootDObjectList, keepFlags, rootDObjectCount]()
		{
			D_DEBUG_LOG(eLogType::D_LOG_TYPE13, "Start Mark a object");
			while (true)
			{
				const size_t rootObjectIndex = gcMultithreadCounter.workingOnRootObjectCount++;
				if (rootObjectIndex >= rootDObjectCount)
				{
					D_DEBUG_LOG(eLogType::D_LOG_TYPE13, "End Mark a object");
					break;
				}

				Mark(keepFlags, rootDObjectList[rootObjectIndex]);

				const size_t currentGCCompletedRootObjectCount = ++gcMultithreadCounter.gcCompletedRootObjectCount;
				if (currentGCCompletedRootObjectCount >= rootDObjectCount)
				{
					D_DEBUG_LOG(eLogType::D_LOG_TYPE13, "End Mark a object");
					break;
				}
			}
		};
		
		auto futures = dooms::resource::JobSystem::GetSingleton()->PushBackJobToAllThread(multiThreadJob);
		multiThreadJob();

		D_START_PROFILING(WaitProfilingThreadJobFinished, dooms::profiler::eProfileLayers::Rendering);
		while (gcMultithreadCounter.gcCompletedRootObjectCount.load(std::memory_order_seq_cst) < rootDObjectCount)
		{
			std::this_thread::yield();
		}
		for(auto& future : futures)
		{
			future.wait();
		}
		D_END_PROFILING(WaitProfilingThreadJobFinished);


	}
}


void dooms::gc::garbageCollectorSolver::StartSweepStage(const eGCMethod gcMethod, const UINT32 keepFlags, std::unordered_set<dooms::DObject*>& dObjectList, const size_t maxSweepedObjectCount)
{
	std::atomic_thread_fence(std::memory_order_seq_cst);

	std::vector<dooms::DObject*> deletedDObjectList;
	deletedDObjectList.reserve(maxSweepedObjectCount);

	auto beginIter = dObjectList.begin();
	const auto endIter = dObjectList.end();
	while(beginIter != endIter)
	{
		dooms::DObject* const dObject = (*beginIter);


		const bool isUnreachable = dObject->HasDObjectFlag(dooms::eDObjectFlag::Unreachable | dooms::eDObjectFlag::NewAllocated, std::memory_order_relaxed);
		dObject->SetDObjectFlag(dooms::eDObjectFlag::Unreachable | dooms::eDObjectFlag::IsNotCheckedByGC, std::memory_order_relaxed);

		if(isUnreachable == true)
		{
			/*
			// Mark unreachable dObject before sweep.
			// when there is time between Mark stage and Sweep stage, this works is required.
			const reflection::DClass dClass = dObject->GetDClass();
			MarkRecursively(keepFlags, dObject, reflection::eProperyQualifier::VALUE, &dClass);
			*/

			dObject->SetIsPendingKill();

			deletedDObjectList.push_back(dObject);
			D_DEBUG_LOG(eLogType::D_LOG_TYPE13, "GC DObject IsPendingKill Enabled and Sweeped ready : %s ( TypeName : %s )", dObject->GetDObjectName().c_str(), dObject->GetTypeFullName());

			if(deletedDObjectList.size() >= maxSweepedObjectCount)
			{
				break;
			}
		}
		beginIter++;
	}

	for (dooms::DObject* deletedDbject : deletedDObjectList)
	{
		D_ASSERT(deletedDbject != nullptr);
		deletedDbject->DestroySelfInstantly();
		D_DEBUG_LOG(eLogType::D_LOG, "GC Collect Object ( Type Name : %s, DObject Name : %s )", deletedDbject->GetTypeFullName(), deletedDbject->GetDObjectName().c_str());
	}
}


