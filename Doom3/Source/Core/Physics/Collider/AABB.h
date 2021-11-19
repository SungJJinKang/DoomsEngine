#pragma once

#include "../Core.h"
#include <Utility.h>
#include <Vector2.h>
#include <Vector3.h>
#include "Collider.h"
#include <Matrix4x4.h>
#include <functional>

#include "AABB.reflection.h"
namespace dooms
{
	namespace physics
	{
		class AABB2D;
		class AABB3D;

		/// <summary>
		/// reference : https://box2d.org/files/ErinCatto_DynamicBVH_GDC2019.pdf
		/// </summary>
		class DOOM_API D_CLASS AABB3D : public Collider
		{
			GENERATE_BODY_AABB3D()
		public:
			using component_type = typename math::Vector4;
		
			virtual void DrawCollider(eColor color, bool drawInstantly = false) const;

			D_PROPERTY()
			component_type mLowerBound; 
			/// <summary>
			/// Padding is required for FrostbiteCulling System
			/// </summary>
			//FLOAT32 padding1{ 1.0f };
			D_PROPERTY()
			component_type mUpperBound;
			//FLOAT32 padding2{ 1.0f };
			
			
			bool IsValid() const;

			
			void Validate();

			FORCE_INLINE virtual void* data() final
			{
				return &(mLowerBound);
			}

			FORCE_INLINE virtual const void* data() const final
			{
				return &(mLowerBound);
			}

			
			component_type GetHalfExtent() const;

			/// <summary>
			/// Get �밢��
			/// </summary>
			/// <returns></returns>
			
			FLOAT32 GetDiagonarLineLength() const;
			virtual void Render2DTopView(eColor color, bool drawInstantly = false);

			
			ColliderType GetColliderType() const override;

			
			FORCE_INLINE component_type GetCenter() const
			{
				return component_type{ (mLowerBound + mUpperBound) / 2 };
			}

			
			void Expand(const component_type& movedVector);

			
			void SignedExpand(const component_type& movedVector);

			/// <summary>
			/// ����
			/// </summary>
			/// <param name="A"></param>
			/// <returns></returns>
			///	
			FORCE_INLINE static FLOAT32 GetArea(const AABB3D& A)
			{
				math::Vector4 d = A.mUpperBound - A.mLowerBound;
				return 2.0f * (d.x * d.y + d.y * d.z + d.z * d.x);
			}
			
			FORCE_INLINE static AABB3D Union(const AABB3D& A, const AABB3D& B)
			{
				return AABB3D(math::Min(A.mLowerBound, B.mLowerBound), math::Max(A.mUpperBound, B.mUpperBound));
			}
			
			FORCE_INLINE static FLOAT32 GetUnionArea(const AABB3D& A, const AABB3D& B)
			{
				math::Vector3 d = math::Vector3{ math::Max(A.mUpperBound, B.mUpperBound) - math::Min(A.mLowerBound, B.mLowerBound) };
				return 2.0f * (d.x * d.y + d.y * d.z + d.z * d.x);
			}

			
			static AABB3D EnlargeAABB(const AABB3D& aabb);


			/// <summary>
			/// /// See Christer Ericson's Real-time Collision Detection, p. 87, or
			/// James Arvo's "Transforming Axis-aligned Bounding Boxes" in Graphics Gems 1, pp. 548-550.
			/// http://www.graphicsgems.org/
			/// </summary>
			/// <param name="localAABB"></param>
			/// <param name="modelMatrix"></param>
			/// <param name="resultAABB"></param>
			static void ApplyModelMatrix(const AABB3D& localAABB, const math::Matrix4x4& modelMatrix, AABB3D& resultAABB);

			
			/// <summary>
			/// This is different with IsOverlap
			/// This function check if innerAABB is completly enclosed by outerAABB
			/// </summary>
			/// <param name="A"></param>
			/// <param name="B"></param>
			/// <returns></returns>
			static bool CheckIsCompletlyEnclosed(const AABB3D& innerAABB, const AABB3D& outerAABB);

			AABB3D() = delete;
			FORCE_INLINE AABB3D(int*) : mLowerBound{ nullptr }, mUpperBound{ nullptr }
			{}

			FORCE_INLINE AABB3D(const math::Vector4& lowerBound, const math::Vector4& upperBound)
				: mLowerBound(lowerBound), mUpperBound(upperBound)
			{
#ifdef DEBUG_MODE
				Validate();
#endif
			}

			FORCE_INLINE AABB3D(const math::Vector3& lowerBound, const math::Vector3& upperBound)
				: mLowerBound(lowerBound), mUpperBound(upperBound)
			{
#ifdef DEBUG_MODE
				Validate();
#endif
			}
			FORCE_INLINE AABB3D(const AABB2D& aabb2D);
			AABB3D(const AABB3D&) = default;
			AABB3D(AABB3D&&) noexcept = default;
			AABB3D& operator=(const AABB3D&) = default;
			AABB3D& operator=(AABB3D&&) noexcept = default;
		};

		
		bool IsOverlapAABB3DAndPoint(const AABB3D& A, const math::Vector3& Point);
		bool IsOverlapAABB3DAndAABB3D(const AABB3D& A, const AABB3D& B);
		bool IsOverlapAABB3DAndAABB3D(const Collider* const A, const Collider* const B);

		math::Vector3 ClosestPointToPoint(const AABB3D& aabb, const math::Vector3& point);

		
		class DOOM_API D_CLASS AABB2D : public Collider
		{
			GENERATE_BODY_AABB2D()

		public:

			using component_type = typename math::Vector2;

			virtual void DrawCollider(eColor color, bool drawInstantly = false) const;

			D_PROPERTY()
			component_type mLowerBound;
			D_PROPERTY()
			component_type mUpperBound;

		
			
			bool IsValid() const;

			
			void Validate();

			FORCE_INLINE virtual void* data() final
			{
				return &(mLowerBound);
			}

			FORCE_INLINE virtual const void* data() const final
			{
				return &(mLowerBound);
			}

			
			component_type GetHalfExtent() const;
			
			ColliderType GetColliderType() const override;

			
			FORCE_INLINE component_type GetCenter() const
			{
				return (mLowerBound + mUpperBound) / 2;
			}

			
			FORCE_INLINE void Expand(const component_type& movedVector)
			{
				math::Vector2 expandVec{ std::abs(movedVector.x) ,  std::abs(movedVector.y) };
				mUpperBound += expandVec;
				mLowerBound -= expandVec;
			}


			
			void SignedExpand(const component_type& movedVector);

			
			FORCE_INLINE static FLOAT32 GetArea(const AABB2D& A)
			{
				math::Vector2 d = A.mUpperBound - A.mLowerBound;
				return 2.0f * (d.x + d.y);
			}
			
			FORCE_INLINE static AABB2D Union(const AABB2D& A, const AABB2D& B)
			{
				return AABB2D(math::Min(A.mLowerBound, B.mLowerBound), math::Max(A.mUpperBound, B.mUpperBound));
			}
			
			FORCE_INLINE static FLOAT32 GetUnionArea(const AABB2D& A, const AABB2D& B)
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
			static void ApplyModelMatrix(const AABB2D& localAABB, const math::Matrix4x4& modelMatrix, AABB2D& resultAABB);

			/// <summary>
			/// This is different with IsOverlap
			/// This function check if innerAABB is completly enclosed by outerAABB
			/// </summary>
			/// <param name="innerAABB"></param>
			/// <param name="outerAABB"></param>
			/// <returns></returns>
			static bool CheckIsCompletlyEnclosed(const AABB2D& innerAABB, const AABB2D& outerAABB);

			AABB2D() = delete;
			FORCE_INLINE AABB2D(int*) : mLowerBound{ nullptr }, mUpperBound{ nullptr }
			{}
			FORCE_INLINE AABB2D(const math::Vector2& lowerBound, const math::Vector2& upperBound)
				: mLowerBound(lowerBound), mUpperBound(upperBound)
			{
#ifdef DEBUG_MODE
				Validate();
#endif
			}

			AABB2D(const AABB2D&) = default;
			AABB2D(AABB2D&&) noexcept = default;
			AABB2D(const AABB3D & aabb3D) : mLowerBound{ nullptr }, mUpperBound{ nullptr }
			{
				mLowerBound = aabb3D.mLowerBound;
				mUpperBound = aabb3D.mUpperBound;
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
		FORCE_INLINE bool IsOverlapAABB2DAndAABB2D(const Collider* const aabb, const Collider* const B)
		{
			return IsOverlapAABB2DAndAABB2D(*static_cast<const AABB2D*>(aabb), *static_cast<const AABB2D*>(B));
		}
		math::Vector2 ClosestPointToPoint(const AABB2D& aabb, const math::Vector2& point);
	
		

		FORCE_INLINE dooms::physics::AABB3D::AABB3D(const AABB2D& aabb2D) : mLowerBound{nullptr}, mUpperBound{nullptr}
		{
			mLowerBound = aabb2D.mLowerBound;
			mUpperBound = aabb2D.mUpperBound;
		}

	}
}

template<>
struct std::greater <dooms::physics::AABB2D>
{
	bool operator()(const dooms::physics::AABB2D& lhs, const dooms::physics::AABB2D& rhs) const
	{
		return dooms::physics::AABB2D::GetArea(lhs) > dooms::physics::AABB2D::GetArea(rhs);
	}
};

template<>
struct std::greater <dooms::physics::AABB3D>
{
	bool operator()(const dooms::physics::AABB3D& lhs, const dooms::physics::AABB3D& rhs) const
	{
		return dooms::physics::AABB3D::GetArea(lhs) > dooms::physics::AABB3D::GetArea(rhs);
	}
};