

#include <sys/time.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <utility>



const double PI = 3.141592653589793238463;

class dbScanPoint{
	public:
		float x;
		float y;
		float z;
};

class DbscanPlay{
public :


	static double  calcDist(double dX0, double dY0, double dX1, double dY1, double dZ0, double dZ1){
		return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0) + (dZ1 - dZ0)*(dZ1 - dZ0));
	}

	static void  dbscanCalculator(char * inputFile, int minPts, float removePercentage){

		clock_t start_time, end_time;	  // clock_t
		start_time = clock();				  // Start_Time
		std::ifstream nodeCmty; 	std::ifstream nodeCmty2;
		std::ofstream ofs;		std::ofstream distanceofs;
		std::string str(inputFile);

		std::stringstream out;
		out << minPts;

		std::ostringstream streamer;
		streamer << removePercentage * 100;
		std::string removeP(streamer.str());

		nodeCmty.open(inputFile);
		std::string line;
		std::string x, y, z, del, cluster;
		int nodeNum = 0;
		int nid;
		int maxValue, nodeNumber;
		char oneLine[256];
		maxValue = 0;
		nodeNumber = 0;
		maxValue = 0;
		if (nodeCmty.is_open()){//calc maximal cluster size
			while (getline(nodeCmty, line)){
				strcpy(oneLine, line.c_str());
				del = strtok(oneLine, "\t ");
				x = strtok(NULL, "\t ");
				y = strtok(NULL, "\t ");
				nodeNum++;
			}
		}
		else{
			std::cout << "can't read file" << std::endl;
		}


		nodeCmty.close();
		nodeCmty2.open(inputFile);

		int* communitySelf = new int[nodeNum];
		float* X = new float[nodeNum];
		float* Y = new float[nodeNum];
		float* Z = new float[nodeNum];
		bool* visited = new bool[nodeNum];
		int* countN = new int[nodeNum];
		int* cmty = new int[nodeNum];
		bool* isSeed = new bool[nodeNum];
		for (int i = 0; i < nodeNum; i++){
			X[i] = 0.0f;
			Y[i] = 0.0f;
			Z[i] = 0.0f;
			visited[i] = false;
			countN[i] = 0;
			cmty[i] = -1;
			isSeed[i] = false;
		}
		int tmo = 0;
		if (nodeCmty2.is_open()){
			while (getline(nodeCmty2, line)){
				strcpy(oneLine, line.c_str());
				del = strtok(oneLine, "\t ");
				x = strtok(NULL, "\t ");
				y = strtok(NULL, "\t ");
				z = strtok(NULL, "\t ");
				X[tmo] = atof(x.c_str());
				Y[tmo] = atof(y.c_str());
				Z[tmo] = atof(z.c_str());

				tmo++;
			}
		}

		else{
			std::cout << "can't read file" << std::endl;
		}

		std::cout << "Step 2\t";

		float* dist_vec = new float[nodeNum];
		float* dist_sorted = new float[nodeNum];
		float eps;

		for (int i = 0; i < nodeNum; i++){
			for (int j = 0; j < nodeNum; j++){
				dist_sorted[j] = calcDist(X[i], Y[i], X[j], Y[j], Z[i], Z[j]);		//precalc
			}
			std::sort(dist_sorted, dist_sorted + nodeNum);
			dist_vec[i] = dist_sorted[minPts - 1];
		}

		//##############################################################
		//To Select EPS
		//##############################################################

		std::sort(dist_vec, dist_vec + nodeNum, std::greater< float>());

		std::cout << "Step 3\t";


		//NORMALIZATION ********************
		//Removing outlier to maximal value

		double trunc = (nodeNum * removePercentage);
		int tr = (int)trunc;
		std::cout << "Truncated # = " << tr << std::endl;

		for (int i = 0; i < tr; i++){
			dist_vec[i] = 0;
		}

		std::sort(dist_vec, dist_vec + nodeNum, std::greater< float>());


		//**********************************


		std::cout << inputFile << std::endl;


		std::string outputdistance = str + "_MinPts_" + out.str() + "_RemovePercent_" + removeP + "_distance.dat";
		distanceofs.open(outputdistance.c_str());
		for (int i = 0; i < nodeNum; i++){
			distanceofs << i + 1 << "\t" << dist_vec[i] << std::endl;
		}

		distanceofs.close();



		//Save to point array
		dbScanPoint* original = new dbScanPoint[nodeNum];
		for (int i = 0; i < nodeNum; i++){
			original[i].x = i;
			original[i].y = dist_vec[i];
		}
		std::cout << "Step 4\t";


		//find minVal, maxVal of Y
		float maxVal = -1;
		float minVal = 999999;
		for (int i = 0; i < nodeNum; i++){
			if (original[i].y >= maxVal){
				maxVal = original[i].y;
			}
			if (original[i].y <= minVal){
				minVal = original[i].y;
			}
		}
		//min-max normalization
		//std::cout<<"original value = "<<std::endl;
		for (int i = 0; i < nodeNum; i++){
			original[i].x = ((original[i].x - 0) / nodeNum) * 1;
			original[i].y = ((original[i].y - minVal) / (maxVal - minVal));
			// std::cout<<original[i].x<<"\t"<<original[i].y<<std::endl;
		}

		//std::cout<<"################################"<<std::endl;
		//std::cout<<"rotated value = "<<std::endl;
		for (int i = 0; i < nodeNum; i++){
			original[i].x = cos(-PI / 4.0f) * original[i].x + sin(-PI / 4.0f)*(original[i].y - 1.0f);
			original[i].y = -sin(-PI / 4.0f) * original[i].x + cos(-PI / 4.0f)*(original[i].y - 1.0f);
			//std::cout<<original[i].x<<"\t"<<original[i].y<<std::endl;
		}
		int minValue = 9999;
		int minValueIdx = -1;
		for (int i = 0; i < nodeNum; i++){
			if (original[i].y <= minVal){
				minVal = original[i].y;
				minValueIdx = i;
			}
		}

		std::cout << "rotated minValue = " << minVal << std::endl;
		std::cout << "rotated minValue idx = " << minValueIdx << std::endl;
		std::cout << "dist_vec[minidx] = " << dist_vec[minValueIdx] << std::endl;
		eps = dist_vec[minValueIdx];
		std::cout << "Step 5\t";


		delete  dist_sorted;
		delete  dist_vec;



		std::cout << "Step 6\t";

		//##############################################################
		//Algorithm Start
		//##############################################################

		for (int i = 0; i < nodeNum; i++){
			for (int j = 0; j < nodeNum; j++){
				if (calcDist(X[i], Y[i], X[j], Y[j], Z[i], Z[j]) <= eps){
					countN[i]++;
				}
			}
		}


		int currentCmty = 0;

		int icmty;

		std::set< int> setN;

		for (int i = 0; i < nodeNum; i++){
			visited[i] = true;   //Mark P as visited

			setN.clear();

			if (countN[i] >= minPts){   //NeighborPts = regionQuery(P, eps)
				isSeed[i] = true;

				if (cmty[i] == -1){
					cmty[i] = ++currentCmty;
				}
				icmty = cmty[i];

				for (int j = 0; j < nodeNum; j++){  //insert one hop
					if (i == j)
						continue;

					if (calcDist(X[i], Y[i], X[j], Y[j], Z[i], Z[j]) <= eps){
						setN.insert(j);
						if (countN[j] >= minPts){
							isSeed[j] = true;
						}
					}
				}


				for (std::set<int >::iterator IterPos = setN.begin(); IterPos != setN.end();){
					IterPos = setN.begin();

					int cur = *IterPos;
					setN.erase(IterPos++);
					if (visited[cur] == false){
						visited[cur] = true;
						for (int k = 0; k < nodeNum; k++){
							if (cur == k)
								continue;

							if (calcDist(X[cur], Y[cur], X[k], Y[k], Z[cur], Z[k]) <= eps){
								setN.insert(k);
								if (countN[k] >= minPts){
									isSeed[k] = true;
								}
							}
						}
					}

					if (cmty[cur] == -1 || cmty[cur] == 0)
						cmty[cur] = icmty;
				}

				for (int j = 0; j < nodeNum; j++){
					if (i == j)
						continue;

					if (calcDist(X[i], Y[i], X[j], Y[j], Z[i], Z[j]) <= eps){
						if (visited[j] == false){   //unvisited
							visited[j] = true;
							cmty[j] = cmty[i];
						}
					}
				}
			}

			else {  //mark P as noise
				if (cmty[i] == -1)
					cmty[i] = 0;
			}
		}
		end_time = clock();				   // End_Time


		std::cout << "Step 7\t" << std::endl;

		std::ostringstream oout;
		oout << eps;
		std::string varAs = oout.str();
		std::string outputname = str + "_MinPts_" + out.str() + "_RemovePercent_" + removeP + "_EPS_" + varAs + ".dat";
		ofs.open(outputname.c_str());
		for (int z = 0; z< nodeNum; z++){

			ofs << z + 1 << "\t" << cmty[z] << "\t" << isSeed[z] << std::endl;
		}






		printf("Time : %f\n", ((double)(end_time - start_time)) / CLOCKS_PER_SEC);


		ofs.close();
		nodeCmty2.close();

		delete[] original;
		delete[] X;
		delete[] Y;
		delete[] Z;
		delete[] cmty;
		delete[] visited;
		delete[] isSeed;
		delete[]communitySelf;
	}

};
