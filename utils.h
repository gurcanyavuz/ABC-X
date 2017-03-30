#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>

using namespace std;

class Utils{

  public:
    static void loadRowVectorFromFile(string filename, int columns, double * row);
    static void loadRowVector(ifstream & fs, int columns, double * row);
    static void loadColumnVectorFromFile(string filename, int columns, double * column);
    static void loadColumnVector(ifstream & fs, int columns, double * column);
    static void loadMatrixFromFile(string filename, int N, int rows, int columns, double *** matrix3D);
    static void loadMatrixFromFile(string filename, int rows, int columns, double** matrix2D);
    static void loadMatrix(ifstream & fs, int rows, int columns, double ** matrix);
  
};
#endif