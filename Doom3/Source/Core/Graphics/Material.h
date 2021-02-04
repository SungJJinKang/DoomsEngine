#pragma once
#include <string>
#include "Graphics_Core.h"
#include "../OverlapBindChecker/OverlapBindChecker.h"

namespace doom
{
	class ShaderAsset;
	namespace graphics
	{
		
		class Material
		{
		private:
			unsigned int mID;
			ShaderAsset* mShaderAsset;

			void SetShaderAsset(ShaderAsset& shaderAsset);
		public:
			Material(ShaderAsset& shaderAsset);
			~Material();

			void UseProgram()
			{
				D_CHECK_OVERLAP_BIND("Material", this->mID);
				glUseProgram(this->mID);
			}

			void SetBool(const char* str, bool value1)
			{
				glUniform1i(glGetUniformLocation(this->mID, str), static_cast<int>(value1));
			}
			void SetBool(const char* str, bool value1, bool value2)
			{
				glUniform2i(glGetUniformLocation(this->mID, str), static_cast<int>(value1), static_cast<int>(value2));
			}
			void SetBool(const char* str, bool value1, bool value2, bool value3)
			{
				glUniform3i(glGetUniformLocation(this->mID, str), static_cast<int>(value1), static_cast<int>(value2), static_cast<int>(value3));
			}
			void SetBool(const char* str, bool value1, bool value2, bool value3, bool value4)
			{
				glUniform4i(glGetUniformLocation(this->mID, str), static_cast<int>(value1), static_cast<int>(value2), static_cast<int>(value3), static_cast<int>(value4));
			}

			void SetInt(const char* str, int value1)
			{
				glUniform1i(glGetUniformLocation(this->mID, str), value1);
			}
			void SetInt(const char* str, int value1, int value2)
			{
				glUniform2i(glGetUniformLocation(this->mID, str), value1, value2);
			}
			void SetInt(const char* str, int value1, int value2, int value3)
			{
				glUniform3i(glGetUniformLocation(this->mID, str), value1, value2, value3);
			}
			void SetInt(const char* str, int value1, int value2, int value3, int value4)
			{
				glUniform4i(glGetUniformLocation(this->mID, str), value1, value2, value3, value4);
			}

			void SetFloat(const char* str, float value1)
			{
				glUniform1f(glGetUniformLocation(this->mID, str), value1);
			}
			void SetFloat(const char* str, float value1, float value2)
			{
				glUniform2f(glGetUniformLocation(this->mID, str), value1, value2);
			}
			void SetFloat(const char* str, float value1, float value2, float value3)
			{
				glUniform3f(glGetUniformLocation(this->mID, str), value1, value2, value3);
			}
			void SetFloat(const char* str, float value1, float value2, float value3, float value4)
			{
				glUniform4f(glGetUniformLocation(this->mID, str), value1, value2, value3, value4);
			}
		};
	}
}

