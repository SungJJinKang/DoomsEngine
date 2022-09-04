#include "FDrawCommand.h"

#include <Graphics/GraphicsAPI/Manager/GraphicsAPIManager.h>
#include "DrawState.h"

void dooms::graphics::FDrawCommand::Draw()
{
	D_ASSERT(PrimitiveType != GraphicsAPI::ePrimitiveType::NONE);

	if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		BindVertexArrayObject();
	}
	else if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		BindVertexBufferObject();
	}
	else
	{
		NEVER_HAPPEN;
	}

	if (ElementBufferObjectID.IsValid())
	{
		// TODO : WHY THIS MAKE ERROR ON RADEON GPU, CHECK THIS https://stackoverflow.com/questions/18299646/gldrawelements-emits-gl-invalid-operation-when-using-amd-driver-on-linux
		// you don't need bind EBO everytime, EBO will be bound automatically when bind VAO
		BindIndexBufferObject();
		GraphicsAPI::DrawIndexed(PrimitiveType, IndiceCount);
	}
	else
	{
		GraphicsAPI::Draw(PrimitiveType, 0, VertexCount);
	}
}

void dooms::graphics::FDrawCommand::BindVertexArrayObject()
{
	if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		D_ASSERT(VertexArrayObjectID.IsValid() == true);
		if (drawState::BOUND_VERTEX_ARRAY_ID != VertexArrayObjectID.GetBufferID())
		{
			drawState::BOUND_VERTEX_ARRAY_ID = VertexArrayObjectID;
			dooms::graphics::GraphicsAPI::BindVertexArrayObject(VertexArrayObjectID);
		}
	}
}

void dooms::graphics::FDrawCommand::BindVertexBufferObject()
{
	D_ASSERT(VertexDataBuffer.IsValid() == true);
	D_ASSERT(TotalStride > 0);

	if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		if (drawState::BOUND_VERTEX_BUFFER_ID[0] != VertexArrayObjectID.GetBufferID())
		{
			drawState::BOUND_VERTEX_BUFFER_ID[0] = VertexArrayObjectID;
			dooms::graphics::GraphicsAPI::BindVertexDataBuffer
			(
				VertexDataBuffer,
				0,
				TotalStride,
				0
			);
		}
	}
	else if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		for (UINT32 bufferLayoutIndex = 0; bufferLayoutIndex < VertexBufferLayoutCount; bufferLayoutIndex++)
		{
			if (drawState::BOUND_VERTEX_BUFFER_ID[bufferLayoutIndex] != VertexDataBuffer.GetBufferID())
			{
				drawState::BOUND_VERTEX_BUFFER_ID[bufferLayoutIndex] = VertexDataBuffer;
				dooms::graphics::GraphicsAPI::BindVertexDataBuffer
				(
					VertexDataBuffer,
					bufferLayoutIndex,
					VertexBufferLayouts[bufferLayoutIndex].mStride,
					VertexBufferLayouts[bufferLayoutIndex].mOffset
				);
			}
		}

	}
	else
	{
		NEVER_HAPPEN;
	}
}

void dooms::graphics::FDrawCommand::BindIndexBufferObject()
{
	D_ASSERT(VertexDataBuffer.IsValid() == true);
	if (drawState::BOUND_INDEX_BUFFER_ID != ElementBufferObjectID.GetBufferID())
	{
		drawState::BOUND_INDEX_BUFFER_ID = ElementBufferObjectID;
		dooms::graphics::GraphicsAPI::BindBuffer(ElementBufferObjectID, 0, graphics::GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER, graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY);
	}
}
