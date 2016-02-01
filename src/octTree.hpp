#ifndef _OCT_H_
#define _OCT_H_

#define DIMESION 3

#include "blackHoleNode.hpp"

class memoryManager;

class OctTree{
public :
	static const int MAX_DEPTH = 18;	// Max Tree Depth
	blackHoleNode* node;
	OctTree** children;
	int childCount;
	int childLength;
	double position[DIMESION];
	double weight;
	double minPos[DIMESION];
	double maxPos[DIMESION];

public :

	OctTree();

	OctTree(blackHoleNode* node, double* position, double* minPos, double* maxPos);

	void setElement(blackHoleNode* node, double* position, double* minPos, double* maxPos, memoryManager* mgr);

	double getPosX();

	double getPosY();

	double* getValues();

	blackHoleNode* getNode();

	int getLength();

	void LengthIncrease();

	double getWeight();

	bool getUsed();

	void addNode(blackHoleNode* newNode, double* newPos, int depth, memoryManager* mgr);

	void addNode2(blackHoleNode* newNode, double* newPos, int depth, memoryManager* mgr, bool st);

	double getWidth();

	int getHeight();

	void removeNode(blackHoleNode* oldNode, double* oldPos, int depth, memoryManager* mgr);

	void clearMemory();
	 
	void clearMemory(OctTree* p);
};

#endif
