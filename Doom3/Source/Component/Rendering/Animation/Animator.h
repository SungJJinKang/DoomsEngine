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
	class Animator : public ServerComponent
	{
		friend class graphics::Graphics_Server;

	private: 

		Animation* mTargetAnimation;

		float mCurrentAnimationTime;

	public:

		void UpdateAnimation(float deltatTime);

	};

}
