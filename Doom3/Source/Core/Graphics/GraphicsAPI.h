#pragma once
#include "Graphics_Core.h"
#include "../../Helper/Singleton.h"
#include "../Game/IGameFlow.h"
#include "Buffer/UniformBufferObjectManager.h"



namespace doom
{
	class GameCore;
	namespace graphics
	{
		/// <summary>
		/// Graphics Server class
		/// Contain graphics api function wrapper
		/// </summary>
		class GraphicsAPI 
		{
		private:
		
		protected:
		
		public:
			

			

			enum class eBufferMode : unsigned int
			{
				FRONT_LEFT = GL_FRONT_LEFT,
				FRONT_RIGHT = GL_FRONT_RIGHT,
				BACK_LEFT = GL_BACK_LEFT,
				BACK_RIGHT = GL_BACK_RIGHT,
				FRONT = GL_FRONT,
				BACK = GL_BACK,
				LEFT = GL_LEFT,
				RIGHT = GL_RIGHT,
				COLOR_ATTACHMENT0 = GL_COLOR_ATTACHMENT0,
				COLOR_ATTACHMENT1 = GL_COLOR_ATTACHMENT1,
				COLOR_ATTACHMENT2 = GL_COLOR_ATTACHMENT2,
				COLOR_ATTACHMENT3 = GL_COLOR_ATTACHMENT3,
				COLOR_ATTACHMENT4 = GL_COLOR_ATTACHMENT4,
				COLOR_ATTACHMENT5 = GL_COLOR_ATTACHMENT5,
				COLOR_ATTACHMENT6 = GL_COLOR_ATTACHMENT6,
				COLOR_ATTACHMENT7 = GL_COLOR_ATTACHMENT7,
				COLOR_ATTACHMENT8 = GL_COLOR_ATTACHMENT8,
				COLOR_ATTACHMENT9 = GL_COLOR_ATTACHMENT9,
				COLOR_ATTACHMENT10 = GL_COLOR_ATTACHMENT10

			};

			enum class eCullFaceMode : unsigned int
			{
				FRONT = GL_FRONT,
				BACK = GL_BACK,
				FRONT_AND_BACK = GL_FRONT_AND_BACK
			};

			static inline void ReadBuffer(eBufferMode mode) noexcept
			{
				glReadBuffer(static_cast<unsigned int>(mode));
			}
			static inline void WriteBuffer(eBufferMode mode) noexcept
			{
				glDrawBuffer(static_cast<unsigned int>(mode));
			}
			static inline void CullFace(eCullFaceMode mode) noexcept
			{
				glCullFace(static_cast<unsigned int>(mode));
			}

			static inline void ClearColor(float r, float g, float b, float a) noexcept
			{
				glClearColor(r, g, b, a);
			}

			static inline void ClearDepth(double depth) noexcept
			{
				glClearDepth(depth);
			}

			static inline void ClearStencil(unsigned int stencil) noexcept
			{
				glClearStencil(stencil);
			}

			enum class eClearMask : unsigned int
			{
				COLOR_BUFFER_BIT = GL_COLOR_BUFFER_BIT,
				DEPTH_BUFFER_BIT = GL_DEPTH_BUFFER_BIT,
				STENCIL_BUFFER_BIT = GL_STENCIL_BUFFER_BIT
			};
			static inline void Clear(eClearMask mask1) noexcept
			{
				glClear(static_cast<unsigned int>(mask1));
			}
			static inline void Clear(eClearMask mask1, eClearMask mask2) noexcept
			{
				glClear(static_cast<unsigned int>(mask1) | static_cast<unsigned int>(mask2));
			}
			static inline void Clear(eClearMask mask1, eClearMask mask2, eClearMask mask3) noexcept
			{
				glClear(static_cast<unsigned int>(mask1) | static_cast<unsigned int>(mask2) | static_cast<unsigned int>(mask3));
			}

			enum class eCapability
			{
				BLEND = GL_BLEND,
				COLOR_LOGIC_OP = GL_COLOR_LOGIC_OP,
				COLOR_TABLE = GL_COLOR_TABLE,
				CONVOLUTION_1D = GL_CONVOLUTION_1D,
				CONVOLUTION_2D = GL_CONVOLUTION_2D,
				CULL_FACE = GL_CULL_FACE,
				DEPTH_TEST = GL_DEPTH_TEST,
				DITHER = GL_DITHER,
				HISTOGRAM = GL_HISTOGRAM,
				LINE_SMOOTH = GL_LINE_SMOOTH,
				MINMAX = GL_MINMAX,
				MULTISAMPLE = GL_MULTISAMPLE,
				POLYGON_OFFSET_FILL = GL_POLYGON_OFFSET_FILL,
				POLYGON_OFFSET_LINE = GL_POLYGON_OFFSET_LINE,
				POLYGON_OFFSET_POINT = GL_POLYGON_OFFSET_POINT,
				POLYGON_SMOOTH = GL_POLYGON_SMOOTH,
				POST_COLOR_MATRIX_COLOR_TABLE = GL_POST_COLOR_MATRIX_COLOR_TABLE,
				POST_CONVOLUTION_COLOR_TABLE = GL_POST_CONVOLUTION_COLOR_TABLE,
				SAMPLE_ALPHA_TO_COVERAGE = GL_SAMPLE_ALPHA_TO_COVERAGE,
				SAMPLE_ALPHA_TO_ONE = GL_SAMPLE_ALPHA_TO_ONE,
				SAMPLE_COVERAGE = GL_SAMPLE_COVERAGE,
				SEPARABLE_2D = GL_SEPARABLE_2D,
				SCISSOR_TEST = GL_SCISSOR_TEST,
				STENCIL_TEST = GL_STENCIL_TEST,
				TEXTURE_1D = GL_TEXTURE_1D,
				TEXTURE_2D = GL_TEXTURE_2D,
				TEXTURE_3D = GL_TEXTURE_3D,
				TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
				VERTEX_PROGRAM_POINT_SIZE = GL_VERTEX_PROGRAM_POINT_SIZE,

			};

			static inline void Enable(eCapability c) noexcept
			{
				glEnable(static_cast<unsigned int>(c));
			}

			static inline void Disable(eCapability c) noexcept
			{
				glDisable(static_cast<unsigned int>(c));
			}

			enum class eSourceFactor : unsigned int
			{
				ZERO = GL_ZERO,
				ONE = GL_ONE,
				SRC_COLOR = GL_SRC_COLOR,
				ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
				DST_COLOR = GL_DST_COLOR,
				ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
				SRC_ALPHA = GL_SRC_ALPHA,
				ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
				DST_ALPHA = GL_DST_ALPHA,
				ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
				CONSTANT_COLOR = GL_CONSTANT_COLOR,
				ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR,
				CONSTANT_ALPHA = GL_CONSTANT_ALPHA,
				ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA,
				SRC_ALPHA_SATURATE = GL_SRC_ALPHA_SATURATE,
				SRC1_COLOR = GL_SRC1_COLOR,
				ONE_MINUS_SRC1_COLOR = GL_ONE_MINUS_SRC1_COLOR,
				SRC1_ALPHA = GL_SRC1_ALPHA,
				ONE_MINUS_SRC1_ALPHA = GL_ONE_MINUS_SRC1_ALPHA,

			};

			enum class eDestinationFactor : unsigned int
			{
				ZERO = GL_ZERO,
				ONE = GL_ONE,
				SRC_COLOR = GL_SRC_COLOR,
				ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
				DST_COLOR = GL_DST_COLOR,
				ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
				SRC_ALPHA = GL_SRC_ALPHA,
				ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
				DST_ALPHA = GL_DST_ALPHA,
				ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
				CONSTANT_COLOR = GL_CONSTANT_COLOR,
				ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR,
				CONSTANT_ALPHA = GL_CONSTANT_ALPHA,
				ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA,

			};
			static inline void BlendFunc(eSourceFactor sourceFactor, eDestinationFactor destinationFactor) noexcept
			{
				glBlendFunc(static_cast<unsigned int>(sourceFactor), static_cast<unsigned int>(destinationFactor));
			}

			enum class eFrontFaceMode : unsigned int
			{
				CW = GL_CW,
				CCW = GL_CCW

			};

			static inline void FrontFace(eFrontFaceMode faceMode) noexcept
			{
				glFrontFace(static_cast<unsigned int>(faceMode));
			}

			static inline void ViewPort(int x, int y, int width, int height) noexcept
			{
				glViewport(x, y, width, height);
			}

			enum class eBufferType
			{
				COLOR = GL_COLOR_BUFFER_BIT,
				DEPTH = GL_DEPTH_BUFFER_BIT,
				DEPTH_STENCIL = GL_STENCIL_BUFFER_BIT
			};


		};
	}
}