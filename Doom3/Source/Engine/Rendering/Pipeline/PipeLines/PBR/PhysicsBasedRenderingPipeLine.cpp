#include "PhysicsBasedRenderingPipeLine.h"

dooms::graphics::PhysicsBasedRenderingPipeLine::PhysicsBasedRenderingPipeLine(dooms::graphics::Graphics_Server& graphicsServer)
	: DefaultGraphcisPipeLine(graphicsServer)
{
}

void dooms::graphics::PhysicsBasedRenderingPipeLine::Initialize()
{
	DefaultGraphcisPipeLine::Initialize();
}

void dooms::graphics::PhysicsBasedRenderingPipeLine::LateInitialize()
{
	DefaultGraphcisPipeLine::LateInitialize();
}

void dooms::graphics::PhysicsBasedRenderingPipeLine::PreRender()
{
}

void dooms::graphics::PhysicsBasedRenderingPipeLine::Render()
{
}

void dooms::graphics::PhysicsBasedRenderingPipeLine::PostRender()
{
}
