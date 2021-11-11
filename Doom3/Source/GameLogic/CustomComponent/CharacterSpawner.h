#pragma once
#include <Doom_Core.h>

namespace dooms
{
	namespace asset
	{
		class ShaderAsset;
	}

	class D_CLASS CharacterSpawner : public PlainComponent
	{

		DOBJECT_CLASS_BODY(CharacterSpawner)
		DOBJECT_CLASS_BASE_CHAIN(PlainComponent)

	private:
		
		inline static asset::ShaderAsset* mBillboardShader{ nullptr };

	protected:
		void InitComponent() override;
		void UpdateComponent() override;

	public:

		void CreateEnemy(const math::Vector3& position);
	

	};
}

