#pragma once
#include <cstdlib>
#include "Engine.h"
class Memorymanager : public Logger
{
public:
	class DEStackAllocator {
	private:
		bool todelete = true;
	public:
		DEStackAllocator(int blocksize);  //engine configuration file?
		~DEStackAllocator();
		void* topAddress;
		void* bottomAddress;
		int topmarker;
		int bottommarker;
		void* newAllocator(unsigned int numberofbytes, size_t alignment);
		template <typename T>
		T* allignPointer(T* ptr, size_t align){	
			const uintptr_t address = reinterpret_cast<uintptr_t>(ptr);
			const uintptr_t addressAligned = allignBlock(address, align);
			return reinterpret_cast<T*>(addressAligned);
		};
		uintptr_t allignBlock(uintptr_t address, size_t align);
		int getTopMarker();
		int getBottomMarker();

		void engineDeallocate(void* userpointer);
		void clearAllocator();
		void deleteEngineAllocator(void * userallocation);
	};

	Memorymanager();
	~Memorymanager();

	/*void* engineAllocate(DEStackAllocator destack);*/

	/*DEStackAllocator newDEAllocator(int stacksize);*/
	void memoryManagerstartup(int stacksize);
	void memoryManagershutdown();
};
