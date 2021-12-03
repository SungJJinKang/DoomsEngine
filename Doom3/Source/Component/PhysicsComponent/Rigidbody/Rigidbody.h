#pragma once

#include <vector>

#include "../Core/ServerComponent.h"
#include <StaticContainer/StaticContainer.h>

#include "Rigidbody.reflection.h"
namespace dooms
{
	class ColliderComponent;
	namespace physics
	{
		class Collider;
	}

	class DOOM_API D_CLASS Rigidbody : public ServerComponent, public StaticContainer<Rigidbody>
	{
		GENERATE_BODY()
		

	private:

		std::vector<ColliderComponent*> mAttachedColliderComponents;

		std::vector<dooms::physics::Collider*> mCollideCollidersAtFrame;

		void InitializeAttachedColliderComponents();
		void CheckIsRigidbodyComponentAlreadyExist();

	protected:
		

	public:

		Rigidbody();
		~Rigidbody();
		Rigidbody(const Rigidbody& rigid);
		Rigidbody& operator=(const Rigidbody& rigid);

		void InitComponent() override;
		void UpdateComponent() override;
		void OnDestroy() override;
		void OnActivated() override;
		void OnDeActivated() override;

		void AddColliderComponent(ColliderComponent* const colliderComponent);
		void RemoveColliderComponent(ColliderComponent* const colliderComponent);

		const std::vector<ColliderComponent*>& GetAttachedColliderComponents() const;


		FORCE_INLINE void AddCollideCollidersAtFrame(dooms::physics::Collider* const collider)
		{
			mCollideCollidersAtFrame.push_back(collider);
		}
		FORCE_INLINE const std::vector<dooms::physics::Collider*>& GetCollideCollidersAtFrame() const
		{
			return mCollideCollidersAtFrame;
		}
		void ClearCollideCollidersAtFrame();
		
	};
}


