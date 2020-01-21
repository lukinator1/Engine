#include "Memorymanager.h"
Memorymanager::Memorymanager()
{
}
Memorymanager::~Memorymanager()
{
}
/*void* Memorymanager::engineAllocate(DEStackAllocator destack)
{
}*/
void Memorymanager::memoryManagerstartup()
{
}
void Memorymanager::memoryManagershutdown()
{
}
Memorymanager::DEStackAllocator::DEStackAllocator(int blocksize)
{
	memoryBlockAddress = std::malloc(blocksize);
	if (memoryBlockAddress == nullptr) {
		Logger::engineLog(__FILE__, __LINE__, "The memory block requested was too large, switching to default 600.)", 3, 1, true);
		memoryBlockAddress = std::malloc(600);
	}
}
Memorymanager::DEStackAllocator::~DEStackAllocator()
{
	if (todelete = true) {
		delete memoryBlockAddress;
	}
}
