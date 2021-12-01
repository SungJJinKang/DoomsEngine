#pragma once
#include <Core.h>

#include <vector>
#include <array>

#include <Game/IGameFlow.h>

#define GC_HIERARCHY_MAX_LEVEL 3

namespace dooms
{
	class DObject;

	namespace gc
	{
		class DOOM_API D_CLASS GarbageCollectorManager : public IGameFlow, public ISingleton<GarbageCollectorManager>
		{

		private:

			// Max Level is long term alive object
			std::array<std::vector<DObject*>, GC_HIERARCHY_MAX_LEVEL> mRootsDObjectsList;

		public:

			GarbageCollectorManager();

			void Init() final;
			void Update() final;
			void OnEndOfFrame() final;

			/// <summary>
			/// 
			/// </summary>
			/// <param name="dObjet"></param>
			/// <param name="level"></param>
			/// <returns></returns>
			bool AddToRootsDObjectsList(DObject* const dObjet, const int initialLevel);
			bool RemoveFromDObjectsList(DObject* const dObjet);
		};
	}
	
}


