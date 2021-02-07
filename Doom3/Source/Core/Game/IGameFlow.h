#pragma once
#include "../Core.h"

namespace doom
{
	class IGameFlow
	{
	private:

	protected:
		virtual void Init() = 0;
		virtual void Update() = 0;

	public:
		virtual ~IGameFlow() {}
	};
}