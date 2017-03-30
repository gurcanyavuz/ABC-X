#include "rng.h"

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

using namespace std;

gsl_rng* RNG::R = gsl_rng_alloc(gsl_rng_env_setup());
gsl_permutation* RNG::P = gsl_permutation_alloc(1);

void RNG::initializeRNG(unsigned long int rngSeed){	
    gsl_rng_set(RNG::R, rngSeed);   
}

void RNG::initializePermutation(unsigned int size){
	//Deallocate default
	gsl_permutation_free( RNG::P );

	//Allocate correct one	
	RNG::P = gsl_permutation_alloc(size);
	gsl_permutation_init (RNG::P);
}

double RNG::randVal(double min,double max){
	return gsl_ran_flat( RNG::R, min, max);
}

double RNG::randGauss(double sd){
	return gsl_ran_gaussian( RNG::R, sd);
}

void RNG::shufflePermutation(){
	gsl_ran_shuffle (RNG::R, RNG::P->data, gsl_permutation_size(RNG::P), sizeof(size_t));
}

int RNG::getPermutationElement(int index){
	return gsl_permutation_get (RNG::P,index);
}

void RNG::deallocateRNG(){
	 gsl_rng_free( RNG::R );
}

void RNG::deallocatePermutation(){
	 gsl_permutation_free( RNG::P );
}
