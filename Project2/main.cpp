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
void jacobis_method(mat , mat , int);
double maxoffdiag(mat , int *, int *, int );
void rotate(mat , mat , int , int , int );
mat Matrix_creator(double *, int, double);

int main(int argc, char *argv[])
{

    //UNIT TESTS
//    bool tests = True;
//    bool tests_pass = True;
//    try { unittest_correct_eigenvalues()}

//    try { unittest_largest_off_diagonal()}

//    try { unittest_orthogonality() }
    int n;
    double h, rho_start, rho_stop ;
    double *HO_potential, *rho;

    n = 10;
    rho_start = -10.0;
    rho_stop = 10.0;
    h = (rho_stop - rho_start)/(n+1.0);
    HO_potential = new double[n];
    rho = new double[n];

    for (int i=0; i<n ;i++){
        rho[i] = rho_start + i*h;
        HO_potential[i] = pow(rho[i],2.0);
    }

    mat A = Matrix_creator(HO_potential, n, h);

    mat R(n,n);

    jacobis_method(A, R, n);

    return 0;
}


/*
Function that creates a matrix A for the discretized dimensionless Schrodinger equation.
input:
potential: a vector of the potential at the discretized positions.
n: number of steps in our discretized system excluding the first and last values which are known from boundary conditions.
*/

mat Matix_creator(double *potential, int n, double h)
{
    mat A(n,n);
    for(int i = 0; i<n-1; i++){
        A(i,i) = 2.0/(h*h) + potential[i];
        A(i,i+1) = -1.0/(h*h);
        A(i+1,i) = -1.0/(h*h);
    }
    A(n-1,n-1) = 2.0/(h*h) + potential[n-1];
return A;
}



/*
 Jacobis method for determining the eigenvalues and eigenvectors of a symmetric matrix.
 Take input:
 A: The matrix that you wish to find the eigenvalues and eigenvectors of.
 R: An empty matrix that will store the eigenvectors.
 n: The dimension of the the matricies that are input.
 tolerance: The largest off diagonal element allowed in the finished diagonal matrix. Passivly set to 10^{-8}.

 output:
 A: A is diagonalzed until the eigenvalues are the diagonal elements of A, i.e. A[i][i].
 R: R stores the eigenvectors where the eigenvector corresponding to eigenvalue A[i][i] is R[i][:].

 Code also includes a max number of iterations n^3, such that the program will end even if the matrix input is not diagonalizable

 */

void jacobis_method(mat A, mat R, int n, double tolerance = pow(10,-8))
{
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            if (i==j){
                R(i)(j) = 1.0;
            } else {
                R(i)(j) = 0.0;
            }
        }
    }

    int k, l;
    double max_number_iterations = (double) n * (double) n * (double) n;
    int iterations = 0;
    double max_offdiag = maxoffdiag( A, &k, &l, n);

    while (fabs(max_offdiag) > tolerance && (double) iterations < max_number_iterations){
        max_offdiag = maxoffdiag(A, &k,&l,n);
        rotate (A, R,k,l,n);
        iterations ++;
    }
return;
}


/*
 Function that finds the max off diagonal elements of a matrix.
 input:
 A: matrix we wish to find the max off diagonal element off.
 k: integer that will store the coloum number of the max element
 l: integer that will store the row number of the max element
 n: dimension of the input matrix A

 output:
 Does not change A or n. Gives k and l the position of the max element.

*/

double maxoffdiag(mat A, int *k, int *l, int n)
{
    double max = 0.0;

    for(int i = 0; i < n; i++){
        for(int j = i+1; j <n; j++){
            if(fabs(A(i)(j) > max)){
                max = fabs(A(i)(j));
                *l = i;
                *k = j;

            }
        }
    }
    return max;
}



/*
Function that rotates a matrix A with a similarity transformation, rotation in n-dim space around axis of element A[l][k].

input:
A: Matrix that we wish to rotate
R: Matrix that we wish to store corresponding eigenvectors
k: coloum number of element we wish to rotate around
l: row number of element we wish to rotate around
n: dimension of input matrices

*/

void rotate(mat A, mat R, int k, int l, int n)
{
    double s,c;
    if (A(k)(l) != 0.00){
        double t, tau;
        tau = (A(l)(l) - A(k)(k))/(2*A(k)(l));
        if(tau > 0){
            t = 1.0/(tau + sqrt(1.0 + tau*tau));
        } else {
            t = -1.0/(-tau + sqrt(1.0 + tau*tau));
        }

        c = 1/sqrt(1 + t*t);
        s = c*t;
    } else {
        c = 1.0;
        s = 0.0;
    }

    double a_kk, a_ll, a_ik, a_il, r_ik, r_il;
    a_kk = A(k)(k);
    a_ll = A(l)(l);
    // Changing the matric elements with indices k and l
    A(k)(k) = c*c*a_kk - 2.0*c*s*A(k)(l) + s*s*a_ll;
    A(l)(l) = s*s*a_kk + 2.0*c*s*A(k)(l) + c*c*a_ll;
    A(k)(l) = 0.0; //Hard-coding of the zeros
    A(l)(k) = 0.0;
    //Then we change the remaining elements
    for(int i = 0; i<n;i++){
        if (i != k && i != l) {
            a_ik = A(i)(k);
            a_il = A(i)(l);
            A(i)(k) = c*a_ik - s*a_il;
            A(k)(i) = A(i)(k);
            A(i)(l) = c*a_il + s*a_ik;
            A(l)(i) = A(i)(l);
        }
        // Computing the new eigenvectors
        r_ik = R(i)(k);
        r_il = R(i)(l);
        R(i)(k) = c*r_ik - s*r_il;
        R(i)(l) = c*r_il + s*r_ik;
    }
return;
}






