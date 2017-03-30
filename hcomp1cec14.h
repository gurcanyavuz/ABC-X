#ifndef HYBRIDCOMP1CEC14_H
#define HYBRIDCOMP1CEC14_H

#include "configuration.h"
#include "problem.h"

class HybridComp1CEC14: public Problem {

     private:
	Rosenbrock* problem1;
	Ellipse* problem2;
	Cigar* problem3;
	Discus* problem4;
	Ellipse* problem5;

	long double h2Function(int dim, const double* x);

      public:
	 HybridComp1CEC14(Configuration* config, int variantID);
	 ~HybridComp1CEC14();

	long double evaluate(int dim, const double* x);
	
};

#endif
