#pragma once
#include "Core/ServerComponent.h"

namespace doom
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
	class DOOM_API Animator : public ServerComponent
	{
		friend class graphics::Graphics_Server;

	private: 

		Animation* mTargetAnimation;

		FLOAT32 mCurrentAnimationTime;

	public:

		void UpdateAnimation(FLOAT32 deltatTime);

	};

}
