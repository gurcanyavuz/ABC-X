#ifndef CHAOTIC_MAPS
#define CHAOTIC_MAPS


class ChaoticMaps{
public:

static double Logistic(double val);
static double Circle(double val);
static double Gauss(double val);
static double Henon(double val, double prev);
static double Sinusoidal(double val);
static double Sinus(double val);
static double Tent(double val);
static double ACFunc(double val, double mu);

};

#endif 