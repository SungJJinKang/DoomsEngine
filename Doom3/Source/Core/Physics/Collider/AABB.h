#pragma once

#include "../Core.h"
#include <Utility.h>
#include <Vector2.h>
#include <Vector3.h>
#include "Collider.h"
#include "Ray.h"
#include <Matrix4x4.h>

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
			/// <summary>
			/// this is local coordinate, you should map to your world coordinate
			/// </summary>
			math::Vector3 mLowerBound; // minimum extent
			/// <summary>
			/// this is local coordinate, you should map to your world coordinate
			/// </summary>
			math::Vector3 mUpperBound; // maximum extent

			AABB3D() : mLowerBound{}, mUpperBound{}
			{}
			AABB3D(const math::Vector3& lowerBound, const math::Vector3& upperBound)
				:mLowerBound(lowerBound), mUpperBound(upperBound)
			{
#ifdef DEBUG_MODE
				this->Validate();
#endif
			}
			AABB3D(const AABB3D&) = default;
			AABB3D(AABB3D&&) noexcept = default;
			AABB3D& operator=(const AABB3D&) = default;
			AABB3D& operator=(AABB3D&&) noexcept = default;
			
			bool IsValid() const;
			void Validate();

			math::Vector3 GetHalfExtent() const;
			/// <summary>
			/// Get 대각선
			/// </summary>
			/// <returns></returns>
			float GetDiagonarLineLength();

			virtual void Render(eColor color) final;


			ColliderType GetColliderType() const override;

		};

	
		/// <summary>
		/// 부피
		/// </summary>
		/// <param name="A"></param>
		/// <returns></returns>
		float GetArea(const AABB3D& A);
		AABB3D Union(const AABB3D& A, const AABB3D& B);

		bool IsOverlapAABB3DAndPoint(const AABB3D& aabb, const math::Vector3& Point);
		bool IsOverlapAABB3DAndAABB3D(const AABB3D& aabb, const AABB3D& B);
		bool IsOverlapAABB3DAndAABB3D(Collider* aabb, Collider* B);

		math::Vector3 ClosestPointToPoint(const AABB3D& aabb, const math::Vector3& point);

		void ApplyModelMatrixToAABB3D(const AABB3D& localAABB, const math::Matrix4x4& modelMatrix, AABB3D& resultAABB);

		class AABB2D : public Collider
		{
		public:
			/// <summary>
			/// this is local coordinate, you should map to your world coordinate
			/// </summary>
			math::Vector2 mLowerBound; // minimum extent
			/// <summary>
			/// this is local coordinate, you should map to your world coordinate
			/// </summary>
			math::Vector2 mUpperBound; // maximum extent

			AABB2D() : mLowerBound{}, mUpperBound{}
			{}
			AABB2D(const math::Vector2& lowerBound, const math::Vector2& upperBound)
				:mLowerBound(lowerBound), mUpperBound(upperBound)
			{
#ifdef DEBUG_MODE
				this->Validate();
#endif
			}
			AABB2D(const AABB2D&) = default;
			AABB2D(AABB2D&&) noexcept = default;
			AABB2D(const AABB3D& aabb3D);
			AABB2D& operator=(const AABB2D&) = default;
			AABB2D& operator=(AABB2D&&) noexcept = default;
			AABB2D& operator=(const AABB3D& aabb3D);

			bool IsValid() const;
			void Validate();

			math::Vector2 GetHalfExtent() const;

			virtual void Render(eColor color) final;

			ColliderType GetColliderType() const override;

		};


		float GetArea(const AABB2D& A);

		AABB2D Union(const AABB2D& A, const AABB2D& B);

		bool IsOverlapAABB2DAndPoint(const AABB2D& aabb, const math::Vector2& Point);
		bool IsOverlapAABB2DAndAABB2D(const AABB2D& aabb, const AABB2D& B);
		bool IsOverlapAABB2DAndAABB2D(Collider* aabb, Collider* B);
		math::Vector2 ClosestPointToPoint(const AABB2D& aabb, const math::Vector2& point);
	
		void ApplyModelMatrixToAABB2D(const AABB2D& localAABB, const math::Matrix4x4& modelMatrix, AABB2D& resultAABB);
	}
}

