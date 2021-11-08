#pragma once
#include "Core/ServerComponent.h"

namespace dooms
{
	namespace graphics
	{
		class Graphics_Server;
	}

	class DOOM_API D_CLASS Animation : public ServerComponent
	{

		DOBJECT_CLASS_BODY(Animation)
		DOBJECT_CLASS_BASE_CHAIN(ServerComponent)

		friend class graphics::Graphics_Server;

	private:

	public:

	};

}
