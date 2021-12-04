#pragma once
#include "Core/Component.h"

#include "Animation.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class Graphics_Server;
	}

	class DOOM_API D_CLASS Animation : public Component
	{
		GENERATE_BODY()
		
		

		friend class graphics::Graphics_Server;

	private:

	public:

	};

}
