#pragma once
#include <DoomsGameLogicCore.h>

#include "CharacterSpawner.reflection.h"
namespace dooms
{
	namespace asset
	{
		class ShaderAsset;
	}

	class DOOM_API D_CLASS CharacterSpawner : public Component
	{
		GENERATE_BODY()
		
		

	private:
		
		inline static asset::ShaderAsset* mBillboardShader{ nullptr };

	protected:
		void InitComponent() override;
		void UpdateComponent() override;

	public:

		void CreateEnemy(const math::Vector3& position);
	

	};
}

