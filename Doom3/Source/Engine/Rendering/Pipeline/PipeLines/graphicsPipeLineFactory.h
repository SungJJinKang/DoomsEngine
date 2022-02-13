#pragma once

namespace dooms
{
	namespace graphics
	{
		class GraphicsPipeLine;
		class Graphics_Server;
		namespace graphicsPipeLineFactory
		{
			extern GraphicsPipeLine* CreateGraphicsPipeLineFromConfigFile(Graphics_Server* const graphicsServer);
		};
	}
}

