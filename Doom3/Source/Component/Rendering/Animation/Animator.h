#pragma once
#include "Core/ServerComponent.h"

namespace dooms
{
	namespace graphics
	{
		class Graphics_Server;
	}

	class Animation;

	/// <summary>
	/// Requirement :
	/// Sprite, MeshAnimation, 
	/// </summary>
	class DOOM_API D_CLASS Animator : public ServerComponent
	{

		DOBJECT_CLASS_BODY(Animator)
		DOBJECT_CLASS_BASE_CHAIN(ServerComponent)

		friend class graphics::Graphics_Server;

	private: 

		Animation* mTargetAnimation;

		FLOAT32 mCurrentAnimationTime;

	public:

		void UpdateAnimation(FLOAT32 deltatTime);

	};

}
