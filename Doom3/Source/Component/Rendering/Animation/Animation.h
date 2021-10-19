#pragma once
#include "Core/ServerComponent.h"

namespace doom
{
	namespace graphics
	{
		class Graphics_Server;
	}

	class DOOM_API Animation : public ServerComponent
	{

		DOBJECT_CLASS_BODY(Animation)

		friend class graphics::Graphics_Server;

	private:

	public:

	};

}
