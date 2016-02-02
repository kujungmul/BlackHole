#include <iostream>
#include <iomanip>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include "exponentVar.hpp"
#include "octTree.hpp"

#pragma once

struct by_id { 
    bool operator()(blackHoleNode* const &a, blackHoleNode* const &b) const {
        return a->getID() < b->getID();
    }
};

class nodeCollection{
private :
	std::map<int, blackHoleNode*> nodeMap;
	std::vector<blackHoleNode*> nodeVec;
	int* degMat;
	float** adjMat;
public :
	void putNode(int nNodeId, int other);
	//void setClear();
	void clearAll();
	void copyToVector();	
	bool checkEdge(int id1_notMinus, int id2_notMinus);
	void setAdjMat(int maxValue);
	void setDegMat(int maxValue);
	int getSumOfDegree();
	bool checkExists(int nID);
	void degreeSet();
	void clearClusterId();
	void canopyClustering(double threshold);
	void putEdge(int a, int b);
	std::vector<blackHoleNode*>* getNodeVec();
	std::map<int, blackHoleNode*>& getNodeMap();

	//Classic
	double addRepulsionDir(blackHoleNode* unp, double* dir, exponentVar& expVar);
	double addAttractionDir(blackHoleNode* unp, double* dir, exponentVar& expVar);
	void setDir(blackHoleNode* unp, double* dir,  exponentVar& expVar);
	double getEnergy(blackHoleNode* unp, exponentVar& expVar);
	double getEnergyR(blackHoleNode* unp , exponentVar& expVar);
	double getEnergyA(blackHoleNode* unp , exponentVar& expVar);
	double findInitEnergy(exponentVar& expVar);
	//
	//Barneshut
	double addRepulsionDir(blackHoleNode* unp, double* dir, exponentVar& expVar,OctTree* octTree);
	double addAttractionDir(blackHoleNode* unp, double* dir, exponentVar& expVar,OctTree* octTree);
	void setDir(blackHoleNode* unp, double* dir,  exponentVar& expVar,OctTree* octTree);
	double getEnergy(blackHoleNode* unp, exponentVar& expVar,OctTree* octTree);
	double getEnergyR(blackHoleNode* unp , exponentVar& expVar,OctTree* octTree);
	double getEnergyA(blackHoleNode* unp , exponentVar& expVar, OctTree* octTree);
	double findInitEnergy(exponentVar& expVar, OctTree* octTree);

	//Advanced Version
	double addAttractionDirA(blackHoleNode* unp, double* dir, exponentVar& expVar,OctTree* octTree);
	double getEnergyAA(blackHoleNode* unp , exponentVar& expVar, OctTree* octTree);
};
