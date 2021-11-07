#pragma once

#include <vector>

#include "../Core/ServerComponent.h"
#include <StaticContainer/StaticContainer.h>

namespace dooms
{
	class ColliderComponent;
	namespace physics
	{
		class Collider;
	}

	class DOOM_API Rigidbody : public ServerComponent, public StaticContainer<Rigidbody>
	{
		DOBJECT_CLASS_BODY(Rigidbody)
		DOBJECT_CLASS_BASE_CHAIN(ServerComponent)

	private:

		std::vector<ColliderComponent*> mAttachedColliderComponents;

		std::vector<dooms::physics::Collider*> mCollideCollidersAtFrame;

		void InitializeAttachedColliderComponents();
		void CheckIsRigidbodyComponentAlreadyExist();

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


