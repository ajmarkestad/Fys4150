#include <iostream>
#include <cmath>
#include <string>
#include <fstream> // For reading to file
#include <iomanip>
#include <sstream>
#include <time.h>
#include <armadillo>

using namespace arma;
using namespace std;


bool unittest_largest_off_diagonal();
bool unittest_orthogonality();
bool unittest_correct_eigenvalues();
void jacobis_method(mat,double);

int main(int argc, char *argv[])
{

    //UNIT TESTS
    bool tests = True;
    bool tests_pass = True;
    try { unittest_correct_eigenvalues()}

    try { unittest_largest_off_diagonal()}

    try { unittest_orthogonality() }



    return 0;
}



void jacobis_method(mat, double tolerance = pow(10,-8))
{

}



