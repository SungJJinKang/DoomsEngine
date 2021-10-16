#pragma once

#include <vector>

#include "../Core/ServerComponent.h"
#include <StaticContainer/StaticContainer.h>

namespace doom
{
	class ColliderComponent;
	namespace physics
	{
		class Collider;
	}

	class DOOM_API Rigidbody : public ServerComponent, public StaticContainer<Rigidbody>
	{
		DOBJECT_BODY(Rigidbody)

	private:

		std::vector<ColliderComponent*> mAttachedColliderComponents;

		std::vector<doom::physics::Collider*> mCollideCollidersAtFrame;

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


		FORCE_INLINE void AddCollideCollidersAtFrame(doom::physics::Collider* const collider)
		{
			mCollideCollidersAtFrame.push_back(collider);
		}
		FORCE_INLINE const std::vector<doom::physics::Collider*>& GetCollideCollidersAtFrame() const
		{
			return mCollideCollidersAtFrame;
		}
		void ClearCollideCollidersAtFrame();
		
	};
}


