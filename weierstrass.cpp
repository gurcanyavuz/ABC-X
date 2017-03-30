#include "rng.h"
#include "problem.h"
#include "weierstrass.h"
#include "utils.h"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

  
Weierstrass::Weierstrass(Configuration* config, int variantID):Problem(config, variantID){
	optimum = 0.0;
	
	if(vID == SHIFTED_ROTATED){
	  if(config->getCompetitionID() == CEC05){
		z = new double[dimension];
		m_r = new double[dimension];
		
		rotation_matrix  = allocateMemory2D(dimension, dimension);
		shift_vector = new double[dimension]; 
		string file_data = "supportData/input_data/shift_data_6.txt";
		stringstream dim_name;
		dim_name << dimension;
		string file_m = "supportData/input_data/M_6_D" + dim_name.str() + ".txt";
		Utils::loadRowVectorFromFile(file_data, dimension, shift_vector);
		Utils::loadMatrixFromFile(file_m, dimension, dimension, rotation_matrix);
	  }else
	  if(config->getCompetitionID() == MIXTURE){
		z = new double[dimension];
		m_r = new double[dimension];
		
		rotation_matrix  = allocateMemory2D(dimension, dimension);
		shift_vector = new double[dimension]; 
		string file_data = "supportData/weierstrass_func_data.txt";
		stringstream dim_name;
		dim_name << dimension;
		string file_m = "supportData/weierstrass_M_D" + dim_name.str() + ".txt";
		Utils::loadRowVectorFromFile(file_data, dimension, shift_vector);
		Utils::loadMatrixFromFile(file_m, dimension, dimension, rotation_matrix);
	  }	    
	}
		

}

Weierstrass::~Weierstrass(){
	if(vID == SHIFTED_ROTATED){
		deallocateMemory2D(rotation_matrix,dimension);
		delete [] z;
		delete [] m_r;
	}
}

long double Weierstrass::evaluate(int dim, const double* x) {
	long double result;
	
	switch(vID){
	      case BASIC: 
		    result = weierstrassFunction(dim, x);
		    break;
	      case SHIFTED_ROTATED:
		    result = shiftedRotatedWeierstrassFunction(dim, x);
		    break;
	      default: cout<<"There is no function such that !!"<< endl;
		    exit(0);
		    break;
	} 
	
	return result;

}

long double Weierstrass::weierstrassFunction(int dim, const double* x){
  
	double a = 0.5;
	double b = 3.0;
	int Kmax = 20;

	double sum1 = 0.0;
	for (int i = 0 ; i < dim ; i ++) {
		for (int k = 0 ; k <= Kmax ; k ++) {
			sum1 += pow(a, k) * cos(PI * 2 * pow(b, k) * (x[i] + 0.5));
		}
	}

	double sum2 = 0.0;
	for (int k = 0 ; k <= Kmax ; k ++) {
		sum2 += pow(a, k) * cos(PI * 2 * pow(b, k) * (0.5));
	}

	return (sum1 - sum2*((double )dim));

}


long double Weierstrass::shiftedRotatedWeierstrassFunction(int dim, const double* x){

	shift(dim, z, x,shift_vector);
	if(config->getCompetitionID() == MIXTURE){
	    double shiftRate = 0.5/100.0;
	    for(int i = 0; i < dim; i++)
	      z[i]*=shiftRate;
	}
	rotate(dim, m_r, z, rotation_matrix);
	return weierstrassFunction(dim, m_r) + optimum;
}
