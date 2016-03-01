#include "edgeReader.hpp"
#include "nodeCollection.hpp"
#include "ClusterPlay.hpp"
#include "DBscanPlay.hpp"
#include <string>
#include <cstdlib>

int main(int argc, char* args[]){

	if(argc < 3){
		std::cerr<<"Error occured! please check the usage!"<<std::endl;
		std::cerr<<"usage : BlackHole.exe [Input] [Alpha] [MinPTS] [PruningPercents]"<<std::endl;
		std::cerr<<"example) ./BlackHole ./Data/football.dat 0.01 5 0.1"<<std::endl;
		return -1;
	}

	srand((unsigned int) time( NULL));


	// input parameter processing
	double alpha = atof(args[2]);

	int minPts = atoi(args[3]);

	double pruningFraction = atof(args[4]);

	// Layout
	ClusterPlay::play(args[1], alpha, args[2]);

	std::string fileName(args[1]);
	fileName.append("_position.out");

	// DBSCAN
	DBscanPlay::dbscanCalculator((char *)fileName.c_str(), minPts, pruningFraction/100.0f);

	return 0;
}
