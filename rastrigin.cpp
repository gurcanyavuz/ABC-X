#include "rng.h"
#include "problem.h"
#include "rastrigin.h"
#include "utils.h"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

Rastrigin::Rastrigin(Configuration* config, int variantID):Problem(config, variantID){

  
	if(config->getCompetitionID() == CEC05){
	    if(vID == SHIFTED_ROTATED){
		  rotation_matrix  = allocateMemory2D(dimension, dimension);
		  shift_vector = new double[dimension]; 
		  z = new double[dimension];
		  m_r = new double[dimension];
		  string file_data = "supportData/rastrigin_CEC05_func_data.txt";
		  stringstream dim_name;
		  dim_name<< dimension;
		  string file_m = "supportData/rastrigin_M_D" + dim_name.str() + ".txt";
		  Utils::loadRowVectorFromFile(file_data, dimension, shift_vector);
		  Utils::loadMatrixFromFile(file_m, dimension, dimension, rotation_matrix);
	    }
	    
	    if(vID == SHIFTED){
		  shift_vector = new double[dimension]; 
		  z = new double[dimension]; 
		  string file_data = "supportData/rastrigin_CEC05_func_data.txt";
		  Utils::loadRowVectorFromFile(file_data, dimension, shift_vector);
	    }
	 }else if (config->getCompetitionID() == MIXTURE){
	    if(vID == SHIFTED_ROTATED){
		  
		  shift_vector = new double[dimension]; 
		  z = new double[dimension];
		  string file_data = "supportData/input_data/shift_data_8.txt";
		  Utils::loadRowVectorFromFile(file_data, dimension, shift_vector);

		  rotation_matrix  = allocateMemory2D(dimension, dimension);
		  m_r = new double[dimension];
		  stringstream dim_name;
		  dim_name << dimension;
		  string file_m = "supportData/input_data/M_8_D" + dim_name.str() + ".txt";
		  Utils::loadMatrixFromFile(file_m, dimension, dimension, rotation_matrix);
	    }	  

   	    if(vID == SHIFTED){
		  shift_vector = new double[dimension]; 
		  z = new double[dimension]; 
		  string file_data = "supportData/rastrigin_CEC08_func_data.txt";
		  Utils::loadRowVectorFromFile(file_data, dimension, shift_vector);
	    }

	}
	 else{
	    if(vID == SHIFTED){
		  shift_vector = new double[dimension]; 
		  z = new double[dimension]; 
		  string file_data = "supportData/rastrigin_CEC08_func_data.txt";
		  Utils::loadRowVectorFromFile(file_data, dimension, shift_vector);
	    }
	}

}

Rastrigin::~Rastrigin(){
       if(vID == SHIFTED_ROTATED){
	    deallocateMemory2D(rotation_matrix,dimension);
	    delete [] shift_vector;      
	    delete [] z;
	    delete [] m_r;
       }else
       if(vID == SHIFTED){
	    delete [] shift_vector;      
	    delete [] z;
       }
}


long double Rastrigin::evaluate(int dim, const double* x) {
	long double result;
	
	switch(vID){
	      case BASIC: 
		    result = rastriginFunction(dim, x);
		    break;
	      case SHIFTED:
		    result = shiftedRastriginFunction(dim, x);
		    break;
	      case SHIFTED_ROTATED:
		    result = shiftedRotatedRastriginFunction(dim, x);
		    break;
	      case NONCONTINUOUS_BASIC:
		    result = noncontinuousRastriginFunction(dim, x);
		    break;
	      default: cout<<"There is no function such that !!"<< endl;
		    exit(0);
		    break;
	} 
	
	return result;

}


long double Rastrigin::rastriginFunction(int dim, const double* x){
	int i;
	long double F = 0;
	
	for(i=0;i<dim;i++){
		F = F + ( pow(x[i],2) - 10*cos(2*PI*x[i]) + 10);
	}
	
	return F;
}


long double Rastrigin::shiftedRastriginFunction(int dim, const double* x){

	shift(dim, z, x,shift_vector);

	return rastriginFunction(dim, z);
}


long double Rastrigin::shiftedRotatedRastriginFunction(int dim, const double* x){

    shift(dim, z, x,shift_vector);
    if (config->getCompetitionID() == MIXTURE){
      double shiftRate = 5.12/100.0;
      for(int i = 0; i < dim; i++)
	z[i]*=shiftRate;
    }
    
	rotate(dim, m_r, z, rotation_matrix);
	return rastriginFunction(dim, m_r);
}

long double Rastrigin::noncontinuousRastriginFunction(int dim, const double* x){
	int i;
	long double F = 0;
	
	for(i=0;i<dim;i++){
		double currx = xRound(x[i]);
		F = F + ( pow(currx,2) - 10*cos(2*PI*currx) + 10);
	}
	
	return F;	

}
