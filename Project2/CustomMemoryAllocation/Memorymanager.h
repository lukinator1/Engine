#pragma once
#include <cstdlib>
#include "Engine.h"
#include <vector>
#include <map>
#include <iterator>
//maybe change the swapbuffers() function to use an array since it might increase performance
//improve syntax on engineallocate, take in template + no. elements instead? (sizeof(t) * elements)
class Memorymanager : public Logger
{
public:
	class StackAllocator {
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

		StackAllocator(int blocksize, size_t alignment);
		~StackAllocator();

		void engineAllocatorPop(void* userpointer);
		void engineDeallocateToMarker();
		void clearAllocator();
		void deleteStack();
	};

	class DBAllocator {
	public:
		bool first = false;
		StackAllocator firststackallocator;
		StackAllocator secondstackallocator;
		void swapBufferrs();
		void clearCurrentBuffer();
		void* engineAllocate(unsigned int numberofbytes, size_t alignment, bool setmarker);
		DBAllocator(int blocksize, size_t alignment);
		~DBAllocator();
	};

	Memorymanager();
	~Memorymanager();

	StackAllocator sfAllocator;
	DBAllocator dbAllocator;
	StackAllocator* newAllocator(int stacksize, size_t alignment);
	void deleteAllocator(StackAllocator* &userpointer);

	/*std::vector<void**> currentpointers;
	std::map<void*, std::pair<size_t,size_t>> pointermap;
	/*template <typename T>
	void* engineMalloc(size_t numberofbytes, T datatype) {
			void* engineblock = std::malloc(numberofbytes);
			std::pair <size_t, size_t> pair(ceil(_msize(engineblock) / sizeof(datatype)), _msize(engineblock));
			/*void** blockpointer = &engineblock;
			currentpointers.push_back(blockpointer)
			pointermap.emplace(engineblock, pair);
			return engineblock;
	}
	void engineDeallocate(void* userpointer);
	void engineDefragment();*/

	void memorymanagerUpdate();
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