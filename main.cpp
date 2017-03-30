//Configuration
#include "configuration.h"

//Problems
#include "problem.h"
#include "hcjob.h"

#include "sphere.h"
#include "schwefel213.h" 	
#include "schwefel221.h"
#include "schwefel222.h" 	
#include "schwefel12.h" 	
#include "schwefel26.h" 	
#include "rosenbrock.h" 	
#include "rastrigin.h" 		
#include "griewank.h" 		
#include "ackley.h" 	
#include "extendedF10.h" 	
#include "bohachevsky.h" 	
#include "schaffer.h" 		
#include "schafferf6.h"
#include "elliptic.h"
#include "weierstrass.h"
#include "griewank_rosenbrock.h"
#include "schwefel.h"
#include "hgbat.h"
#include "happycat.h"
#include "cigar.h"
#include "discus.h" 
#include "katsuura.h"
#include "h1.h"			
#include "h2.h"			
#include "h3.h"			
#include "h4.h"			
#include "h7.h"			
#include "h8.h"			
#include "h9.h"			
#include "h10.h"	
#include "h1cec14.h"
#include "h2cec14.h"
#include "h3cec14.h"
#include "h4cec14.h"
#include "h5cec14.h"
#include "h6cec14.h"
#include "hybrid_composition1.h"
#include "hybrid_composition2.h"
#include "hybrid_composition3.h"
#include "hybrid_composition4.h"

//Algorithms
#include "ABC.h" 
#include "originalABC.h" // original ABC algorithm 

//Timers
#include <sys/time.h>
#include <sys/resource.h>

//C++ Libraries
#include <iostream>


using namespace std;


Problem* initializeProblem(Configuration * config){

    Problem* problem;

    if(config->getCompetitionID() == MIXTURE){
	//Problem initialization
	    switch(config->getProblemID()){
	      /////////UNIMODAL FUNCTIONS //////////////////////////////////////////////////
		    case SHIFTED_SPHERE:{
			    problem = new Sphere(config, SHIFTED);
		    }break;
		    case SHIFTED_ROTATED_HIGH_CONDITIONED_ELLIPTIC:{
			    problem = new Elliptic(config, SHIFTED_ROTATED_HIGH_CONDITIONED);
		    }break;		    
		    case ROTATED_BENT_CIGER:{
			    problem = new Cigar(config, SHIFTED_ROTATED);
		    }break;
		    case ROTATED_DISCUS:{
			    problem = new Discus(config, SHIFTED_ROTATED);
		    }break;
		    case SHIFTED_SCHWEFEL221:{
			    problem = new Schwefel221(config, SHIFTED);
		    }break;
		    case SHIFTED_SCHWEFEL12:{
			    problem = new Schwefel12(config, SHIFTED);
		    }break;
		    case SHIFTED_SCHWEFELS12_NOISE_IN_FITNESS:{
			    problem = new Schwefel12(config, NOISE_SHIFTED);
		    }break;
		    case SHIFTED_SCHWEFEL222:{
			    problem = new Schwefel222(config, SHIFTED);
		    }break;
		    case SHIFTED_EXTENDED_F10:{
			    problem = new ExtendedF10(config, SHIFTED);
		    }break;
		    case SHIFTED_BOHACHEVSKY:{
			    problem = new Bohachevsky(config, SHIFTED);
		    }break;
		    case SHIFTED_SCHAFFER:{
			    problem = new Schaffer(config, SHIFTED);
		    }break;
		    case SCHWEFEL26_GLOBAL_OPTIMUM_ON_BOUNDS:{
			    problem = new Schwefel26(config, BASIC_GLOBAL_OPTIMUM_ON_BOUNDS);
		    }break;
      ///////////////////////////////////////////MULTIMODAL FUNCTIONS
		    case SHIFTED_ACKLEY:{
			    problem = new Ackley(config, SHIFTED);
		    }break;
		    case SHIFTED_ROTATED_ACKLEY:{
			    problem = new Ackley(config, SHIFTED_ROTATED);
		    }break;
		    case SHIFTED_ROSENBROCK:{
			    problem = new Rosenbrock(config, SHIFTED);
		    }break;
		    case SHIFTED_ROTATED_ROSENBROCK:{
			    problem = new Rosenbrock(config, SHIFTED_ROTATED);
		    }break;
		    case SHIFTED_GRIEWANK:{
			    problem = new Griewank(config, SHIFTED);
		    }break;
		    case SHIFTED_ROTATED_GRIEWANK:{
			    problem = new Griewank(config, SHIFTED_ROTATED);
		    }break;
		    case SHIFTED_RASTRIGIN:{
			    problem = new Rastrigin(config, SHIFTED);
		    }break;
		    case SHIFTED_ROTATED_RASTRIGIN:{
			    problem = new Rastrigin(config, SHIFTED_ROTATED);
		    }break;
		    case SHIFTED_SCHWEFEL:{
			    problem = new Schwefel(config, SHIFTED);
		    }break;
		    case SHIFTED_ROTATED_SCHWEFEL:{
			    problem = new Schwefel(config, SHIFTED_ROTATED);
		    }break;
		    case SHIFTED_ROTATED_WEIERSTRASS:{
			    problem = new Weierstrass(config, SHIFTED_ROTATED);
		    }break;
		    case SHIFTED_ROTATED_KATSUURA:{
			    problem = new Katsuura(config, SHIFTED_ROTATED);
		    }break;
		    case SHIFTED_ROTATED_HAPPYCAT:{
			    problem = new Happycat(config, SHIFTED_ROTATED);
		    }break;
		    case SHIFTED_ROTATED_HGBAT:{
			    problem = new Hgbat(config, SHIFTED_ROTATED);
		    }break;
      /////////////////////////////////////HYBRID FUNCTIONS
		    case H1_SOCO:{
			    problem = new Hybrid1(config, BASIC);
		    }break;
		    case H2_SOCO:{
			    problem = new Hybrid2(config, BASIC);
		    }break;
		    case H3_SOCO:{
			    problem = new Hybrid3(config, BASIC);
		    }break;
		    case H4_SOCO:{
			    problem = new Hybrid4(config, SHIFTED);
		    }break;
		    case H7_SOCO:{
			    problem = new Hybrid7(config, BASIC);
		    }break;
		    case H8_SOCO:{
			    problem = new Hybrid8(config, BASIC);
		    }break;
		    case H9_SOCO:{
			    problem = new Hybrid9(config, BASIC);
		    }break;
		    case H10_SOCO:{
			    problem = new Hybrid10(config, SHIFTED);
		    }break;		    
		    case H1_CEC14:{
			    problem = new Hybrid1CEC14(config, SHIFTED_ROTATED);
		    }break;
		    case H2_CEC14:{
			    problem = new Hybrid2CEC14(config, SHIFTED_ROTATED);
		    }break;
		    case H3_CEC14:{
			    problem = new Hybrid3CEC14(config, SHIFTED_ROTATED);
		    }break;
		    case H4_CEC14:{
			    problem = new Hybrid4CEC14(config, SHIFTED_ROTATED);
		    }break;
		    case H5_CEC14:{
			    problem = new Hybrid5CEC14(config, SHIFTED_ROTATED);
		    }break;
		    case H6_CEC14:{
			    problem = new Hybrid6CEC14(config, SHIFTED_ROTATED);
		    }break;
	/////////////////////////// COMPOSITION FUNCTIONS
		    case COMPOSITION_F1:{
			    problem = new HC_1(config, BASIC);
		    }break;
		    case COMPOSITION_F2:{
			    problem = new HC_1(config, ROTATED);
		    }break;
		    case COMPOSITION_F3:{
			    problem = new HC_1(config, NOISE_ROTATED);
		    }break;	    
		    case COMPOSITION_F4:{
			    problem = new HC_2(config, ROTATED);
		    }break;
		    case COMPOSITION_F5:{
			    problem = new HC_2(config, ROTATED_WITH_NORROW_BASIN_GLOBAL_OPTIMUM);
		    }break;
		    case COMPOSITION_F6:{
			    problem = new HC_2(config, ROTATED_GLOBAL_OPTIMUM_ON_BOUNDS);
		    }break;
		    case COMPOSITION_F7:{
			    problem = new HC_3(config, ROTATED);
		    }break;
		    case COMPOSITION_F8:{
			    problem = new HC_3(config, ROTATED_WITH_HIGH_CONDITION_NUMBER_MATRIX);
		    }break;
		    case COMPOSITION_F9:{
			    problem = new HC_3(config, NONCONTINUOUS_ROTATED);
		    }break;
		    case COMPOSITION_F10:{
			    problem = new HC_4(config, ROTATED);
		    }break;
	      
	    }
    }
    if(config->getCompetitionID() == SOFT_COMPUTING){
	//Problem initialization
	    switch(config->getProblemID()){
		    case SHIFTED_SPHERE_SOCO:{
			    problem = new Sphere(config, SHIFTED);
		    }break;
		    case SHIFTED_SCHWEFEL221_SOCO:{
			    problem = new Schwefel221(config, SHIFTED);
		    }break;
		    case SHIFTED_ROSENBROCK_SOCO:{
			    problem = new Rosenbrock(config,SHIFTED);
		    }break;
		    case SHIFTED_RASTRIGIN_SOCO:{
			    problem = new Rastrigin(config, SHIFTED);
		    }break;
		    case SHIFTED_GRIEWANK_SOCO:{
			    problem = new Griewank(config, SHIFTED);
		    }break;
		    case SHIFTED_ACKLEY_SOCO:{
			    problem = new Ackley(config, SHIFTED);
		    }break;
		    case SHIFTED_SCHWEFEL222_SOCO:{
			    problem = new Schwefel222(config, SHIFTED);
		    }break;
		    case SHIFTED_SCHWEFEL12_SOCO:{
			    problem = new Schwefel12(config, SHIFTED);
		    }break;
		    case SHIFTED_EXTENDED_F10_SOCO:{
			    problem = new ExtendedF10(config, SHIFTED);
		    }break;
		    case SHIFTED_BOHACHEVSKY_SOCO:{
			    problem = new Bohachevsky(config, SHIFTED);
		    }break;
		    case SHIFTED_SCHAFFER_SOCO:{
			    problem = new Schaffer(config, SHIFTED);
		    }break;
		    case H1:{
			    problem = new Hybrid1(config, BASIC);
		    }break;
		    case H2:{
			    problem = new Hybrid2(config, BASIC);
		    }break;
		    case H3:{
			    problem = new Hybrid3(config, BASIC);
		    }break;
		    case H4:{
			    problem = new Hybrid4(config, SHIFTED);
		    }break;
		    case H7:{
			    problem = new Hybrid7(config, BASIC);
		    }break;
		    case H8:{
			    problem = new Hybrid8(config, BASIC);
		    }break;
		    case H9:{
			    problem = new Hybrid9(config, BASIC);
		    }break;
		    case H10:{
			    problem = new Hybrid10(config, SHIFTED);
		    }break;
	    }
	    
	}else if(config->getCompetitionID() == CEC05){
		//Problem initialization
		switch(config->getProblemID()){
		    case SHIFTED_SPHERE_CEC05:{
			    problem = new Sphere(config, SHIFTED);
		    }break;
		    case SHIFTED_SCHWEFEL12_CEC05:{
			    problem = new Schwefel12(config, SHIFTED);
		    }break;
		    case SHIFTED_ROTATED_HIGH_CONDITIONED_ELLIPTIC_CEC05:{
			    problem = new Elliptic(config, SHIFTED_ROTATED_HIGH_CONDITIONED);
		    }break;
		    case NOISE_SHIFTED_SCHWEFEL12_CEC05:{
			    problem = new Schwefel12(config, NOISE_SHIFTED);
		    }break;
		    case SCHWEFEL26_GLOBAL_OPTIMUM_ON_BOUNDS_CEC05:{
			    problem = new Schwefel26(config, BASIC_GLOBAL_OPTIMUM_ON_BOUNDS);
		    }break;
		    case SHIFTED_ROSENBROCK_CEC05:{
			    problem = new Rosenbrock(config,SHIFTED);
		    }break; 
		    case SHIFTED_ROTATED_GRIEWANK_CEC05:{
			    problem = new Griewank(config, ROTATED_WITHOUT_BOUNDS);
		    }break;
		    case SHIFTED_ROTATED_ACKLEY_GOOB_CEC05:{
			    problem = new Ackley(config, SHIFTED_ROTATED_GLOBAL_OPTIMUM_ON_BOUNDS);
		    }break;
		    case SHIFTED_RASTRIGIN_CEC05:{
			    problem = new Rastrigin(config, SHIFTED);
		    }break;
		    case SHIFTED_ROTATED_RASTRIGIN_CEC05:{
			    problem = new Rastrigin(config, SHIFTED_ROTATED);
		    }break;
		    case SHIFTED_ROTATED_WEIERSTRASS_CEC05:{
			    problem = new Weierstrass(config, SHIFTED_ROTATED);
		    }break;
		    case BASIC_SCHWEFEL213_CEC05:{
			    problem = new Schwefel213(config, BASIC);
		    }break;    
		    case SHIFTED_EXPANDED_GRIEWANKROSENBROCK_CEC05:{
			    problem = new GriewankRosenbrock(config, SHIFTED_EXPANDED);
		    }break;
		    case SHIFTED_ROTATED_EXPANDED_SCHAFFERF6_CEC05:{
			    problem = new SchafferF6(config, SHIFTED_ROTATED_EXPANDED);
		    }break;
		    case BASIC_HYBRIDCOMPOSITION1:{
			    problem = new HC_1(config, BASIC);
		    }break;
		    case ROTATED_HYBRIDCOMPOSITION1:{
			    problem = new HC_1(config, ROTATED);
		    }break;
		    case NOISE_ROTATED_HYBRIDCOMPOSITION1:{
			    problem = new HC_1(config, NOISE_ROTATED);
		    }break;	    
		    case ROTATED_HYBRIDCOMPOSITION2:{
			    problem = new HC_2(config, ROTATED);
		    }break;
		    case ROTATED_HYBRIDCOMPOSITION2_NBGO:{
			    problem = new HC_2(config, ROTATED_WITH_NORROW_BASIN_GLOBAL_OPTIMUM);
		    }break;
		    case ROTATED_HYBRIDCOMPOSITION2_GOOB:{
			    problem = new HC_2(config, ROTATED_GLOBAL_OPTIMUM_ON_BOUNDS);
		    }break;
		    case ROTATED_HYBRIDCOMPOSITION3:{
			    problem = new HC_3(config, ROTATED);
		    }break;
		    case ROTATED_HYBRIDCOMPOSITION3_HCNM:{
			    problem = new HC_3(config, ROTATED_WITH_HIGH_CONDITION_NUMBER_MATRIX);
		    }break;
		    case NONCONTINUOUS_ROTATED_HYBRIDCOMPOSITION3:{
			    problem = new HC_3(config, NONCONTINUOUS_ROTATED);
		    }break;
		    case ROTATED_HYBRIDCOMPOSITION4:{
			    problem = new HC_4(config, ROTATED);
		    }break;
		    case ROTATED_HYBRIDCOMPOSITION4_NO_BOUNDS:{
			    problem = new HC_4(config, ROTATED_WITHOUT_BOUNDS);
		    }break;
		}
	}

	return problem;

}




int main( int argc, char** argv) {	

	double stime;
	static struct timeval tp;	

	Problem* problem;

	//Command line parsing
	Configuration* config = new Configuration(argc,argv);

	//Random number generator
	RNG::initializeRNG(config->getRNGSeed());

    	//Initialize Problem
	problem = initializeProblem(config);
	
	//Start timer
	gettimeofday( &tp, NULL );
   	stime =(double) tp.tv_sec + (double) tp.tv_usec/1000000.0;
	config->setStartTime(stime);
	
	//ABC intialization	
	ABC* abc = new OriginalABC(config, problem);

	//ABC execution
	abc->run();
	

	cout.precision(20);
	cout<<"solution: "<<scientific<<problem->getBestSolutionValue()<<endl;

	//Memory release
	RNG::deallocateRNG();
	RNG::deallocatePermutation();
	
	delete problem;
	
	delete abc;
	
	delete config;
		
	return 0;
}
