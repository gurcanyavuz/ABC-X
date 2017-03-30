#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <vector>
#include <cmath>

//SOCO problems
#define	SHIFTED_SPHERE_SOCO 		0
#define SHIFTED_SCHWEFEL221_SOCO	1
#define SHIFTED_ROSENBROCK_SOCO 	2
#define SHIFTED_RASTRIGIN_SOCO		3
#define SHIFTED_GRIEWANK_SOCO 		4
#define SHIFTED_ACKLEY_SOCO 		5
//#define FFDOUBLEDIP 			6
#define SHIFTED_SCHWEFEL222_SOCO 	6
#define SHIFTED_SCHWEFEL12_SOCO		7
#define SHIFTED_EXTENDED_F10_SOCO 	8
#define SHIFTED_BOHACHEVSKY_SOCO 	9
#define SHIFTED_SCHAFFER_SOCO 		10
#define	H1 				11
#define H2				12
#define H3				13
#define H4				14
#define H7				15
#define H8				16
#define H9				17
#define H10				18

//CEC2005 problems
#define SHIFTED_SPHERE_CEC05				0	
#define SHIFTED_SCHWEFEL12_CEC05			1
#define SHIFTED_ROTATED_HIGH_CONDITIONED_ELLIPTIC_CEC05	2
#define NOISE_SHIFTED_SCHWEFEL12_CEC05			3
#define SCHWEFEL26_GLOBAL_OPTIMUM_ON_BOUNDS_CEC05	4
#define SHIFTED_ROSENBROCK_CEC05			5
#define	SHIFTED_ROTATED_GRIEWANK_CEC05			6
#define	SHIFTED_ROTATED_ACKLEY_GOOB_CEC05		7
#define	SHIFTED_RASTRIGIN_CEC05				8
#define	SHIFTED_ROTATED_RASTRIGIN_CEC05			9
#define	SHIFTED_ROTATED_WEIERSTRASS_CEC05		10
#define	BASIC_SCHWEFEL213_CEC05				11
#define	SHIFTED_EXPANDED_GRIEWANKROSENBROCK_CEC05	12
#define	SHIFTED_ROTATED_EXPANDED_SCHAFFERF6_CEC05	13
#define	BASIC_HYBRIDCOMPOSITION1			14
#define	ROTATED_HYBRIDCOMPOSITION1			15
#define	NOISE_ROTATED_HYBRIDCOMPOSITION1		16
#define	ROTATED_HYBRIDCOMPOSITION2			17
#define	ROTATED_HYBRIDCOMPOSITION2_NBGO			18
#define	ROTATED_HYBRIDCOMPOSITION2_GOOB			19
#define	ROTATED_HYBRIDCOMPOSITION3			20
#define	ROTATED_HYBRIDCOMPOSITION3_HCNM			21
#define	NONCONTINUOUS_ROTATED_HYBRIDCOMPOSITION3	22
#define	ROTATED_HYBRIDCOMPOSITION4			23
#define	ROTATED_HYBRIDCOMPOSITION4_NO_BOUNDS		24

//ABC-X PROBLEMS (MIXTURE)
//UNIMODAL FUNCTIONS
#define SHIFTED_SPHERE					0 //SOCO	
#define SHIFTED_ROTATED_HIGH_CONDITIONED_ELLIPTIC	1 // CEC14
#define ROTATED_BENT_CIGER				2 // CEC14
#define ROTATED_DISCUS					3 // CEC14
#define SHIFTED_SCHWEFEL221				4 // SOCO
#define SHIFTED_SCHWEFEL12				5 // SOCO
#define SHIFTED_SCHWEFELS12_NOISE_IN_FITNESS		6 // CEC05
#define SHIFTED_SCHWEFEL222				7 // SOCO
#define SHIFTED_EXTENDED_F10 				8 // SOCO
#define SHIFTED_BOHACHEVSKY 				9 // SOCO
#define SHIFTED_SCHAFFER 				10 // SOCO
#define SCHWEFEL26_GLOBAL_OPTIMUM_ON_BOUNDS		11 // CEC05
//MULTIMODAL FUNCTIONS
#define SHIFTED_ACKLEY					12 // SOCO
#define SHIFTED_ROTATED_ACKLEY				13 // CEC14
#define	SHIFTED_ROSENBROCK				14 // SOCO
#define	SHIFTED_ROTATED_ROSENBROCK			15 // CEC14
#define SHIFTED_GRIEWANK				16 // SOCO
#define SHIFTED_ROTATED_GRIEWANK			17 // CEC14
#define SHIFTED_RASTRIGIN				18 // SOCO
#define	SHIFTED_ROTATED_RASTRIGIN			19 // CEC14
#define	SHIFTED_SCHWEFEL				20 // CEC14
#define SHIFTED_ROTATED_SCHWEFEL			21 // CEC14
#define	SHIFTED_ROTATED_WEIERSTRASS			22 // CEC14
#define SHIFTED_ROTATED_KATSUURA			23 // CEC14
#define	SHIFTED_ROTATED_HAPPYCAT			24 // CEC14
#define	SHIFTED_ROTATED_HGBAT				25 // CEC14
//HYBRID FUNCTIONS
#define	H1_SOCO						26 // SOCO 
#define H2_SOCO						27 // SOCO
#define H3_SOCO						28 // SOCO
#define H4_SOCO						29 // SOCO
#define H7_SOCO						30 // SOCO
#define H8_SOCO						31 // SOCO
#define H9_SOCO						32 // SOCO
#define H10_SOCO					33 // SOCO
#define	H1_CEC14					34 //CEC14
#define H2_CEC14					35 //CEC14
#define H3_CEC14					36 //CEC14
#define H4_CEC14					37 //CEC14
#define H5_CEC14					38 //CEC14
#define H6_CEC14					39 //CEC14
//COMPOSITION FUNCTIONS
#define COMPOSITION_F1					40 //CEC05
#define COMPOSITION_F2					41 //CEC05
#define COMPOSITION_F3					42 //CEC05
#define COMPOSITION_F4					43 //CEC05
#define COMPOSITION_F5					44 //CEC05
#define COMPOSITION_F6					45 //CEC05
#define COMPOSITION_F7					46 //CEC05
#define COMPOSITION_F8					47 //CEC05
#define COMPOSITION_F9					48 //CEC05
#define COMPOSITION_F10					49 //CEC05



//scout bee strategies
#define DEFAULT_SCOUT	1
#define BABC_SCOUT	2
#define CABC_SCOUT	3
#define IABC_SCOUT	4
#define ERABC_SCOUT	5

//probability calculation strategies
#define DEFAULT_PROBCALC	1
#define WEIGHTED_PROBCALC	2
#define ORDERED_PROBCALC	3

//initialization strategies
#define DEFAULT_INIT	1
#define CHAOTIC_INIT	2


	
// Chaotic Maps
#define LOGISTIC	1
#define CIRCLE		2
#define GAUSS		3
#define SINUSOIDAL	4
#define SINUS		5
#define TEND		6
#define HENON		7
#define ACFUNC		8


//random number generation range
#define DEFAULT_RAND	0
#define	NOTDEFAULT_RAND	1

// terms of Search equations (2., 3., and 4. terms)
#define GBEST_CURRENT 	1
#define GBEST_RANDOM	2 
#define CURRENT_RANDOM	3
#define RANDOM_RANDOM	4
#define CURRENT_GBESTDIST 5
#define NO_STRATEGY	6
// (1. term)    
#define CURRENTLOC	1
#define RANDOMLOC	2
#define GBESTLOC	3

//competitions
#define CEC05	 	0
#define CEC08		1
#define SOFT_COMPUTING 	2
#define MIXTURE		3

#define PI acos(-1)
#define E  exp(1)

#define EPSILON 1E-15

#define MAX_DIMENSION 1000


class Configuration {

      private:

	//general parameters
	unsigned long rngSeed;
	unsigned int maxFES;

	//problem parameters
	unsigned int competitionID;
	unsigned int problemID;
	unsigned int problemDimension;
	double minInitRange;
	double maxInitRange;

	//---------------------------------------------ABC PARAMETERS-------------------------------------------------

	unsigned int numOfFoods;//population size
	double limitF; // limit factor (limit=limitF*numOfFoods*problemDimension))
	
	// PARAMETERS FOR INITIALIZATION STRATEGIES
	unsigned int initStr; // is uniform or chotic random initialization?
	bool isOppInit; // is opposition-based initialization added?
	unsigned int cmapID; // selected caotik map ID
	unsigned int k_param; // k parameter for chaotic maps
	double mu; // a parameter for a chaotic map

	
	// EMPLOYED BEES AND ONLOOKER BEES STEPS PARAMETERS
	//MR parameters
	int mre; 
	int mro; 
	int mrer;
	int mror;
	unsigned int  dmre;
	unsigned int  dmro;
	// phi parameters
	unsigned int drand1e;
	unsigned int drand2e;
	unsigned int drand3e;
	unsigned int drand1o;
	unsigned int drand2o;
	unsigned int drand3o;
	
	// range of phi parameters
	// U(-a1,a1) = U(-1*randRange1e,randRange1e) 
	double randRange1o;
	double randRange2o;
	double randRange3o;

	double randRange1e;
	double randRange2e;
	double randRange3e;
	
	// term ids for selected search equations
	unsigned int firstTermOnl;
	unsigned int secondTermOnl;
	unsigned int thirdTermOnl;	
	unsigned int fourthTermOnl;

	unsigned int firstTermEmp;
	unsigned int secondTermEmp;
	unsigned int thirdTermEmp;	
	unsigned int fourthTermEmp;
	
	
	//selection probability calculation type
	unsigned int pctype;
	double sp; // a parameter in ordered strategy (ORDERED_PROBCALC) 
	
	// PARAMETERS OF SCOUT BEE STEP 
	unsigned int scoutStrID;//which strategy wil be selected?
	// wMax ve wMin parameters in  BABC_SCOUT strategy
	double wMax;
	double wMin;
	// a parameter for IABC_SCOUT strategy
	double shakingFactor;
	
	//PARAMETERS OF INCREMENTAL POPULATION SIZE STRATEGY
	bool isIncrementedPop; // is population is fix or incremental?
	unsigned int maxFoodSize; // if incremental then the maximum population size?
 	unsigned int growthPeriod; // how often a new food source will be added?
	
	//Other parameters
	double startTime; // it is for calculates time elapsed


  public:

	Configuration(int argc,char** argv);
	~Configuration();

	unsigned long getRNGSeed();
	unsigned int getMaxFES();

	
	unsigned int getCompetitionID();
	unsigned int getProblemID();
	unsigned int getProblemDimension();
	double getMinInitRange();
	double getMaxInitRange();

	double getMinInitBound();
	double getMaxInitBound();

	//paramaters for all ABC variants
	unsigned int numOfFoodSources();
	void setCurrentFoodSize(unsigned int newSize);
	
	unsigned int getLimit();

	// wMax and wMin parameters for best-so-far solution ABC
	double getWMax();
	double getWMin();

	unsigned int getMRE();
	unsigned int getMRO();
	
	unsigned int getK();
	double getMu();
	
	//improved ABC and Chaotic ABC
	unsigned int getChaoticMapID();
	
	double getSP();


	double getShakingFactor();

	
	unsigned int initStrategy(){return initStr;}
	unsigned int probabilityCalcType(){ return pctype;}
	unsigned int scoutBeeStrategy(){return scoutStrID;}

	bool isPopulationIncremented(){return isIncrementedPop;}
	unsigned int getMaximumFoodSize();
	unsigned int getGrowthPeriod();
	unsigned int getMaxRepeatedFailures();
	
	bool isOppositeInit(){return isOppInit;}  
	  
	bool isDefaultUniformRE1();
	bool isDefaultUniformRE2();
	bool isDefaultUniformRE3();
	bool isDefaultUniformRO1();
	bool isDefaultUniformRO2();
	bool isDefaultUniformRO3();
	
	double getRandRange1o(){return randRange1o;}
	double getRandRange2o(){return randRange2o;}
	double getRandRange3o(){return randRange3o;}

	double getRandRange1e(){return randRange1e;}
	double getRandRange2e(){return randRange2e;}
	double getRandRange3e(){return randRange3e;}
	
	unsigned int FirstTermStrategyOnl(){return firstTermOnl;}
	unsigned int SecondTermStrategyOnl(){return secondTermOnl;}
	unsigned int ThirdTermStrategyOnl(){return thirdTermOnl;}	
	unsigned int FourthTermStrategyOnl(){return fourthTermOnl;}

	unsigned int FirstTermStrategyEmp(){return firstTermEmp;}
	unsigned int SecondTermStrategyEmp(){return secondTermEmp;}
	unsigned int ThirdTermStrategyEmp(){return thirdTermEmp;}	
	unsigned int FourthTermStrategyEmp(){return fourthTermEmp;}
	
	void setStartTime(double stime);
	double getStartTime();

	void print();
};

#endif
