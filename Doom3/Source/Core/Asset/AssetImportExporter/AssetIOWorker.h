#pragma once

#include <Core.h>

#include <array>
#include <vector>
#include <string>

#include <Asset/eAssetType.h>
#include <Misc/DynamicLinkingHelper/SmartDynamicLinking.h>

#include "AssetIOWorker.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS AssetIOWorker : public DObject
	{
		GENERATE_BODY()

	private:

		bool bmIsRequiredDllIsLoaded;
		std::vector<SmartDynamicLinking> mDynamicLinkedDLLs;
		void LoadRequiredDLLs();

	protected:

		virtual std::vector<std::string> GetRequiredDLLPathList();

	public:

		AssetIOWorker();

	};
}
