#include "Util.hpp"
#include <set>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
#include <algorithm>

#pragma once

class node{
protected :
	int nodeId;
	double points[DIMENSION];

public :
	bool setPosition(int nLabel, double* ar);
	double getValue(int idx);
	void setValue(double value,int idx);
	int getID() const;
	
};

class blackHoleNode : public node {
private :
	int clusterId;
	int degree;
	std::vector<int> eSet;
public :
	blackHoleNode(int nNodeId, int other);
	void setClusterId(int x);
	int getClusterId();
	bool isnot_labeled();
	bool setEdge(int other);
	int getDegree();
	double* getValues();
	void setDegree(int x);
	std::vector<int>* getEdgeSet();
	inline bool operator<(const blackHoleNode& i) const{
		return nodeId < i.getID();	
	};
	bool findEdge(int origin, int id);
};
