#ifndef FOODSOURCE_H
#define FOODSOURCE_H

#include	"configuration.h"
#include	"problem.h"

class FoodSource{

  public:
      FoodSource(Configuration * conf, Problem * problem);
      FoodSource(Configuration * conf, Problem * problem, unsigned int K);
      FoodSource(Configuration * conf, Problem * problem, double* loc);
      FoodSource(Configuration * conf, Problem * problem, FoodSource * bestFood);
      FoodSource(FoodSource * copy);
      ~FoodSource();
      
      void reInit();
      void reInit(const double * bestSoFarSolution);
      void reInit(double shake, const double * bestSoFarSolution);
      void chaoticReInit(unsigned int K);
      void inverseReInit(double * loc);
      
      long double getFitness() { return 1.0 / (objectiveValue+1.0) ;}
      
      // This Fitness Function is for Rosenbrock ABC 
      long double getFitness(double sp, int order, unsigned int popSize){ return 2 - sp + 2 * (sp-1) * (order-1) / (popSize-1); }
      
      long double getObjectiveValue(){return objectiveValue;}
      void setObjectiveValue(long double value) {objectiveValue = value; }
      
      void calculateObjectiveValue();
      
      double* getLocation() { return location;}
      void setLocation(const double * x);
      
      long double getProbability() {return prob;}
      void setProbability(long double value) { prob = value;}
      
      int getTrail() { return trail;}
      void initTrail() { trail = 0; }
      void increaseTrailVal(){ trail++;}
      
      long double distanceTo(FoodSource * fsource);
      unsigned int getFailedAttempts(){return failedAttempts;}
      void resetFailedAttempts(){ failedAttempts = 0; }				
      void incrementFailedAttempts(){ failedAttempts++; }
      
  private:

      long double prob; // probability
      int trail;
      double * location;
      unsigned int failedAttempts;
      
      long double objectiveValue;
      Problem * p;
      Configuration * config;
      
};


#endif