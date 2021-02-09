#pragma once
#include "../Core.h"
#include "FrameDirtyChecker.h"
namespace doom
{
	/// <summary>
	/// Interface for In Game Loop
	/// 
	/// Only Manager class can inherit this class
	/// 
	/// WARNING : Be careful virtual function would be shadowed by children class
	/// </summary>
	class GameFlow : public FrameDirtyChecker
	{
	private:
		
	protected:

		/// <summary>
		/// Don't put virtual
		/// </summary>
		void Init_Internal();
		virtual void Init() = 0;

		/// <summary>
		/// Don't put virtual
		/// </summary>
		void Update_Internal();
		virtual void Update() = 0;

		/// <summary>
		/// Don't put virtual
		/// </summary>
		void OnEndOfFrame_Internal();
		virtual void OnEndOfFrame() = 0;

		
	public:
		virtual ~GameFlow();
	};
}