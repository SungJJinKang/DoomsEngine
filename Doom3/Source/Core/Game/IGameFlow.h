#pragma once
#include "../Core.h"
#include <Misc/FrameDirtyChecker/FrameDirtyChecker.h>

#include "IGameFlow.reflection.h"
namespace dooms
{
	/// <summary>
	/// Interface for In Game Loop
	/// 
	/// Only Server class can inherit this class
	/// 
	/// WARNING : Be careful virtual function would be shadowed by children class
	/// </summary>
	class DOOM_API D_CLASS IGameFlow : public DObject, public FrameDirtyChecker
	{
		GENERATE_BODY()
		

	private:
		
	public:

		/// <summary>
		/// Don't put virtual
		/// </summary>
		void Init_Internal() {}
		virtual void Init(const int argc, char* const* const argv) = 0;
		virtual void LateInit() {}
		virtual void PostSceneInit(){}

		/// <summary>
		/// Don't put virtual
		/// </summary>
		void Update_Internal() {}
		virtual void Update() = 0;

		void FixedUpdate_Internal(){}
		virtual void FixedUpdate() {}

		/// <summary>
		/// Don't put virtual
		/// </summary>
		void OnEndOfFrame_Internal()
		{
			FrameDirtyChecker_EndOfFrame();
		}
		virtual void OnEndOfFrame() = 0;

		IGameFlow();
		IGameFlow(const IGameFlow&) = delete;
		IGameFlow(IGameFlow&&) noexcept = delete;

		IGameFlow& operator=(const IGameFlow&) = delete;
		IGameFlow& operator=(IGameFlow&&) noexcept = delete;

		virtual ~IGameFlow();
	};
}