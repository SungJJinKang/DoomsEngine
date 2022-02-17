#include "DefaultLayers.h"

std::vector<dooms::Layer> dooms::defaultLayers::CreateDefaultLayers()
{
	std::vector<dooms::Layer> defaultLayers;

	defaultLayers.emplace_back("Default");
	defaultLayers.emplace_back("Layer1");
	defaultLayers.emplace_back("Layer2");
	defaultLayers.emplace_back("Layer3");
	defaultLayers.emplace_back("Layer4");
	defaultLayers.emplace_back("Layer5");


	return defaultLayers;
}
