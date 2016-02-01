#include <set>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
#include <algorithm>
#include "Util.hpp"

#pragma once

class node{
protected :
	int nodeId;
	double points[DIMESION];

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
	blackHoleNode();
	blackHoleNode(int nNodeId);
	blackHoleNode(int nNodeId, int other);
	void setNode(int nI, double* ar);
	void setClusterId(int x);
	int getClusterId();
	bool isnot_labeled();
	bool setEdge(int other);
	void increaseDegree();
	int getDegree();
	double* getValues();
	void setDegree(int x);
	std::vector<int>* getEdgeSet();
	inline bool operator<(const blackHoleNode& i) const{
		return nodeId < i.getID();	
	};
	bool findEdge(int origin, int id);
};
