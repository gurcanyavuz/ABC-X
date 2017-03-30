#ifndef ORIGINAL_ABC_H
#define ORIGINAL_ABC_H

#include	"configuration.h"
#include	"problem.h"
#include	"foodSource.h"
#include	"ABC.h"


#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

class OriginalABC: public ABC{

  public:
      OriginalABC(Configuration * conf, Problem * problem);
      ~OriginalABC();
      void initFoodSources();
      void sendEmployedBees();
      void sendOnlookerBees();
      void sendScoutBees();
      void calculateProbabilities();
      void run();
private:

      //initialization strategies
      void initFoodSourcesDefault();
      void initFoodSourcesChaotic();
      void initFoodSourcesOpposition();
      
      //strategies for employed bees and onlooker bees
      FoodSource * getSuitableReferencefor(FoodSource * fsource, unsigned int fID);
      double getFirstTermEmp(int index, int p2c);
      double getSecondTermEmp(int index, int p2c);
      double getThirdTermEmp(int index, int p2c);
      double getFourthTermEmp(int index, int p2c);
      
      double getFirstTermOnl(int index, int p2c);
      double getSecondTermOnl(int index, int p2c);
      double getThirdTermOnl(int index, int p2c);
      double getFourthTermOnl(int index, int p2c);
      
      //probability calculation strategies
      void calculateProbabilitiesDefault(); 
      void calculateProbabilitiesWeighted();
      void calculateProbabilitiesOrdered();
      int * getOrder();
      
      //scout bees strategies
      void sendScoutBeesDefault();
      void sendScoutBeesBABC();
      void sendScoutBeesCABC();
      void sendScoutBeesIABC();
      void sendScoutBeesERABC();
      
      void chaoticSearchCABC(FoodSource * fsource);
      void chaoticSearchERABC(FoodSource * fsource);
      void reinitFSourceBABC(FoodSource * fsource);
      
      
};


#endif
