#pragma once
#include "../Core.h"

namespace doom
{
	/// <summary>
	/// Interface for In Game Loop
	/// 
	/// WARNING : Be careful virtual function would be shadowed by children class
	/// </summary>
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