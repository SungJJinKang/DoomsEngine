#pragma once

#include <Core.h>

#include <Rendering/Culling/EveryCulling/EveryCulling.h>

namespace dooms
{
	class Camera;
	namespace graphics
	{
		class D_CLASS RenderingCullingManager : public DObject
		{
		private:

			D_PROPERTY()
			UINT32 mCullingCameraCount;

			void UpdateCameraIndexInCullingSystemOfCameraComponent();

		public:

			std::unique_ptr<culling::EveryCulling> mCullingSystem;

			RenderingCullingManager();

			void Initialize();
			void PreCullJob();
			void CameraCullJob(dooms::Camera* const camera);
		};
	}
}

