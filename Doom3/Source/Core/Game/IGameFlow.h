#pragma once
#include "../Core.h"
#include "FrameDirtyChecker.h"
namespace doom
{
	/// <summary>
	/// Interface for In Game Loop
	/// 
	/// Only Server class can inherit this class
	/// 
	/// WARNING : Be careful virtual function would be shadowed by children class
	/// </summary>
	class IGameFlow : public FrameDirtyChecker
	{
	private:
		
	protected:

		/// <summary>
		/// Don't put virtual
		/// </summary>
		void Init_Internal();
		virtual void Init() = 0;
		virtual void LateInit();

		/// <summary>
		/// Don't put virtual
		/// </summary>
		void Update_Internal();
		virtual void Update() = 0;

		void FixedUpdate_Internal();
		virtual void FixedUpdate() {}

		/// <summary>
		/// Don't put virtual
		/// </summary>
		void OnEndOfFrame_Internal()
		{
			this->FrameDirtyChecker_EndOfFrame();
		}
		virtual void OnEndOfFrame() = 0;

		
	public:
		virtual ~IGameFlow();
	};
}