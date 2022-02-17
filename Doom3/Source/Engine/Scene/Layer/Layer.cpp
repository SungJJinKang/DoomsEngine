#include "Layer.h"

dooms::Layer::Layer()
	: mLayerIndex((UINT32)-1), mLayerName()
{
}

dooms::Layer::Layer(const char* const layerName)
	: mLayerIndex((UINT32)-1), mLayerName(layerName)
{
}
