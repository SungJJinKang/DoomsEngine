#pragma once
#include <Core.h>

#include <vector>

#include <Rendering/Scene/FDrawCommand.h>

namespace dooms
{
	namespace graphics
	{
		class DOOM_API RenderScene
		{
		public:

			void AddDrawCommand(FDrawCommand* const InDrawCommand);
			void RemoveDrawCommand(FDrawCommand* const InDrawCommand);
			void SortDrawCommand();

		private:

			std::vector<FDrawCommand> DrawCommandList{};
			std::vector<UINT8> VisibityList{};
		};
	}
}

