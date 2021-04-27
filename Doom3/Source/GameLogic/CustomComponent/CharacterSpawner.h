#pragma once
#include <Doom_Core.h>

namespace doom
{
	namespace asset
	{
		class ShaderAsset;
	}

	class CharacterSpawner : public PlainComponent
	{
	private:
		
		inline static asset::ShaderAsset* mBillboardShader{ nullptr };

	protected:
		void InitComponent() override;
		void UpdateComponent() override;

	public:

		void CreateEnemy(const math::Vector3& position);
	

	};
}

