#pragma once

#include <Core.h>

#include <vector>

#include <Vector3.h>
#include "../../Color.h"
#include <Math/LightMath_Cpp/Vector4.h>
#include "../../GraphicsAPI/GraphicsAPI.h"

namespace dooms
{
	namespace graphics
	{
		class DebugPrimitiveContainer
		{

		public:

			inline static const UINT32 COLOR_COUNT = ENUM_COLOR_COUNT;


		protected:

			std::array<std::vector<float>, ENUM_COLOR_COUNT> mColoredVertexData;

			std::vector<float> mSpecialColoredVertexData;
			std::vector<math::Vector4> mSpecialColorData;

		

			std::vector<float>& GetColoredVertexVector(const eColor color);

		public:

			/// <summary>
			///
			/// ex )
			/// 2D line -> 2
			/// 3D Triangle -> 3
			/// 
			/// </summary>
			/// <returns></returns>
			virtual UINT32 GetVertexCountPerPrimitive() const = 0;

			/// <summary>
			///
			/// ex )
			/// 2D line -> 6 ( 3 * 2 float )
			/// 3D Triangle -> 9 ( 3 * 3 float )
			/// 
			/// </summary>
			/// <returns></returns>
			virtual UINT32 GetComponentCountPerPrimitive() const = 0;

			virtual bool Is3DPrimitive() const = 0;
			virtual dooms::graphics::GraphicsAPI::ePrimitiveType GetPrimitiveType() const = 0;

			const float* GetColoredVertexData(const eColor color) const;
			//size_t GetColoredVertexCount(const eColor color) const;
			size_t GetColoredPrimitiveCount(const eColor color) const;

			const float* GetSpecialColoredVertexData() const;
			size_t GetSpecialColoredVertexDataCount() const;
			const math::Vector4* GetSpecialColorData() const;
			size_t GetSpecialColorDataCount() const;
			size_t GetSpecialColoredPrimitiveCount() const;

			void ReserveVector(const size_t primitiveCount);
			void ClearDatas();

			bool IsColoredVertexDataEmpty(const eColor color) const;
			bool IsSpecialColoredVertexDataEmpty() const;
		};
	}
}

