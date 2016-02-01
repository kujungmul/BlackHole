#include <iostream>
#ifndef _MEM_H_
#define _MEM_H_
#include <vector>

class OctTree;

class memoryManager{
private :
	int current;
	int child_current;
	int prior;
	int maxNum;
	OctTree* temp;
	std::vector<OctTree**> childVec;

public :
	memoryManager(int nodeNum);
	OctTree* get_Instance();
	OctTree** get_children();
	void dealloc();
	int getCurrent();
	int getChildCurrent();
	void setCurrent(int x);
	void setChildCurrent(int x);
	void takeAPicture();
	void restore();
	void swap(OctTree* swapper);
};

#endif
