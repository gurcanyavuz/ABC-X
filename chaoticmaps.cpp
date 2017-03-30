#include	"chaoticmaps.h"
#include	"configuration.h"

#include	<cmath>

using namespace std;

double ChaoticMaps::Logistic(double val){
  return 4 * val * (1 - val);
}

double ChaoticMaps::Circle(double val){
  return val + 1.2 - fmod((0.5 / (2*PI)) * sin(2*PI*val), 1.0);
}

double ChaoticMaps::Gauss(double val){
  if (val == 0) return 0;
  return 1/val - floor(1/val);
}

double ChaoticMaps::Henon(double val, double prev){
  return 1 - 1.4*val*val + 0.3*prev;
}

double ChaoticMaps::Sinusoidal(double val){
  return sin(PI*val);
}

double ChaoticMaps::Sinus(double val){
  return 2.3 * pow(val,2*sin(PI*val));
}

double ChaoticMaps::Tent(double val){
  if(val < 0.7) 
    return val / 0.7;
  return 10 / 3*val*(1-val);
}

double ChaoticMaps::ACFunc(double val, double mu){
  return mu * (1 - val);
}

 
