#pragma once
#include <cstdlib>
#include "Engine.h"
#include <vector>
class Memorymanager : public Logger
{
public:
	class DEStackAllocator {
	private:
	public:
		int allocatorcapacity;
		int currentallocatorsize = 0;
		uint8_t* stackTop;
		uint8_t* bottomAddress;
		uint8_t* marker;
		void* engineAllocate(unsigned int numberofbytes, size_t alignment, bool setmarker);
		template <typename T>
		T* allignPointer(T* ptr, size_t align) {
			const uintptr_t address = reinterpret_cast<uintptr_t>(ptr);
			const uintptr_t addressAligned = allignBlock(address, align);
			return reinterpret_cast<T*>(addressAligned);
		};
		uintptr_t allignBlock(uintptr_t address, size_t align);
		uint8_t* getMarker();

		DEStackAllocator(int blocksize, size_t alignment);
		~DEStackAllocator();

		void engineAllocatorPop(void* userpointer);
		void engineDeallocateToMarker();
		void clearAllocator();
		void deleteStack();
	};

	Memorymanager();
	~Memorymanager();

	DEStackAllocator* newAllocator(int stacksize, size_t alignment);
	void deleteAllocator(DEStackAllocator* &userpointer);
	void memoryManagerstartup();
	void memoryManagershutdown();
};



/*#pragma once
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
		uint8_t* getMarker();

		void engineDeallocateToMarker(void* userpointer);
		void clearAllocator();
		void deleteAllocator(void * userallocation);
	};

	Memorymanager();
	~Memorymanager();
	void memoryManagerstartup();
	void memoryManagershutdown();
};*/
