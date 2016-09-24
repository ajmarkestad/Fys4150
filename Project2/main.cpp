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

int unittest_largest_off_diagonal();
int unittest_orthogonality();
int unittest_correct_eigenvalues();
void jacobis_method(mat &A, mat &R, int, double);
double maxoffdiag(mat &A, int *, int *, int );
void rotate(mat &A, mat &R, int , int , int );
int test_orthogonality(mat &A, int );
void sorting(mat , mat , vec &V, mat &R);
void potential_generator(double *, double *, double , double , int );
void matrix_creator(mat &A, double *, int, double);
void output(mat &R, vec &V, int , double);


ofstream ofile;
int main(int argc, char *argv[])
{

    //INITIALIZATION TESTS
    try {
        unittest_largest_off_diagonal();
    }catch (const char* msg) {
        cerr << "Noe feil i test av larges off diagonal!" << endl;
    }

    if (unittest_correct_eigenvalues()!=0){
        cerr << "Noe feil i test av egenverdier!" << endl;
    }

    if (unittest_orthogonality()!=0){
        cerr << "Noe feil i test av ortogonalitet!" << endl;
    }



    //ALLOCATION
    int n;
    double h, rho_start, rho_stop, Harmonic_oscillator_frequency, columbfactor;
    double *potential, *rho;

    // Read in output file, abort if there are too few command-line arguments
    if( argc <= 3){
      cout << "Bad Usage: " << argv[0] << " read three values: number of grid points, unitless harmonic oscillator frequency, and unitless columb factor om same line" << endl;
      exit(1);
    }
    else{
       n = atof(argv[1]);
       Harmonic_oscillator_frequency = atof(argv[2]);
       columbfactor = atof(argv[3]);
       rho_stop = atof(argv[4]);
    }

    //FILLING VALUES
    rho_start = 0.0000001;
    h = (rho_stop - rho_start)/(n+1.0);
    rho = new double[n];
    for (int i=0; i<n ;i++){
        rho[i] = rho_start + i*h;
    }
    potential = new double[n];
    potential_generator(rho, potential, Harmonic_oscillator_frequency, columbfactor, n);
    mat A(n,n);
    matrix_creator(A, potential, n, h);
    mat R(n,n);
    double epsilon;
    epsilon = pow(10.0,-8.0);


    //FINDING EIGENVALUES AND EIGENVECTORS
    double time;
    clock_t start, finish;
    start = clock();
    jacobis_method(A,R,n,epsilon);
    finish = clock();
    time = (finish-start)/((double) CLOCKS_PER_SEC);
    cout << "CPU time of jacobi's method: " << time << endl;


    //TESTING ORTHOGONALITY
    if(test_orthogonality(R,n)!=0){
        cout << "Orthogonality test: failed!" << endl;
    }else{
        cout << "Orthogonality test: passed!" << endl;
    }


    //SORTING
    vec eigenvalues_sorted(n);
    mat eigenvectors_sorted(n,n);
    sorting(A, R, eigenvalues_sorted, eigenvectors_sorted);



    cout << "First eigenvalue: " << eigenvalues_sorted(0) << endl;
    cout << "Sencond eigenvalue: " << eigenvalues_sorted(1) << endl;
    cout << "Third eigenvalue: " << eigenvalues_sorted(2) << endl;

    string str1 = "Project_2_Wr=";
    string outfilename;
    outfilename.append(str1);
    int number1 = Harmonic_oscillator_frequency;
    stringstream ss1;
    ss1 << number1;
    outfilename.append(ss1.str());
    string str2 = "_Columb_factor=";
    outfilename.append(str2);
    int number2 = columbfactor;
    stringstream ss2;
    ss2 << number2;
    outfilename.append(ss2.str());
    string str3 = "_n=";
    outfilename.append(str3);
    int number3 = n;
    stringstream ss3;
    ss3 << number3;
    outfilename.append(ss3.str());
    string str4 = "_rho_stop=";
    outfilename.append(str4);
    stringstream ss4;
    ss4 << rho_stop;
    outfilename.append(ss4.str());
    ofile.open(outfilename);
    output(eigenvectors_sorted, eigenvalues_sorted, n, time);

    // close output file
    ofile.close();


    return 0;
}



void potential_generator(double *rho, double *potential, double factor1, double factor2, int n)
{
    /* Creates a potensial with a input */
    for (int i=0; i<n ;i++){
        potential[i] = factor1 * pow(rho[i],2.0) + factor2 * 1.0/rho[i];
    }
    return;
}

void matrix_creator(mat &A, double *potential, int n, double h){
/*

Function that creates a matrix A for the discretized dimensionless Schrodinger equation.
input:
potential: a vector of the potential at the discretized positions.
n: number of steps in our discretized system excluding the first and last values which are known from boundary conditions.
*/
    for(int i = 0; i<n-1; i++){
        A(i,i) = 2.0/(h*h) + potential[i];
        A(i,i+1) = -1.0/(h*h);
        A(i+1,i) = -1.0/(h*h);
    }
    A(n-1,n-1) = 2.0/(h*h) + potential[n-1];
return;
}

void jacobis_method(mat &A, mat &R, int n, double tolerance){
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
    int iterations = 0, iter = 0;
    double max_offdiag = maxoffdiag(A,&k,&l,n);

    while (fabs(max_offdiag) > tolerance && (double) iterations < max_number_iterations){
        max_offdiag = maxoffdiag(A, &k,&l,n);
        rotate (A,R,k,l,n);
        iterations ++;
        iter ++;
        if (iter == 1000){
            cout << iterations << "Iterations. Max offdiagonal element" << max_offdiag<< endl;
            iter = 0;
        }

    }
return;
}

double maxoffdiag(mat &A, int *k, int *l, int n)
{
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

void rotate(mat &A, mat &R, int k, int l, int n)
{
    /*
    Function that rotates a matrix A with a similarity transformation, rotation in n-dim space around axis of element A[l][k].

    input:
    A: Matrix that we wish to rotate
    R: Matrix that we wish to store corresponding eigenvectors
    k: coloum number of element we wish to rotate around
    l: row number of element we wish to rotate around
    n: dimension of input matrices

    */
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

void sorting(mat A,mat R, vec &V_sorted, mat &R_sorted)
{
    vec V = A.diag();
    V_sorted = sort(V);
    uvec indices = sort_index(V);
    uvec cols = linspace<uvec>(0,R.n_cols -1, R.n_cols);
    R_sorted = R.submat(cols, indices);
    return;
}

int unittest_largest_off_diagonal(){
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

int unittest_correct_eigenvalues(){
    /* test if the jacobis method finds the analytical eigenvalues of -1 and 3
     */
    int n = 2;
    mat testmatrix = zeros(n,n);
    testmatrix(0,0)= 3;
    testmatrix(0,1) = sqrt(2);
    testmatrix(1,1)=-1;
    mat eigvectors = zeros(n,n);
    jacobis_method(testmatrix,eigvectors,n,pow(10,-6));
    vec eigenvalues_sorted(n);
    mat eigenvectors_sorted(n,n);
    sorting(testmatrix, eigvectors, eigenvalues_sorted, eigenvectors_sorted);
    int results = 0;
    if ((eigenvalues_sorted(0)!=-1) || (eigenvalues_sorted(1) != 3)) results = 1;
    return results;
}

int unittest_orthogonality(){
    int n = 10, result = 0;
    // creates a symmetric matrix
    mat A = randu<mat>(n,n);
    mat L, U, P;
    lu(L, U, P, A);
    A = L + L.t();
    mat eigvectors = zeros(n,n);
    jacobis_method(A,eigvectors,n,pow(10,-6));
    result = test_orthogonality(eigvectors,n);
    return result;
}

void output(mat &R, vec &V, int n , double time)
{
    ofile << "Three first eigenvalues and CPU time:" << endl;
    ofile << setiosflags(ios::uppercase | ios::uppercase | ios::uppercase | ios::uppercase) ;
    ofile << setw(15) << setprecision(8) << V(0);
    ofile << setw(15) << setprecision(8) << V(1);
    ofile << setw(15) << setprecision(8) << V(2);
    ofile << setw(15) << setprecision(8) << time << endl;
    ofile << "Corresponding Eigenvectors:" << endl;
    ofile << setiosflags(ios::uppercase | ios::uppercase | ios::uppercase);
    for(int i=0; i < n; i++)
    {
        ofile << setw(15) << setprecision(8) << R(i,0);
        ofile << setw(15) << setprecision(8) << R(i,1);
        ofile << setw(15) << setprecision(8) << R(i,2) << endl;
    }
}

int test_orthogonality(mat &R, int n){
    int result = 0;
    double innerproduct = 0;
    for (int i = 0; i<n; i++){
        for (int j= 0; j<n; j++){
            innerproduct = dot(R.col(j),R.col(i));
            if ((i==j) && (abs(abs(innerproduct)-1) > pow(10,-12))) result = 1;
            if ((i!=j) && (abs(innerproduct)>pow(10,-12))) result = 1;
        }
    }
    return result;
}

