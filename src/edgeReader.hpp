#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>      
#include <vector>
#include <cstring>
#include <cstdlib>
#include "nodeCollection.hpp"
#define DIMENSION 2
#pragma once

class edgeReader{
private :
	std::ofstream ofs;
	std::ifstream ifs;
	std::ifstream iifs;
public :
	inline void readFile(char* filePath, nodeCollection* ncp){
		ifs.open(filePath);
			std::string line;
			std::string x, y, del;
			int maxValue, a, b;
			char oneLine[256];
			maxValue = 0;

			//To find max Value (to make dynamic array)
			if(ifs.is_open()){
				int lineNumber = 0;
				while(getline(ifs, line)){
					//getline(ifs, line);

					strcpy(oneLine,line.c_str());
					del = strtok(oneLine,"\t ");
					x = del;
					y = strtok(NULL,"\t ");
					lineNumber++;
					a = atoi(x.c_str());
					b = atoi(y.c_str());
					
					if ( a > b){
						if(a > maxValue){
							maxValue = a;}
					}
					else{
						if(b > maxValue){
							maxValue = b;}
					}
				}
			}
			else{
				std::cout<<"Error Occured!"<<std::endl;
			}

			//ncp->setAdjMat(maxValue);	//Make matrix
			ncp->setDegMat(maxValue);	//Make degMatrix
			ifs.seekg(0, ifs.beg);		//to read again
			ifs.close();
			//ifs.open(filePath);
			iifs.open(filePath);
			//Setup!
			int i = 0; 
			if(iifs.is_open()){
				while(getline(iifs, line)){	
					strcpy(oneLine,line.c_str());
					del = strtok(oneLine,"\t ");
					x = del;
					y = strtok(NULL,"\t ");
					a = atoi(x.c_str());
					b = atoi(y.c_str());

					ncp->putNode(a, b);
					ncp->putNode(b, a);
					}
			}
			else{
				std::cout<<"Error Occured!"<<std::endl;
			}
			std::cout<<"####  FILE READ & SETUP FINISHED####"<<std::endl;
			iifs.close();
			
	}

	inline void writeFile(char* filePath, nodeCollection* ncp){
		ofs.open(filePath);
		std::vector<blackHoleNode*>* vect = ncp->getNodeVec();
		for(unsigned int i = 0; i < (*vect).size(); i++){
			ofs << (*vect)[i]->getID() << "\t";
			for (int p = 0; p < DIMENSION; p++){
				ofs << (*vect)[i]->getValue(p) << "\t";
			}
			ofs <<(*vect)[i]->getClusterId()<<std::endl;
			//std::cout<<(*vect)[i]->getID()<<"  "<<(*vect)[i]->getX()<<"\t"<<(*vect)[i]->getY()<<std::endl;
		
		}

		//std::cout<<"####  FILE WRITE FINISHED####"<<std::endl;
		ofs.close();
	}
};
