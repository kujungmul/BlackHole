

#define DIMENSION 2

#pragma once

//Common Utility for calculate distances
class CalculateUtil {
public :
	//calculate distance
	static double calcDist_DIM(double* a, double* b){
		double sum = 0.0;
		for (int i = 0; i < DIMENSION; i++){
			sum = sum + ((a[i] - b[i]) * (a[i] - b[i]));
		}
		return sqrt(sum);
	}
};
