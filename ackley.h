#ifndef SHIFTED_ACKLEY_H
#define SHIFTED_ACKLEY_H

#include "configuration.h"
#include "problem.h"

class Ackley: public Problem {

     private:
	double * z;
	double * m_r;
	
	long double shiftedAckleyFunction(int dim, const double* x);
	long double shiftedRotatedAckleyFunction(int dim, const double* x);
	long double ackleyFunction(int dim, const double * x);
	
      public:

	 Ackley(Configuration* config, int variantID);
	 ~Ackley();

	long double evaluate(int dim, const double* x);
	
};

#endif
