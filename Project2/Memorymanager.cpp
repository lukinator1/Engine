#include "Memorymanager.h"
Memorymanager::Memorymanager()
{
}
Memorymanager::~Memorymanager()
{
}

Memorymanager::DEStackAllocator::DEStackAllocator(int blocksize)
{
	bottomAddress = new uint8_t[blocksize];
	if (bottomAddress == nullptr) {
		engineLog(__FILE__, __LINE__, "The memory block requested was too large, switched to default size 600.)", 3, 1, true);
		bottomAddress = new uint8_t[600];
		allocatorcapacity = 600;
	}
	else {
		allocatorcapacity = blocksize;
	}
	stackTop = bottomAddress;
}
Memorymanager::DEStackAllocator::~DEStackAllocator()
{
	if (todelete = true) {
		delete bottomAddress;
	}
}

void* Memorymanager::DEStackAllocator::engineAllocate(unsigned int blocksize, size_t alignment, bool setmarker = false)	//allignment must be power of two 
{
	const size_t checkpower = alignment - 1;
	if (((alignment & checkpower) != 0) || alignment < 2 || alignment > 256) {
		engineLog(__FILE__, __LINE__, "The memory block didn't allocate. alignment must be a power of 2, => 2 and <= 256. A nullptr was returned instead.", 3, 1, false);
		return nullptr;
	}

	size_t worstcasealignment = blocksize + alignment;
	currentallocatorsize += worstcasealignment;
	if (blocksize + currentallocatorsize > allocatorcapacity) {
		engineLog(__FILE__, __LINE__, "The allocator is out of space, the allocation didn't go through. A nullptr was returned.)", 3, 1, true);
		std::cout << "Current allocator capacity: " << currentallocatorsize << std::endl;
		 }
	uint8_t* unalignedAddress = stackTop;
	stackTop = &stackTop[worstcasealignment];
	/*uint8_t* unalignedAddress = stackTop[worstcasealignment];*/
	/*if (unalignedAddress == nullptr) {
		engineLog(__FILE__, __LINE__, "The memory block requested was too large, switched to default size 600.)", 3, 1, true);
		unalignedAddress = new uint8_t[600];
	}*/
	uint8_t* allignedPointer = allignPointer(unalignedAddress, alignment);
	if (allignedPointer = unalignedAddress) {	//if no aligning took place
		allignedPointer += alignment;
	}
	__int64 shift = allignedPointer - unalignedAddress;
	allignedPointer[-1] = static_cast<uint8_t>(shift & 0xFF);
	if (setmarker == true) {
		marker = stackTop;
	}
	return allignedPointer;
}
uintptr_t Memorymanager::DEStackAllocator::allignBlock(uintptr_t address, size_t align){
	size_t mask = align - 1;
	return (address + mask) & ~mask;
}
/*int Memorymanager::DEStackAllocator::getTopMarker()
{
		return topmarker;
}*/
uint8_t* Memorymanager::DEStackAllocator::getMarker()
{
		return marker;
}

void Memorymanager::DEStackAllocator::engineDeallocateToMarker(void * marker)
{
		/*	if (marker == nullptr){
		engineLog(__FILE__, __LINE__, "The marker is nullptr. Deallocation didn't go through.", 3, 1, false);
}*/
		uint8_t* alignedpointer = reinterpret_cast<uint8_t*>(marker);
		__int64 shift = alignedpointer[-1];
		if (shift == 0) {
			shift = 256;
		}
		uint8_t* unalignedpointer = alignedpointer - shift;
		/*delete[] unalignedpointer;*/
		stackTop = unalignedpointer;
}
void Memorymanager::DEStackAllocator::clearAllocator()
{
	marker = bottomAddress;
	stackTop = bottomAddress;
	currentallocatorsize = 0;
}
void Memorymanager::DEStackAllocator::deleteAllocator(void * userallocation) //remove void pointer?
{
	delete[] bottomAddress;
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
