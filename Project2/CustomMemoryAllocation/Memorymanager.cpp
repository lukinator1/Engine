#include "Memorymanager.h"
Memorymanager::Memorymanager(int sfsize = 500, int sfalignment = 8, int dbsize = 500, int dbalignment = 8) : sfAllocator(sfsize, sfalignment), dbAllocator(dbsize, dbalignment)
{
}
Memorymanager::StackAllocator::StackAllocator(int blocksize = 600, size_t alignment = 8) {
	const size_t checkpower = alignment - 1;
	if (((alignment & checkpower) != 0) || alignment < 2 || alignment > 256) {
		engineLog(__FILE__, __LINE__, "The stack allocator wassn't created, the alignment must be a power of 2, => 2 and <= 256. A nullptr was returned instead.", 3, 1, false);
	}
	else {
		size_t worstcasealignment = blocksize + alignment;
		allocatorcapacity = blocksize;
		bottomAddress = new uint8_t[blocksize];
		if (bottomAddress == nullptr) {
			engineLog(__FILE__, __LINE__, "The memory block requested was too large, switched to default size 600.)", 3, 1, true);
			bottomAddress = new uint8_t[600];
			allocatorcapacity = 600;
		}
		else {
			allocatorcapacity = blocksize;
		}
		uint8_t* allignedPointer = allignPointer(bottomAddress, alignment);
		if (allignedPointer = bottomAddress) {	//if no aligning took place
			allignedPointer += alignment;
		}
		__int64 shift = allignedPointer - bottomAddress;
		allignedPointer[-1] = static_cast<uint8_t>(shift & 0xFF);
		stackTop = allignedPointer;
		marker = stackTop;
	}
}
Memorymanager::StackAllocator::~StackAllocator()
{
}

void* Memorymanager::StackAllocator::engineAllocate(unsigned int blocksize, size_t alignment, bool setmarker = false)	//allignment must be power of two 
{
	if (blocksize < 2) {
		engineLog(__FILE__, __LINE__, "The blocksize was invalid, please use only unsigned integers. A nullptr was returned instead.", 3, 1, false);
		return nullptr;
	}
	const size_t checkpower = alignment - 1;
	if (((alignment & checkpower) != 0) || alignment < 2 || alignment > 256) {
		engineLog(__FILE__, __LINE__, "The memory block didn't allocate. alignment must be a power of 2, => 2 and <= 256. A nullptr was returned instead.", 3, 1, false);
		return nullptr;
	}
	size_t worstcasealignment = blocksize + alignment;
	if (worstcasealignment + currentallocatorsize > allocatorcapacity) {
		engineLog(__FILE__, __LINE__, "The allocator is out of space, the allocation didn't go through. A nullptr was returned instead.", 3, 1, true);
		std::cout << "Current allocator capacity: " << currentallocatorsize << std::endl;
		return nullptr;
	}
	currentallocatorsize += worstcasealignment;

	uint8_t* unalignedAddress = stackTop;
	stackTop = &stackTop[worstcasealignment];
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
uintptr_t Memorymanager::StackAllocator::allignBlock(uintptr_t address, size_t align) {
	size_t mask = align - 1;
	return (address + mask) & ~mask;
}
uint8_t* Memorymanager::StackAllocator::getMarker()
{
	return marker;
}
void Memorymanager::StackAllocator::engineAllocatorPop(void* userpointer)
{
	uint8_t* alignedpointer = reinterpret_cast<uint8_t*>(marker);
	__int64 shift = alignedpointer[-1];
	if (shift == 0) {
		shift = 256;
	}
	uint8_t* unalignedpointer = alignedpointer - shift;
	stackTop = unalignedpointer;
	currentallocatorsize = stackTop - bottomAddress;
}

void Memorymanager::StackAllocator::engineDeallocateToMarker()
{ 
	stackTop = marker;
	currentallocatorsize = stackTop - bottomAddress;
}
void Memorymanager::StackAllocator::clearAllocator()
{
	marker = bottomAddress;
	stackTop = bottomAddress;
	currentallocatorsize = 0;
}
void Memorymanager::StackAllocator::deleteStack() //remove void pointer?
{
	if (bottomAddress == nullptr) {
		engineLog(__FILE__, __LINE__, "The stackaddress got set to nullptr somehow, the deallocation didn't go through. ", 3, 1, false);
		return;
	}
	this->clearAllocator();
	delete[] bottomAddress;
}


void Memorymanager::DBAllocator::swapBufferrs()
{
	first = !first;
}
void Memorymanager::DBAllocator::clearCurrentBuffer()
{
	if (first) {
		firststackallocator.clearAllocator();
	}
	else {
		secondstackallocator.clearAllocator();
	}
}
void * Memorymanager::DBAllocator::engineAllocate(unsigned int numberofbytes, size_t alignment, bool setmarker)
{
	if (first) {
		return firststackallocator.engineAllocate(numberofbytes, alignment, setmarker);
	}
	else {
		return secondstackallocator.engineAllocate(numberofbytes, alignment, setmarker);
	}
}
Memorymanager::DBAllocator::DBAllocator(int blocksize, size_t alignment) : firststackallocator(blocksize, alignment), secondstackallocator(blocksize, alignment)
{
}
Memorymanager::DBAllocator::~DBAllocator()
{
}


Memorymanager::StackAllocator* Memorymanager::newAllocator(int stacksize, size_t alignment)
{
	StackAllocator* allocator = new StackAllocator{ {stacksize}, {alignment} };
	return allocator;
}
void Memorymanager::deleteAllocator(StackAllocator* &userpointer) {
	if (userpointer == nullptr) {
		engineLog(__FILE__, __LINE__, "The pointer to the stack allocator got set to nullptr, the deallocatation didn't go through. ", 3, 1, true);
		return;
	}
	userpointer->deleteStack();
	delete userpointer;
}
/*void* Memorymanager::engineMalloc(size_t numberofbytes, T datatype)
{
	void* engineblock = std::malloc(numberofbytes);

	void* blockpointer = &engineblock;
	if (pointermap.size() != 1) {
	}
	return engineblock;
}
/*void Memorymanager::engineDefragment() {
	/*for (int i = 0; i < currentpointers.size() - 1; i++) {
		int distance = (int)currentpointers[i + 1] - (int)currentpointers[i];
		if currentpointers[i]
		if ((int)currentpointers[i + 1] - (int)currentpointers[i] > 
	}
	if (pointermap.size() >= 2) {
		int currentblock = 0;
		auto u = pointermap.begin();
		u++;		
		int counter = 0;
		bool swapped = false;
		while (counter < 9 && swapped == false) {
			swapped = true;
			/*currentblock = 0;
			for (auto i = pointermap.begin(); u != pointermap.end(); i++, u++) {
					if (((int)(u->first) - (int)(i->first)) > (std::get<0>(i->second))){
					memmove((void *)(((int)i->first) + (int)std::get<0>(i->second)), u->first, std::get<1>(u->second));
					swapped = true;
					counter++;
				}
				/*currentblock++;
			}
		}
	}
}*/
/*void Memorymanager::engineDeallocate(void * userpointer) {
	for (auto i = pointermap.begin(); i != pointermap.end(); i++) {
		if (i->first == userpointer) {
			delete i->first;
			pointermap.erase(i);
			return;
		}
	}
}/**/

void Memorymanager::memorymanagerUpdate() {
	sfAllocator.clearAllocator();
	dbAllocator.swapBufferrs();
	dbAllocator.clearCurrentBuffer();
}
void Memorymanager::memoryManagerstartup()
{
}
void Memorymanager::memoryManagershutdown()
{
	sfAllocator.deleteStack();
	dbAllocator.firststackallocator.deleteStack();
	dbAllocator.secondstackallocator.deleteStack();
}

Memorymanager::~Memorymanager()
{
}






/*#include "Memorymanager.h"
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
	/*uint8_t* unalignedAddress = stackTop[worstcasealignment];
	/*if (unalignedAddress == nullptr) {
		engineLog(__FILE__, __LINE__, "The memory block requested was too large, switched to default size 600.)", 3, 1, true);
		unalignedAddress = new uint8_t[600];
	}
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
}
uint8_t* Memorymanager::DEStackAllocator::getMarker()
{
		return marker;
}

void Memorymanager::DEStackAllocator::engineDeallocateToMarker(void * marker)
{
		/*	if (marker == nullptr){
		engineLog(__FILE__, __LINE__, "The marker is nullptr. Deallocation didn't go through.", 3, 1, false);
}
		uint8_t* alignedpointer = reinterpret_cast<uint8_t*>(marker);
		__int64 shift = alignedpointer[-1];
		if (shift == 0) {
			shift = 256;
		}
		uint8_t* unalignedpointer = alignedpointer - shift;
		/*delete[] unalignedpointer;
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

Memorymanager::DEStackAllocator Memorymanager::newDEAllocator(int stacksize)
{
	return DEStackAllocator(stacksize);
}
void Memorymanager::memoryManagerstartup(int stacksize)
{
	DEStackAllocator enginestack(stacksize);
}
void Memorymanager::memoryManagershutdown()
{
}
*/
