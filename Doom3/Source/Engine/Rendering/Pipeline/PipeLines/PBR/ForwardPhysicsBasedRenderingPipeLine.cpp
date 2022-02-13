#include "ForwardPhysicsBasedRenderingPipeLine.h"

dooms::graphics::ForwardPhysicsBasedRenderingPipeLine::ForwardPhysicsBasedRenderingPipeLine(dooms::graphics::Graphics_Server& graphicsServer)
	: DefaultGraphcisPipeLine(graphicsServer)
{
}

void dooms::graphics::ForwardPhysicsBasedRenderingPipeLine::Initialize()
{
	DefaultGraphcisPipeLine::Initialize();
}

void dooms::graphics::ForwardPhysicsBasedRenderingPipeLine::LateInitialize()
{
	DefaultGraphcisPipeLine::LateInitialize();
}

void dooms::graphics::ForwardPhysicsBasedRenderingPipeLine::PreRender()
{
	DefaultGraphcisPipeLine::PreRender();
}

void dooms::graphics::ForwardPhysicsBasedRenderingPipeLine::Render()
{
	DefaultGraphcisPipeLine::Render();
}

void dooms::graphics::ForwardPhysicsBasedRenderingPipeLine::PostRender()
{
	DefaultGraphcisPipeLine::PostRender();
}

dooms::graphics::eGraphicsPipeLineType dooms::graphics::ForwardPhysicsBasedRenderingPipeLine::GetGraphicsPipeLineType() const
{
	return eGraphicsPipeLineType::ForwardPhysicsBasedRendering;
}