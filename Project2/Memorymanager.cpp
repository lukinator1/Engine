#include "Memorymanager.h"
Memorymanager::Memorymanager()
{
}
Memorymanager::~Memorymanager()
{
}

Memorymanager::DEStackAllocator::DEStackAllocator(int blocksize)
{
}
Memorymanager::DEStackAllocator::~DEStackAllocator()
{
	if (todelete = true) {
		delete bottomAddress;
	}
}

void* Memorymanager::DEStackAllocator::newAllocator(unsigned int blocksize, size_t alignment)	//allignment must be power of two 
{
	const size_t checkpower = alignment - 1;
	if (((alignment & checkpower) != 0) || alignment < 2 || alignment > 128) {
		/*logging.engineLog(__FILE__, __LINE__, "The stack allocator wasn't created, alignment must be a power of 2, => 2 and <= 128. A nullptr was returned instead.", 3, 1, false);*/
		return nullptr;
	}
	size_t worstcasealignment = blocksize + alignment - 1;
	void * unalignedAddress = std::malloc(worstcasealignment);
	if (unalignedAddress == nullptr) {
		/*logging.engineLog(__FILE__, __LINE__, "The memory block requested was too large, switched to default size 600.)", 3, 1, true);*/
		unalignedAddress = std::malloc(600);
	}
	return allignPointer(unalignedAddress, alignment);
}
uintptr_t Memorymanager::DEStackAllocator::allignBlock(uintptr_t address, size_t align){
	size_t mask = align - 1;
	return (address + mask) & ~mask;
}

int Memorymanager::DEStackAllocator::getTopMarker()
{
		return topmarker;
}
int Memorymanager::DEStackAllocator::getBottomMarker()
{
		return bottommarker;
}

void * Memorymanager::DEStackAllocator::engineDeallocate()
{
	return nullptr;
}
void Memorymanager::DEStackAllocator::clearAllocator()
{
}
void Memorymanager::DEStackAllocator::deleteEngineAllocator(void * userallocation) //remove void pointer?
{
	delete bottomAddress;
	delete userallocation;
	todelete = false;
}

/*Memorymanager::DEStackAllocator Memorymanager::newDEAllocator(int stacksize)
{
	return DEStackAllocator(stacksize);
}*/
void Memorymanager::memoryManagerstartup(int stacksize)
{
	DEStackAllocator enginestack(stacksize);
}
void Memorymanager::memoryManagershutdown()
{
}
