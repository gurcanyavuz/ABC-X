#include	"foodSource.h"
#include	"ABC.h"
#include	"originalABC.h"
#include	"configuration.h"
#include	"rng.h"
#include	"problem.h"
#include	"chaoticmaps.h" 
#include	<cfloat> 
#include	<iostream>

/**********************************************************************************************************************
 * class for ABC-X algorithm 
 * ********************************************************************************************************************/

//////////////////////////////////////////// CONSTRUCTOR AND DESTRUCTOR ////////////////////////////////////////////////
/**********************************************************************************************************
 * parameters
 * ------------
 * conf: reference of configuration object  
 * problem: reference of problem object  
 * 
 * Initiases the food sources and other fields
 * ********************************************************************************************************/
OriginalABC::OriginalABC(Configuration * conf, Problem * problem): ABC(conf,problem){
 
  initFoodSources();
  tempSource = new double[conf->getProblemDimension()];
  solution = new double[conf->getProblemDimension()];
  
}

// destructor
OriginalABC::~OriginalABC(){

  delete [] tempSource;
  delete [] solution;
  int popsize= foodSources.size();
  for(unsigned int i=0;i<popsize;i++)
	  delete foodSources.at(i);
  foodSources.clear();

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////// INITIALIZATION STRATEGIES //////////////////////////////////////////////////

/*******************************************************************************************************************
 * These method initiazes the food sources. DEFAULT_INIT is for standart initialization method, 
 * CHAOTIC_INIT is for chaotic initilalization strategy.
 * Moreover, oppositinal based initialization strategy can be added
 * 
 * *****************************************************************************************************************/
void OriginalABC::initFoodSources(){
  switch(config->initStrategy()){
    case DEFAULT_INIT: initFoodSourcesDefault(); break;
    case CHAOTIC_INIT: initFoodSourcesChaotic(); break;
  }
  
  if(config->isOppositeInit())
    initFoodSourcesOpposition();
}

/******************************************************************************************************************
 * Creates food sources according to standart initialization strategy
 * 
 * ***************************************************************************************************************/
void OriginalABC::initFoodSourcesDefault(){
  for(int i = 0; i < config->numOfFoodSources(); i++){
      FoodSource * newFoodSource = new FoodSource(config, p);
      foodSources.push_back(newFoodSource);
  }
}



/******************************************************************************************************************
 * Creates food sources according to chatic initialization strategy. 
 * ***************************************************************************************************************/
void OriginalABC::initFoodSourcesChaotic(){
  for(int i = 0; i < config->numOfFoodSources(); i++){
      FoodSource * newFoodSource = new FoodSource(config, p, config->getK());
      foodSources.push_back(newFoodSource);
  }  
}

/*****************************************************************************************************************
 * Comparator class for food sources. The comparison criteria is objective function value of the food sources. 
 * This class is used for opposition-based initialization which is based on sorting the food sources according 
 * to objective function values. 
 * ***************************************************************************************************************/
class FSComparator{
  public:
    bool operator()(FoodSource * f1, FoodSource * f2){
	return f1->getObjectiveValue() < f2->getObjectiveValue();
    }
};

/****************************************************************************************************************
 * Creates food sources according to opposition based initialization strategy. To do so, oppositional position of the
 * food sources are created as new food sources at first, then all food sources are sorted and finally,
 * the worst half is eliminated 
 * *************************************************************************************************************/
void OriginalABC::initFoodSourcesOpposition(){
  for(int i = 0; i < config->numOfFoodSources(); i++){
      FoodSource * aFoodSource = foodSources.at(i);
      FoodSource * oppositeFoodSource = new FoodSource(config, p, aFoodSource->getLocation());
      foodSources.push_back(oppositeFoodSource);		
  }
  
  //sort foodsources according to their fitness
  FSComparator fscomp;
  sort(foodSources.begin(), foodSources.end(), fscomp);
  //delete half of the worst food sources
  for (int i =config->numOfFoodSources(); i < config->numOfFoodSources()*2; i++)
    	  delete foodSources.at(i);
  foodSources.erase(foodSources.begin()+config->numOfFoodSources(), foodSources.end()); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////Search Equations////////////////////////////

/****************************************************************************************************************
 * fsource: reference food source
 * fID: reference food source id
 * Selects a food source accoring to distance of the reference food source (with a pseudo-random selection rule) 
 * **************************************************************************************************************/
FoodSource * OriginalABC::getSuitableReferencefor(FoodSource * fsource, unsigned int fID){
    
    long double denum = 0.0;
    long double fProbs[foodSources.size()];
    
    for (unsigned int i=0;i<foodSources.size();i++) { 
	if (i != fID){
	    FoodSource * refFood = foodSources.at(i);
	    fProbs[i] = 1.0 / fsource->distanceTo(refFood);
	    denum += fProbs[i];
	}
    }
    
    double r = RNG::randVal(0,1);
    long double totalprobs = 0.0;
    unsigned int k = -1;
    
    do{
	k++;
	if(k != fID){
	    totalprobs += fProbs[k];
	}
    }while(r * denum > totalprobs);
    
    return foodSources.at(k);
}

/******************************************************************************************************
 * index: reference food source
 * p2c: selected dimension of food source for mutation
 * 
 * Gets the first term of search equation in employed bees step
 * ****************************************************************************************************/
double OriginalABC::getFirstTermEmp(int index, int p2c){

  FoodSource * currentFood = foodSources.at(index);

  double * currloc = currentFood->getLocation();
  

  int neighbour = -1;
  do{
      neighbour= floor (RNG::randVal(0,foodSources.size())); 
  }while(neighbour == index);
  
  double * neighbourloc = (foodSources.at(neighbour))->getLocation();


  double * gbestloc = (getBestFSource())->getLocation();
  
  double value = 0;
  switch(config->FirstTermStrategyEmp()){
    case CURRENTLOC: value = currloc[p2c]; break;
    case RANDOMLOC: value = neighbourloc[p2c]; break;
    case GBESTLOC: value = gbestloc[p2c]; break;
  }
  
  return value;
}


/******************************************************************************************************
 * index: reference food source
 * p2c: selected dimension of food source for mutation
 * 
 * Gets the second term of search equation in employed bees step
 * ****************************************************************************************************/
double OriginalABC::getSecondTermEmp(int index, int p2c){
  
  FoodSource * currentFood = foodSources.at(index);
  
  double * currloc = currentFood->getLocation();
 
  
  int neighbour = -1;
  do{
      neighbour= floor (RNG::randVal(0,foodSources.size())); 
  }while(neighbour == index);
  
  int neighbour2 = -1;
  do{
      neighbour2= floor (RNG::randVal(0,foodSources.size())); 
  }while(neighbour2 == index || neighbour2 == neighbour);

  double * neighbourloc = (foodSources.at(neighbour))->getLocation();
  double * neighbour2loc = (foodSources.at(neighbour2))->getLocation();
  
  
  double * gbestloc = (getBestFSource())->getLocation();
  
  
  FoodSource * gbestneighbour = getSuitableReferencefor(currentFood, index);
  double * gbestdistloc = gbestneighbour->getLocation();

  double value = 0;
  
  double randlr= -1.0; 
  double randhr= 1.0;  
  
  if(!config->isDefaultUniformRE1()){
      randlr= -1.0*config->getRandRange1e();
      randhr= config->getRandRange1e();
  }
  
  
  switch(config->SecondTermStrategyEmp()){
    case GBEST_CURRENT: value = RNG::randVal(randlr,randhr)*(gbestloc[p2c]-currloc[p2c]); break;
    case GBEST_RANDOM: value = RNG::randVal(randlr,randhr)*(gbestloc[p2c]-neighbourloc[p2c]); break;
    case CURRENT_RANDOM: value = RNG::randVal(randlr,randhr)*(currloc[p2c]-neighbourloc[p2c]); break;
    case RANDOM_RANDOM: value = RNG::randVal(randlr,randhr)*(neighbourloc[p2c]-neighbour2loc[p2c]); break;
    case CURRENT_GBESTDIST: value = RNG::randVal(randlr,randhr)*(currloc[p2c]- gbestdistloc[p2c]); break;
    case NO_STRATEGY: value = 0; break;
  }

  return value;
 
}


/******************************************************************************************************
 * index: reference food source
 * p2c: selected dimension of food source for mutation
 * 
 * Gets the third term of search equation in employed bees step
 * ****************************************************************************************************/
      
double OriginalABC::getThirdTermEmp(int index, int p2c){
   FoodSource * currentFood = foodSources.at(index);
  double * currloc = currentFood->getLocation();
  /*A randomly chosen solution is used in producing a mutant solution of the solution i*/ 
  int neighbour = -1;
  do{
      neighbour= floor (RNG::randVal(0,foodSources.size())); 
  }while(neighbour == index);
  
  int neighbour2 = -1;
  do{
      neighbour2= floor (RNG::randVal(0,foodSources.size())); 
  }while(neighbour2 == index || neighbour2 == neighbour);

  double * neighbourloc = (foodSources.at(neighbour))->getLocation();
  double * neighbour2loc = (foodSources.at(neighbour2))->getLocation();
  
  double * gbestloc = (getBestFSource())->getLocation();
  
  FoodSource * gbestneighbour = getSuitableReferencefor(currentFood, index);
  double * gbestdistloc = gbestneighbour->getLocation();
  
  
  double value = 0;
  double randlr= -1.0;
  double randhr= 1.0;
  
  if(!config->isDefaultUniformRE2()){
      randlr= -1.0*config->getRandRange2e();
      randhr= config->getRandRange2e();
  }
  switch(config->ThirdTermStrategyEmp()){
    case GBEST_CURRENT: value = RNG::randVal(randlr,randhr)*(gbestloc[p2c]-currloc[p2c]); break;
    case GBEST_RANDOM: value = RNG::randVal(randlr,randhr)*(gbestloc[p2c]-neighbourloc[p2c]); break;
    case CURRENT_RANDOM: value = RNG::randVal(randlr,randhr)*(currloc[p2c]-neighbourloc[p2c]); break;
    case RANDOM_RANDOM: value = RNG::randVal(randlr,randhr)*(neighbourloc[p2c]-neighbour2loc[p2c]); break;
    case CURRENT_GBESTDIST: value = RNG::randVal(randlr,randhr)*(currloc[p2c]- gbestdistloc[p2c]); break;
    case NO_STRATEGY: value = 0; break;
  }
  
  return value;
}
      
/******************************************************************************************************
 * index: reference food source
 * p2c: selected dimension of food source for mutation
 * 
 * Gets the fourth term of search equation in employed bees step
 * ****************************************************************************************************/
      
double OriginalABC::getFourthTermEmp(int index, int p2c){
   FoodSource * currentFood = foodSources.at(index);
  double * currloc = currentFood->getLocation();
  /*A randomly chosen solution is used in producing a mutant solution of the solution i*/ 
  int neighbour = -1;
  do{
      neighbour= floor (RNG::randVal(0,foodSources.size())); 
  }while(neighbour == index);
  
  int neighbour2 = -1;
  do{
      neighbour2= floor (RNG::randVal(0,foodSources.size())); 
  }while(neighbour2 == index || neighbour2 == neighbour);

  double * neighbourloc = (foodSources.at(neighbour))->getLocation();
  double * neighbour2loc = (foodSources.at(neighbour2))->getLocation();
  
  double * gbestloc = (getBestFSource())->getLocation();

  FoodSource * gbestneighbour = getSuitableReferencefor(currentFood, index);
  double * gbestdistloc = gbestneighbour->getLocation();

  
  double value = 0;
  
  double randlr= -1.0;
  double randhr= 1.0;
  
  if(!config->isDefaultUniformRE3()){
      randlr= -1.0*config->getRandRange3e();
      randhr= config->getRandRange3e();
  }

  switch(config->FourthTermStrategyEmp()){
    case GBEST_CURRENT: value = RNG::randVal(randlr,randhr)*(gbestloc[p2c]-currloc[p2c]); break;
    case GBEST_RANDOM: value = RNG::randVal(randlr,randhr)*(gbestloc[p2c]-neighbourloc[p2c]); break;
    case CURRENT_RANDOM: value = RNG::randVal(randlr,randhr)*(currloc[p2c]-neighbourloc[p2c]); break;
    case RANDOM_RANDOM: value = RNG::randVal(randlr,randhr)*(neighbourloc[p2c]-neighbour2loc[p2c]); break;
    case CURRENT_GBESTDIST: value = RNG::randVal(randlr,randhr)*(currloc[p2c]- gbestdistloc[p2c]); break;
    case NO_STRATEGY: value = 0; break;
  }
  
  return value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double OriginalABC::getFirstTermOnl(int index, int p2c){
  FoodSource * currentFood = foodSources.at(index);
  double * currloc = currentFood->getLocation();
  /*A randomly chosen solution is used in producing a mutant solution of the solution i*/ 
  int neighbour = -1;
  do{
      neighbour= floor (RNG::randVal(0,foodSources.size())); 
  }while(neighbour == index);
  
  double * neighbourloc = (foodSources.at(neighbour))->getLocation();

  double * gbestloc = (getBestFSource())->getLocation();
  
  double value = 0;
  switch(config->FirstTermStrategyOnl()){
    case CURRENTLOC: value = currloc[p2c]; break;
    case RANDOMLOC: value = neighbourloc[p2c]; break;
    case GBESTLOC: value = gbestloc[p2c]; break;
  }
  
  return value;
}


double OriginalABC::getSecondTermOnl(int index, int p2c){
  FoodSource * currentFood = foodSources.at(index);
  double * currloc = currentFood->getLocation();
  /*A randomly chosen solution is used in producing a mutant solution of the solution i*/ 
  int neighbour = -1;
  do{
      neighbour= floor (RNG::randVal(0,foodSources.size())); 
  }while(neighbour == index);
  
  int neighbour2 = -1;
  do{
      neighbour2= floor (RNG::randVal(0,foodSources.size())); 
  }while(neighbour2 == index || neighbour2 == neighbour);

  double * neighbourloc = (foodSources.at(neighbour))->getLocation();
  double * neighbour2loc = (foodSources.at(neighbour2))->getLocation();
  
  double * gbestloc = (getBestFSource())->getLocation();
  
  FoodSource * gbestneighbour = getSuitableReferencefor(currentFood, index);
  double * gbestdistloc = gbestneighbour->getLocation();
  
  double value = 0;
  double randlr= -1.0;
  double randhr= 1.0;
  
  if(!config->isDefaultUniformRO1()){
      randlr= -1.0*config->getRandRange1o();
      randhr= config->getRandRange1o();
  }

  switch(config->SecondTermStrategyOnl()){
    case GBEST_CURRENT: value = RNG::randVal(randlr,randhr)*(gbestloc[p2c]-currloc[p2c]); break;
    case GBEST_RANDOM: value = RNG::randVal(randlr,randhr)*(gbestloc[p2c]-neighbourloc[p2c]); break;
    case CURRENT_RANDOM: value = RNG::randVal(randlr,randhr)*(currloc[p2c]-neighbourloc[p2c]); break;
    case RANDOM_RANDOM: value = RNG::randVal(randlr,randhr)*(neighbourloc[p2c]-neighbour2loc[p2c]); break;
    case CURRENT_GBESTDIST: value = RNG::randVal(randlr,randhr)*(currloc[p2c]- gbestdistloc[p2c]); break;
    case NO_STRATEGY: value = 0; break;
  }
  
  return value;
 
}
      
double OriginalABC::getThirdTermOnl(int index, int p2c){
   FoodSource * currentFood = foodSources.at(index);
  double * currloc = currentFood->getLocation();
  /*A randomly chosen solution is used in producing a mutant solution of the solution i*/ 
  int neighbour = -1;
  do{
      neighbour= floor (RNG::randVal(0,foodSources.size())); 
  }while(neighbour == index);
  
  int neighbour2 = -1;
  do{
      neighbour2= floor (RNG::randVal(0,foodSources.size())); 
  }while(neighbour2 == index || neighbour2 == neighbour);

  double * neighbourloc = (foodSources.at(neighbour))->getLocation();
  double * neighbour2loc = (foodSources.at(neighbour2))->getLocation();
  
  double * gbestloc = (getBestFSource())->getLocation();
  
  FoodSource * gbestneighbour = getSuitableReferencefor(currentFood, index);
  double * gbestdistloc = gbestneighbour->getLocation();
  
  double value = 0;
  double randlr= -1.0;
  double randhr= 1.0;
  
  if(!config->isDefaultUniformRO2()){
      randlr= -1.0*config->getRandRange2o();
      randhr= config->getRandRange2o();
  }
  
  switch(config->ThirdTermStrategyOnl()){
    case GBEST_CURRENT: value = RNG::randVal(randlr,randhr)*(gbestloc[p2c]-currloc[p2c]); break;
    case GBEST_RANDOM: value = RNG::randVal(randlr,randhr)*(gbestloc[p2c]-neighbourloc[p2c]); break;
    case CURRENT_RANDOM: value = RNG::randVal(randlr,randhr)*(currloc[p2c]-neighbourloc[p2c]); break;
    case RANDOM_RANDOM: value = RNG::randVal(randlr,randhr)*(neighbourloc[p2c]-neighbour2loc[p2c]); break;
    case CURRENT_GBESTDIST: value = RNG::randVal(randlr,randhr)*(currloc[p2c]- gbestdistloc[p2c]); break;
    case NO_STRATEGY: value = 0; break;
  }
  
  return value;
}
      
      
double OriginalABC::getFourthTermOnl(int index, int p2c){
   FoodSource * currentFood = foodSources.at(index);
  double * currloc = currentFood->getLocation();
  /*A randomly chosen solution is used in producing a mutant solution of the solution i*/ 
  int neighbour = -1;
  do{
      neighbour= floor (RNG::randVal(0,foodSources.size())); 
  }while(neighbour == index);
  
  int neighbour2 = -1;
  do{
      neighbour2= floor (RNG::randVal(0,foodSources.size())); 
  }while(neighbour2 == index || neighbour2 == neighbour);

  double * neighbourloc = (foodSources.at(neighbour))->getLocation();
  double * neighbour2loc = (foodSources.at(neighbour2))->getLocation();
  
  double * gbestloc = (getBestFSource())->getLocation();
  
  FoodSource * gbestneighbour = getSuitableReferencefor(currentFood, index);
  double * gbestdistloc = gbestneighbour->getLocation();
  
  double value = 0;
  double randlr= -1.0;
  double randhr= 1.0;
  
  if(!config->isDefaultUniformRO3()){
      randlr= -1.0*config->getRandRange3o();
      randhr= config->getRandRange3o();
  }  

  switch(config->FourthTermStrategyOnl()){
    case GBEST_CURRENT: value = RNG::randVal(randlr,randhr)*(gbestloc[p2c]-currloc[p2c]); break;
    case GBEST_RANDOM: value = RNG::randVal(randlr,randhr)*(gbestloc[p2c]-neighbourloc[p2c]); break;
    case CURRENT_RANDOM: value = RNG::randVal(randlr,randhr)*(currloc[p2c]-neighbourloc[p2c]); break;
    case RANDOM_RANDOM: value = RNG::randVal(randlr,randhr)*(neighbourloc[p2c]-neighbour2loc[p2c]); break;
    case CURRENT_GBESTDIST: value = RNG::randVal(randlr,randhr)*(currloc[p2c]- gbestdistloc[p2c]); break;
    case NO_STRATEGY: value = 0; break;
  }
  
  return value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*****************************************************************************************************************
 * 
 * The method for employed bees step
 * ***************************************************************************************************************/
void OriginalABC::sendEmployedBees(){

      int i,j; 
      
      for (i=0;i<foodSources.size();i++) { // for each food source

	  FoodSource * currentFood = foodSources.at(i); // get the food source
	  double * currloc = currentFood->getLocation(); // and its location
	  
	  for(j=0;j<config->getProblemDimension();j++) // store the location to a temporary array
	      tempSource[j]= currloc[j]; 
	  
	  // for the number of modification ratio mutate a randomly selected dimension of the selected food source
	  for(int m=0; m < config->getMRE(); m++){
	      // dimension (parameter) to change
	      int param2change= floor (RNG::randVal(0,config->getProblemDimension())); 

	      // mutate accoding to four-termed search equation
	      tempSource[param2change]= getFirstTermEmp(i,param2change)+getSecondTermEmp(i,param2change)+getThirdTermEmp(i,param2change)+getFourthTermEmp(i,param2change);
	 
	      // check the bounds
	      if (tempSource[param2change] < config->getMinInitRange()) 
		  tempSource[param2change] = config->getMinInitRange(); 
	      if (tempSource[param2change] > config->getMaxInitRange()) 
		  tempSource[param2change] = config->getMaxInitRange(); 
	      
	  }
	  
	  // evaulate new location
	  long double objectiveValue=p->getFunctionValue(tempSource); 
	  
	    
	  // if new food source location is better than the previous, update
	  if (1.0/ (objectiveValue+1.0) > currentFood->getFitness()) { 
	    
	      currentFood->initTrail(); // initilaize trail value
	      currentFood->setLocation(tempSource); // update food source location
	      currentFood->setObjectiveValue(objectiveValue); // update objective value of the food source
	  } 
	  else {  //otherwise
	      currentFood->increaseTrailVal(); // increase trail value of the food source
	  } 

      } 
      /*end of employed bee phase*/ 

}



////////////////////////////// CALCULATE PROBABILITIES ////////////////////////////////////////////////////////////
/**********************************************************************************************************************
 * The methods calculate the selection probabilities of the food sources. It includes three different strategies
 * ********************************************************************************************************************/
void OriginalABC::calculateProbabilities(){
  switch(config->probabilityCalcType()){
    case DEFAULT_PROBCALC: calculateProbabilitiesDefault(); break;
    case WEIGHTED_PROBCALC: calculateProbabilitiesWeighted(); break;
    case ORDERED_PROBCALC: calculateProbabilitiesOrdered(); break;
  }
  
}

/*******************************************************************************************************************
 * Canonical selection probability calculation strategy for ABC
 *******************************************************************************************************************/
void OriginalABC::calculateProbabilitiesDefault(){
      int i; 
      double totalfit = 0.0; 
  
      for (i=0;i<foodSources.size();i++) { 
	   totalfit += (foodSources.at(i))->getFitness(); 
      } 

      for (i=0;i<foodSources.size();i++) { 
	  (foodSources.at(i))->setProbability( (foodSources.at(i))->getFitness() / totalfit ); 
      } 


}

/*******************************************************************************************************************
 * Wieghted probability calulation strategy
 * pi = 0.9 - (0.9*(fitness(i)/maxfit))+0.1
 * *****************************************************************************************************************/
void OriginalABC::calculateProbabilitiesWeighted(){
      int i; 
      double maxfit; 
      maxfit=(foodSources.at(0))->getObjectiveValue(); 
  
      for (i=1;i<foodSources.size();i++) { 
	    if ((foodSources.at(i))->getObjectiveValue() > maxfit) 
		maxfit= (foodSources.at(i))->getObjectiveValue(); 
      } 

      for (i=0;i<foodSources.size();i++) { 
	  (foodSources.at(i))->setProbability( (0.9 - (0.9*((foodSources.at(i))->getObjectiveValue()/maxfit))) + 0.1 ); 
      } 


}

/*********************************************************************************************************************
 * Selection probability calculation based on the rank (order) of the food source according to fitness values.
 * It is defined in Rosenbrock ABC.
 * *******************************************************************************************************************/
void OriginalABC::calculateProbabilitiesOrdered(){
      int i; 
      double totalfit = 0.0; 
  
      int * ord = getOrder();
      
      for (i=0;i<foodSources.size();i++) { 
	   totalfit += (foodSources.at(i))->getFitness(config->getSP(), ord[i], foodSources.size()); 
      } 

      for (i=0;i<foodSources.size();i++) { 
	  (foodSources.at(i))->setProbability( (foodSources.at(i))->getFitness(config->getSP(), ord[i], foodSources.size()) / totalfit ); 
      } 

      delete [] ord;
}

/******************************************************************************************************
 * 
 * Gets the ranks of the food sources
 * ****************************************************************************************************/

int * OriginalABC::getOrder()
{
	int i,j;
	int * order = new int[foodSources.size()];

	for(i=0;i<foodSources.size();i++)
	{
		order[i]=1;
		for(j=0;j<foodSources.size();j++){
		  if((foodSources.at(i))->getObjectiveValue()<(foodSources.at(j))->getObjectiveValue())
		    order[i]=order[i]+1;
		}
	}
	
	return order;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////// ONLOOKER BEES ///////////////////////////////////////////////////////////////////////

/*****************************************************************************************************************
 * 
 * The method for onlooker bees step
 * ***************************************************************************************************************/
void OriginalABC::sendOnlookerBees(){
    
    int i,j,t; 
    i=0; 
    t=0; 
    /*onlooker Bee Phase*/ 
    while(t < foodSources.size()) { 
	  FoodSource * currentFood = foodSources.at(i);
    
	  double r = RNG::randVal(0,1);
	  
	  if(r < currentFood->getProbability()) {          
	  
	    t++; 
	    
	    int param2change= floor (RNG::randVal(0,config->getProblemDimension())); 
	    

	    double * currloc = currentFood->getLocation();
	    for(j=0;j<config->getProblemDimension();j++) 
		tempSource[j]= currloc[j]; 
	  
	    for(int m=0; m < config->getMRO(); m++){
		/*The parameter to be changed is determined randomly*/ 
		int param2change= floor (RNG::randVal(0,config->getProblemDimension())); 
		tempSource[param2change]= getFirstTermOnl(i,param2change)+getSecondTermOnl(i,param2change)+getThirdTermOnl(i,param2change)+getFourthTermOnl(i,param2change);
	    
		/*if generated parameter value is out of boundaries, it is shifted onto the boundaries*/ 
		if (tempSource[param2change] < config->getMinInitRange()) 
		    tempSource[param2change] = config->getMinInitRange(); 
		if (tempSource[param2change] > config->getMaxInitRange()) 
		    tempSource[param2change] = config->getMaxInitRange(); 
	    }
	    
	    long double objectiveValue=p->getFunctionValue(tempSource); 
	    
	      
	    /*a greedy selection is applied between the current solution i and its mutant*/ 
	    if (1.0/ (objectiveValue+1.0) > currentFood->getFitness()) { 
	      
		/*If the mutant solution is better than the current solution i, replace the solution with the mutant and reset the trial counter of solution i*/ 
		currentFood->initTrail();
		currentFood->setLocation(tempSource);
		currentFood->setObjectiveValue(objectiveValue);
	    } 
	    else {   /*if the solution i can not be improved, increase its trial counter*/ 
		currentFood->increaseTrailVal();
	    } 
	  	     
	  } /*if */ 
	  
	  i++; 
	  if (i == foodSources.size()-1) 
	    i=0; 
      }/*while*/ 
      /*end of onlooker bee phase     */ 

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// SCOUT BEE STEP //////////////////////////////

/*****************************************************************************************************************
 * 
 * The method for scout bees step. It consists of 5 diffirent strategies
 * ***************************************************************************************************************/
void OriginalABC::sendScoutBees(){
    switch(config->scoutBeeStrategy()){
      case DEFAULT_SCOUT: sendScoutBeesDefault(); break;
      case BABC_SCOUT: sendScoutBeesBABC(); break;
      case CABC_SCOUT: sendScoutBeesCABC(); break;
      case IABC_SCOUT: sendScoutBeesIABC(); break;
      case ERABC_SCOUT: sendScoutBeesERABC(); break;
    }
}


/**************************************************************************************************************
 * Original ABC's scout bee strategy
 **************************************************************************************************************/
void OriginalABC::sendScoutBeesDefault(){
      int maxtrialindex,i; 
      maxtrialindex=0; 
      for (i = 1; i < foodSources.size(); i++) { // bir yiyecek kaynaginin limite gelip gelmedigini kontrol et
	  if ((foodSources.at(i))->getTrail() > (foodSources.at(maxtrialindex))->getTrail()) {
	      maxtrialindex=i;
	  }
      } 
      if( (foodSources.at(maxtrialindex))->getTrail() >= config->getLimit()) 
      { 
	      (foodSources.at(maxtrialindex))->reInit(); // limit degerine ulasan yiyecek kaynagini bastan olustur
      }

}


/*******************************************************************************************************************
 * Best-so-far selection ABC's (BABC) scout bees Strategy
 * 
 */
void OriginalABC::sendScoutBeesBABC(){
      int i; 
      for (i = 0; i < foodSources.size(); i++) { 
	  if( (foodSources.at(i))->getTrail() >= config->getLimit()) {
	      reinitFSourceBABC(foodSources.at(i));
	  }
      } 
}

/********************************************************************************************************************
 * Reinitialization method in BABC's scout bee strategy
 * fsource: the food source to reinitialize
 ********************************************************************************************************************/
void OriginalABC::reinitFSourceBABC(FoodSource * fsource){
      double wMax = config->getWMax(); 
      double wMin = config->getWMin();
      double currEvals = (double)p->getFunctionEvaluations();
      double maxEvals = (double)config->getMaxFES();
  
      double * floc = fsource->getLocation();
      for(unsigned int i=0;i<config->getProblemDimension();i++) 
	  tempSource[i]= floc[i]; 

      //update position of scout bees
      for(unsigned int i=0;i<config->getProblemDimension();i++){
	  double r = RNG::randVal(0,1);
	  // BABC de tanimli formul: vij = xij + xij*U(-1,1)*(wMax-(currItr/maxItr)*(wMax-wMin))
	  tempSource[i]= floc[i] + (wMax - ((double)currEvals / (double)maxEvals)*(wMax-wMin)) * (floc[i])*(r-0.5)*2; 
	  if (tempSource[i] < config->getMinInitRange()) 
	      tempSource[i] = config->getMinInitRange(); 
	  if (tempSource[i] > config->getMaxInitRange()) 
	      tempSource[i] = config->getMaxInitRange(); 
      
      }
      
      long double objectiveValue=p->getFunctionValue(tempSource); 
      
	
      /*a greedy selection is applied between the current solution i and its mutant*/ 
      if (objectiveValue < fsource->getObjectiveValue()) { 
	
	  /*If the mutant solution is better than the current solution i, replace the solution with the mutant and reset the trial counter of solution i*/ 
	  fsource->initTrail();
	  fsource->setLocation(tempSource);
	  fsource->setObjectiveValue(objectiveValue);
      } 
      else {   /*if the solution i can not be improved, increase its trial counter*/ 
	  fsource->increaseTrailVal();
      } 

      
}


/**
 * Chaotic ABC's scout bee strategy: after the trial value of a food source reaches to "Limit/2" a chaotic search begins
 */
void OriginalABC::sendScoutBeesCABC(){
      int i; 
      for (i = 0; i < foodSources.size(); i++) { 
	  if( (foodSources.at(i))->getTrail() >= config->getLimit() / 2) 
	  { 
	      chaoticSearchCABC(foodSources.at(i));
	  }
	  if( (foodSources.at(i))->getTrail() >= config->getLimit()) 
	  { 
	      (foodSources.at(i))->reInit(); 
	  }
      } 
      
}


/**
 * CABC's chaotic search algorithm
 */
void OriginalABC::chaoticSearchCABC(FoodSource * fsource){
    
    int param2change= floor (RNG::randVal(0,config->getProblemDimension())); 
    //double ch = 0.0;
    int t = 0;
    double ch = RNG::randVal(0,1);
    double prev = RNG::randVal(0,1); 
    double temp = prev;
    
    do{
	for (unsigned k = 0; k < config->getK(); k++){ 
	    switch(config->getChaoticMapID()){ 
	      case LOGISTIC:
		ch = ChaoticMaps::Logistic(ch);
		break;
	      case CIRCLE:
		ch = ChaoticMaps::Circle(ch);
		break;
	      case GAUSS:
		ch = ChaoticMaps::Gauss(ch);
		break;
	      case SINUSOIDAL:
		ch = ChaoticMaps::Sinusoidal(ch);
		break;
	      case SINUS:
		ch = ChaoticMaps::Sinus(ch);
		break;
	      case TEND:
		ch = ChaoticMaps::Tent(ch);
		break;
	      case HENON:
		prev=ch;
		ch = ChaoticMaps::Henon(ch,temp);
		break;
	      case ACFUNC:
		ch = ChaoticMaps::ACFunc(ch,config->getMu());
		break;
	    }
	}
	
	
	double * currloc = fsource->getLocation();
	for(int j=0;j<config->getProblemDimension();j++) 
	    tempSource[j]= currloc[j]; 

	tempSource[param2change]= currloc[param2change] + ((config->getMaxInitRange()-config->getMinInitRange()) / 2.0) * (2.0 * ch - 1);

	/*if generated parameter value is out of boundaries, it is shifted onto the boundaries*/ 
	if (tempSource[param2change] < config->getMinInitRange()) 
	    tempSource[param2change] = config->getMinInitRange(); 
	if (tempSource[param2change] > config->getMaxInitRange()) 
	    tempSource[param2change] = config->getMaxInitRange(); 

	long double objectiveValue=p->getFunctionValue(tempSource); 
	
	  
	/*a greedy selection is applied between the current solution i and its mutant*/ 
	if (1.0/ (objectiveValue+1.0) > fsource->getFitness()) { 
	    fsource->setLocation(tempSource);
	    fsource->setObjectiveValue(objectiveValue);
	    while (param2change = floor (RNG::randVal(0,config->getProblemDimension())) == param2change);
	} 
        fsource->increaseTrailVal();
	t++;
    }while(t < config->getLimit() / 2);
}

/***************************************************************************************************************************
 * Incremental ABC's (IABC's) scout bee strategy
 * *************************************************************************************************************************/
void OriginalABC::sendScoutBeesIABC(){
      int maxtrialindex,i; 
      maxtrialindex=0; 
      for (i = 1; i < foodSources.size(); i++) { /* check if food source exceed its trail limit and take its index if any */
	  if ((foodSources.at(i))->getTrail() > (foodSources.at(maxtrialindex))->getTrail()) {
	      maxtrialindex=i; 
	  }
      } 
      if( (foodSources.at(maxtrialindex))->getTrail() >= config->getLimit()) 
      { 
	      (foodSources.at(maxtrialindex))->reInit(config->getShakingFactor(), p->getBestSoFarSolution());
      }

}

/*****************************************************************************************************************************
 * Efficient and Robust ABC's (ERABC) Scout bee strategy.
 * 
 * ***************************************************************************************************************************/
void OriginalABC::sendScoutBeesERABC(){
      int i; 
      for (i = 0; i < foodSources.size(); i++) { 
	  if( (foodSources.at(i))->getTrail() >= config->getLimit()) 
	  { 
	      chaoticSearchERABC(foodSources.at(i));
	  }
      } 
      
}


void OriginalABC::chaoticSearchERABC(FoodSource * fsource){
    
	double cx[config->getProblemDimension()];
	double * currloc = fsource->getLocation();
	for(int j=0;j<config->getProblemDimension();j++){ 
	    tempSource[j]= currloc[j];
	    cx[j] = (currloc[j]-config->getMinInitRange()) / (config->getMaxInitRange()-config->getMinInitRange());
	}
	
	for (int k = 0; k < 300; k++){
	  for(int j=0;j<config->getProblemDimension();j++){ 
	    // attaki islem bu aramada kullanilan kaotik map fonksiyonudur.
	    cx[j] = 4 * cx[j] * (config->getMaxInitRange()-config->getMinInitRange());
	    
	    tempSource[j] = config->getMinInitRange() + cx[j] * (config->getMaxInitRange()-config->getMinInitRange());
	    
	    if (tempSource[j] < config->getMinInitRange() || tempSource[j] > config->getMaxInitRange()) 
	      tempSource[j] = config->getMinInitRange() + RNG::randVal(0,1)* (config->getMaxInitRange()-config->getMinInitRange());
	    
	  }
	  
	  long double objectiveValue=p->getFunctionValue(tempSource); 
	
	  
	  /*a greedy selection is applied between the current solution i and its mutant*/ 
	  if (1.0/ (objectiveValue+1.0) > fsource->getFitness()) { 
	      fsource->setLocation(tempSource);
	      fsource->setObjectiveValue(objectiveValue);
	      fsource->initTrail();
	      return;
	  } 
	  else
	      fsource->increaseTrailVal();
	  
	}
	
}

/********************************************************************************************************************************
 * The general steps of the ABC algorithm
 * 
 * *******************************************************************************************************************************/
void OriginalABC::run(){
      unsigned int iterations=0;

      do{

	  sendEmployedBees();

	  calculateProbabilities();

	  sendOnlookerBees();
	  getBestFSource();

	  sendScoutBees();
	  FoodSource * bestfood = getBestFSource(); 

	  if(config->isPopulationIncremented()) 
	      
	      if(iterations>0 && iterations % config->getGrowthPeriod() == 0 && foodSources.size()<config->getMaximumFoodSize()){
		  foodSources.push_back(new FoodSource(config,p,getBestFSource())); 
	  }

	  iterations++;
	  
      }while(notDone());
}

