#pragma once


#include "../Graphics_Core.h"

#ifdef DEBUG_MODE

#include <memory>


namespace doom
{
	namespace asset
	{
		class ShaderAsset;
	}

	namespace graphics
	{
		class OverDrawVisualization
		{
			class OverDrawVisualizationPimpl;
		private:

			bool bmIsInitialized = false;


			std::unique_ptr<OverDrawVisualizationPimpl> mOverDrawVisualizationPimpl;


			
			void Initialize();

	

		public:

			OverDrawVisualization();
			~OverDrawVisualization();

			void SetOverDrawVisualizationRenderingState(const bool isSet);
			void ShowOverDrawVisualizationPIP(const bool isPIPDrawed);
		};
	}
}


#endif