#pragma once
#include "Core/ServerComponent.h"

#include "Animation.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class Graphics_Server;
	}

	class DOOM_API D_CLASS Animation : public ServerComponent
	{
		GENERATE_BODY()
		
		

		friend class graphics::Graphics_Server;

	private:

	public:

	};

}
