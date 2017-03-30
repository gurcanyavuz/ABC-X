#include "utils.h"

//#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


using namespace std;

void Utils::loadRowVector(ifstream & fs, int columns, double * row){
    	
	string aline;
	getline(fs, aline);
	istringstream lineStream(aline);

	for (int i = 0 ; i < columns ;i++) {
		lineStream >> row[i];
	}
	
}

void Utils::loadRowVectorFromFile(string filename, int columns, double * row){
	ifstream file(filename.c_str());
	loadColumnVector(file, columns, row);
	file.close();
}


void Utils::loadColumnVectorFromFile(string filename, int rows, double * column){
	ifstream file(filename.c_str());
	loadColumnVector(file, rows, column);
	file.close();
}

void Utils::loadColumnVector(ifstream & fs, int rows, double * column){
	string aline;
	getline(fs, aline);
	istringstream lineStream(aline);
	
	for (int i = 0 ; i < rows ;i++) {
		lineStream >> column[i];
        }
}

void Utils::loadMatrixFromFile(string filename, int N, int rows, int columns, double *** matrix3D){
	ifstream file(filename.c_str());
	for (int i = 0 ; i < N ; i++) {
		loadMatrix(file, rows, columns, matrix3D[i]);
	}
	file.close();
}


void Utils::loadMatrixFromFile(string filename, int rows, int columns, double** matrix2D){
	ifstream file(filename.c_str());
	loadMatrix(file, rows, columns, matrix2D);
	file.close();
}

void Utils::loadMatrix(ifstream & fs, int rows, int columns, double ** matrix){
	for (int i = 0 ; i < rows ; i ++) {
		loadRowVector(fs, columns, matrix[i]);
	}
}
