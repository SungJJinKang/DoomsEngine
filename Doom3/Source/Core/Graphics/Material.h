#pragma once
#include <string>
#include <vector>
#include <array>

#include "Graphics_Core.h"
#include "Texture.h"
#include "OverlapBindChecker.h"


namespace doom
{
	class ShaderAsset;
	
	namespace graphics
	{
		class UniformBufferObject;
		class Material
		{
		private:
			unsigned int mID;
			ShaderAsset* mShaderAsset;
			std::vector<Texture*> mTargetTextures{};
			std::array<UniformBufferObject*, MAX_UNIFORM_BLOCK_BINDING_POINT> mUniformBufferObjects;

			void SetShaderAsset(ShaderAsset& shaderAsset);
		public:
			Material(ShaderAsset& shaderAsset);
			~Material();

			void AddTexture(Texture& texture);
			void AddTextures(std::vector<Texture*> textures);

			void UseProgram()
			{
				for (unsigned int i = 0; i < this->mTargetTextures.size(); i++)
				{
					auto& texture = *(this->mTargetTextures[i]);
					texture.ActiveTexture(i);
					texture.BindTexture();
				}

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


			/*	you don't need this function ( from opengl 4.2 and onwards, you can set binding point explicitly like "binding = 1" )
			///
			/// <summary>
			/// Set UniformBlock to specific binding point
			/// if you write shader like this : layout (std140, binding = 0), 
			/// </summary>
			/// <param name="uniformBlockName"></param>
			/// <param name="bindingPoint"></param>
			void SetUniformBlockPoint(const std::string uniformBlockName, unsigned int bindingPoint);
			*/

			/// <summary>
			/// return Uniform Block Count
			/// do iterate from 0 to return value
			/// </summary>
			/// <returns>0 ~ return value</returns>
			int GetUniformBlocksCount();
			void InitUniformBufferObject();
		};
	}
}

