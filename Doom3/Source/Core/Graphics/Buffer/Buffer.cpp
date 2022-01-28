#include "Buffer.h"

void dooms::graphics::Buffer::OnSetPendingKill()
{
	DObject::OnSetPendingKill();
	
}

dooms::graphics::Buffer::Buffer() = default;
dooms::graphics::Buffer::~Buffer() = default;
dooms::graphics::Buffer::Buffer(Buffer&& buffer) noexcept = default;
dooms::graphics::Buffer& dooms::graphics::Buffer::operator=(Buffer&& buffer) noexcept = default;