#include "UniformBufferObject.h"

#define USE_DYNAMIC_UNIFORM_BUFFER 1 // this shows much better gpu activity, frame because dynamic constant buffer doesn't require resource barrier

UINT64 dooms::graphics::UniformBufferObject::BOUND_UNIFORM_BUFFER_ID[GRAPHICS_PIPELINE_STAGE_COUNT][MAX_UNIFORM_BUFFER_SLOT_COUNT]{(UINT64)-1};

void dooms::graphics::UniformBufferObject::InitializeUniformVariableOffset
(
	const std::vector<asset::shaderReflectionDataParser::UniformBufferMember>& uboMembers
)
{
	mUniformVariableInfos.clear();
	mUniformVariableInfos.reserve(uboMembers.size());
	for(const asset::shaderReflectionDataParser::UniformBufferMember& uboMember : uboMembers)
	{
		D_ASSERT_LOG(mUniformVariableInfos.find(uboMember.mName) == mUniformVariableInfos.end(), "UBO member with same name is detected");
		mUniformVariableInfos.emplace(uboMember.mName, uboMember);
	}
}

void dooms::graphics::UniformBufferObject::OnSetPendingKill()
{
	Buffer::OnSetPendingKill();

	DeleteBuffers();
}

void dooms::graphics::UniformBufferObject::UpdateLocalBuffer_Internal(const void* sourceData, const UINT64 offsetInUniformBlock, const UINT64 sizeOfSourceData)
{
	D_ASSERT(IsBufferGenerated() == true);

	std::memcpy(mUniformBufferLocalBuffer.get() + offsetInUniformBlock, sourceData, sizeOfSourceData);
}

void dooms::graphics::UniformBufferObject::UpdateDataToGPU_Internal(const void* sourceData, const UINT64 offsetInUniformBlock, const UINT64 sizeOfSourceData) noexcept
{
	D_ASSERT(IsBufferGenerated() == true);

	if (USE_DYNAMIC_UNIFORM_BUFFER)
	{
		UINT8* bufferAddress;
		
		if (GraphicsAPI::RangedMapBufferObjectToClientAddress)
		{
			// it seems that can't make dynamic uniform buffer object(reside on write-combining system memory page, gpu reads it directly when it need) with glMapBuffer in opengl
			bufferAddress = reinterpret_cast<UINT8*>(GraphicsAPI::RangedMapBufferObjectToClientAddress(
				mUniformBufferObject,
				0,
				GetUniformBufferSize(),
				GraphicsAPI::eBufferTarget::UNIFORM_BUFFER,
				dooms::graphics::GraphicsAPI::eMapBufferAccessOption::WRITE_DISCARD)
			);
		}
		else
		{
			bufferAddress = reinterpret_cast<UINT8*>(GraphicsAPI::MapBufferObjectToClientAddress(
				mUniformBufferObject,
				GraphicsAPI::eBufferTarget::UNIFORM_BUFFER,
				dooms::graphics::GraphicsAPI::eMapBufferAccessOption::WRITE_DISCARD)
			);
		}

		std::memcpy(bufferAddress, reinterpret_cast<const UINT8*>(sourceData), mUniformBufferSize);

		GraphicsAPI::UnMapBufferObjectMappedToClientAddress(mUniformBufferObject, GraphicsAPI::eBufferTarget::UNIFORM_BUFFER);
	}
	else
	{
		GraphicsAPI::UpdateDataToBuffer(mUniformBufferObject, GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, offsetInUniformBlock, sizeOfSourceData, sourceData);
	}
}

dooms::graphics::UniformBufferObject::UniformBufferObject()
	:
	mUniformBufferObject(),
	mUniformBlockName(),
	mUniformBufferSize(0),
	mDefaultBindingPoint(0),
	mUniformBufferLocalBuffer()
{
	AddToRootObjectList();
}

dooms::graphics::UniformBufferObject::UniformBufferObject
(
	const std::string& uniformBlockName,
	const UINT64 uniformBufferSize,
	const UINT32 defaultBindingPoint, 
	const void* const initialData,
	const std::vector<asset::shaderReflectionDataParser::UniformBufferMember>* const uboMembers
)
	:
	mUniformBufferObject(),
	mUniformBlockName(),
	mUniformBufferSize(0),
	mDefaultBindingPoint(0),
	mUniformBufferLocalBuffer()
{
	AddToRootObjectList();
	InitializeUniformBufferObject(uniformBlockName, uniformBufferSize, defaultBindingPoint, initialData, uboMembers);
}

dooms::graphics::UniformBufferObject::~UniformBufferObject()
{
	DeleteBuffers();
}

bool dooms::graphics::UniformBufferObject::InitializeUniformBufferObject
(
	const std::string& uniformBlockName,
	const UINT64 uniformBufferSize, 
	const UINT32 defaultBindingPoint,
	const void* const initialData,
	const std::vector<asset::shaderReflectionDataParser::UniformBufferMember>* const uboMembers
)
{
	bool isSuccess = false;

	if(IsBufferGenerated() == false)
	{
		mUniformBlockName = uniformBlockName;
		mUniformBufferSize = uniformBufferSize;
		mDefaultBindingPoint = defaultBindingPoint;
		mUniformBufferLocalBuffer = nullptr;

		GenerateUniformBufferObject(uniformBufferSize);

		if(uboMembers != nullptr)
		{
			InitializeUniformVariableOffset(*uboMembers);
		}

		isSuccess = true;
	}

	return isSuccess;
}

std::string dooms::graphics::UniformBufferObject::GetUniformBlockName()
{
	return mUniformBlockName;
}

const std::string& dooms::graphics::UniformBufferObject::GetUniformBlockName() const
{
	return mUniformBlockName;
}

UINT64 dooms::graphics::UniformBufferObject::GetUniformBufferSize() const
{
	return mUniformBufferSize;
}

UINT32 dooms::graphics::UniformBufferObject::GetDefaultBindingPoint() const
{
	return mDefaultBindingPoint;
}

void dooms::graphics::UniformBufferObject::GenerateUniformBufferObject(const UINT64 uniformBufferSize, const void* const initialData)
{
	D_ASSERT(IsBufferGenerated() == false); // prevent overlap generating buffer
	if (IsBufferGenerated() == false)
	{
		mUniformBufferObject = GraphicsAPI::CreateBufferObject(GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, uniformBufferSize, initialData, USE_DYNAMIC_UNIFORM_BUFFER);

		mUniformBufferSize = uniformBufferSize;

		if (mUniformBufferLocalBuffer)
		{
			mUniformBufferLocalBuffer.reset();
		}

		mUniformBufferLocalBuffer = std::make_unique<UINT8[]>(uniformBufferSize);
		std::memset(mUniformBufferLocalBuffer.get(), 0x00, uniformBufferSize);
	}

}

void dooms::graphics::UniformBufferObject::DeleteBuffers()
{
	if(mUniformBufferObject.IsValid())
	{
		dooms::graphics::GraphicsAPI::DestroyBuffer(mUniformBufferObject);
		mUniformBufferObject.Reset();
	}

	if (mUniformBufferLocalBuffer != nullptr)
	{
		mUniformBufferLocalBuffer.reset();
	}

	mUniformBlockName.clear();
	mUniformBufferSize = 0;
	mDefaultBindingPoint = 0;
	mUniformVariableInfos.clear();
	
}

UINT64 dooms::graphics::UniformBufferObject::GetUniformVariableOffset(const char* const targetVariableName) const
{
	size_t offset = 0;

	D_ASSERT(IsBufferGenerated() == true);
	auto node = mUniformVariableInfos.find(targetVariableName);

	D_DEBUG_LOG(eLogType::D_ERROR, "Fail to find uniform variable ( %s ) from uniform buffer object ( %s )", targetVariableName, GetUniformBlockName().c_str());
	D_ASSERT(node != mUniformVariableInfos.end());

	if(node != mUniformVariableInfos.end())
	{
		offset = node->second.mOffset;
	}
	return offset;
}

void dooms::graphics::UniformBufferObject::BindBuffer(const UINT32 bindingPoint, const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage) const noexcept
{
	D_ASSERT(mUniformBufferObject.IsValid() == true);
	if (IsBufferGenerated() == true)
	{
		if(BOUND_UNIFORM_BUFFER_ID[static_cast<UINT32>(targetPipeLineStage)][bindingPoint] != mUniformBufferObject.GetBufferID())
		{
			BOUND_UNIFORM_BUFFER_ID[static_cast<UINT32>(targetPipeLineStage)][bindingPoint] = mUniformBufferObject.GetBufferID();
			GraphicsAPI::BindConstantBuffer(mUniformBufferObject, bindingPoint, targetPipeLineStage);
		}					
	}
}

void dooms::graphics::UniformBufferObject::UnBindBuffer(const UINT32 bindingPoint, const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage) const noexcept
{
	if (BOUND_UNIFORM_BUFFER_ID[static_cast<UINT32>(targetPipeLineStage)][bindingPoint] != 0)
	{
		BOUND_UNIFORM_BUFFER_ID[static_cast<UINT32>(targetPipeLineStage)][bindingPoint] = 0;
		GraphicsAPI::BindConstantBuffer(0, bindingPoint, targetPipeLineStage);
	}
}

void dooms::graphics::UniformBufferObject::UpdateLocalBufferToGPU() noexcept
{
	D_ASSERT(IsBufferGenerated() == true);
	if ( (bmIsDirty == true) && (IsBufferGenerated() == true) )
	{
		D_ASSERT(mUniformBufferLocalBuffer);
		UpdateDataToGPU_Internal(mUniformBufferLocalBuffer.get(), 0, mUniformBufferSize);
		bmIsDirty = false;
	}
}

void dooms::graphics::UniformBufferObject::UpdateDataToGPU(const void* sourceData, const UINT64 offsetInUniformBlock, const UINT64 sizeOfSourceData) noexcept
{
	D_ASSERT(IsBufferGenerated() == true);

	if (IsBufferGenerated() == true)
	{
		UpdateLocalBuffer_Internal(sourceData, offsetInUniformBlock, sizeOfSourceData);
		UpdateDataToGPU_Internal(sourceData, offsetInUniformBlock, sizeOfSourceData);
	}
}

void dooms::graphics::UniformBufferObject::UpdateDataToGPU(const void* sourceData, const char* const targetVariableName, const UINT64 sizeOfSourceData) noexcept
{
	D_ASSERT(IsBufferGenerated() == true);

	if (IsBufferGenerated() == true)
	{
		D_DEBUG_LOG(eLogType::D_WARNING, "Uniform buffer object is updated with string variable name. This is slow operation. Please pass offset directly");
		const UINT64 offset = GetUniformVariableOffset(targetVariableName);

		UpdateLocalBuffer_Internal(sourceData, offset, sizeOfSourceData);
		UpdateDataToGPU_Internal(sourceData, offset, sizeOfSourceData);
	}
}

void dooms::graphics::UniformBufferObject::UpdateLocalBuffer
(
	const void* sourceData,
	const UINT64 offsetInUniformBlock,
	const UINT64 sizeOfSourceData
)
{
	D_ASSERT(IsBufferGenerated() == true);
	D_ASSERT_LOG(static_cast<UINT64>(offsetInUniformBlock) + static_cast<UINT64>(sizeOfSourceData) <= mUniformBufferSize, "Updated data is out of range");

	if(IsBufferGenerated() == true)
	{
		D_ASSERT(mUniformBufferLocalBuffer);
		UpdateLocalBuffer_Internal(sourceData, offsetInUniformBlock, sizeOfSourceData);
		bmIsDirty = true;
	}
}


bool dooms::graphics::UniformBufferObject::IsBufferGenerated() const
{
	return mUniformBufferObject.IsValid();
}

