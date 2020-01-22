#include "Memorymanager.h"
Memorymanager::Memorymanager()
{
}
Memorymanager::~Memorymanager()
{
}

Memorymanager::DEStackAllocator::DEStackAllocator(int blocksize)
{
	/*void * monkey = std::malloc()*/
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
	if (((alignment & checkpower) != 0) || alignment < 2 || alignment > 256) {
		engineLog(__FILE__, __LINE__, "The stack allocator wasn't created, alignment must be a power of 2, => 2 and <= 256. A nullptr was returned instead.", 3, 1, false);
		return nullptr;
	}
	size_t worstcasealignment = blocksize + alignment;
	uint8_t* unalignedAddress = new uint8_t[worstcasealignment];
	if (unalignedAddress == nullptr) {
		engineLog(__FILE__, __LINE__, "The memory block requested was too large, switched to default size 600.)", 3, 1, true);
		unalignedAddress = new uint8_t[600];
	}
	uint8_t* allignedPointer = allignPointer(unalignedAddress, alignment);
	if (allignedPointer = unalignedAddress) {	//if no aligning took place
		allignedPointer += alignment;
	}
	__int64 shift = allignedPointer - unalignedAddress;
	allignedPointer[-1] = static_cast<uint8_t>(shift & 0xFF);
	return allignedPointer;
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

void Memorymanager::DEStackAllocator::engineDeallocate(void * userpointer)
{
	if (userpointer == nullptr){
		engineLog(__FILE__, __LINE__, "You tried to deallocate a nullptr. Deallocation didn't go through.", 3, 1, false);
}
	else {
		uint8_t* alignedpointer = reinterpret_cast<uint8_t*>(userpointer);
		__int64 shift = alignedpointer[-1];
		if (shift == 0) {
			shift = 256;
		}
		uint8_t* unalignedpointer = alignedpointer - shift;
		delete[] unalignedpointer;
	}
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
