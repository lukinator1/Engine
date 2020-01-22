#pragma once
#include <cstdlib>
#include "Engine.h"
class Memorymanager : public Logger
{
public:
	class DEStackAllocator {
	private:
		bool todelete = true;
		int allocatorcapacity;
		int currentallocatorsize = 0;
	public:
		DEStackAllocator(int blocksize);  //engine configuration file?
		~DEStackAllocator();
		uint8_t* stackTop;
		uint8_t* bottomAddress;
		int topmarker;
		uint8_t* marker;
		void* engineAllocate(unsigned int numberofbytes, size_t alignment, bool setmarker);
		template <typename T>
		T* allignPointer(T* ptr, size_t align){	
			const uintptr_t address = reinterpret_cast<uintptr_t>(ptr);
			const uintptr_t addressAligned = allignBlock(address, align);
			return reinterpret_cast<T*>(addressAligned);
		};
		uintptr_t allignBlock(uintptr_t address, size_t align);
		/*int getTopMarker();*/
		uint8_t* getMarker();

		void engineDeallocateToMarker(void* userpointer);
		void clearAllocator();
		void deleteAllocator(void * userallocation);
	};

	Memorymanager();
	~Memorymanager();

	/*void* engineAllocate(DEStackAllocator destack);*/

	/*DEStackAllocator newDEAllocator(int stacksize);*/
	void memoryManagerstartup(int stacksize);
	void memoryManagershutdown();
};
