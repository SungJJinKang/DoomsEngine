#pragma once

namespace dooms
{
	/// <summary>
	/// Interface For Class independent from world ( even if specific world is destoryed, this class instance is alive
	/// </summary>
	class I_IndependentFromScene
	{

	private:
	
	protected:
		constexpr I_IndependentFromScene() {}

	public:
		

		I_IndependentFromScene(const I_IndependentFromScene&) = delete;
		I_IndependentFromScene(I_IndependentFromScene&&) noexcept = delete;
		I_IndependentFromScene& operator=(const I_IndependentFromScene&) = delete;
		I_IndependentFromScene& operator=(I_IndependentFromScene&&) noexcept = delete;
	
	};
}