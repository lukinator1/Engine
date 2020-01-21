#pragma once
#include <cstdlib>
#include "Logger.h"
class Memorymanager
{
private:
	class DEStackAllocator {
	private:
		bool todelete = true;
	public:
		DEStackAllocator(int blocksize);  //engine configuration file?
		~DEStackAllocator();

		void* memoryBlockAddress;
		int topmarker;
		int bottommarker;

		void* engineAllocate(unsigned int numberofbytes) {
			
		}
		int getTopMarker() {
			return topmarker;
		}
		int getBottomMarker() {
			return bottommarker;
		}

		void engineDeallocate() {
		}
		void clearAllocator() {

		}
		void deleteEngineAllocator(void * userallocation) { //remove void pointer?
			delete memoryBlockAddress;
			delete userallocation;
			todelete = false;
		}
	};

	Memorymanager();
	~Memorymanager();

	/*void* engineAllocate(DEStackAllocator destack);*/

	void memoryManagerstartup();
	void memoryManagershutdown();

};

