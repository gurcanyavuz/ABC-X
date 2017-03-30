#include	"foodSource.h"
#include	"ABC.h"
#include	"configuration.h"
#include	"rng.h"
#include	"problem.h"

#include	<cfloat> 
#include	<iostream>
 
ABC::ABC(Configuration * conf, Problem * problem){
 
  p = problem;
  config = conf;
  
  solutionValue = LDBL_MAX;

  
}

bool ABC::notDone(){
	//Check termination criterion
	if(p->getFunctionEvaluations() >= config->getMaxFES() || (p->getBestSolutionValue() <= EPSILON && config->getCompetitionID() != 1 && config->getProblemID() != 6))
	    return false;
	return true;
}



ABC::~ABC(){
}


double* ABC::getSolution(){ return solution;} // en iyi cozumu getir

void ABC::setSolution( const double * x){ // en iyi cozumu guncelle
      for(int i = 0; i < config->getProblemDimension(); i++)
	  solution[i] = x[i];
}

/**
 * en iyi yiyecek kaynagini getir
 */
FoodSource * ABC::getBestFSource(){
      
      int i,j; 
      FoodSource * bestFood;
      solutionValue = LDBL_MAX;
      for(i = 0; i < foodSources.size(); i++) { 
	  if ((foodSources.at(i))->getObjectiveValue() < solutionValue) { 
	      solutionValue = (foodSources.at(i))->getObjectiveValue(); 
	      setSolution((foodSources.at(i))->getLocation());
	      bestFood = foodSources.at(i);
	  } 
      } 

      return bestFood;
}	


/*
 * En iyi yiyecek kaynaginin indeksini getir
 */
int ABC::getBestFSourceIndex(){

      int i,j; 
      int bestFoodIndex;
      solutionValue = LDBL_MAX;
      for(i = 0; i < foodSources.size(); i++) { 
	  if ((foodSources.at(i))->getObjectiveValue() < solutionValue) { 
	      solutionValue = (foodSources.at(i))->getObjectiveValue(); 
	      bestFoodIndex = i;
	  } 
      } 

      return bestFoodIndex;

}

