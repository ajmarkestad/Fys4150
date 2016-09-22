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
void jacobis_method(mat &A, mat &R, int, double);
double maxoffdiag(mat &A, int *, int *, int );
void rotate(mat &A, mat &R, int , int , int );
void test(mat &A, int );
void sorting(mat , mat , vec &V, mat &R,  int );
//mat matrix_creator(double *, int, double);

int main(int argc, char *argv[])
{

    //UNIT TESTS
    try {
        unittest_largest_off_diagonal();
    }catch (const char* msg) {
        cerr << "Noe feil i test av larges off diagonal!" << endl;
    }
    try {
        unittest_correct_eigenvalues();
    }catch (const char* msg) {
        cerr << "Noe feil i test av egenverdier!" << endl;
    }

//    try { unittest_orthogonality() }
    int n;
    double h, rho_start, rho_stop, edge;
    double *HO_potential, *rho;

    n = 100;
    edge = 4;
    rho_start = -edge;
    rho_stop = edge;
    h = (rho_stop - rho_start)/(n+1.0);
    HO_potential = new double[n];
    rho = new double[n];
    for (int i=0; i<n ;i++){
        rho[i] = rho_start + i*h;
        HO_potential[i] = pow(rho[i],2.0);
    }

//    mat A = matrix_creator(HO_potential, n, h);

    mat A(n,n);
    for(int i = 0; i<n-1; i++){
        A(i,i) = 2.0/(h*h) + HO_potential[i];
        A(i,i+1) = -1.0/(h*h);
        A(i+1,i) = -1.0/(h*h);
    }
    A(n-1,n-1) = 2.0/(h*h) + HO_potential[n-1];

    mat R(n,n);
    double epsilon;
    epsilon = pow(10.0,-8.0);

    jacobis_method(A,R,n,epsilon);
    //test(R,n);

    vec eigenvalues_sorted(n);
    mat eigenvectors_sorted(n,n);
    sorting(A, R, eigenvalues_sorted, eigenvectors_sorted, n);




    return 0;
}

/*
Function that creates a matrix A for the discretized dimensionless Schrodinger equation.
input:
potential: a vector of the potential at the discretized positions.
n: number of steps in our discretized system excluding the first and last values which are known from boundary conditions.

DOES NOT WORK
*/

//mat matix_creator(double *potential, int n, double h)
//{
//    mat A(n,n);
//    for(int i = 0; i<n-1; i++){
//        A(i,i) = 2.0/(h*h) + potential[i];
//        A(i,i+1) = -1.0/(h*h);
//        A(i+1,i) = -1.0/(h*h);
//    }
//    A(n-1,n-1) = 2.0/(h*h) + potential[n-1];
//return A;
//}



/*
 Jacobis method for determining the eigenvalues and eigenvectors of a symmetric matrix.
 Take input:
 A: The matrix that you wish to find the eigenvalues and eigenvectors of.
 R: An empty matrix that will store the eigenvectors.
 n: The dimension of the the matricies that are input.
 tolerance: The largest off diagonal element allowed in the finished diagonal matrix.

 output:
 A: A is diagonalzed until the eigenvalues are the diagonal elements of A, i.e. A[i][i].
 R: R stores the eigenvectors where the eigenvector corresponding to eigenvalue A[i][i] is R[i][:].

 Code also includes a max number of iterations n^3, such that the program will end even if the matrix input is not diagonalizable

 */

void jacobis_method(mat &A, mat &R, int n, double tolerance)
{
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            if (i==j){
                R(i,j) = 1.0;
            } else {
                R(i,j) = 0.0;
            }
        }
    }

    int k=0, l=0;
    double max_number_iterations = (double) n * (double) n * (double) n;
    int iterations = 0;
    double max_offdiag = maxoffdiag(A,&k,&l,n);

    while (fabs(max_offdiag) > tolerance && (double) iterations < max_number_iterations){
        max_offdiag = maxoffdiag(A, &k,&l,n);
        rotate (A,R,k,l,n);
        iterations ++;
    }
return;
}


/*
 Function that finds the max off diagonal elements of a square matrix.
 input:
 A: matrix we wish to find the max off diagonal element off.
 k: integer that will store the coloum number of the max element
 l: integer that will store the row number of the max element
 n: dimension of the input matrix A

 output:
 Does not change A or n. Gives k and l the position of the max element.

*/

double maxoffdiag(mat &A, int *k, int *l, int n)
{
    double max = 0.0;

    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(fabs(A(i,j)) > max){
                max = fabs(A(i,j));
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

void rotate(mat &A, mat &R, int k, int l, int n)
{
    double s,c;
    if (A(k,l) != 0.00){
        double t, tau;
        tau = (A(l,l) - A(k,k))/(2*A(k,l));
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
    a_kk = A(k,k);
    a_ll = A(l,l);
    // Changing the matric elements with indices k and l
    A(k,k) = c*c*a_kk - 2.0*c*s*A(k,l) + s*s*a_ll;
    A(l,l) = s*s*a_kk + 2.0*c*s*A(k,l) + c*c*a_ll;
    A(k,l) = 0.0; //Hard-coding of the zeros
    A(l,k) = 0.0;
    //Then we change the remaining elements
    for(int i = 0; i<n;i++){
        if (i != k && i != l) {
            a_ik = A(i,k);
            a_il = A(i,l);
            A(i,k) = c*a_ik - s*a_il;
            A(k,i) = A(i,k);
            A(i,l) = c*a_il + s*a_ik;
            A(l,i) = A(i,l);
        }
        // Computing the new eigenvectors
        r_ik = R(i,k);
        r_il = R(i,l);
        R(i,k) = c*r_ik - s*r_il;
        R(i,l) = c*r_il + s*r_ik;
    }
return;
}



void sorting(mat A,mat R, vec &V_sorted, mat &R_sorted, int n)
{
    vec V = A.diag();
    V_sorted = sort(V);
    uvec indices = sort_index(V);
    uvec cols = linspace<uvec>(0,R.n_cols -1, R.n_cols);
    R_sorted = R.submat(cols, indices);
    return;
}


bool unittest_largest_off_diagonal(){
    bool results = 0;
    int n=3, column=0, row=0;
    mat testmatrix = zeros(n,n);
    testmatrix(1,2)=1.0;
    if ( fabs(maxoffdiag(testmatrix, &column, &row, n))!=fabs(testmatrix(1,2))){
        results = 1;
        throw "Test av maks offdiagonal element ble feil!";
    }
    if (column!=2){
        throw "Feil kolonne!";
        results = 1;
    }
    if (row!=1){
        throw "Feil rad!";
        results = 1;
    }
    testmatrix(2,1)=-20;
    if (maxoffdiag(testmatrix, &column, &row, n)==-20){
        throw "Den plukket opp negative verdier istedenfor positive i maks-offdiagonal!";
        results = 1;
    }
    return results;
}

bool unittest_correct_eigenvalues(){
    mat testmatrix = zeros(2,2);
    testmatrix(0,0)= 3;
    testmatrix(0,1) = sqrt(2);
    testmatrix(1,1)=-1;
    mat eigvectors = zeros(2,2);
    double n = 2;
    double tolerance = pow(10,-8);
}
    /*the matrix testmatrix has analytical eigenvalues 1 and 3
    and eigenvectors
    */




