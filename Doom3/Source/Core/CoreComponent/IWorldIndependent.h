#pragma once

namespace doom
{
	/// <summary>
	/// Interface For Class independent from world ( even if specific world is destoryed, this class instance is alive
	/// </summary>
	class IWorldIndependent
	{

	private:
	
	protected:
		constexpr IWorldIndependent() {}

	public:
		

		IWorldIndependent(const IWorldIndependent&) = delete;
		IWorldIndependent(IWorldIndependent&&) noexcept = delete;
		IWorldIndependent& operator=(const IWorldIndependent&) = delete;
		IWorldIndependent& operator=(IWorldIndependent&&) noexcept = delete;
	
	};
}