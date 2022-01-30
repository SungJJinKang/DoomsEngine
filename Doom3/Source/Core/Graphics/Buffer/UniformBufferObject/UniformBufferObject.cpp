#include "UniformBufferObject.h"


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

dooms::graphics::UniformBufferObject::UniformBufferObject()
	:
	mUniformBufferObject(),
	mUniformBlockName(),
	mUniformBufferSize(0),
	mDefaultBindingPoint(0),
	mUniformBufferTempData()
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
	mUniformBufferTempData()
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
		mUniformBufferTempData = nullptr;

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
		mUniformBufferObject = GraphicsAPI::CreateBufferObject(GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, uniformBufferSize, initialData);

		mUniformBufferSize = uniformBufferSize;

		if (mUniformBufferTempData)
		{
			mUniformBufferTempData.reset();
		}

		mUniformBufferTempData = std::make_unique<UINT8[]>(uniformBufferSize);
		std::memset(mUniformBufferTempData.get(), 0x00, uniformBufferSize);
	}

}

void dooms::graphics::UniformBufferObject::DeleteBuffers()
{
	if(mUniformBufferObject.IsValid())
	{
		dooms::graphics::GraphicsAPI::DestroyBuffer(mUniformBufferObject);
		mUniformBufferObject.Reset();
	}

	if (mUniformBufferTempData != nullptr)
	{
		mUniformBufferTempData.reset();
	}

	mUniformBlockName.clear();
	mUniformBufferSize = 0;
	mDefaultBindingPoint = 0;
	mUniformVariableInfos.clear();
	
}

void dooms::graphics::UniformBufferObject::UpdateLocalBufferToGPU() noexcept
{
	D_ASSERT(IsBufferGenerated() == true);
	if ( (bmIsDirty == true) && (IsBufferGenerated() == true) )
	{
		D_ASSERT(mUniformBufferTempData);
		GraphicsAPI::UpdateDataToBuffer(mUniformBufferObject, GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, 0, mUniformBufferSize, mUniformBufferTempData.get());
		bmIsDirty = false;
	}
}

void dooms::graphics::UniformBufferObject::UpdateLocalBuffer
(
	const void* sourceData, 
	const UINT32 sizeOfSourceData, 
	const UINT32 offsetInUniformBlock,
	const bool instantlyUpdateToGPU
)
{
	D_ASSERT(IsBufferGenerated() == true);
	D_ASSERT_LOG(static_cast<UINT64>(offsetInUniformBlock) + static_cast<UINT64>(sizeOfSourceData) <= mUniformBufferSize, "Updated data is out of range");

	if(IsBufferGenerated() == true)
	{
		D_ASSERT(mUniformBufferTempData);
		std::memcpy(mUniformBufferTempData.get() + offsetInUniformBlock, sourceData, sizeOfSourceData);
		bmIsDirty = true;
	}
}


bool dooms::graphics::UniformBufferObject::IsBufferGenerated() const
{
	return mUniformBufferObject.IsValid();
}

