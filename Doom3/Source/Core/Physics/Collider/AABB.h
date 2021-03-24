#pragma once

#include "../Core.h"
#include <Utility.h>
#include <Vector2.h>
#include <Vector3.h>
#include "Collider.h"
#include <Matrix4x4.h>
#include <functional>

namespace doom
{
	namespace physics
	{
		class AABB2D;
		class AABB3D;

		/// <summary>
		/// reference : https://box2d.org/files/ErinCatto_DynamicBVH_GDC2019.pdf
		/// </summary>
		class AABB3D : public Collider
		{
		public:
			using component_type = typename math::Vector3;
		private:
			virtual void Render(eColor color, bool drawInstantly = false);

		public:

			math::Vector3 mLowerBound; 
			math::Vector3 mUpperBound; 

			bool IsValid() const;

			void Validate();

			math::Vector3 GetHalfExtent() const;
			/// <summary>
			/// Get 대각선
			/// </summary>
			/// <returns></returns>
			float GetDiagonarLineLength() const;
			virtual void Render2DTopView(eColor color, bool drawInstantly = false);
			ColliderType GetColliderType() const override;
			FORCE_INLINE math::Vector3 GetCenter() const
			{
				return (this->mLowerBound + this->mUpperBound) / 2;
			}

			void Expand(const math::Vector3& movedVector);

			void SignedExpand(const math::Vector3& movedVector);

			/// <summary>
			/// 부피
			/// </summary>
			/// <param name="A"></param>
			/// <returns></returns>
			FORCE_INLINE static float GetArea(const AABB3D& A)
			{
				math::Vector3 d = A.mUpperBound - A.mLowerBound;
				return 2.0f * (d.x * d.y + d.y * d.z + d.z * d.x);
			}
			FORCE_INLINE static AABB3D Union(const AABB3D& A, const AABB3D& B)
			{
				return AABB3D(math::Min(A.mLowerBound, B.mLowerBound), math::Max(A.mUpperBound, B.mUpperBound));
			}
			FORCE_INLINE static float GetUnionArea(const AABB3D& A, const AABB3D& B)
			{
				math::Vector3 d = math::Max(A.mUpperBound, B.mUpperBound) - math::Min(A.mLowerBound, B.mLowerBound);
				return 2.0f * (d.x * d.y + d.y * d.z + d.z * d.x);
			}
			static AABB3D EnlargeAABB(const AABB3D& aabb);


			/// <summary>
			/// https://twitter.com/Herschel/status/1188613724665335808
			/// </summary>
			/// <param name="localAABB"></param>
			/// <param name="modelMatrix"></param>
			/// <param name="resultAABB"></param>

			inline static void ApplyModelMatrix(const AABB3D& localAABB, const math::Matrix4x4& modelMatrix, AABB3D& resultAABB)
			{
				resultAABB.mLowerBound = modelMatrix * localAABB.mLowerBound;
				resultAABB.mUpperBound = modelMatrix * localAABB.mUpperBound;
			}

			
			/// <summary>
			/// This is different with IsOverlap
			/// This function check if innerAABB is completly enclosed by outerAABB
			/// </summary>
			/// <param name="A"></param>
			/// <param name="B"></param>
			/// <returns></returns>
			FORCE_INLINE static bool CheckIsCompletlyEnclosed(const AABB3D& innerAABB, const AABB3D& outerAABB)
			{
				return innerAABB.mLowerBound.x >= outerAABB.mLowerBound.x &&
					innerAABB.mLowerBound.y >= outerAABB.mLowerBound.y &&
					innerAABB.mLowerBound.z >= outerAABB.mLowerBound.z &&
					innerAABB.mUpperBound.x <= outerAABB.mUpperBound.x &&
					innerAABB.mUpperBound.y <= outerAABB.mUpperBound.y &&
					innerAABB.mUpperBound.z <= outerAABB.mUpperBound.z;
			}

			FORCE_INLINE constexpr AABB3D() : mLowerBound{}, mUpperBound{}
			{}
			FORCE_INLINE AABB3D(const math::Vector3& lowerBound, const math::Vector3& upperBound)
				: mLowerBound(lowerBound), mUpperBound(upperBound)
			{
#ifdef DEBUG_MODE
				this->Validate();
#endif
			}
			FORCE_INLINE AABB3D(const AABB2D& aabb2D);
			constexpr AABB3D(const AABB3D&) = default;
			constexpr AABB3D(AABB3D&&) noexcept = default;
			constexpr AABB3D& operator=(const AABB3D&) = default;
			constexpr AABB3D& operator=(AABB3D&&) noexcept = default;
		};

		
		FORCE_INLINE bool IsOverlapAABB3DAndPoint(const AABB3D& aabb, const math::Vector3& Point)
		{
			return (Point.x >= aabb.mLowerBound.x && Point.x <= aabb.mUpperBound.x) &&
				(Point.y >= aabb.mLowerBound.y && Point.y <= aabb.mUpperBound.y) &&
				(Point.z >= aabb.mLowerBound.z && Point.z <= aabb.mUpperBound.z);
		}
		FORCE_INLINE bool IsOverlapAABB3DAndAABB3D(const AABB3D& aabb, const AABB3D& B)
		{
			return (aabb.mLowerBound.x <= B.mUpperBound.x && aabb.mUpperBound.x >= B.mLowerBound.x) &&
				(aabb.mLowerBound.y <= B.mUpperBound.y && aabb.mUpperBound.y >= B.mLowerBound.y) &&
				(aabb.mLowerBound.z <= B.mUpperBound.z && aabb.mUpperBound.z >= B.mLowerBound.z);
		}
		FORCE_INLINE bool IsOverlapAABB3DAndAABB3D(Collider* aabb, Collider* B)
		{
			return IsOverlapAABB3DAndAABB3D(*static_cast<AABB3D*>(aabb), *static_cast<AABB3D*>(B));
		}

		math::Vector3 ClosestPointToPoint(const AABB3D& aabb, const math::Vector3& point);

		
		class AABB2D : public Collider
		{
		public:
			using component_type = typename math::Vector2;

		private:
			virtual void Render(eColor color, bool drawInstantly = false);

		public:

			math::Vector2 mLowerBound; 
			math::Vector2 mUpperBound; 

		

			bool IsValid() const;
			void Validate();

			math::Vector2 GetHalfExtent() const;
			ColliderType GetColliderType() const override;

			FORCE_INLINE math::Vector2 GetCenter() const
			{
				return (this->mLowerBound + this->mUpperBound) / 2;
			}

			FORCE_INLINE void Expand(const math::Vector2& movedVector)
			{
				math::Vector2 expandVec{ math::abs(movedVector.x) ,  math::abs(movedVector.y) };
				this->mUpperBound += expandVec;
				this->mLowerBound -= expandVec;
			}


			inline void SignedExpand(const math::Vector2& movedVector)
			{
				if (movedVector.x > 0)
				{
					this->mUpperBound.x += movedVector.x;
				}
				else
				{
					this->mLowerBound.x += movedVector.x;
				}


				if (movedVector.y > 0)
				{
					this->mUpperBound.y += movedVector.y;
				}
				else
				{
					this->mLowerBound.y += movedVector.y;
				}
			}

			FORCE_INLINE static constexpr float GetArea(const AABB2D& A)
			{
				math::Vector2 d = A.mUpperBound - A.mLowerBound;
				return 2.0f * (d.x + d.y);
			}
			FORCE_INLINE static AABB2D Union(const AABB2D& A, const AABB2D& B)
			{
				return AABB2D(math::Min(A.mLowerBound, B.mLowerBound), math::Max(A.mUpperBound, B.mUpperBound));
			}
			FORCE_INLINE static constexpr float GetUnionArea(const AABB2D& A, const AABB2D& B)
			{
				math::Vector2 d = math::Max(A.mUpperBound, B.mUpperBound) - math::Min(A.mLowerBound, B.mLowerBound);
				return 2.0f * (d.x + d.y);
			}

			static AABB2D EnlargeAABB(const AABB2D& aabb);

			/// <summary>
			/// https://twitter.com/Herschel/status/1188613724665335808
			/// </summary>
			/// <param name="localAABB"></param>
			/// <param name="modelMatrix"></param>
			/// <param name="resultAABB"></param>

			// this function is not tested
			inline static void ApplyModelMatrix(const AABB2D& localAABB, const math::Matrix4x4& modelMatrix, AABB2D& resultAABB)
			{
				for (int i = 0; i < 2; i++)
				{
					resultAABB.mLowerBound[i] = resultAABB.mUpperBound[i] = modelMatrix[3][i];

					for (int j = 0; j < 2; j++)
					{
						float e = modelMatrix[i][j] * localAABB.mLowerBound[j];
						float f = modelMatrix[i][j] * localAABB.mUpperBound[j];
						if (e < f)
						{
							resultAABB.mLowerBound[i] += e;
							resultAABB.mUpperBound[i] += f;
						}
						else
						{
							resultAABB.mLowerBound[i] += f;
							resultAABB.mUpperBound[i] += e;
						}
					}
				}
			}

			/// <summary>
			/// This is different with IsOverlap
			/// This function check if innerAABB is completly enclosed by outerAABB
			/// </summary>
			/// <param name="innerAABB"></param>
			/// <param name="outerAABB"></param>
			/// <returns></returns>
			FORCE_INLINE static bool CheckIsCompletlyEnclosed(const AABB2D& innerAABB, const AABB2D& outerAABB)
			{
				return innerAABB.mLowerBound.x >= outerAABB.mLowerBound.x &&
					innerAABB.mLowerBound.y >= outerAABB.mLowerBound.y &&
					innerAABB.mUpperBound.x <= outerAABB.mUpperBound.x &&
					innerAABB.mUpperBound.y <= outerAABB.mUpperBound.y;
			}

			FORCE_INLINE constexpr AABB2D() : mLowerBound{}, mUpperBound{}
			{}
			FORCE_INLINE AABB2D(const math::Vector2& lowerBound, const math::Vector2& upperBound)
				: mLowerBound(lowerBound), mUpperBound(upperBound)
			{
#ifdef DEBUG_MODE
				this->Validate();
#endif
			}

			constexpr AABB2D(const AABB2D&) = default;
			constexpr AABB2D(AABB2D&&) noexcept = default;
			constexpr AABB2D(const AABB3D & aabb3D)
			{
				this->mLowerBound = aabb3D.mLowerBound;
				this->mUpperBound = aabb3D.mUpperBound;
			}
			AABB2D& operator=(const AABB2D&) = default;
			AABB2D& operator=(AABB2D&&) noexcept = default;
			AABB2D& operator=(const AABB3D & aabb3D);
		};

		
		
		FORCE_INLINE bool IsOverlapAABB2DAndPoint(const AABB2D& aabb, const math::Vector2& Point)
		{
			return (Point.x >= aabb.mLowerBound.x && Point.x <= aabb.mUpperBound.x) &&
				(Point.y >= aabb.mLowerBound.y && Point.y <= aabb.mUpperBound.y);
		}
		FORCE_INLINE bool IsOverlapAABB2DAndAABB2D(const AABB2D& aabb, const AABB2D& B)
		{
			return aabb.mUpperBound.x > B.mLowerBound.x && aabb.mLowerBound.x < B.mUpperBound.x&&
				aabb.mUpperBound.y  > B.mLowerBound.y && aabb.mLowerBound.y < B.mUpperBound.y;
		}
		FORCE_INLINE bool IsOverlapAABB2DAndAABB2D(Collider* aabb, Collider* B)
		{
			return IsOverlapAABB2DAndAABB2D(*static_cast<AABB2D*>(aabb), *static_cast<AABB2D*>(B));
		}
		math::Vector2 ClosestPointToPoint(const AABB2D& aabb, const math::Vector2& point);
	
		

		FORCE_INLINE doom::physics::AABB3D::AABB3D(const AABB2D& aabb2D)
		{
			this->mLowerBound = aabb2D.mLowerBound;
			this->mUpperBound = aabb2D.mUpperBound;
		}

	}
}

template<>
struct std::greater <doom::physics::AABB2D>
{
	bool operator()(const doom::physics::AABB2D& lhs, const doom::physics::AABB2D& rhs) const
	{
		return doom::physics::AABB2D::GetArea(lhs) > doom::physics::AABB2D::GetArea(rhs);
	}
};

template<>
struct std::greater <doom::physics::AABB3D>
{
	bool operator()(const doom::physics::AABB3D& lhs, const doom::physics::AABB3D& rhs) const
	{
		return doom::physics::AABB3D::GetArea(lhs) > doom::physics::AABB3D::GetArea(rhs);
	}
};