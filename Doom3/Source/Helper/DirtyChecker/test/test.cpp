#include <iostream>

#include "../DirtyReceiver.h"
#include "../DirtySender.h"

int main()
{
	{
		DirtySender sender{};
		DirtyReceiver receiver{};
		sender.AddDirtyReceiver(&receiver);
		sender.NotifyDirty();

		std::cout << "1 = " << receiver.GetIsDirty(true) << std::endl;
		std::cout << "0 = " << receiver.GetIsDirty(true) << std::endl;
	}

	{
		DirtySender sender{};
		DirtyReceiver receiver{};
		sender.RemoveDirtyReceiver(&receiver);

		std::cout << "1 = " << receiver.GetIsDirty(false) << std::endl;
		std::cout << "1 = " << receiver.GetIsDirty(false) << std::endl;
	}

	{
		DirtySender sender{};
		DirtyReceiver receiver{};
		sender.AddDirtyReceiver(&receiver);
		sender.RemoveDirtyReceiver(&receiver);
	}

	{
		DirtyReceiver receiver{};
		DirtySender sender{};
		
		sender.AddDirtyReceiver(&receiver);
	}
}