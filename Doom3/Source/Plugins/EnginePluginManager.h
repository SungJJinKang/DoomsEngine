#pragma once

#include <Core.h>

#include <unordered_map>
#include <string>
#include "EnginePlugin.h"
#include <SingleTon/Singleton.h>

#include "EnginePluginManager.reflection.h"
namespace dooms
{
	namespace plugin
	{
		class EnginePlugin;
		class D_CLASS EnginePluginManager : public DObject, public ISingleton<EnginePluginManager>
		{
			GENERATE_BODY()
			
			friend class EnginePlugin;

		private:

			D_PROPERTY()
			std::unordered_map<UINT64, EnginePlugin*> mEnginePlugins;

			bool AddEnginePlugins(EnginePlugin* const enginePlugin);
			bool RemoveEnginePlugins(EnginePlugin* const enginePlugin);

			/*
		public:

			template <typename ENGINE_PLUGIN_TYPE>
			ENGINE_PLUGIN_TYPE* GetOrCreateEnginePlugin()
			{
				static_assert(std::is_base_of_v<dooms::plugin::EnginePlugin, ENGINE_PLUGIN_TYPE> == true);

				dooms::plugin::EnginePlugin* enginePlugin = nullptr;

				auto node = mEnginePlugins.find(ENGINE_PLUGIN_TYPE::TYPE_FULL_NAME_HASH_VALUE);
				if (node != mEnginePlugins.end())
				{
					enginePlugin = node->second;
				}
				else
				{
					enginePlugin = dooms::CreateDObject<ENGINE_PLUGIN_TYPE>();
					D_ASSERT_LOG(IsValid(enginePlugin), "Fail to create Engine Plugin ( Plugin Name : %s )", ENGINE_PLUGIN_TYPE::TYPE_FULL_NAME);
					if(IsValid(enginePlugin))
					{
						AddEnginePlugins(enginePlugin);
					}
				}

				D_ASSERT(IsValid(enginePlugin));

				return enginePlugin;
			}
			*/

			
		};
	}
}


