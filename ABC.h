#ifndef ABC_H
#define ABC_H

#include	"configuration.h"
#include	"problem.h"
#include	"foodSource.h"


#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;


class ABC{

  public:
      ABC(Configuration * conf, Problem * problem);
      virtual ~ABC();      
      virtual void run() = 0;
      
      double* getSolution();
      void setSolution( const double * x);
      int getPopulationSize() {return NP;}



  protected:
      virtual void initFoodSources() = 0;
      virtual void sendEmployedBees() = 0;
      virtual void sendOnlookerBees() = 0;
      virtual void sendScoutBees() = 0;
      virtual void calculateProbabilities() = 0;

      bool notDone();
      double getStepSize();
      FoodSource * getBestFSource();
      int getBestFSourceIndex();
      
      vector<FoodSource*> foodSources; // yiyecek kaynaklarinin tutuldugu vektor
      int NP; // number of population
      double * solution, * tempSource; // cozum ve islemler icin gecici olarak kullanilan dizi
      long double solutionValue; // cozum degeri
      Configuration * config;
      Problem * p;
      int limit;

};


#endif
