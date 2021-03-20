#pragma once

namespace doom
{
	class ITester
	{
	private:
		
	public:
		virtual void Init() = 0;
		virtual void Update() = 0;
	};
}