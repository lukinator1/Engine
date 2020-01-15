#pragma once
class MemoryHandler
{
	//implement double-ended stack allocator, single frame allocator, double buffer allocator
private:
	int stackallocatormarker;
	int getMarker();
	void freeToMarker(int &marker);
public:
	MemoryHandler();
	~MemoryHandler();
	void startUp();
	void shutDown();
	void * EngineAllocate();
	void clearStackAllocator();

};

