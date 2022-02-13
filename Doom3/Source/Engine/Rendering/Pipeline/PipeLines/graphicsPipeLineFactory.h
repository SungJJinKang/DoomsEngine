#pragma once

namespace dooms
{
	namespace graphics
	{
		class GraphicsPipeLine;
		namespace graphicsPipeLineFactory
		{
			extern GraphicsPipeLine* CreateGraphicsPipeLineFromConfigFile();
		};
	}
}

