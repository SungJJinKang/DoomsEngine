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
	DefaultGraphcisPipeLine::PreRender();
}

void dooms::graphics::PhysicsBasedRenderingPipeLine::Render()
{
	DefaultGraphcisPipeLine::Render();
}

void dooms::graphics::PhysicsBasedRenderingPipeLine::PostRender()
{
	DefaultGraphcisPipeLine::PostRender();
}
