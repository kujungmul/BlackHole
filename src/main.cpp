#include "edgeReader.hpp"
#include "nodeCollection.hpp"
#include "ClusterPlay.hpp"
#include "DbscanPlay.hpp"
#include <string>
#include <cstdlib>


int main(int argc, char* args[]){

	if(argc < 3){
		std::cerr<<"Error occured! please check the usage!"<<std::endl;
		std::cerr<<"usage : BlackHole.exe [Input] [Alpha]"<<std::endl;
		return -1;
	}

	double alpha = atof(args[2]);
	srand((unsigned int) time( NULL));

	ClusterPlay::play(args[1], alpha, args[2]);

	std::string fileName(args[1]);
	fileName.append("_position.out");


	DBscanPlay::dbscanCalculator((char *)fileName.c_str(), 5, 0.1/100.0f);

// 	if (strcmp(args[1], "dbscan") == 0){
//		if (argc != 5){
//			std::cout << "Check parameter!" << std::endl;
//			std::cout << "dbscan filename minPts removePercentage" << std::endl;
//			std::cout << "dbscan filename minPts 0.1(means 0.1%)" << std::endl;
//			return 0;
//		}
//		//dbscanCalculator(args[2], atoi(args[3]), atof(args[4]) / 100.0f);
//	}


	return 0;
}
