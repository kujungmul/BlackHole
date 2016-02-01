#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>      
#include <vector>
#include <cstring>
#include <cstdlib>
#include "nodeCollection.hpp"
#pragma once

class edgeReader{

private :
	std::ofstream outputFileStreamer;
	std::ifstream inputFile;
	std::ifstream inputFileTemp;

public :
	inline void readFile(char* filePath, nodeCollection* nodeCollector){
		inputFile.open(filePath);
		std::string line;
		std::string StrValX, StrValY, tempVariable;
		int maxValue, firstIdx, secondIdx;
		char oneLine[256];
		maxValue = 0;

		//To find max Value (to make dynamic array)
		if(inputFile.is_open()){
			int lineNumber = 0;
			while(getline(inputFile, line)){
				strcpy(oneLine,line.c_str());
				tempVariable = strtok(oneLine,"\t ");
				StrValX = tempVariable;
				StrValY = strtok(NULL,"\t ");
				lineNumber++;
				firstIdx = atoi(StrValX.c_str());
				secondIdx = atoi(StrValY.c_str());

				if ( firstIdx > secondIdx){
					if(firstIdx > maxValue){
						maxValue = firstIdx;
					}
				}
				else{
					if(secondIdx > maxValue){
						maxValue = secondIdx;
					}
				}
			}
		}
		else{
			std::cout<<"Error Occured!"<<std::endl;
		}

		nodeCollector->setDegMat(maxValue);	//Make degMatrix
		inputFile.seekg(0, inputFile.beg);		//to read again
		inputFile.close();
		inputFileTemp.open(filePath);

		//Setup!
		if(inputFileTemp.is_open()){
			while(getline(inputFileTemp, line)){
				strcpy(oneLine,line.c_str());
				tempVariable = strtok(oneLine,"\t ");
				StrValX = tempVariable;
				StrValY = strtok(NULL,"\t ");
				firstIdx = atoi(StrValX.c_str());
				secondIdx = atoi(StrValY.c_str());
				nodeCollector->putNode(firstIdx, secondIdx);
				nodeCollector->putNode(secondIdx, firstIdx);
				}
		}
		else{
			std::cout<<"Error Occured!"<<std::endl;
		}
		std::cout<<"####  FILE READ & SETUP FINISHED####"<<std::endl;
		inputFileTemp.close();
	}

	inline void writeFile(char* filePath, nodeCollection* ncp){
		outputFileStreamer.open(filePath);
		std::vector<blackHoleNode*>* vect = ncp->getNodeVec();
		for(unsigned int i = 0; i < (*vect).size(); i++){
			outputFileStreamer << (*vect)[i]->getID() << "\t";
			for (int p = 0; p < DIMESION; p++){
				outputFileStreamer << (*vect)[i]->getValue(p) << "\t";
			}
			outputFileStreamer <<(*vect)[i]->getClusterId()<<std::endl;
		}
		outputFileStreamer.close();
		std::cout<<"####  FILE WRITE FINISHED####"<<std::endl;
	}
};
