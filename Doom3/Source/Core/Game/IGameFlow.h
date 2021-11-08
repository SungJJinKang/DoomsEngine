#pragma once
#include "../Core.h"
#include "FrameDirtyChecker.h"
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
		DOBJECT_ABSTRACT_CLASS_BODY(IGameFlow, dooms::eDOBJECT_ClassFlags::NonCopyable);
		DOBJECT_CLASS_BASE_CHAIN(DObject)

	private:
		
	public:

		/// <summary>
		/// Don't put virtual
		/// </summary>
		void Init_Internal() {}
		virtual void Init() = 0;
		virtual void LateInit() {}

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