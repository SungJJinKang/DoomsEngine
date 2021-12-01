#pragma once
#include <Core.h>

#include <vector>
#include <array>

#define GC_HIERARCHY_MAX_LEVEL 3

namespace dooms
{
	class DObject;

	namespace gc
	{
		class DOOM_API D_CLASS GarbageCollectorManager
		{

		private:
			
			static std::array<float, GC_HIERARCHY_MAX_LEVEL> mElapsedTime;

			// Max Level is long term alive object
			static std::array<float, GC_HIERARCHY_MAX_LEVEL> mCollectTimeStep;
			static std::array<std::vector<DObject*>, GC_HIERARCHY_MAX_LEVEL> mRootsDObjectsList;

			static void PoolRootsDObjectsList();
			static void InitializeCollectTimeStep();

			static void Collect();
			static void Collect(const UINT32 level);
			static void Collect(std::vector<DObject*>& rootObjectList);

		public:

			static void Init();
			static void TickGC();
			
			
			/// <summary>
			/// 
			/// </summary>
			/// <param name="dObjet"></param>
			/// <param name="level"></param>
			/// <returns></returns>
			static bool AddToRootsDObjectsList(DObject* const dObjet, const UINT32 initialLevel);
			static bool RemoveFromDObjectsList(DObject* const dObjet);
		};
	}
	
}


