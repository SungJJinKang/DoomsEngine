#pragma once
#include "../Core.h"
namespace doom
{
	namespace graphics
	{
		/// <summary>
		/// Why need this?
		/// Read this : https://sungjjinkang.github.io/c++/2021/02/20/problemWhenUseMoveContrucotrCompilerMade.html
		/// </summary>
		template <typename T>
		class ZeroResetMoveContainer
		{
		private:
			T data;
		public:
			ZeroResetMoveContainer() : data{ 0 }
			{}
			
			ZeroResetMoveContainer(const ZeroResetMoveContainer&)
			{
				NODEFAULT; 
				// Don't try ZeroResetMoveContainer
				// Think if you copy ZeroResetMoveContainer and Copyed Object is destroyed
				// Other ZeroResetMoveContainer Objects can't know their bufferId is invalidated.
				// This will make bugs hard to find, debug
			}
			ZeroResetMoveContainer(ZeroResetMoveContainer&& bufferID) noexcept
			{
				this->data = bufferID.data;
				bufferID.data = 0;
			}

			ZeroResetMoveContainer& operator=(const ZeroResetMoveContainer&)
			{
				NODEFAULT;
				// Don't try ZeroResetMoveContainer
				// Think if you copy ZeroResetMoveContainer and Copyed Object is destroyed
				// Other ZeroResetMoveContainer Objects can't know their bufferId is invalidated.
				// This will make bugs hard to find, debug
			}
			ZeroResetMoveContainer& operator=(ZeroResetMoveContainer&& bufferID) noexcept
			{
				this->data = bufferID.data;
				bufferID.data = 0;
				return *this;
			}

			ZeroResetMoveContainer(T ID) : data{ ID }
			{}
			void operator=(T iD) noexcept
			{
				this->data = iD;
			}

			operator T()
			{
				return this->data;
			}

			operator T*()
			{
				return &(this->data);
			}

			T& GetReference()
			{
				return this->data;
			}

			const T& GetReference() const
			{
				return this->data;
			}
		};

		using BufferID = typename ZeroResetMoveContainer<unsigned int>;
	}

}